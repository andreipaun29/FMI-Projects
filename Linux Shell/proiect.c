#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <utime.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/statvfs.h>
#include <sys/statfs.h>
#include <sys/mount.h>
#include <sys/utsname.h>
#include <sys/sysmacros.h>

#define MAX_N 1024

char *history; //history -> max 100 lines
char *result; //output of commands
int should_run = 1; //flag to indicate if the program should keep running
int error_code; //error code to treat possible errors

void show_error(int code)
{
    //Error message for every possible type of error
    if(error_code == 1) 
        printf("Wrong number of arguments\n");
    if(error_code == 2) 
        printf("This directory doesn't exist\n");
    if(error_code == 3) 
        printf("Cannot get current directory\n");
    if(error_code == 4) 
        printf("Unable to open source file\n");
    if(error_code == 5) 
        printf("Unable to move file contents\n");
    if(error_code == 6) 
        printf("Unable to open source file\n");
    if(error_code == 7) 
        printf("Unable to create directory\n");
    if(error_code == 8) 
        printf("Unable to delete file\n");
    if(error_code == 9) 
        printf("Unable to delete directory\n");
}

void help()
{
    printf("cd <directory> - change current directory to <directory> \n");
    printf("pwd - print the current working directory \n");
    printf("ls - list the contents of the current directory \n");
    printf("cp <source> <destination> - copy <source> to <destination> \n");
    printf("mv <source> <destination> - move <source> to <destination> \n");
    printf("search <file> - search for <file> in the current directory \n");
    printf("makedir <directory> - create a new directory <directory> \n");
    printf("removedir <directory> - remove <directory> \n");
    printf("rm <file> - remove <file> \n");
    printf("quit - exit the shell \n");
}

void print_history()
{
    printf("%s", history);
}

void cd(char *path)
{
    if (chdir(path) == -1)
    {
        error_code = 2;
    }
}

void pwd()
{
    char current_path[MAX_N];

    if (getcwd(current_path, sizeof(current_path))) 
    {
        strcat(result, current_path);
        printf("%s\n", result);
    } 
    else 
    {
        error_code = 3;
        return;
    }
}

void ls()
{   
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
                printf("%s ", ent->d_name);
        }
        printf("\n");


        closedir(dir);
    }
    else
    {
        error_code = 3;
        return;
    }
}

void cp(char* arg1, char* arg2)
{
        int fd1, fd2;
        char buf[1024];
        int n;
        if ((fd1 = open(arg1, O_RDONLY)) == -1)
        {
            error_code = 4;
            return;
        }
        if ((fd2 = open(arg2, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
        {
            error_code = 5;
            return;
        }
        while ((n = read(fd1, buf, 1024)) > 0)
        {
            if (write(fd2, buf, n) != n)
            {
                perror("");
                return;
            }
        }
        if (n == -1)
        {
            perror("");
            return;
        }
        if (close(fd1) == -1)
        {
            perror("");
            return;
        }
        if (close(fd2) == -1)
        {
            perror("");
            return;
        }
}

void mv(char* arg1, char* arg2)
{
    if (rename(arg1, arg2) == -1)
    {
        error_code = 6;
        return;
    }
}

void makedir(char* arg)
{

    if (mkdir(arg, 0755) == -1)
        {
            error_code = 7;
            return;
        }
    else
    {
        strcat(result, "Directory created");
        printf("%s\n", result);
    }
}

void rm(char* arg)
{
    if (unlink(arg) == -1)
    {
        error_code = 8;
        return;
    }

    else
    {
        strcat(result, "File removed");
        printf("%s\n", result);
    }
}

void removedir(char* arg)
{
    if (rmdir(arg) == -1)
    {
        error_code = 9;
        return;
    }

    else
    {
        strcat(result, "Directory removed");
        printf("%s\n", result);
    }
}

void search(char* arg)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
                if (strcmp(ent->d_name, arg) == 0)
                {
                    strcat(result, ent->d_name);
                }
        }
        printf("%s\n", result);
        closedir(dir);
    }
    else
    {
        error_code = 3;
    }
}


void execute(char **args, int nr_args)
{

    if (strcmp(args[0], "help") == 0)
    {
        if (nr_args != 1)
        {
            error_code = 1;
            return;
        }
        help();
    }

    else if (strcmp(args[0], "quit") == 0)
    {
        if (nr_args != 1)
        {
            error_code = 1;
            return;
        }
        exit(0);
    }

    else if (strcmp(args[0], "history") == 0)
    {
        if (nr_args != 1)
        {
            error_code = 1;
            return;
        }
        print_history();
    }

    else if (strcmp(args[0], "cd") == 0)
    {
        if (nr_args == 2)
        {
            cd(args[1]);
        }
        else if(nr_args == 1)
            cd("..");
        else
            {
            error_code = 1;
            return;
            }
    }

    else if (strcmp(args[0], "pwd") == 0)
    {
        if (nr_args != 1)
        {
            error_code = 1;
            return;
        }

        pwd();
    }

    else if (strcmp(args[0], "ls") == 0)
    {
        if (nr_args != 1)
        {
            error_code = 1;
            return;
        }

        ls();
    }

    else if (strcmp(args[0], "cp") == 0)
    {
        if (nr_args != 3)
        {
            error_code = 1;
            return;
        }

        cp(args[1], args[2]);
    }

    else if (strcmp(args[0], "mv") == 0)
    {
        if (nr_args != 3)
        {
            error_code = 1;
            return;
        }

        mv(args[1], args[2]);
    }

    else if (strcmp(args[0], "makedir") == 0)
    {
        if (nr_args != 2)
        {
            error_code = 1;
            return;
        }

        makedir(args[1]);
    }

    else if (strcmp(args[0], "rm") == 0)
    {
        if (nr_args != 2)
        {
            error_code = 1;
            return;
        }

        rm(args[1]);
    }

    else if (strcmp(args[0], "removedir") == 0)
    {
        if (nr_args != 2)
        {
            error_code = 1;
            return;
        }

        rmdir(args[1]);
    }

    else if (strcmp(args[0], "search") == 0)
    {
        if (nr_args != 2)
        {
            error_code = 1;
            return;
        }

        search(args[1]);
    }

}


int main()
{
    history = malloc(100* MAX_N * sizeof(char)); //history -> max 100 lines
    result = malloc(MAX_N * sizeof(char)); 
    char ** arguments; // arguments to be passed to the commands
    int nr_arguments = 0;
    char line[MAX_N]; //every line that we will read 
    int nr_comenzi = 0;
    char comanda[MAX_N];
    char *word;
    error_code = 0;
    while(should_run)
    {
        fflush(stdout);
        printf("dbx> ");
        
        fgets(line, MAX_N, stdin);
        line[strlen(line) - 1] = '\0';

        if(!strcmp(line, "")) //in case of empty line
        {
            printf("\n");
            continue;
        }
    
        //add to history
        nr_comenzi ++;
        sprintf(comanda, "%d", nr_comenzi);
        //command index
        strcat(history, comanda);
        strcat(history, ": ");
        //and the command itself
        strcat(history, line); 
        strcat(history, "\n");

        //now we will break apart our command into words
        arguments = malloc(MAX_N * sizeof(char*));
        nr_arguments = 0;

        //first word of our command
        word = strtok(line, " ");
        

        //keep reading words
        while(word != NULL)
        {
            char* c = malloc(MAX_N * sizeof(char));
            strcpy(c, word);
            //if we want to execute multiple commands and we reach the && symbol
            if(!strcmp(c, "&&"))
            {   
                //we clear the output and execute the command before the &&
                strcpy(result, "");
                execute(arguments, nr_arguments);

                //if we get an error from that command, it means we have no reason to execute the next
                if(error_code != 0 )
                {
                    break;
                }
                nr_arguments = 0;
            }
            else
            {   
                //if it's not the && symbol, we have another argument to add to our list
                arguments[nr_arguments] = c;
                nr_arguments ++;
                
                
            }
            word = strtok(NULL, " ");
            

        }
        if(error_code == 0)
        {   
            //if we haven't gotten an error, execute the command 
            strcpy(result, "");
            execute(arguments, nr_arguments);
            
        }

        if(error_code != 0)
        {
            //if we get an error
            show_error(error_code);
            error_code = 0;
        }


    }
    free(result);
    free(history);
    free(arguments);
    return 0;
}





