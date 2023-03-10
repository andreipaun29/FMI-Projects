#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

class Angajat         
{
private:
    int zileDeLaAngajare;
    char hireDate[25];
    char functieDepartament[25];
    char* nume;
    string prenume;
    bool manager;
 
    int* proiecteRealizateDeLaAngajarePeLuna;
    int nrTotalProiecte;
 
    const int idAngajat;
    static int contorId;

public:


    Angajat();  

    Angajat(int nrTotalProiecte, int* proiecteRealizateDeLaAngajarePeLuna);

    Angajat(char* nume, string prenume,char functieDepartament[]);

    Angajat(int zileDeLaAngajare, char hireDate[], char functieDepartament[], char* nume, string prenume, bool manager, int* proiecteRealizateDeLaAngajarePeLuna, int nrTotalProiecte);

    Angajat(const Angajat& altAngajat);

    Angajat& operator=(const Angajat& altAngajat);

    friend istream& operator >> (istream& in, Angajat& s);
    friend ostream& operator << (ostream& out, const Angajat& s);    

    int operator[](int index); //proiecte realizate in urma cu index luni

    Angajat& operator++();//angajatul a mai facut un proiect
    Angajat operator++(int);

    bool operator==(const Angajat& altAngajat);//se compara nr de proiecte totale
    bool operator>(const Angajat& altAngajat);

    Angajat operator+(int x);//creste nr de proiecte cu x
    friend Angajat operator+(int x, Angajat ang);
    Angajat operator+(Angajat ang);//se aduna nr de proiecte dintre 2 angajati

    Angajat operator-(int x);//scade nr de proiecte cu x
    friend Angajat operator-(int x, Angajat ang);
    Angajat operator-(Angajat ang);//se scade nr de proiecte dintre 2 angajati


    explicit operator int();


    ~Angajat();

    void setZileDeLaAngajare(int zile);
    void setFunctieDepartament(char func[25]);
    void setNrTotalProiecte(int pr);

    int getNrTotalProiecte();
    int getZileDeLaAngajare();
    char* getFunctieDepartament();
    bool getManager();
    
    const int getIdAngajat();

};

class Sistem 
{
protected:
    char* numeEchipa;
    int nrMembrii;

    int nrComanda;
    double buget;

    float* preturiComponente;  // (0-gpu, 1-cpu, 2-mobo, 3-ram, 4-hdd/ssd, 5-psu, 6-case)
    int nrComponente;

    string numeClient;
    char dataStart[25];
    char dataFinish[25];

public:

    Sistem();
    Sistem(char dataStart[], char dataFinish[]);
    Sistem(double buget, int nrMembrii, char* numeEchipa);
    Sistem(char* numeEchipa, int nrMembrii, int nrComanda, double buget,float* preturiComponente,int nrComponente, string numeClient, char dataStart[], char dataFinish[]);
    Sistem(const Sistem& altSistem);
    Sistem& operator=(const Sistem& altSistem);

    friend istream& operator >> (istream& in, Sistem& s);
    friend ostream& operator << (ostream& out, const Sistem& s);    

    float operator[](int index); //pretul componentei de pe pozitia index 

    Sistem& operator++(); //pre-incrementare  se adauga un nou membru la echipa
    Sistem operator++(int);// post-incrementare

    bool operator==(const Sistem& altSistem); //acelasi buget
    bool operator>(const Sistem& altSistem); //sistemul a fost terminat dupa alt sistem

    Sistem operator+(int x); //creste bugetul cu x
    friend Sistem operator+(int x, Sistem sis);//creste bugetul cu x
    Sistem operator+(Sistem sis);//creste echipa pentru sistem
    
    Sistem operator-(int x); //scade bugetul cu x
    friend Sistem operator-(int x, Sistem sis);//scade bugetul cu x
    Sistem operator-(Sistem sis);//scade echipa pentru sistem

    explicit operator float(); //transform bugetul in float

    ~Sistem();

    void setDates(char dataS[], char dataF[]);
    void setBuget(int bug);
    void setMembriiEchipa(int memb);

    char* getStartDate();

    char* getFinishDate();

    int getMembriiEchipa();

    string getNumeClient();
    int getNrComanda();
    double getBuget();


};


class SistemRacireAer: public virtual Sistem
{
protected:
    int nrVentilatoare;
    int* ventilatoare;
    float RPM;
public:

    SistemRacireAer();
    SistemRacireAer(char* numeEchipa, int nrMembrii, int nrComanda, double buget, float* preturiComponente, int nrComponente, string numeclient, char dataStart[25], char dataFinish[25],int nrVentilatoare, int* ventilatoare, float RPM);
    SistemRacireAer(const SistemRacireAer& altSistem);
    SistemRacireAer& operator=(const SistemRacireAer& altSistem);
    ~SistemRacireAer();

    friend istream& operator>>(istream& in , SistemRacireAer& s);
    friend ostream& operator<<(ostream& out, const SistemRacireAer& s);


};




class SistemRacireLichid: public virtual Sistem
{
protected:
    float capacitateRezervor;
    bool hardTubing;
    bool softTubing;

public:
    SistemRacireLichid();
    SistemRacireLichid(char* numeEchipa, int nrMembrii, int nrComanda, double buget, float* preturiComponente, int nrComponente, string numeClient, char dataStart[], char dataFinish[], float capacitateRezervor, bool hardTubing, bool softTubing);
    SistemRacireLichid(const SistemRacireLichid& altSistem);
    ~SistemRacireLichid();
    SistemRacireLichid& operator=(const SistemRacireLichid& altSistem);

    friend istream& operator>>(istream& in , SistemRacireLichid& s);
    friend ostream& operator<<(ostream& out, const SistemRacireLichid& s);

};


class SistemRacireHibrida: public virtual SistemRacireAer, public virtual SistemRacireLichid
{
private:

    int nrRadioatoare;
    float pumpRPM;
public:

    SistemRacireHibrida();
    SistemRacireHibrida(char* numeEchipa, int nrMembrii, int nrComanda, double buget,float* preturiComponente,int nrComponente, string numeClient, char dataStart[], char dataFinish[], int nrVentilatoare, int* ventilatoare , float RPM, float capacitateRezervor, bool hardTubing, bool softTubing, int nrRadiatoare, float pumpRPM);
    SistemRacireHibrida(const SistemRacireHibrida& altSistem);
    SistemRacireHibrida& operator=(const SistemRacireHibrida& altSistem);
    ~SistemRacireHibrida();

    friend istream& operator>>(istream& in, SistemRacireHibrida& s);
    friend ostream& operator<<(ostream& out, const SistemRacireHibrida& s);

    SistemRacireHibrida operator++(int) //creste capacitatea rezervorului cu un litru
    {
        SistemRacireHibrida sis(*this);
        this->capacitateRezervor++;
        return sis;
    }

    SistemRacireHibrida& operator++()//creste capacitatea rezervorului cu un litru
    {
        this->capacitateRezervor++;
        return *this;
    }

    SistemRacireHibrida operator+(int x)//viteza pompei radiatorului e imbunatatita
    {
        SistemRacireHibrida sis(*this);
        sis.pumpRPM=sis.pumpRPM+x;
        return sis;
    }

    friend SistemRacireHibrida operator+(int x, SistemRacireHibrida sis)//viteza pompei radiatorului e imbunatatita
    {
        sis.pumpRPM = sis.pumpRPM+x;
        return sis;
    }

    bool operator>(const SistemRacireHibrida& s)//un sistem are mai multe ventilatoare decat altul
    {
        if(this->nrVentilatoare > s.nrVentilatoare)
            return true;
        return false;
    }

    float getCapacitateRezervor(){
        return this->capacitateRezervor;
    }

    float getVitezaPompa(){
        return this->pumpRPM;
    }

};

class Departament
{
protected:
    int nrAngajati;
    char* numeDepartament;
    char* locatieDepartament;
    char* numeManager;

    Angajat* listaAngajati;
    int angajatiInregistrati;

public:

    Departament();
    Departament(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager, Angajat* listaAngajati, int angajatiInregistrati);
    Departament(const Departament& altDep);
    Departament& operator=(const Departament& altDep);

    friend istream& operator >>(istream& in, Departament& altDep);
    friend ostream& operator <<(ostream& out, const Departament& altDep);

    Angajat operator[](int index); //angajatul inregistrat de pe poz index

    Departament& operator++(); //pre-incrementare  se adauga un nou angajat
    Departament operator++(int);// post-incrementare

    bool operator==(const Departament& altDepartament); //acelasi nr de angajati

    bool operator>(const Departament& altDepartament); //departamentul are mai multi angajati decat alt departament

    Departament operator+(int x); //creste nr de angajati cu x

    friend Departament operator+(int x, Departament dep);//creste nr de angajati cu x

    Departament operator+(Departament dep);//se imbina echipajele din 2 departamente
    

    Departament operator-(int x); //scade nr de angajati cu x

    friend Departament operator-(int x, Departament dep);//scade nr de angajati cu x

    Departament operator-(Departament dep);//se afla diferenta in nr de angajati dintre 2 departamente


    friend Departament operator+(Departament d, const Angajat& a);
    friend Departament operator+(const Angajat& a, Departament d);


    explicit operator int(); //transform media de comenzi primite lunar in int


    ~Departament();

    void setNrAngajati(int numar);
    void setnNumeDepartament(char* numeDep);

    int getNrAngajati();
    char* getNumeDepartament();

};

class DepartamentAsamblare: public Departament
{
protected:
    float comenziPrimiteLunar;

public:

    DepartamentAsamblare();
    DepartamentAsamblare(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager,Angajat* listaAngajati,int angajatiInregistrati,float comenziPrimiteLunar);
    DepartamentAsamblare(const DepartamentAsamblare& altDepartament);
    DepartamentAsamblare& operator=(const DepartamentAsamblare& altDepartament);
    ~DepartamentAsamblare();

    friend istream& operator>>(istream& in, DepartamentAsamblare& d);
    friend ostream& operator<<(ostream& out, const DepartamentAsamblare& d);



};

class DepartamentAsamblarePremium: public DepartamentAsamblare
{
private:
    int comenziPentruStudiouri;
    int comenziSistemeServer;
    int licenseKeys;
    int BIOSFlashes;

public:
    DepartamentAsamblarePremium();
    DepartamentAsamblarePremium(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager,Angajat* listaAngajati,int angajatiInregistrati, float comenziPrimiteLunar, int comenziPentruStudiouri, int comenziSistemeServer, int licenseKeys, int BIOSFlashes);
    DepartamentAsamblarePremium(const DepartamentAsamblarePremium& altDepartament);
    DepartamentAsamblarePremium& operator=(const DepartamentAsamblarePremium& altDepartament);
    ~DepartamentAsamblarePremium();

    friend istream& operator>>(istream& in, DepartamentAsamblarePremium& d);
    friend ostream& operator<<(ostream& out, const DepartamentAsamblarePremium& d);

    DepartamentAsamblarePremium operator++(int) //se adauga o noua comanda pentru studiouri
    {
        DepartamentAsamblarePremium dep(*this);
        this->comenziPentruStudiouri++;
        return *this;
    }

    DepartamentAsamblarePremium& operator++()
    {
        this->comenziPentruStudiouri++;
        return *this;
    }

    DepartamentAsamblarePremium operator+(DepartamentAsamblarePremium dep) //se imbina echipajele dintre 2 departamente
    {
        dep.nrAngajati=this->nrAngajati+dep.nrAngajati;
        return dep;
    }


    int getLicente(){
        return this->licenseKeys;
    }

    int getBIOS(){
        return this->BIOSFlashes;
    }

    int getComenziStudio(){
        return this->comenziPentruStudiouri;
    }


};

class Curier
{
private:
    long codCurier;
    char* numeCurier;
    string prenumeCurier;
    int* livrariInUltimeleLuni;
    int nrLuni;

    char dataContract[25];
    char durataContract[25];
    char infoContract[60];

public:

    Curier();
    Curier(long codCurier, char* numeCurier);
    Curier(int* livrariInUltimeleLuni,int nrLuni, char* numeCurier);
    Curier(long codCurier, char* numeCurier, string prenumeCurier, int* livrariInUltimeleLuni, int nrLuni, char dataContract[], char durataContract[], char infoContract[]);
    Curier(const Curier& altCurier);
    Curier& operator=(const Curier& altCurier);

    friend istream& operator >> (istream& in, Curier& c);
    friend ostream& operator << (ostream& out, const Curier& c);

    int operator[](int index); //cate livrari s-au efectuat in urma cu index luni

    Curier& operator++(); //se adauga o luna la contract
    Curier operator++(int);

    Curier& operator--();//se scade o luna din contract
    Curier operator--(int);

    Curier operator+(Curier c);//pentru ultimele luni, se aduna livrarile din fiecare luna
    Curier operator-(Curier c);//pentru ultimele luni, se afla diferenta in numarul lunar de livrari

    bool operator==(const Curier& altCurier);//contractul se finalizeaza in aceeasi data
    bool operator>(const Curier& altCurier);//contractul curierului se termina dupa alt curier

    explicit operator int();//codul curierului se transforma in intreg


    ~Curier();

    void setDateCurier(char dataContr[], char durataContr[]);
    void setCodCurier(long cod);
    void setLivrariInUltimeleLuni(int* livrari, int nLuni);


    char* getDataIncepereContract();
    char* getDataFinalizareContract();
    char* getDateCurier();
    long getCodCurier();
    int getLivrariInUltimeleLuni();

};



class IOInterface
{
public:
    virtual istream& citire(istream& in)=0;
    virtual ostream& afisare(ostream& out) const = 0;
};

class Client: public IOInterface
{
protected:
    string nume;
    string prenume;
    char* nrTelefon;
    char* adresaLivrare;
    int varsta;
    float buget;
public:

    Client();
    Client(string nume, string prenume, char* nrTelefon, char* adresaLivrare, int varsta,float buget);
    Client(const Client& altClient);
    Client& operator=(const Client& altClient);
    ~Client();

    bool operator==(const Client& altClient);

    int operator++();

    virtual void adaugarePretLaBuget(int x)=0;

    virtual void metodaClient()=0;

    virtual void modificareBugetCuDiscount(int z) = 0;

    istream& citire(istream& in)
    {
        char buffer[20];
        cout<<"Introduceti numele: "<<endl;
        in>>this->nume;

        cout<<"Introduceti prenumele: "<<endl;
        in>>this->prenume;

        cout<<"Introduceti numarul de telefon: "<<endl;
        in>>buffer;

        this->nrTelefon = new char[strlen(buffer)+1];
        strcpy(this->nrTelefon, buffer);

        cout<<"Introduceti adresa de livrare: "<<endl;
        in>>buffer;

        this->adresaLivrare = new char[strlen(buffer)+1];
        strcpy(this->adresaLivrare, buffer);

        cout<<"Introduceti vasrta: "<<endl;
        in>>this->varsta;

        cout<<"Introduceti bugetul: "<<endl;
        in>>this->buget;

        return in;

    }

    ostream& afisare(ostream& out) const
    {
        out<<"Numele clientului: "<<this->nume<<endl;
        out<<"Prenumele clientului: "<<this->prenume<<endl;
        out<<"Numarul de telefon: "<<this->nrTelefon<<endl;
        out<<"Adresa unde se livreaza sistemul: "<<this->adresaLivrare<<endl;
        out<<"Varsta clientului: "<<this->varsta<<endl;
        out<<"Bugetul alocat: "<<this->buget<<endl;

        return out;
    }

    int getVarsta(){
        return this->varsta;
    }


};


class ClientFidelDeUnAn: public Client
{
protected:
    float discountTier1;

public:
    ClientFidelDeUnAn();
    ClientFidelDeUnAn(string nume , string prenume, char* nrTelefon, char* adresaLivrare, int varsta,float buget, float discountTier1);
    ClientFidelDeUnAn(const ClientFidelDeUnAn& altClient);
    ClientFidelDeUnAn& operator=(const ClientFidelDeUnAn& altClient);
    ~ClientFidelDeUnAn();

    bool operator==(const ClientFidelDeUnAn& altClient);
    int operator++();

    void adaugarePretLaBuget(int x)
    {
        this->buget=this->buget+x;
    }
    istream& citire(istream& in)
    {
        Client::citire(in);
        cout<<"Introduceti discountul primit: "<<endl;
        in>>this->discountTier1;

        return in;
    }

    ostream& afisare(ostream& out) const
    {
        Client::afisare(out);
        out<<"Discountul este de: "<<this->discountTier1<<"%"<<endl;

        return out;
    }


    void modificareBugetCuDiscount(int z)
    {
        cout<<"Noul buget dupa aplicarea discountului este: "<<(this->buget*(this->discountTier1/100))+this->buget<<endl;
        this->buget=(this->buget*(this->discountTier1/100))+this->buget;
    }

    virtual void metodaClient()
    {   
        cout<<"Clientul cu numele "<<this->nume<<" a alocat un buget de "<<this->buget<<endl;

    }

    

};


class ClientFidelDe3Ani: public ClientFidelDeUnAn
{
private:
    int cupoanePentruComponente[7];

public:
    ClientFidelDe3Ani();
    ClientFidelDe3Ani(string nume , string prenume, char* nrTelefon, char* adresaLivrare, int varsta,float buget, float discountTier1, int cupoanePentruComponente[7]);
    ClientFidelDe3Ani(const ClientFidelDe3Ani& altClient);
    ClientFidelDe3Ani& operator=(const ClientFidelDe3Ani& altClient);
    ~ClientFidelDe3Ani();

    bool operator==(const ClientFidelDe3Ani& altClient);
    int operator++();

    void adaugarePretLaBuget(int x)
    {
        this->buget=this->buget+x;
    }

    void modificareBugetCuDiscount(int z)
    {
        cout<<"Noul buget dupa aplicarea discountului este: "<<(this->buget*((this->discountTier1+10)/100))+this->buget<<endl;
        this->buget=(this->buget*((this->discountTier1+10)/100))+this->buget;
    }

    

    istream& citire(istream& in)
    {
        ClientFidelDeUnAn::citire(in);
        cout<<"Introduceti cupoanele pentru componente: "<<endl;
        for(int i=0; i<7;i++)
        {
            if(i==0)
                {cout<<"Exista cupon pentru placa video? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==1)
                {cout<<"Exista cupon pentru procesor? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==2)
                {cout<<"Exista cupon pentru placa de baza? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==3)
                {cout<<"Exista cupon pentru RAM? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==4)
                {cout<<"Exista cupon pentru HDD/SSD? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==5)
                {cout<<"Exista cupon pentru sursa? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
            else if(i==6)
                {cout<<"Exista cupon pentru carcasa? (0-nu 1-da)";in>>cupoanePentruComponente[i];}
        }

        return in;
    }

    ostream& afisare(ostream& out) const
    {
        ClientFidelDeUnAn::afisare(out);
        
            if(cupoanePentruComponente[0]==1)
                out<<"Placa video are discount 5%!"<<endl;
             if(cupoanePentruComponente[1]==1)
                out<<"Procesorul are discount 5%!"<<endl;
             if(cupoanePentruComponente[2]==1)
                out<<"Placa de baza are discount 5%!"<<endl; 
             if(cupoanePentruComponente[3]==1)
                out<<"RAM-ul are discount 5%!"<<endl;  
             if(cupoanePentruComponente[4]==1)
                out<<"HDD-ul/SSD-ul are discount 5%!"<<endl; 
             if(cupoanePentruComponente[5]==1)
                out<<"Sursa are discount 5%!"<<endl; 
             if(cupoanePentruComponente[6]==1)
                out<<"Carcasa are discount 5%!"<<endl; 

        return out;
    }

    void metodaClient()
    {
        int sum=0;
        for(int i=0;i<7;i++)
            if(this->cupoanePentruComponente[i]!=0)
                sum++;
        cout<<"Clientul cu numele "<<this->nume<<" are "<<sum<<" cupoane!"<<endl;
    }


};


//CONSTRUCTORI SI METODE PENTRU ANGAJAT


Angajat::Angajat():idAngajat(contorId++)
   {
        this->nume=new char[strlen("Anonim")+1];
        strcpy( this->nume,"Anonim");
        this->zileDeLaAngajare=-1;
        strcpy(this->hireDate,"01-01-1900");
        strcpy(this->functieDepartament,"DepartamentX");
        this->proiecteRealizateDeLaAngajarePeLuna = new int[1];
        this->proiecteRealizateDeLaAngajarePeLuna[0]=-1;
        this->nrTotalProiecte=0;
        this->prenume="Anonim";
        this->manager=false;
    }

Angajat::Angajat(int nrTotalProiecte, int* proiecteRealizateDeLaAngajarePeLuna):idAngajat(contorId++)
    {
        this->nrTotalProiecte=nrTotalProiecte;

        this->proiecteRealizateDeLaAngajarePeLuna=new int[zileDeLaAngajare/30];
        for(int i=0;i<zileDeLaAngajare/30;i++)
            this->proiecteRealizateDeLaAngajarePeLuna[i]=proiecteRealizateDeLaAngajarePeLuna[i];
    }

Angajat::Angajat(char* nume, string prenume,char functieDepartament[]):idAngajat(contorId++)
{
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume,nume);
        this->prenume=prenume;
        strcpy(this->functieDepartament,functieDepartament);
}

Angajat::Angajat(int zileDeLaAngajare, char hireDate[], char functieDepartament[], char* nume, string prenume, bool manager, int* proiecteRealizateDeLaAngajarePeLuna, int nrTotalProiecte):idAngajat(contorId++)
    {
        this->zileDeLaAngajare=zileDeLaAngajare;
        strcpy(this->hireDate,hireDate);
        strcpy(this->functieDepartament,functieDepartament);

        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume,nume);

        this->prenume=prenume;
        this->manager=manager;
        this->proiecteRealizateDeLaAngajarePeLuna=new int[zileDeLaAngajare/30];
        for(int i=0;i<zileDeLaAngajare/30;i++)
            this->proiecteRealizateDeLaAngajarePeLuna[i]=proiecteRealizateDeLaAngajarePeLuna[i];
        this->nrTotalProiecte=nrTotalProiecte;
    }

Angajat::Angajat(const Angajat& altAngajat):idAngajat(altAngajat.idAngajat)
{
    this->zileDeLaAngajare=altAngajat.zileDeLaAngajare;
    strcpy(this->hireDate,altAngajat.hireDate);
    strcpy(this->functieDepartament,altAngajat.functieDepartament);

    this->nume = new char[strlen(altAngajat.nume)+1];
    strcpy(this->nume,altAngajat.nume);

    this->prenume=altAngajat.prenume;
    this->manager=altAngajat.manager;
    this->proiecteRealizateDeLaAngajarePeLuna=new int[altAngajat.zileDeLaAngajare/30];
    for(int i=0;i<altAngajat.zileDeLaAngajare/30;i++)
        this->proiecteRealizateDeLaAngajarePeLuna[i]=altAngajat.proiecteRealizateDeLaAngajarePeLuna[i];
    this->nrTotalProiecte=altAngajat.nrTotalProiecte;
}

Angajat& Angajat::operator=(const Angajat& altAngajat)
{
    if(this!=&altAngajat)
    {
        if(this->nume!=NULL)
            delete[] this->nume;

        if(this->proiecteRealizateDeLaAngajarePeLuna!=NULL)
            delete[] this->proiecteRealizateDeLaAngajarePeLuna;

        this->zileDeLaAngajare=altAngajat.zileDeLaAngajare;
        strcpy(this->hireDate,altAngajat.hireDate);
        strcpy(this->functieDepartament,altAngajat.functieDepartament);

        this->nume = new char[strlen(altAngajat.nume)+1];
        strcpy(this->nume,altAngajat.nume);

        this->prenume=altAngajat.prenume;
        this->manager=altAngajat.manager;
        this->proiecteRealizateDeLaAngajarePeLuna=new int[altAngajat.zileDeLaAngajare/30];
        for(int i=0;i<altAngajat.zileDeLaAngajare/30;i++)
            this->proiecteRealizateDeLaAngajarePeLuna[i]=altAngajat.proiecteRealizateDeLaAngajarePeLuna[i];
        this->nrTotalProiecte=altAngajat.nrTotalProiecte;
        
    }

    return *this;

}

istream& operator >> (istream& in, Angajat& a)
{
    
    cout<<"numele angajatului: ";
    char nume[50];
    in>>nume;

    if(a.nume != NULL)
        delete[] a.nume;

    a.nume = new char[strlen(nume)+1];
    strcpy(a.nume,nume);   

    cout<<"prenumele: ";
    in>>a.prenume;

    cout<<"data angajarii: ";
    in>>a.hireDate;

    cout<<"zile de la angajare: ";
    in>>a.zileDeLaAngajare;

    cout<<"este manager?: (0-nu, 1-da):";
    in>>a.manager;

    cout<<"functie departament: ";
    in>>a.functieDepartament;


    if(strcmp(a.functieDepartament,"Asamblare")==0)
    {

        cout<<"nr total participare la proiecte: ";
        in>>a.nrTotalProiecte;

        int sumaProiecte=0;

        int proiecte[50];
        if(a.proiecteRealizateDeLaAngajarePeLuna != NULL)
            delete[] a.proiecteRealizateDeLaAngajarePeLuna;
        
        a.proiecteRealizateDeLaAngajarePeLuna = new int[a.zileDeLaAngajare/30];
        cout<<"in aceasta luna a participat la ";
        in>>a.proiecteRealizateDeLaAngajarePeLuna[0];
        cout<<" proiecte"<<endl;

        sumaProiecte+=a.proiecteRealizateDeLaAngajarePeLuna[0];
        if(sumaProiecte>a.nrTotalProiecte)
            {
                cout<<"Numar de proiecte depasit!";
                return in;
            }

        cout<<"in urma cu o luna a participat la ";
        in>>a.proiecteRealizateDeLaAngajarePeLuna[1];
        cout<<" proiecte"<<endl;

        sumaProiecte+=a.proiecteRealizateDeLaAngajarePeLuna[1];
        if(sumaProiecte>a.nrTotalProiecte)
            {
                cout<<"Numar de proiecte depasit!";
                return in;
            }

        for(int i=2;i<a.zileDeLaAngajare/30;i++)
            {
                cout<<"in urma cu "<<i<<" luni a participat la ";
                in>>a.proiecteRealizateDeLaAngajarePeLuna[i];
                cout<<" proiecte"<<endl;

                sumaProiecte+=a.proiecteRealizateDeLaAngajarePeLuna[i];
                if(sumaProiecte>a.nrTotalProiecte)
                {
                    cout<<"Numar de proiecte depasit!";
                    return in;
                }
            }

        return in;

    }

    return in;

}


ostream& operator << (ostream& out, const Angajat& a)
{
    out<<"ID-ul angajatului: "<<a.contorId<<endl;
    out<<"numele angajatului: "<<a.nume<<endl;
    out<<"prenumele angajatului: "<<a.prenume<<endl;
    out<<"este manager? "<<a.manager<<endl;
    out<<"data angajarii: "<<a.hireDate<<endl;
    out<<"angajat de "<<a.zileDeLaAngajare<<" zile"<<endl;
    out<<"lucreaza in departamentul: "<<a.functieDepartament<<endl;

    if(strcmp(a.functieDepartament,"Asamblare")==0)
    {
        out<<"a participat in total la "<<a.nrTotalProiecte<<" proiecte"<<endl;
        out<<"in aceasta luna a participat la "<<a.proiecteRealizateDeLaAngajarePeLuna[0]<<" proiecte"<<endl;
        out<<"in urma cu o luna a participat la "<<a.proiecteRealizateDeLaAngajarePeLuna[1]<<" proiecte"<<endl;
        for(int i=2;i<a.zileDeLaAngajare/30;i++)
            out<<"in urma cu "<<i<<" luni a participat la "<<a.proiecteRealizateDeLaAngajarePeLuna[i]<<" proiecte"<<endl;
            

    }


    return out;
} 


int Angajat::operator[](int index)
{
    if(index < 0 || index>this->zileDeLaAngajare/30)
        return -1;

    return this->proiecteRealizateDeLaAngajarePeLuna[index];
}

 Angajat& Angajat::operator++()
{
    this->nrTotalProiecte++;
    return *this;
}

 Angajat Angajat::operator++(int)
{
    Angajat aux=*this;
    this->nrTotalProiecte++;
    return aux;
}

bool Angajat::operator==(const Angajat& altAngajat)
{
    if(this->nrTotalProiecte == altAngajat.nrTotalProiecte)
        return true;
    return false;

}

bool Angajat::operator>(const Angajat& altAngajat)
{
    if(this->nrTotalProiecte > altAngajat.nrTotalProiecte)
        return true;
    return false;
}

Angajat Angajat::operator+(int x)
{
    Angajat ang=*this;
    ang.nrTotalProiecte=ang.nrTotalProiecte+x;
    return ang;
}

Angajat operator+(int x, Angajat ang)
{
    ang.nrTotalProiecte=ang.nrTotalProiecte+x;
    return ang;
}


Angajat Angajat::operator+(Angajat ang)
{
    ang.nrTotalProiecte=this->nrTotalProiecte+ang.nrTotalProiecte;
    return ang;
}

Angajat Angajat::operator-(int x)
{
    Angajat aux=*this;
    aux.nrTotalProiecte=aux.nrTotalProiecte-x;
    return aux;
}

Angajat operator-(int x, Angajat ang)
{
    ang.nrTotalProiecte=ang.nrTotalProiecte-x;
    return ang;
}


Angajat Angajat::operator-(Angajat ang)
{
    ang.nrTotalProiecte=abs(this->nrTotalProiecte-ang.nrTotalProiecte);
    return ang;
}

Angajat::operator int()
{
    return (int)this->manager;
}


Angajat::~Angajat()
{

        if(this->nume!=NULL)
            delete[] this->nume;

        if(this->proiecteRealizateDeLaAngajarePeLuna!=NULL)
            delete[] this->proiecteRealizateDeLaAngajarePeLuna;

}


void Angajat::setZileDeLaAngajare(int zile)
{
    this->zileDeLaAngajare=zile;
}


void Angajat::setFunctieDepartament(char func[25])
{
    strcpy(this->functieDepartament,func);
}

void Angajat::setNrTotalProiecte(int pr)
{
    this->nrTotalProiecte=pr;
}

int Angajat::getZileDeLaAngajare()
{
    return this->zileDeLaAngajare;
}

int Angajat::getNrTotalProiecte()
{
    return this->nrTotalProiecte;
}

char* Angajat::getFunctieDepartament()
{
    return this->functieDepartament;
}

bool Angajat::getManager()
{
    if(this->manager==1)
        return true;
    return false;
}


int Angajat::contorId=99;

const int Angajat::getIdAngajat()
{
    return this->idAngajat;
}


//CONSTRUCTORI SI METODE PENTRU SISTEM


Sistem::Sistem()
{
    this->numeEchipa = new char[strlen("NoTeam")+1];
    strcpy(this->numeEchipa,"NoTeam");
    this->nrMembrii=-1;
    this->nrComanda=-1;
    this->buget=0;

    this->nrComponente=0;
    this->preturiComponente=new float[1];
    this->preturiComponente[0]=-1;    

    this->numeClient="Anonim";
    strcpy(this->dataStart,"01-01-1900");
    strcpy(this->dataFinish,"01-01-1900");
}

Sistem::Sistem(char dataStart[], char dataFinish[])
{
        strcpy(this->dataStart,dataStart);
        strcpy(this->dataFinish,dataFinish);
}

Sistem::Sistem(double buget, int nrMembrii, char* numeEchipa)
    {
        this->buget=buget;

        this->nrMembrii=nrMembrii;
        this->numeEchipa = new char[strlen(numeEchipa)+1];
        strcpy(this->numeEchipa,numeEchipa);

    }

Sistem::Sistem(char* numeEchipa, int nrMembrii, int nrComanda, double buget,float* preturiComponente,int nrComponente, string numeClient, char dataStart[], char dataFinish[])
    {
        this->numeEchipa = new char[strlen(numeEchipa)+1];
        this->nrMembrii=nrMembrii;
        this->nrComanda=nrComanda;
        this->buget=buget;

        this->nrComponente=nrComponente;
        this->preturiComponente = new float[nrComponente];
        for(int i=0;i<nrComponente;i++)
            this->preturiComponente[i]=preturiComponente[i];


        this->numeClient=numeClient;

        strcpy(this->dataStart,dataStart);
        strcpy(this->dataFinish,dataFinish);
    }

Sistem::Sistem(const Sistem& altSistem)
    {
        this->buget=altSistem.buget;
        this->nrComanda=altSistem.nrComanda;
        this->nrMembrii=altSistem.nrMembrii;
        this->numeEchipa = new char[strlen(altSistem.numeEchipa)+1];
        strcpy(this->numeEchipa,altSistem.numeEchipa);
        this->numeClient=altSistem.numeClient;

        this->nrComponente=altSistem.nrComponente;

        this->preturiComponente = new float[altSistem.nrComponente];
        for(int i=0;i<altSistem.nrComponente;i++)
            this->preturiComponente[i]=altSistem.preturiComponente[i];

        strcpy(this->dataStart,altSistem.dataStart);
        strcpy(this->dataFinish,altSistem.dataFinish);
    }

Sistem& Sistem::operator=(const Sistem& altSistem)
{
    if(this!=&altSistem)
    {
        if(this->numeEchipa!=NULL)
            delete[] this->numeEchipa;

        if(this->preturiComponente!=NULL)
            delete[] this->preturiComponente;

        this->buget=altSistem.buget;
        this->nrComanda=altSistem.nrComanda;
        this->nrMembrii=altSistem.nrMembrii;
        this->numeEchipa = new char[strlen(altSistem.numeEchipa)+1];
        strcpy(this->numeEchipa,altSistem.numeEchipa);
        this->numeClient=altSistem.numeClient;

        this->nrComponente=altSistem.nrComponente;

        this->preturiComponente = new float[altSistem.nrComponente];
        for(int i=0;i<altSistem.nrComponente;i++)
            this->preturiComponente[i]=altSistem.preturiComponente[i];

        strcpy(this->dataStart,altSistem.dataStart);
        strcpy(this->dataFinish,altSistem.dataFinish);
    }

    return *this;
}


istream& operator >> (istream& in, Sistem& s)
{
    cout<<"numarul comenzii: ";
    in>>s.nrComanda;

    cout<<"numarul de componente: ";
    in>>s.nrComponente;

    if(s.nrComponente < 7)
    {
        cout<<"livrare parti separate"<<endl;

        cout<<"livrare pe numele: ";
        in>>s.numeClient;

        cout<<"livrare pe data de: ";
        in>>s.dataFinish;
    }
    else
    {
        char nume[50];
        cout<<"numele echipei: ";
        in>>nume;

        if(s.numeEchipa != NULL)
            delete[] s.numeEchipa;

        s.numeEchipa = new char[strlen(nume)+1];
        strcpy(s.numeEchipa,nume);

        cout<<"numarul de membrii ai echipei: ";
        in>>s.nrMembrii;


        cout<<"bugetul build-ului: ";
        in>>s.buget;


        float preturi[70];
        cout<<"preturile componentelor sunt:(0-gpu, 1-cpu, 2-mobo, 3-ram, 4-hdd/ssd, 5-psu, 6-case) "<<endl;

        if(s.preturiComponente != NULL)
            delete[] s.preturiComponente;
        
        s.preturiComponente = new float[7];    

        for(int i=0;i<7;i++)
        {
            in>>preturi[i];
            s.preturiComponente[i]=preturi[i];
        }


        int suma=0;
        for(int i=0;i<7;i++)
            suma=suma+s.preturiComponente[i];

        if(suma>s.buget)
            {
                cout<<"BUGET INSUFICIENT";
                return in;
            }

        cout<<"data inceperii proiectului: ";
        in>>s.dataStart;
        cout<<"finalizare pana la data de: ";
        in>>s.dataFinish;

        cout<<"livrare pe numele: ";
        in>>s.numeClient;
    }


    return in;
        


}
ostream& operator << (ostream& out, const Sistem& s)
{
    out<<"numarul comenzii: "<<s.nrComanda<<endl;
    out<<"numarul de componente: "<<s.nrComponente<<endl;

    if(s.nrComponente < 7)
    {
        out<<"livrare de parti separate pe numele: "<<s.numeClient<<" pe data de "<<s.dataFinish;
        return out;
    }
    else
    {
        out<<"de proiect se ocupa echipa "<<s.numeEchipa<<" formata din "<<s.nrMembrii<<" membrii"<<endl;

        out<<"bugetul build-ului: "<<s.buget<<endl;

        for(int i =0;i<7;i++)
            {
                if(i==0)
                    out<<"pretul placii video: "<<s.preturiComponente[i]<<endl;
                if(i==1)
                    out<<"pretul procesorului: "<<s.preturiComponente[i]<<endl;
                if(i==2)
                    out<<"pretul placii de baza: "<<s.preturiComponente[i]<<endl;
                if(i==3)
                    out<<"pretul RAM-ului: "<<s.preturiComponente[i]<<endl;
                if(i==4)
                    out<<"pretul  hdd/ssd-ului: "<<s.preturiComponente[i]<<endl;
                if(i==5)
                    out<<"pretul sursei: "<<s.preturiComponente[i]<<endl;
                if(i==6)
                    out<<"pretul carcasei: "<<s.preturiComponente[i]<<endl;
            }

        out<<"asamblarea va dura de pe data de "<<s.dataStart<<" pana pe "<<s.dataFinish<<endl;

        out<<"livrare pe numele: "<<s.numeClient;


    }

    return out;
}

float Sistem::operator[](int index)
{
    return this->preturiComponente[index];
}

 Sistem& Sistem::operator++()
{   
    this->nrMembrii++;
    return *this;

} 
 Sistem Sistem::operator++(int)
{
    Sistem aux = *this;
    this->nrMembrii++;
    return aux;
}

bool Sistem::operator==(const Sistem& altSistem)
{
    if(this->buget == altSistem.buget)
        return true;
    return false;
}

bool Sistem::operator>(const Sistem& altSistem)
{
    if(strcmp(this->dataFinish, altSistem.dataFinish) > 0)
        return true;
    return false;
}

Sistem Sistem::operator+(int x)
{
    Sistem sis=*this;
    sis.buget = sis.buget+x;
    return sis;
}

Sistem operator+(int x, Sistem sis)
{
    sis.buget = sis.buget + x;
    return sis;
}

Sistem Sistem::operator+(Sistem sis)
{
    sis.nrMembrii = this->nrMembrii+sis.nrMembrii;
    return sis;
}

Sistem Sistem::operator-(int x)
{
    Sistem aux(*this);
    aux.buget=aux.buget-x;
    return aux;
}

Sistem operator-(int x, Sistem sis)
{
    sis.buget=sis.buget-x;
    return sis;
}

Sistem Sistem::operator-(Sistem sis)
{
    sis.nrMembrii = abs(this->nrMembrii-sis.nrMembrii);
    return sis;
}

Sistem::operator float()
{
    return (float)this->buget;
}

Sistem::~Sistem()
    {
        if(this->numeEchipa!=NULL)
            delete[] this->numeEchipa;

        if(this->preturiComponente!=NULL)
            delete[] this->preturiComponente;
    }

void Sistem::setDates(char dataS[], char dataF[])
{
        strcpy(this->dataStart,dataS);
        strcpy(this->dataFinish,dataF);
}

void Sistem::setBuget(int bug)
{
    this->buget=bug;
}

void Sistem::setMembriiEchipa(int memb)
{
    this->nrMembrii=memb;
}

int Sistem::getMembriiEchipa(){
    return this->nrMembrii;
}


char* Sistem::getStartDate(){
    return this->dataStart;
}

char* Sistem::getFinishDate(){
    return this->dataFinish;
}

string Sistem::getNumeClient()
{
    return this->numeClient;
}
int Sistem::getNrComanda()
{  
    return this->nrComanda;
}
double Sistem::getBuget()
{
    return this->buget;
}



SistemRacireAer::SistemRacireAer():Sistem()
{
    this->nrVentilatoare=0;
    this->ventilatoare = new int[1];
    this->ventilatoare[0]=0;
    this->RPM=0;
}

SistemRacireAer::SistemRacireAer(char* numeEchipa, int nrMembrii, int nrComanda, double buget, float* preturiComponente, int nrComponente, string numeClient, char dataStart[], char dataFinish[],int nrVentilatoare, int* ventilatoare, float RPM):Sistem(numeEchipa,nrMembrii,nrComanda,buget, preturiComponente, nrComponente, numeClient, dataStart, dataFinish)
{
    this->nrVentilatoare=nrVentilatoare;

    this->ventilatoare = new int[7];
    for(int i=0;i<7;i++)
        this->ventilatoare[i]=ventilatoare[i];
    this->RPM=RPM;
}

SistemRacireAer::SistemRacireAer(const SistemRacireAer& altSistem):Sistem(altSistem)
{
    this->nrVentilatoare=altSistem.nrVentilatoare;

    this->ventilatoare = new int[7];
    for(int i=0;i<7;i++)
        this->ventilatoare[i]=altSistem.ventilatoare[i];
    this->RPM=altSistem.RPM;
}

SistemRacireAer::~SistemRacireAer()
{
    if(this->numeEchipa!=NULL)
        delete[] this->numeEchipa;
    if(this->preturiComponente!=NULL)
        delete[] this->preturiComponente;
    if(this->ventilatoare!=NULL)
        delete[] this->ventilatoare;
}

SistemRacireAer& SistemRacireAer::operator=(const SistemRacireAer& altSistem)
{
    if(this!=&altSistem)
    {
        if(this->numeEchipa!=NULL)
            delete[] this->numeEchipa;
        if(this->preturiComponente!=NULL)
            delete[] this->preturiComponente;
        if(this->ventilatoare!=NULL)
            delete[] this->ventilatoare;

        Sistem::operator=(altSistem);
        this->nrVentilatoare=altSistem.nrVentilatoare;

        this->ventilatoare = new int[7];
        for(int i=0;i<7;i++)
            this->ventilatoare[i]=altSistem.ventilatoare[i];
        this->RPM=altSistem.RPM;

    }

    return *this;
}


istream& operator>>(istream& in, SistemRacireAer& s)
{
    in>>(Sistem&)s;
    cout<<"Numarul de ventilatoare: ";
    in>>s.nrVentilatoare;

    int buffer[20];
    cout<<"Ventilatoare pentru fiecare componenta (0-gpu, 1-cpu, 2-mobo, 3-RAM, 4-HDD, 5-PSU, 6-case)";

    for(int i=0;i<7;i++)
        in>>buffer[i];

    s.ventilatoare = new int[7];
    for(int i=0;i<7;i++)
        s.ventilatoare[i]=buffer[i];

    cout<<"Introduceti viteza ventilatoarelor: ";
    in>>s.RPM;

    return in;
    
}

ostream& operator<<(ostream& out, const SistemRacireAer& s)
{
    out<<(Sistem&)s;
    out<<"\nNumarul de ventilatoare: "<<s.nrVentilatoare<<endl;
    out<<"Repartizarea ventilatoarelor: (0-gpu, 1-cpu, 2-mobo, 3-RAM, 4-HDD, 5-PSU, 6-case)"<<endl;
    for(int i=0;i<7;i++)
    {
        if(i==0) out<<"Placa video are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==1) out<<"Procesorul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==2) out<<"Placa de baza are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==3) out<<"RAM-ul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==4) out<<"HDD-ul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==5) out<<"Sursa are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==6) out<<"In carcasa sunt "<<s.ventilatoare[i]<<" ventilatoare"<<endl;
    }
    out<<"RPM-ul mediu al sistemului: "<<s.RPM<<endl;


    return out;

}


SistemRacireLichid::SistemRacireLichid():Sistem()
{
    this->capacitateRezervor=0;
    this->hardTubing=false;
    this->softTubing=false;
}

SistemRacireLichid::SistemRacireLichid(char* numeEchipa, int nrMembrii, int nrComanda, double buget, float* preturiComponente, int nrComponente, string numeclient, char dataStart[], char dataFinish[], float capacitateRezervor, bool hardTubing, bool softTubing):Sistem(numeEchipa,nrMembrii,nrComanda,buget, preturiComponente, nrComponente, numeClient, dataStart, dataFinish)
{
    this->capacitateRezervor=capacitateRezervor;
    this->hardTubing=hardTubing;
    this->softTubing=softTubing;
}

SistemRacireLichid::SistemRacireLichid(const SistemRacireLichid& altSistem):Sistem(altSistem)
{
    this->capacitateRezervor=altSistem.capacitateRezervor;
    this->hardTubing=altSistem.hardTubing;
    this->softTubing=altSistem.softTubing;
}

SistemRacireLichid& SistemRacireLichid::operator=(const SistemRacireLichid& altSistem)
{
    if(this!=&altSistem)
    {
        if(this->numeEchipa!=NULL)
            delete[] this->numeEchipa;

        if(this->preturiComponente!=NULL)
            delete[] this->preturiComponente;
        
        Sistem::operator=(altSistem);

        this->capacitateRezervor=altSistem.capacitateRezervor;
        this->hardTubing=altSistem.hardTubing;
        this->softTubing=altSistem.softTubing;
        
    }
    return *this;
}

SistemRacireLichid::~SistemRacireLichid()
{
    if(this->numeEchipa!=NULL)
        delete[] this->numeEchipa;
    if(this->preturiComponente!=NULL)
        delete[] this->preturiComponente;
}

istream& operator>>(istream& in, SistemRacireLichid& s)
{
    in>>(Sistem&)s;

    cout<<"capacitate rezervor: ";
    in>>s.capacitateRezervor;

    cout<<"foloseste hard tubing?: (0-nu , 1-da): ";
    in>>s.hardTubing;

    cout<<"foloseste soft tubing?: (0-nu , 1-da): ";
    in>>s.softTubing;


    return in;
}

ostream& operator<<(ostream& out, const SistemRacireLichid& s)
{
    out<<(Sistem&)s;
    out<<"\nCapacitatea rezervorului: "<<s.capacitateRezervor<<" litrii"<<endl;
    if(s.hardTubing)
        out<<"Sistemul foloseste hard tubing? (0-nu  1-da): "<<s.hardTubing<<endl;
    if(s.softTubing)
        out<<"Sistemul foloseste soft tubing? (0-nu  1-da): "<<s.softTubing<<endl;

    return out;
}



SistemRacireHibrida::SistemRacireHibrida():SistemRacireAer(),SistemRacireLichid(),Sistem()
{
    this->nrRadioatoare=0;
    this->pumpRPM=0;
}

SistemRacireHibrida::SistemRacireHibrida(char* numeEchipa, int nrMembrii, int nrComanda, double buget,float* preturiComponente,int nrComponente, string numeClient, char dataStart[], char dataFinish[], int nrVentilatoare, int* ventilatoare , float RPM, float capacitateRezervor, bool hardTubing, bool softTubing, int nrRadiatoare, float pumpRPM):SistemRacireAer(numeEchipa,  nrMembrii,  nrComanda,  buget,  preturiComponente,  nrComponente,  numeClient,  dataStart,  dataFinish, nrVentilatoare,  ventilatoare,  RPM), SistemRacireLichid( numeEchipa,  nrMembrii,  nrComanda,  buget,  preturiComponente,  nrComponente,  numeClient,  dataStart,  dataFinish,  capacitateRezervor,  hardTubing,  softTubing), Sistem(numeEchipa,  nrMembrii,  nrComanda,  buget, preturiComponente, nrComponente,  numeClient,  dataStart,  dataFinish)
{
    this->nrRadioatoare=nrRadiatoare;
    this->pumpRPM=pumpRPM;
}

SistemRacireHibrida::SistemRacireHibrida(const SistemRacireHibrida& altSistem):SistemRacireAer(altSistem), SistemRacireLichid(altSistem), Sistem(altSistem)
{
    this->nrRadioatoare=altSistem.nrRadioatoare;
    this->pumpRPM=altSistem.pumpRPM;
}

SistemRacireHibrida& SistemRacireHibrida::operator=(const SistemRacireHibrida& altSistem)
{
    if(this!=&altSistem)
    {
        if(this->numeEchipa!=NULL)
            delete[] this->numeEchipa;
        if(this->preturiComponente!=NULL)
            delete[] this->preturiComponente;
        if(this->ventilatoare!=NULL)
            delete[] this->ventilatoare;

        Sistem::operator=(altSistem);

        this->nrVentilatoare=altSistem.nrVentilatoare;

        this->ventilatoare = new int[altSistem.nrVentilatoare];
        for(int i=0;i<altSistem.nrVentilatoare;i++)
            this->ventilatoare[i]=altSistem.ventilatoare[i];
        this->RPM=altSistem.RPM;

        this->capacitateRezervor=altSistem.capacitateRezervor;
        this->hardTubing=altSistem.hardTubing;
        this->softTubing=altSistem.softTubing;

        this->nrRadioatoare=altSistem.nrRadioatoare;
        this->pumpRPM=altSistem.pumpRPM;


    }
    return *this;
}

SistemRacireHibrida::~SistemRacireHibrida()
{
    if(this->numeEchipa!=NULL)
        delete[] this->numeEchipa;
    if(this->preturiComponente!=NULL)
        delete[] this->preturiComponente;
    if(this->preturiComponente!=NULL)
        delete[] this->preturiComponente;
}

istream& operator>>(istream& in, SistemRacireHibrida& s)
{
    in>>(Sistem&)s;
    cout<<"Numarul de ventilatoare: ";
    in>>s.nrVentilatoare;

    int buffer[20];
    cout<<"Ventilatoare pentru fiecare componenta (0-gpu, 1-cpu, 2-mobo, 3-RAM, 4-HDD, 5-PSU, 6-case)";

    for(int i=0;i<7;i++)
        in>>buffer[i];

    s.ventilatoare = new int[7];
    for(int i=0;i<7;i++)
        s.ventilatoare[i]=buffer[i];

    cout<<"Introduceti viteza ventilatoarelor: ";
    in>>s.RPM;


    cout<<"capacitate rezervor: ";
    in>>s.capacitateRezervor;

    cout<<"foloseste hard tubing?: (0-nu , 1-da): ";
    in>>s.hardTubing;

    cout<<"foloseste soft tubing?: (0-nu , 1-da): ";
    in>>s.softTubing;

    cout<<"numar radiatoare: ";
    in>>s.nrRadioatoare;

    cout<<"RPM radiatoare: ";
    in>>s.pumpRPM;


    return in;

    
}

ostream& operator<<(ostream& out, const SistemRacireHibrida& s)
{
    out<<(Sistem&)s;

    out<<"\nNumarul de ventilatoare: "<<s.nrVentilatoare<<endl;
    out<<"Repartizarea ventilatoarelor: (0-gpu, 1-cpu, 2-mobo, 3-RAM, 4-HDD, 5-PSU, 6-case)"<<endl;
    for(int i=0;i<7;i++)
    {
        if(i==0) out<<"Placa video are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==1) out<<"Procesorul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==2) out<<"Placa de baza are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==3) out<<"RAM-ul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==4) out<<"HDD-ul are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==5) out<<"Sursa are "<<s.ventilatoare[i]<<" ventilatoare alocate"<<endl;
        if(i==6) out<<"In carcasa sunt "<<s.ventilatoare[i]<<" ventilatoare"<<endl;
    }
    out<<"RPM-ul mediu al sistemului: "<<s.RPM<<endl;

    out<<"\nCapacitatea rezervorului: "<<s.capacitateRezervor<<" litrii"<<endl;
    if(s.hardTubing)
        out<<"Sistemul foloseste hard tubing? (0-nu  1-da): "<<s.hardTubing<<endl;
    if(s.softTubing)
        out<<"Sistemul foloseste soft tubing? (0-nu  1-da): "<<s.softTubing<<endl;

    out<<"Numar radiatoare: "<<s.nrRadioatoare<<endl;
    out<<"RPM radiatoare: "<<s.pumpRPM<<endl;

    return out;


}




//CONSTRUCTORI SI METODE PENTRU DEPARTAMENT


Departament::Departament()
    {
        this->nrAngajati=0;

        this->numeManager=new char[strlen("Anonim")+1];
        strcpy(this->numeManager,"Anonim");

        this->locatieDepartament=new char[strlen("Nedeterminat")+1];
        strcpy(this->locatieDepartament, "Nedeterminat");

        this->numeDepartament=new char[strlen("DepartamentX")+1];
        strcpy(this->numeDepartament,"DepartamentX");

        this->listaAngajati = 0;
        this->angajatiInregistrati=0;
    }

Departament::Departament(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager, Angajat* listaAngajati, int angajatiInregistrati)
{
        this->nrAngajati=nrAngajati;
        this->numeDepartament = new char[strlen(numeDepartament)+1];
        strcpy(this->numeDepartament, numeDepartament);
        this->locatieDepartament = new char[strlen(locatieDepartament)+1];
        strcpy(this->locatieDepartament, locatieDepartament);
        this->numeManager = new char[strlen(numeManager)+1];
        strcpy(this->numeManager, numeManager);

        this->angajatiInregistrati=angajatiInregistrati;
        this->listaAngajati = new Angajat[angajatiInregistrati];
        for(int i=0;i<angajatiInregistrati;i++)
            this->listaAngajati[i]=listaAngajati[i];
}

Departament::Departament(const Departament& altDep)
{
        this->nrAngajati=altDep.nrAngajati;

        this->numeDepartament = new char[strlen(altDep.numeDepartament)+1];
        strcpy(this->numeDepartament,altDep.numeDepartament);

        this->locatieDepartament = new char[strlen(altDep.locatieDepartament)+1];
        strcpy(this->locatieDepartament,altDep.locatieDepartament);

        this->numeManager = new char[strlen(altDep.numeManager)+1];
        strcpy(this->numeManager,altDep.numeManager);

        this->angajatiInregistrati=altDep.angajatiInregistrati;
        this->listaAngajati = new Angajat[altDep.angajatiInregistrati];
        for(int i=0;i<altDep.angajatiInregistrati;i++)
            this->listaAngajati[i] = altDep.listaAngajati[i];
}

Departament& Departament::operator=(const Departament& altDep)
{
    if(this!=&altDep)
    {
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;

        if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;

        if(this->listaAngajati!=NULL)
            delete[] this->listaAngajati;

        this->nrAngajati=altDep.nrAngajati;

        this->numeDepartament = new char[strlen(altDep.numeDepartament)+1];
        strcpy(this->numeDepartament,altDep.numeDepartament);

        this->locatieDepartament = new char[strlen(altDep.locatieDepartament)+1];
        strcpy(this->locatieDepartament,altDep.locatieDepartament);

        this->numeManager = new char[strlen(altDep.numeManager)+1];
        strcpy(this->numeManager,altDep.numeManager);

        this->angajatiInregistrati=altDep.angajatiInregistrati;
        this->listaAngajati = new Angajat[altDep.angajatiInregistrati];
        for(int i=0;i<altDep.angajatiInregistrati;i++)
            this->listaAngajati[i] = altDep.listaAngajati[i];
    }

    return *this;
}

istream& operator >>(istream& in, Departament& dep)
{
    cout<<"introduceti numarul de angajati: ";
    in>>dep.nrAngajati;

    char nume[50];
    cout<<"introduceti numele departamentului: ";
    in>>nume;

    if(dep.numeDepartament != NULL)
        delete[] dep.numeDepartament;

    dep.numeDepartament = new char[strlen(nume)+1];
    strcpy(dep.numeDepartament,nume);

    char loc[50];
    cout<<"introduceti adresa departamentului: ";
    in>>loc;

    if(dep.locatieDepartament != NULL)
        delete[] dep.locatieDepartament;

    dep.locatieDepartament = new char[strlen(loc)+1];
    strcpy(dep.locatieDepartament,loc);

    char manager[50];
    cout<<"introduceti seful de departament: ";
    in>>manager;

    if(dep.numeManager != NULL)
        delete[] dep.numeManager;

    dep.numeManager = new char[strlen(manager)+1];
    strcpy(dep.numeManager,manager);

    cout<<"introduceti numarul de angajati pe care ii inregistrati: ";
    in>>dep.angajatiInregistrati;

    cout<<"inregistrati angajatii:"<<endl;
    if(dep.listaAngajati!=NULL)
        delete[] dep.listaAngajati;

    dep.listaAngajati = new Angajat[dep.angajatiInregistrati];
    for(int i=0;i<dep.angajatiInregistrati;i++)
        in>>dep.listaAngajati[i];

    return in;

}

ostream& operator<<(ostream& out, const Departament& dep)
{
    out<<"numarul total de angajati: "<<dep.nrAngajati<<endl;
    out<<"numarul de angajati inregistrati: "<<dep.angajatiInregistrati<<endl<<endl;

    out<<"angajatii inregistrati in sistem: "<<endl;
    for(int i=0;i<dep.angajatiInregistrati;i++)
        out<<dep.listaAngajati[i]<<endl;

    out<<"numele departamentului: "<<dep.numeDepartament<<endl;
    out<<"seful de departament: "<<dep.numeManager<<endl;
    out<<"adresa departamentului: "<<dep.locatieDepartament<<endl;


    return out;

}

Angajat Departament::operator[](int index)
{
    if(index >= 0 && index<this->angajatiInregistrati)
        return this->listaAngajati[index];
    cout<<"Index gresit"<<endl;
}

 Departament& Departament::operator++()
{
    this->nrAngajati++;
    return *this;
}

 Departament Departament::operator++(int)
{
    Departament aux = *this;
    this->nrAngajati++;
    return aux;
}

bool Departament::operator==(const Departament& altDep)
{
    if(this->nrAngajati == altDep.nrAngajati)
        return true;
    return false;
}

bool Departament::operator>(const Departament& altDep)
{
    if(this->nrAngajati > altDep.nrAngajati)
        return true;
    return false;
}

Departament Departament::operator+(int x)
{
    Departament dep=*this;
    dep.nrAngajati=dep.nrAngajati+x;
    return dep;
}

Departament operator+(int x, Departament dep)
{
    dep.nrAngajati=dep.nrAngajati+x;
    return dep;
}

Departament Departament::operator+(Departament dep)
{
    dep.nrAngajati = this->nrAngajati + dep.nrAngajati;
    return dep;
}


Departament Departament::operator-(int x)
{
    Departament aux=*this;
    aux.nrAngajati=aux.nrAngajati-x;
    return aux;
}

Departament operator-(int x, Departament dep)
{
    dep.nrAngajati=dep.nrAngajati-x;
    return dep;
}

Departament Departament::operator-(Departament dep)
{
    dep.nrAngajati = abs(this->nrAngajati-dep.nrAngajati);
    return dep;
}


Departament operator+(Departament dep, const Angajat& a)
{
    Angajat* listaAngajatiAux;
    listaAngajatiAux = new Angajat[dep.angajatiInregistrati];
    for(int i=0;i<dep.angajatiInregistrati;i++)
        listaAngajatiAux[i] = dep.listaAngajati[i];
    
    if(dep.listaAngajati!=NULL)
        delete[] dep.listaAngajati;
    
    dep.angajatiInregistrati++;

    dep.listaAngajati = new Angajat[dep.angajatiInregistrati];
    for(int i=0;i<dep.angajatiInregistrati-1;i++)
        dep.listaAngajati[i] = listaAngajatiAux[i];

    
    dep.listaAngajati[dep.angajatiInregistrati-1] = a;

    if(listaAngajatiAux!=NULL)
        delete[] listaAngajatiAux;
    return dep;

}

Departament operator+(const Angajat& a, Departament dep)
{
    Angajat* listaAngajatiAux;
    listaAngajatiAux = new Angajat[dep.angajatiInregistrati];
    for(int i=0;i<dep.angajatiInregistrati;i++)
        listaAngajatiAux[i] = dep.listaAngajati[i];
    
    if(dep.listaAngajati!=NULL)
        delete[] dep.listaAngajati;
    
    dep.angajatiInregistrati++;

    dep.listaAngajati = new Angajat[dep.angajatiInregistrati];
    for(int i=0;i<dep.angajatiInregistrati-1;i++)
        dep.listaAngajati[i] = listaAngajatiAux[i];

    dep.listaAngajati[dep.angajatiInregistrati-1] = a;

    if(listaAngajatiAux!=NULL)
        delete[] listaAngajatiAux;
    return dep;
}


Departament::~Departament()
{
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;

        if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;

        if(this->listaAngajati!=NULL)
            delete[] this->listaAngajati;

}

void Departament::setNrAngajati(int numar){
        this->nrAngajati = numar;
}


void Departament::setnNumeDepartament(char* numeDep){
    this->numeDepartament = new char[strlen(numeDep)+1];
    strcpy(this->numeDepartament, numeDep);

}

int Departament::getNrAngajati(){
        return this->nrAngajati;
}

char* Departament::getNumeDepartament(){
    return this->numeDepartament;
}



DepartamentAsamblare::DepartamentAsamblare():Departament()
{
    this->comenziPrimiteLunar=-1;
}

DepartamentAsamblare::DepartamentAsamblare(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager,Angajat* listaAngajati,int angajatiInregistrati,float comenziPrimiteLunar):Departament(nrAngajati, numeDepartament, locatieDepartament, numeDepartament, listaAngajati, angajatiInregistrati)
{
    this->comenziPrimiteLunar=comenziPrimiteLunar;
}

DepartamentAsamblare::DepartamentAsamblare(const DepartamentAsamblare& altDepartament):Departament(altDepartament)
{
    this->comenziPrimiteLunar=altDepartament.comenziPrimiteLunar;
}

DepartamentAsamblare& DepartamentAsamblare::operator=(const DepartamentAsamblare& altDepartament)
{
    if(this!=&altDepartament)
    {
        if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        if(this->listaAngajati !=NULL)
            delete[] this->listaAngajati;

        Departament::operator=(altDepartament);

        this->comenziPrimiteLunar=altDepartament.comenziPrimiteLunar;
    }
    return *this;
}

DepartamentAsamblare::~DepartamentAsamblare()
{
    if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        if(this->listaAngajati!=NULL)
            delete[] this->listaAngajati;
}

istream& operator>>(istream& in, DepartamentAsamblare& d)
{
    in>>(Departament&)d;

    cout<<"introduceti numarul de comenzi lunare (medie): "; in>>d.comenziPrimiteLunar;

    return in;
}

ostream& operator<<(ostream& out, const DepartamentAsamblare& d)
{
    out<<(Departament&)d;
    out<<"numarul mediu de comenzi lunare: "<<d.comenziPrimiteLunar<<endl;
    return out;
}



DepartamentAsamblarePremium::DepartamentAsamblarePremium():DepartamentAsamblare()
{
    this->comenziPentruStudiouri=-1;
    this->comenziSistemeServer=-1;
    this->licenseKeys=-1;
    this->BIOSFlashes=-1;
}

DepartamentAsamblarePremium::DepartamentAsamblarePremium(int nrAngajati, char* numeDepartament, char* locatieDepartament, char* numeManager,Angajat* listaAngajati,int angajatiInregistrati, float comenziPrimiteLunar, int comenziPentruStudiouri, int comenziSistemeServer, int licenseKeys, int BIOSFlashes):DepartamentAsamblare(nrAngajati, numeDepartament, locatieDepartament, numeManager,listaAngajati,angajatiInregistrati, comenziPrimiteLunar)
{
    this->comenziPentruStudiouri=comenziPentruStudiouri;
    this->comenziSistemeServer=comenziSistemeServer;
    this->licenseKeys=licenseKeys;
    this->BIOSFlashes=BIOSFlashes;
}

DepartamentAsamblarePremium::DepartamentAsamblarePremium(const DepartamentAsamblarePremium& altDepartament):DepartamentAsamblare(altDepartament)
{
    this->comenziPentruStudiouri=altDepartament.comenziPentruStudiouri;
    this->comenziSistemeServer=altDepartament.comenziSistemeServer;
    this->licenseKeys=altDepartament.licenseKeys;
    this->BIOSFlashes=altDepartament.BIOSFlashes;
}

DepartamentAsamblarePremium& DepartamentAsamblarePremium::operator=(const DepartamentAsamblarePremium& altDepartament)
{
    if(this!=&altDepartament)
    {
        if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        if(this->listaAngajati!=NULL)
            delete[] this->listaAngajati;

        Departament::operator=(altDepartament);
        this->comenziPrimiteLunar=altDepartament.comenziPrimiteLunar;
        this->comenziPentruStudiouri=altDepartament.comenziPentruStudiouri;
        this->comenziSistemeServer=altDepartament.comenziSistemeServer;
        this->licenseKeys=altDepartament.licenseKeys;
        this->BIOSFlashes=altDepartament.BIOSFlashes;

    }

    return *this;
}

DepartamentAsamblarePremium::~DepartamentAsamblarePremium()
{
    if(this->numeDepartament!=NULL)
            delete[] this->numeDepartament;
        if(this->locatieDepartament!=NULL)
            delete[] this->locatieDepartament;
        if(this->numeManager!=NULL)
            delete[] this->numeManager;
        if(this->listaAngajati!=NULL)
            delete[] this->listaAngajati;
}

istream& operator>>(istream& in, DepartamentAsamblarePremium& d)
{
    in>>(Departament&)d;

    cout<<"introduceti numarul de comenzi lunare (medie): ";
    in>>d.comenziPrimiteLunar;

    cout<<"introduceti numarul de comenzi pentru studiouri: ";
    in>>d.comenziPentruStudiouri;

    cout<<"introduceti numarul de sisteme de tip server: ";
    in>>d.comenziSistemeServer;

    cout<<"introduceti numarul de license keys: ";
    in>>d.licenseKeys;

    cout<<"introduceti numarul de flash-uri BIOS: ";
    in>>d.BIOSFlashes;

    return in;
}

ostream& operator<<(ostream& out,const DepartamentAsamblarePremium& d)
{
    out<<(Departament&)d;
    out<<"comenzi primite lunar: "<<d.comenziPrimiteLunar<<endl;
    out<<"comenzi plasate de studiouri: "<<d.comenziPentruStudiouri<<endl;
    out<<"comenzi de sisteme pentru servere: "<<d.comenziSistemeServer<<endl;
    out<<"numarul de chei de licenta din departament: "<<d.licenseKeys<<endl;
    out<<"numarul de flash-uri BIOS din departament: "<<d.BIOSFlashes<<endl;
    return out;
}



//CONSTRUCTORI SI METODE PENTRU CURIER


Curier::Curier()
{
        this->numeCurier= new char[strlen("Anonim")+1];
        strcpy(this->numeCurier,"Anonim");

        this->codCurier=-1;
        this->livrariInUltimeleLuni=new int[1];
        this->livrariInUltimeleLuni[0]=-1;
        this->nrLuni=0;
        this->prenumeCurier="Anonim";

        strcpy(dataContract,"01-01-1900");
        strcpy(durataContract,"01-01-1900");
        strcpy(infoContract,"");
}
Curier::Curier(long codCurier, char* numeCurier)
{
    this->numeCurier = new char[strlen(numeCurier)+1];
        strcpy(this->numeCurier, numeCurier);

        this->codCurier=-1;
}
Curier::Curier(int* livrariInUltimeleLuni,int nrLuni, char* numeCurier)
{
    this->numeCurier = new char[strlen(numeCurier)+1];
        strcpy(this->numeCurier, numeCurier);

    this->nrLuni=nrLuni;
    this->livrariInUltimeleLuni = new int[this->nrLuni];

    for(int i=0;i<this->nrLuni;i++)
        this->livrariInUltimeleLuni[i]=livrariInUltimeleLuni[i];
}
Curier::Curier(long codCurier, char* numeCurier, string prenumeCurier, int* livrariInUltimeleLuni, int nrLuni, char dataContract[], char durataContract[], char infoContract[])
{
    this->numeCurier=new char[strlen(numeCurier)+1];
        strcpy( this->numeCurier, numeCurier);

        this->codCurier=codCurier;
        this->prenumeCurier=prenumeCurier;
        this->nrLuni=nrLuni;
        this->livrariInUltimeleLuni=new int [this->nrLuni];
        for(int i=0;i<this->nrLuni;i++)
            this->livrariInUltimeleLuni[i]=livrariInUltimeleLuni[i];

        strcpy(this->dataContract,dataContract);
        strcpy(this->durataContract,durataContract);
        strcpy(this->infoContract,infoContract);
}
Curier::Curier(const Curier& altCurier)
{
    this->numeCurier = new char[strlen(altCurier.numeCurier)+1];
        strcpy(this->numeCurier,altCurier.numeCurier);
        this->prenumeCurier=altCurier.prenumeCurier;
        this->codCurier=altCurier.codCurier;

        strcpy(this->dataContract,altCurier.dataContract);
        strcpy(this->durataContract,altCurier.durataContract);
        strcpy(this->infoContract,altCurier.infoContract);

        this->nrLuni=altCurier.nrLuni;
        this->livrariInUltimeleLuni=new int[altCurier.nrLuni];
        for(int i=0;i<altCurier.nrLuni;i++)
            this->livrariInUltimeleLuni[i]=altCurier.livrariInUltimeleLuni[i];
}
Curier& Curier::operator=(const Curier& altCurier)
{
    if(this!=&altCurier)
    {
        if(this->numeCurier!=NULL)
            delete[] this->numeCurier;

        if(this->livrariInUltimeleLuni!=NULL)
            delete[] this->livrariInUltimeleLuni;
        
        this->numeCurier = new char[strlen(altCurier.numeCurier)+1];
        strcpy(this->numeCurier,altCurier.numeCurier);
        this->prenumeCurier=altCurier.prenumeCurier;
        this->codCurier=altCurier.codCurier;

        strcpy(this->dataContract,altCurier.dataContract);
        strcpy(this->durataContract,altCurier.durataContract);
        strcpy(this->infoContract,altCurier.infoContract);

        this->nrLuni=altCurier.nrLuni;
        this->livrariInUltimeleLuni=new int[altCurier.nrLuni];
        for(int i=0;i<altCurier.nrLuni;i++)
            this->livrariInUltimeleLuni[i]=altCurier.livrariInUltimeleLuni[i];

    }

    return *this;
}


istream& operator >> (istream& in, Curier& c)
{
    cout<<"codul curierului: ";
    in>>c.codCurier;

    char nume[50];
    cout<<"numele curierului: ";
    in>>nume;

    if(c.numeCurier != NULL)
        delete[] c.numeCurier;

    c.numeCurier = new char[strlen(nume)+1];
    strcpy(c.numeCurier,nume);

    cout<<"prenumele curierului: ";
    in>>c.prenumeCurier;

    cout<<"pe cate luni se face raportul?: ";
    in>>c.nrLuni;

    if(c.livrariInUltimeleLuni != NULL)
        delete[] c.livrariInUltimeleLuni;

    c.livrariInUltimeleLuni = new int[c.nrLuni];

    for(int i=0;i<c.nrLuni;i++)
    {
        cout<<"nr livrari(luna "<<i<<")";
        in>>c.livrariInUltimeleLuni[i];
    }

    cout<<"data de incepere a contractului: ";
    in>>c.dataContract;

    cout<<"data de finalizare a contractului: ";
    in>>c.durataContract;

    strcpy(c.infoContract,"");
    strcat(c.infoContract,c.dataContract);
    strcat(c.infoContract," -> ");
    strcat(c.infoContract,c.durataContract);
    
    return in;
    
}

ostream& operator << (ostream& out, const Curier& c)
{
    out<<endl;

    out<<"numele curierului: "<<c.numeCurier<<endl;
    out<<"prenumele curierului: "<<c.prenumeCurier<<endl;
    out<<"codul curierului: "<<c.codCurier<<endl;

    out<<"In aceasta luna s-au livrat "<<c.livrariInUltimeleLuni[0]<<" sisteme"<<endl;
    out<<"In urma cu o luna s-au livrat "<<c.livrariInUltimeleLuni[1]<<" sisteme"<<endl;

    for(int i=2;i<c.nrLuni;i++)
        out<<"In urma cu "<<i<<" luni s-au livrat "<<c.livrariInUltimeleLuni[i]<<" sisteme"<<endl;

    out<<"Perioada contractului:"<<c.infoContract;

    return out;
}

int Curier::operator[](int index)
{
    if(index > nrLuni || index < 0)
        return -1;
    return this->livrariInUltimeleLuni[index];
}

 Curier& Curier::operator++()
{
    //02-12-1990
    char data[10]="";
    int intData=0;
    if(this->durataContract[3]=='1' && this->durataContract[4]=='2')
        {
            this->durataContract[3]='0';
            this->durataContract[4]='1';

            strcpy(data, this->durataContract+6);
            intData=atoi(data);

            ++intData;
            char buffer[10];

            strcpy(this->durataContract+6,itoa(intData,buffer,10));

            
        }

    else if(this->durataContract[3]=='1' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='2';
    }

    else if(this->durataContract[3]=='1' && this->durataContract[4]=='0')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='1';
    }


    //02-09-1990
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='9')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='0';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='8')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='9';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='7')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='8';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='6')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='7';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='5')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='6';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='4')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='5';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='3')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='4';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='3';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='2';
    }
    

    return *this;
}

 Curier Curier::operator++(int)
{
    Curier aux=*this;

    //02-12-1990
    char data[10]="";
    int intData=0;
    if(this->durataContract[3]=='1' && this->durataContract[4]=='2')
        {
            this->durataContract[3]='0';
            this->durataContract[4]='1';

            strcpy(data, this->durataContract+6);
            intData=atoi(data);

            ++intData;
            char buffer[10];

            strcpy(this->durataContract+6,itoa(intData,buffer,10));

            
        }
    else if(this->durataContract[3]=='1' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='2';
    }

    else if(this->durataContract[3]=='1' && this->durataContract[4]=='0')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='1';
    }

    //02-09-1990
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='9')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='0';
    }
    //02-05-1990
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='8')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='9';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='7')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='8';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='6')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='7';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='5')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='6';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='4')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='5';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='3')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='4';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='3';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='2';
    }

    return aux;
}

 Curier& Curier::operator--()
{
    //02-12-1990
    char data[10]="";
    int intData=0;
    char buffer[30];
    if(this->durataContract[3]=='1' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='1';
    }

    else if(this->durataContract[3]=='1' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='0';
    }
    
    else if(this->durataContract[3]=='1' && this->durataContract[4]=='0')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='9';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='9')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='8';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='8')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='7';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='7')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='6';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='6')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='5';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='5')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='4';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='4')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='3';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='3')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='2';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='1';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='2';

        strcpy(data,this->durataContract+6);
        intData=atoi(data);

        --intData;

        strcpy(this->durataContract+6, itoa(intData,buffer,10));
    }

    return *this;
}

 Curier Curier::operator--(int)
{
    //02-12-1990
    Curier aux=*this;
    char data[10]="";
    int intData=0;
    char buffer[30];
    if(this->durataContract[3]=='1' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='1';
    }

    else if(this->durataContract[3]=='1' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='0';
    }
    
    else if(this->durataContract[3]=='1' && this->durataContract[4]=='0')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='9';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='9')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='8';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='8')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='7';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='7')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='6';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='6')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='5';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='5')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='4';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='4')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='3';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='3')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='2';
    }
    
    else if(this->durataContract[3]=='0' && this->durataContract[4]=='2')
    {
        this->durataContract[3]='0';
        this->durataContract[4]='1';
    }

    else if(this->durataContract[3]=='0' && this->durataContract[4]=='1')
    {
        this->durataContract[3]='1';
        this->durataContract[4]='2';

        strcpy(data,this->durataContract+6);
        intData=atoi(data);

        --intData;

        strcpy(this->durataContract+6, itoa(intData,buffer,10));
    }

    return aux;
}

Curier Curier::operator+(Curier c)
{
    for(int i=0; i<c.nrLuni;i++)
        c.livrariInUltimeleLuni[i]=this->livrariInUltimeleLuni[i]+c.livrariInUltimeleLuni[i];

    return c;
}

Curier Curier::operator-(Curier c)
{
    for(int i=0;i<c.nrLuni;i++)
        c.livrariInUltimeleLuni[i]=abs(this->livrariInUltimeleLuni[i]-c.livrariInUltimeleLuni[i]);

    return c;
}

bool Curier::operator==(const Curier& altCurier)
{   
    if(strcmp(this->durataContract,altCurier.durataContract)==0)
        return true;
    return false;
}

bool Curier::operator>(const Curier& altCurier)
{
    if(strcmp(this->durataContract,altCurier.durataContract)>0)
        return true;
    return false;
}



Curier::~Curier()
{
    if(this->numeCurier!=NULL)
            delete[] this->numeCurier;

    if(this->livrariInUltimeleLuni!=NULL)
        delete[] this->livrariInUltimeleLuni;
}

void Curier::setDateCurier(char dataContr[], char durataContr[])
{   
    strcpy(this->dataContract,dataContr);
    strcpy(this->durataContract,durataContr);
}
void Curier::setCodCurier(long cod){
    this->codCurier=cod;
}

void Curier::setLivrariInUltimeleLuni(int* livrari, int nrLuni){
    this->nrLuni=nrLuni;
    if(this->livrariInUltimeleLuni != NULL)
        delete[] this->livrariInUltimeleLuni;
    this->livrariInUltimeleLuni = new int[nrLuni];
    for(int i=0; i<nrLuni; i++)
        this->livrariInUltimeleLuni[i]=livrari[i];
}

char* Curier::getDataIncepereContract()
{
    return this->dataContract;
}

char* Curier::getDataFinalizareContract()
{
    return this->durataContract;
}

char* Curier::getDateCurier()
{
    strcpy(infoContract,"");
    strcat(infoContract,dataContract);
    strcat(infoContract," ");
    strcat(infoContract,durataContract);

    return this->infoContract;

    }
long Curier::getCodCurier(){
    return this->codCurier;
}

int Curier::getLivrariInUltimeleLuni(){
    int suma=0;
    for(int i=0;i<this->nrLuni;i++)
        suma+=this->livrariInUltimeleLuni[i];
    return suma;
}




Client::Client()
{
    this->nume="Anonim";
    this->prenume="Anonim";

    this->nrTelefon = new char[strlen("numarTel")+1];
    strcpy(this->nrTelefon, "numarTel");

    this->adresaLivrare = new char[strlen("adresa")+1];
    strcpy(this->adresaLivrare, "adresa");

    this->varsta=0;
    this->buget=0;
    
}

Client::Client(string nume, string prenume, char* nrTelefon, char* adresaLivrare, int varsta, float buget)
{
    this->nume=nume;
    this->prenume=prenume;

    this->nrTelefon = new char[strlen(nrTelefon)+1];
    strcpy(this->nrTelefon, nrTelefon);

    this->adresaLivrare = new char[strlen(adresaLivrare)+1];
    strcpy(this->adresaLivrare, adresaLivrare);

    this->varsta=varsta;
    this->buget=buget;
}

Client::Client(const Client& altClient)
{
    this->nume=altClient.nume;
    this->prenume=altClient.prenume;

    this->nrTelefon = new char[strlen(altClient.nrTelefon)+1];
    strcpy(this->nrTelefon, altClient.nrTelefon);

    this->adresaLivrare = new char[strlen(altClient.adresaLivrare)+1];
    strcpy(this->adresaLivrare, altClient.adresaLivrare);

    this->varsta=altClient.varsta;
    this->buget=altClient.buget;
}

Client& Client::operator=(const Client& altClient)
{
    if(this!=&altClient)
    {
        if(this->nrTelefon!=NULL)
            delete[] this->nrTelefon;
        if(this->adresaLivrare!=NULL)
            delete[] this->adresaLivrare;

        this->nume=altClient.nume;
        this->prenume=altClient.prenume;

        this->nrTelefon = new char[strlen(altClient.nrTelefon)+1];
        strcpy(this->nrTelefon, altClient.nrTelefon);

        this->adresaLivrare = new char[strlen(altClient.adresaLivrare)+1];
        strcpy(this->adresaLivrare, altClient.adresaLivrare);

        this->varsta=altClient.varsta;
        this->buget=altClient.buget;
    }
    return *this;
}

Client::~Client()
{
    if(this->adresaLivrare!=NULL)
        delete[] this->adresaLivrare;

    if(this->nrTelefon!=NULL)
        delete[] this->nrTelefon;
}

istream& operator>>(istream& in, Client& c){
    return c.citire(in);
}

ostream& operator<<(ostream& out, const Client& c){
    return c.afisare(out);
}


bool Client::operator==(const Client& altClient)
{
    if(this->buget==altClient.buget)
        return true;
    return false;
}

int Client::operator++()
{
    this->varsta++;
    return this->varsta;
}

ClientFidelDeUnAn::ClientFidelDeUnAn():Client()
{
    this->discountTier1=0;
}

ClientFidelDeUnAn::ClientFidelDeUnAn(string nume, string prenume, char* nrTelefon, char* adresaLivrare,int varsta, float buget, float discountTier1):Client(nume,prenume,nrTelefon,adresaLivrare,varsta,buget)
{
    this->discountTier1=discountTier1;
}

ClientFidelDeUnAn::ClientFidelDeUnAn(const ClientFidelDeUnAn& altClient):Client(altClient)
{
    this->discountTier1=altClient.discountTier1;
}

ClientFidelDeUnAn& ClientFidelDeUnAn::operator=(const ClientFidelDeUnAn& altClient)
{
    if(this!=&altClient)
    {
        if(this->nrTelefon!=NULL)
            delete[] this->nrTelefon;
        if(this->adresaLivrare!=NULL)
            delete[] this->adresaLivrare;

        Client::operator=(altClient);
        this->discountTier1=altClient.discountTier1;
    }
    return *this;
}

ClientFidelDeUnAn::~ClientFidelDeUnAn()
{
    if(this->nrTelefon!=NULL)
            delete[] this->nrTelefon;
    if(this->adresaLivrare!=NULL)
        delete[] this->adresaLivrare;

}


bool ClientFidelDeUnAn::operator==(const ClientFidelDeUnAn& altClient)
{
    if(this->buget==altClient.buget)
        return true;
    return false;
}

int ClientFidelDeUnAn::operator++(){
    this->varsta++;
    return this->varsta;
}



ClientFidelDe3Ani::ClientFidelDe3Ani():ClientFidelDeUnAn()
{
    for(int i=0;i<7;i++)
    {
        this->cupoanePentruComponente[i]=0;
    }
}

ClientFidelDe3Ani::ClientFidelDe3Ani(string nume, string prenume, char* nrTelefon, char* adresaLivrare,int varsta, float buget, float discountTier1,int cupoanePentruComponente[7]):ClientFidelDeUnAn(nume, prenume, nrTelefon, adresaLivrare, varsta, buget, discountTier1)
{
    for(int i=0;i<7;i++)
    {
        this->cupoanePentruComponente[i]=cupoanePentruComponente[i];
    }
}

ClientFidelDe3Ani::ClientFidelDe3Ani(const ClientFidelDe3Ani& altClient):ClientFidelDeUnAn(altClient)
{
    for(int i=0;i<7;i++)
    {
        this->cupoanePentruComponente[i]=altClient.cupoanePentruComponente[i];
    }
}

ClientFidelDe3Ani& ClientFidelDe3Ani::operator=(const ClientFidelDe3Ani& altClient)
{
    if(this!=&altClient)
    {
        if(this->nrTelefon!=NULL)
            delete[] this->nrTelefon;
        if(this->adresaLivrare!=NULL)
            delete[] this->adresaLivrare;

        ClientFidelDeUnAn::operator=(altClient);
        for(int i=0;i<7;i++)
        {
            this->cupoanePentruComponente[i]=altClient.cupoanePentruComponente[i];
        }
    }
    return *this;
}

ClientFidelDe3Ani::~ClientFidelDe3Ani()
{
    if(this->nrTelefon!=NULL)
            delete[] this->nrTelefon;
    if(this->adresaLivrare!=NULL)
        delete[] this->adresaLivrare;

}


bool ClientFidelDe3Ani::operator==(const ClientFidelDe3Ani& altClient)
{
    if(this->buget==altClient.buget)
        return true;
    return false;
}

int ClientFidelDe3Ani::operator++(){
    this->varsta++;
    return this->varsta;
}


//FUNCTII PENTRU MENIU




void metodeAngajat()
{
    int nrAng,citire,afisare,modifAng,X,Y,z;

    cout<<"Creati un obiect sau mai multe?  (1-unul  n-mai multe)"<<endl;
    cin>>nrAng;

    if(nrAng == 1)
        {
            Angajat a;
            cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
            cin>>citire;
            if(citire == 0)
            {
                a.~Angajat();
                cout<<"Obiect distrus!"<<endl;
            }
            else
            {
                cin>>a;
                cout<<endl<<"Afisati angajatul? (0-nu  1-da)"<<endl;
                cin>>afisare;

                if(afisare==0)
                {
                    a.~Angajat();
                    cout<<"Obiect distrus!";
                }
                else
                {
                    cout<<a;
                    a.~Angajat();
                }


            }

        }
        else
        {
            cout<<"Creati si cititi "<<nrAng<<" angajati"<<endl;

            Angajat arrAng[nrAng];
            int funcAng;

            for(int i=0;i<nrAng;i++)
                cin>>arrAng[i];

            cout<<"---------------------------------------------------------------"<<endl;

            cout<<"Exista cititi mai multi angajati"<<endl<<endl<<"Ii afisati sau aplicati metode?  (1-afisare  2-modificare atribute  3-functionalitate)"<<endl<<endl;
            cout<<"Aplicatia gaseste si afiseaza codurile angajatilor care lucreaza in departamentul de Asamblare de mai mult de 100 de zile si au participat la cele mai multe proiecte"<<endl;
            cin>>funcAng;

            if(funcAng == 1)
            {
                for(int i=0;i<nrAng;i++)
                    cout<<arrAng[i]<<endl;
                for(int i=0;i<nrAng;i++)
                    arrAng[i].~Angajat();

                
                cout<<"Obiectele au fost afisate si distruse!";
            }


            if(funcAng==2)
            {
                cout<<"1-Adaugarea unui numar de proiecte z la istoricul angajatului X (X<nrAng)"<<endl;
                cout<<"2-Stergerea unui numar de proiecte z din istoricul angajatului X (X<nrAng)"<<endl;
                cout<<"3-Verificare daca angajatul X are mai multe proiecte realizate decat angajatul Y (X,Y < nrAng)"<<endl;
                cout<<"4-Aflarea diferentei de proiecte realizate dintre angajatul X si angajatul Y"<<endl;
                cout<<"---------------------------------------------------------------"<<endl;

                while(true)
                {
                    cout<<"Alegeti ce modificati: "<<endl;
                    cin>>modifAng;
                    if(modifAng==1) 
                    {
                        cout<<"Cate proiecte adaugati la angajatul X?  (introduceti X si numarul de proiecte)"<<endl;
                        cin>>X>>z;
                        arrAng[X].setNrTotalProiecte((arrAng[X]+z).getNrTotalProiecte());

                        cout<<"Noul numar de proiecte pentru angajat este "<<arrAng[X].getNrTotalProiecte()<<endl;
                    }
                        
                    if(modifAng==2)
                    {
                        cout<<"Cate proiecte stergeti de la angajatul X?  (introduceti X si numarul de proiecte)"<<endl;
                        cin>>X>>z;
                        arrAng[X].setNrTotalProiecte((arrAng[X]-z).getNrTotalProiecte());

                        cout<<"Noul numar de proiecte pentru angajat este "<<arrAng[X].getNrTotalProiecte()<<endl;
                    }

                    if(modifAng==3)
                    {
                        cout<<"Cititi angajatul X si angajatul Y"<<endl;
                        cin>>X>>Y;
                        if(arrAng[X] > arrAng[Y])
                            cout<<"Angajatul cu ID-ul "<<arrAng[X].getIdAngajat()<<" are mai multe proiecte realizate"<<endl;
                        else if(arrAng[Y] > arrAng[X])
                            cout<<"Angajatul cu ID-ul "<<arrAng[X].getIdAngajat()<<" are mai putine proiect realizate"<<endl;
                        else if(arrAng[X] == arrAng[Y])
                            cout<<"Angajatii "<<arrAng[X].getIdAngajat()<<" si "<<arrAng[Y].getIdAngajat()<<" au realizat la fel de multe proiecte"<<endl;
                    }

                    if(modifAng==4)
                    {
                        cout<<"Cititi angajatul X si angajatul Y"<<endl;
                        cin>>X>>Y;
                        cout<<"Diferenta de proiecte dintre cei doi angajati este: "<<(arrAng[X]-arrAng[Y]).getNrTotalProiecte()<<endl;
                    }

                    if(modifAng != 1 && modifAng != 2 && modifAng != 3 && modifAng != 4)
                    {
                        cout<<"Treceti la functionalitate? (3-da)"<<endl;
                        cin>>funcAng;
                        break;


                    }

                }
                
            }

            if(funcAng==3) //pentru cei angajati de mai mult de 100 de zile la departamentul de Asamblare, sa se afiseze ID-urile celor care au participat la cele mai multre proiecte
            {
                cout<<"---------------------------------------------------------------"<<endl;
                int max=-1;
                for(int i=0;i<nrAng;i++)
                    if(arrAng[i].getZileDeLaAngajare()>100 && strcmp(arrAng[i].getFunctieDepartament(),"Asamblare")==0)
                        if(arrAng[i].getNrTotalProiecte()>max)
                            max=arrAng[i].getNrTotalProiecte();
                
                for(int i=0;i<nrAng;i++)
                    if(arrAng[i].getZileDeLaAngajare()>100 && arrAng[i].getNrTotalProiecte()==max && strcmp(arrAng[i].getFunctieDepartament(),"Asamblare")==0)
                        cout<<"Angajatul cu cele mai multe proiecte are Id-ul: "<<arrAng[i].getIdAngajat()<<" ";


                for(int i=0;i<nrAng;i++)
                    arrAng[i].~Angajat();

            }

        }
}


void metodeSistem()
{

    int nrSis,citire,afisare,modifSis,X,Y,Z,tipSistem, tipSisteme;

    cout<<"Creati un obiect sau mai multe?  (1-unul  n-mai multe)"<<endl;
    cin>>nrSis;

    if(nrSis == 1)
        {
            cout<<"Ce tip de sistem creati?"<<endl;
            cout<<"1-Nespecificat"<<endl<<"2-Cu racire pe aer"<<endl<<"3-Cu racire pe lichid"<<endl<<"4-Cu racire hibrida"<<endl;
            
            cin>>tipSistem;

            if(tipSistem==1)
            {
                Sistem s;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    s.~Sistem();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>s;
                    cout<<endl<<"Afisati sistemul? (0-nu  1-da)"<<endl;
                    cin>>afisare;

                    if(afisare==0)
                    {
                        s.~Sistem();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<s;
                        s.~Sistem();
                    }


                }

            }

            else if(tipSistem==2)
            {

                SistemRacireAer s;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    s.~SistemRacireAer();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>s;
                    cout<<endl<<"Afisati sistemul? (0-nu  1-da)"<<endl;
                    cin>>afisare;

                    if(afisare==0)
                    {
                        s.~SistemRacireAer();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<s;
                        s.~SistemRacireAer();
                    }


                }
            }

            else if(tipSistem==3)
            {

                SistemRacireLichid s;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    s.~SistemRacireLichid();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>s;
                    cout<<endl<<"Afisati sistemul? (0-nu  1-da)"<<endl;
                    cin>>afisare;

                    if(afisare==0)
                    {
                        s.~SistemRacireLichid();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<s;
                        s.~SistemRacireLichid();
                    }


                }
            }

            else if(tipSistem==4)
            {

                SistemRacireHibrida s;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    s.~SistemRacireHibrida();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>s;
                    cout<<endl<<"Afisati sistemul? (0-nu  1-da)"<<endl;
                    cin>>afisare;

                    if(afisare==0)
                    {
                        s.~SistemRacireHibrida();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<s;
                        s.~SistemRacireHibrida();
                    }


                }
            }

            

        }
        else
        {

            cout<<"Creati sisteme normale sau hibride?"<<endl;
            cout<<"1-Normale"<<endl<<"2-Hibride"<<endl;

            cin>>tipSisteme;

            if(tipSisteme==1)
            {

                cout<<"Creati si cititi "<<nrSis<<" sisteme"<<endl;

                Sistem arrSis[nrSis];
                int funcSis;

                for(int i=0;i<nrSis;i++)
                    cin>>arrSis[i];

                cout<<"---------------------------------------------------------------"<<endl;

                cout<<"Exista citite mai multe sisteme"<<endl<<endl<<"Le afisati sau aplicati metode?  (1-afisare 2-modificare atribute  3-functionalitate)"<<endl<<endl;
                cout<<"Aplicatia identifica numele clientilor care au avut cel mai mare buget pentru sistemele cerute"<<endl;
                cin>>funcSis;

                if(funcSis == 1)
                {
                    for(int i=0;i<nrSis;i++)
                        cout<<arrSis[i]<<endl;
                    for(int i=0;i<nrSis;i++)
                        arrSis[i].~Sistem();

                    
                    cout<<"Obiectele au fost afisate si distruse!";
                }


                if(funcSis==2)
                {
                    cout<<"1-Afisati pretul componentei Z a sistemului X citit (doar pentru comenzile cu minim 7 componente) "<<endl;
                    cout<<"2-Cresteti bugetul pentru sistemul X cu Z (doar pentru comenzile cu minim 7 componente)"<<endl;
                    cout<<"3-Combinati echipa asociata sistemului X cu cea a sistemului Y (doar pentru comenzile cu minim 7 componente)"<<endl;
                    cout<<"4-Verificati daca sistemul X a avut acelasi buget ca sistemul Y"<<endl;
                    cout<<"---------------------------------------------------------------"<<endl;


                    while (true)
                    {
                        cout<<"Ce modificati?"<<endl;
                        cin>>modifSis;

                        if(modifSis==1)
                        {
                            cout<<"Introduceti Sistemul X si indexul Z al componentei  (0-gpu 1-cpu  2-mobo  3-ram  4-hdd/ssd  5-psu  6-case)"<<endl;
                            cin>>X>>Z;

                            if(Z==0) //gpu
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul placii video "<<arrSis[X][Z]<<endl;


                            if(Z==1)//cpu
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul procesorului "<<arrSis[X][Z]<<endl;


                            if(Z==2)//mobo
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul placii de baza "<<arrSis[X][Z]<<endl;


                            if(Z==3)//ram
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul RAM-ului "<<arrSis[X][Z]<<endl;


                            if(Z==4)//hdd/ssd
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul unitatii de stocare "<<arrSis[X][Z]<<endl;


                            if(Z==5)//psu
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul sursei "<<arrSis[X][Z]<<endl;


                            if(Z==6)//case
                                cout<<"Sistemul cu numarul "<<arrSis[X].getNrComanda()<<" are pretul carcasei "<<arrSis[X][Z]<<endl;


                        }

                        if(modifSis==2)
                        {
                            cout<<"Introduceti sistemul X si valoarea cu care modificati Z"<<endl;
                            cin>>X>>Z;

                            cout<<"Noul buget pentru sistem este "<<(arrSis[X]+Z).getBuget()<<endl;
                            arrSis[X].setBuget((arrSis[X]+Z).getBuget());
                            

                        }

                        if(modifSis==3)
                        {
                            cout<<"Introduceti sistemele X si Y"<<endl;
                            cin>>X>>Y;

                            cout<<"Noua echipa pentru sistem este formata din "<<(arrSis[X]+arrSis[Y]).getMembriiEchipa()<<" membrii"<<endl;
                            arrSis[X].setMembriiEchipa((arrSis[X]+arrSis[Y]).getMembriiEchipa());

                        }

                        if(modifSis==4)
                        {
                            cout<<"Introduceti sistemele X si Y"<<endl;
                            cin>>X>>Y;

                            if(arrSis[X] == arrSis[Y])
                                cout<<"Sistemul cu numarul comenzii "<<arrSis[X].getNrComanda()<<" a avut acelasi buget alocat ca sistemul cu numarul comenzii "<<arrSis[Y].getNrComanda()<<endl;
                            else
                                cout<<"Cele 2 sisteme nu au acelasi buget"<<endl;
                        }

                        if(modifSis != 1 && modifSis != 2 && modifSis !=3 && modifSis !=4)
                            {
                                cout<<"Treceti la functionalitate? (3-da)"<<endl;
                                cin>>funcSis;
                                break;
                            }

                    }
                    

                }



                if(funcSis==3)// pentru toate sistemele existente, se afis numele clientului care a avut cel mai mare buget
                {
                    cout<<"---------------------------------------------------------------"<<endl;
                    double max=-1;
                    for(int i=0;i<nrSis;i++)
                        if(arrSis[i].getBuget() > max)
                            max=arrSis[i].getBuget();
                    
                    for(int i=0;i<nrSis;i++)
                        if(arrSis[i].getBuget()==max)
                            cout<<"Comanda care a avut cel mai mare buget a fost "<<arrSis[i].getNrComanda()<<" pe numele "<<arrSis[i].getNumeClient();

                }
            }

            else if(tipSisteme==2)
            {
                cout<<"Creati si cititi "<<nrSis<<" sisteme hibride"<<endl;

                SistemRacireHibrida arrSis[nrSis];
                int funcSis;

                for(int i=0;i<nrSis;i++)
                    cin>>arrSis[i];

                cout<<"---------------------------------------------------------------"<<endl;

                cout<<"Exista citite mai multe sisteme"<<endl<<endl<<"Le afisati sau aplicati metode?  (1-afisare 2-modificare atribute  3-functionalitate)"<<endl<<endl;
                cout<<"Aplicatia identifica numele clientilor care au avut cel mai mare buget pentru sistemele cerute"<<endl;
                cin>>funcSis;

                if(funcSis == 1)
                {
                    for(int i=0;i<nrSis;i++)
                        cout<<arrSis[i]<<endl;
                    for(int i=0;i<nrSis;i++)
                        arrSis[i].~Sistem();

                    
                    cout<<"Obiectele au fost afisate si distruse!";
                }

                if(funcSis==2)
                {
                    cout<<"1-Cresteti capacitatea rezervorului cu un litru pentru un sistem"<<endl;
                    cout<<"2-Imbunatatiti pompa radiatorului"<<endl;
                    cout<<"3-Comparati numarul de ventilatoare dintre 2 sisteme"<<endl;
                    cout<<"---------------------------------------------------------------"<<endl;

                    while(true)
                    {
                        cout<<"Ce modificati?"<<endl;
                        cin>>modifSis;

                        if(modifSis==1)
                        {
                            cout<<"Introduceti sistemul X: ";
                            cin>>X;

                            cout<<"Noua capacitate a rezervorului este de "<<(++arrSis[X]).getCapacitateRezervor()<<" litrii"<<endl;
                        }

                        if(modifSis==2)
                        {
                            cout<<"Introduceti sistemul X si valoarea Z cu care imbunatatiti: ";
                            cin>>X>>Z;

                            cout<<"Noua viteza a pompei radiatorului este de "<<(arrSis[X]+Z).getVitezaPompa()<<" RPM"<<endl;
                        }

                        if(modifSis==3)
                        {
                            cout<<"Introduceti sistemele X si Y";
                            cin>>X>>Y;

                            if(arrSis[X] > arrSis[Y])
                                cout<<"Sistemul cu numarul comenzii "<<arrSis[X].getNrComanda()<<" are in componenta mai multe ventilatoare"<<endl;
                            else
                                cout<<"Sistemul cu numarul comenzii "<<arrSis[Y].getNrComanda()<<" are in componenta mai multe ventilatoare"<<endl;

                        }

                        if(modifSis != 1 && modifSis != 2 && modifSis !=3)
                            {
                                cout<<"Treceti la functionalitate? (3-da)"<<endl;
                                cin>>funcSis;
                                break;
                            }

                    }
                }

                if(funcSis==3)
                {

                    cout<<"---------------------------------------------------------------"<<endl;
                    double max=-1;
                    for(int i=0;i<nrSis;i++)
                        if(arrSis[i].getBuget() > max)
                            max=arrSis[i].getBuget();
                    
                    for(int i=0;i<nrSis;i++)
                        if(arrSis[i].getBuget()==max)
                            cout<<"Comanda care a avut cel mai mare buget a fost "<<arrSis[i].getNrComanda()<<" pe numele "<<arrSis[i].getNumeClient();

                }

            }

            

        }


}

void metodeDep()
{
    int nrDep,citire,afisare,X,Y,Z,modDep, tipDepartament, tipDepartamente;

    cout<<"Creati un obiect sau mai multe?  (1-unul  n-mai multe)"<<endl;
    cin>>nrDep;

    if(nrDep == 1)
        {
            cout<<"Ce tip de departament creati?"<<endl;
            cout<<"1-Nespecificat"<<endl<<"2-De asamblare speciala"<<endl;

            cin>>tipDepartament;

            if(tipDepartament==1)
            {
                Departament d;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    d.~Departament();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>d;
                    cout<<endl<<"Afisati departamentul? (0-nu  1-da)";
                    cin>>afisare;

                    if(afisare==0)
                    {
                        d.~Departament();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<d;
                        d.~Departament();
                    }


                }
                
            }

            else if(tipDepartament==2)
            {
                DepartamentAsamblarePremium d;
                cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
                cin>>citire;
                if(citire == 0)
                {
                    d.~DepartamentAsamblarePremium();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cin>>d;
                    cout<<endl<<"Afisati departamentul? (0-nu  1-da)";
                    cin>>afisare;

                    if(afisare==0)
                    {
                        d.~DepartamentAsamblarePremium();
                        cout<<"Obiect distrus!";
                    }
                    else
                    {
                        cout<<d;
                        d.~DepartamentAsamblarePremium();
                    }


                }
            }

            

        }
        else
        {
            cout<<"Creati departamente normale sau de asamblare speciala?"<<endl;
            cout<<"1-Normale"<<endl<<"2-Asamblare"<<endl;

            cin>>tipDepartamente;

            if(tipDepartamente==1)
            {
                cout<<"Creati si cititi "<<nrDep<<" departamente"<<endl;

                Departament arrDep[nrDep];
                int funcDep;

                for(int i=0;i<nrDep;i++)
                    cin>>arrDep[i];

                cout<<"---------------------------------------------------------------"<<endl;

                cout<<"Exista citite mai multe departamente"<<endl<<endl<<"Le afisati sau aplicati metode?  (1-afisare  2-modificare atribute)"<<endl;
                cin>>funcDep;

                if(funcDep == 1)
                {
                    for(int i=0;i<nrDep;i++)
                        cout<<arrDep[i]<<endl;
                    for(int i=0;i<nrDep;i++)
                        arrDep[i].~Departament();

                    
                    cout<<"Obiectele au fost afisate si distruse!";
                }

                if(funcDep==2)
                {

                    cout<<"1. Adaugati un angajat A la departamentul X"<<endl;
                    cout<<"2. Scadeti un numar Z de angajati din departamentul X"<<endl;
                    cout<<"3. Verificati daca departamentul X are acelasi nr de angajati ca departamentul Y"<<endl;
                    cout<<"4. Verificati daca departamentul X are mai multi angajati decat departamentul Y"<<endl;
                    cout<<"---------------------------------------------------------------"<<endl;


                    while(true)
                    {
                        cout<<"Ce modificati?"<<endl;
                        cin>>modDep;
                        if(modDep==1)
                        {
                            Angajat A;
                            cout<<"Inregistrati angajatul: "<<endl;

                            cin>>A;

                            cout<<"Introduceti departamentul X unde adaugati angajatul inregistrat "<<endl;
                            cin>>X;

                            cout<<endl;
                            cout<<A+arrDep[X];

                            // cout<<"Noul numar de angajati din departamentul "<<arrDep[X].getNumeDepartament()<<" este "<<(A+arrDep[X]).getNrAngajati()<<endl;
                            // arrDep[X].setNrAngajati((A+arrDep[X]).getNrAngajati());


                        }

                        if(modDep==2)
                        {
                            cout<<"Introduceti departamentul X si nr Z"<<endl;
                            cin>>X>>Z;

                            cout<<"Noul numar de angajati din departamentul "<<arrDep[X].getNumeDepartament()<<" este"<<(arrDep[X]-Z).getNrAngajati()<<endl;
                            arrDep[X].setNrAngajati((arrDep[X]-Z).getNrAngajati());
                            
                        }

                        if(modDep==3)
                        {
                            cout<<"Introduceti departamentele X si Y"<<endl;
                            cin>>X>>Y;
                            if(arrDep[X]==arrDep[Y])
                                cout<<"Departamentele "<<arrDep[X].getNumeDepartament()<<" si "<<arrDep[Y].getNumeDepartament()<<" au acelasi nr de angajati"<<endl;
                            else
                                cout<<"Departamentele "<<arrDep[X].getNumeDepartament()<<" si "<<arrDep[Y].getNumeDepartament()<<"nu au acelasi nr de angajati"<<endl;

                        }

                        if(modDep==4)
                        {
                            cout<<"Introduceti departamentele X si Y"<<endl;
                            cin>>X>>Y;
                            if(arrDep[X]>arrDep[Y])
                                cout<<"Departamentul "<<arrDep[X].getNumeDepartament()<<" are mai multi angajati decat "<<arrDep[Y].getNumeDepartament()<<endl;
                            else
                                cout<<"Departamentul "<<arrDep[X].getNumeDepartament()<<" nu are mai multi angajati decat "<<arrDep[Y].getNumeDepartament()<<endl;
                            
                        }

                        if(modDep!=1 && modDep!=2 && modDep!=3 && modDep!=4){
                            break;
                        }
                    }

                }


            }
            else if(tipDepartamente==2)
            {
                cout<<"Creati si cititi "<<nrDep<<" departamente de asamblare"<<endl;

                DepartamentAsamblarePremium arrDep[nrDep];

                int funcDep;

                for(int i=0;i<nrDep;i++)
                    cin>>arrDep[i];

                cout<<"---------------------------------------------------------------"<<endl;

                cout<<"Exista citite mai multe departamente"<<endl<<endl<<"Le afisati sau aplicati metode?  (1-afisare 2-modificare atribute  3-functionalitate)"<<endl<<endl;
                cout<<"Aplicatia afiseaza numele departamentului cu cele mai multe comenzi primite lunar"<<endl;

                cin>>funcDep;

                if(funcDep == 1)
                {
                    for(int i=0;i<nrDep;i++)
                        cout<<arrDep[i]<<endl;
                    for(int i=0;i<nrDep;i++)
                        arrDep[i].~DepartamentAsamblarePremium();

                    
                    cout<<"Obiectele au fost afisate si distruse!";
                }

                if(funcDep==2)
                {
                    cout<<"1-Verificati stocul de licente si flash-uri BIOS"<<endl;
                    cout<<"2-Adaugati o noua comanda pentru studiouri"<<endl;
                    cout<<"3-Imbinati echipele din doua departamente"<<endl;
                    cout<<"------------------------------------------------------------"<<endl;

                    while(true)
                    {
                        cout<<"Ce modificati?"<<endl;
                        cin>>modDep;

                        if(modDep==1)
                        {
                            cout<<"Introduceti departamentul X unde verificati stocul"<<endl;
                            cin>>X;
                            cout<<"In departamentul "<<arrDep[X].getNumeDepartament()<<" sunt "<<arrDep[X].getLicente()<<" chei de licenta si "<<arrDep[X].getBIOS()<<" flash-uri de BIOS"<<endl;

                        }

                        if(modDep==2)
                        {
                            cout<<"Introduceti departamentul X unde adaugati comanda"<<endl;
                            cin>>X;

                            cout<<"Departamentul "<<arrDep[X].getNumeDepartament()<<" are "<<(++arrDep[X]).getComenziStudio()<<" comenzi pentru studiouri"<<endl;

                        }

                        if(modDep==3)
                        {
                            cout<<"Introduceti departamentele X si Y"<<endl;
                            cin>>X>>Y;

                            cout<<"Noul numar total de angajati este "<<(arrDep[X] + arrDep[Y]).getNrAngajati()<<endl;

                        }

                        if(modDep!=1 && modDep!=2 && modDep !=3)
                        {
                            cout<<"Treceti la functionalitate? (3-da)"<<endl;
                            cin>>funcDep;
                            break;
                        }
                    }
                }

                if(funcDep==3)
                {
                    cout<<"---------------------------------------------------------------"<<endl;
                    int max=-1;
                    for(int i=0;i<nrDep;i++)
                        if(arrDep[i].getNrAngajati() > max)
                            max=arrDep[i].getNrAngajati();
                    for(int i=0;i<nrDep;i++)
                        if(arrDep[i].getNrAngajati() == max)
                            cout<<"Departamentul "<<arrDep[i].getNumeDepartament()<<" are "<<arrDep[i].getNrAngajati()<<" angajati"<<endl;
                }

            }


            

        }
}


void metodeCurier()
{
    int nrCurier,citire,afisare,X,Y,Z,modCurier;

    cout<<"Creati un obiect sau mai multe?  (1-unul  n-mai multe)"<<endl;
    cin>>nrCurier;

    if(nrCurier == 1)
        {
            Curier c;
            cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu   1-da)"<<endl;
            cin>>citire;
            if(citire == 0)
            {
                c.~Curier();
                cout<<"Obiect distrus!"<<endl;
            }
            else
            {
                cin>>c;
                cout<<endl<<"Afisati curierul? (0-nu  1-da)"<<endl;
                cin>>afisare;

                if(afisare==0)
                {
                    c.~Curier();
                    cout<<"Obiect distrus!";
                }
                else
                {
                    cout<<c;
                    c.~Curier();
                }


            }

        }
        else
        {
            cout<<"Creati si cititi "<<nrCurier<<" curieri"<<endl;

            Curier arrC[nrCurier];
            int funcCurier;

            for(int i=0;i<nrCurier;i++)
                cin>>arrC[i];

            cout<<"---------------------------------------------------------------"<<endl;

            cout<<"Exista cititi mai multi curieri"<<endl<<"Ii afisati sau aplicati metode?  (1-afisare  2-modificare atribute  3-functionalitate)"<<endl;
            cout<<"Aplicatia afiseaza codurile curierilor care isi termina contractul pe aceeasi data"<<endl;
            cin>>funcCurier;

            if(funcCurier == 1)
            {
                for(int i=0;i<nrCurier;i++)
                    cout<<arrC[i]<<endl;
                for(int i=0;i<nrCurier;i++)
                    arrC[i].~Curier();

                
                cout<<"Obiectele au fost afisate si distruse!";
            }

            if(funcCurier==2)
            {
                cout<<"1. Adaugati o luna la contractul curierului X"<<endl;
                cout<<"2. Scurtati contractul curierului X cu o luna"<<endl;
                cout<<"3. Pentru curierii X si Y aflati diferenta de livrari in ultimele luni"<<endl;
                cout<<"4. Pentru curierul X, aflati cate livrari a efectuat acum Z luni"<<endl;
                cout<<"---------------------------------------------------------------"<<endl;

                while(true)
                {
                    cout<<"Ce modificati?"<<endl;
                    cin>>modCurier;

                    if(modCurier==1)
                    {
                        cout<<"Introduceti curierul X"<<endl;
                        cin>>X;

                        cout<<"Noua data pentru finalizarea contractului este "<<(++arrC[X]).getDataFinalizareContract()<<endl;
                        arrC[X].setDateCurier(arrC[X].getDataIncepereContract() , (arrC[X]++).getDataFinalizareContract());
                    }

                    if(modCurier==2)
                    {
                        cout<<"Introduceti curierul X"<<endl;
                        cin>>X;

                        cout<<"Noua data pentru finalizarea contractului este "<<(--arrC[X]).getDataFinalizareContract()<<endl;
                        arrC[X].setDateCurier(arrC[X].getDataIncepereContract() , (arrC[X]--).getDataFinalizareContract());
                    }

                    if(modCurier==3)
                    {
                        cout<<"Introduceti curierii X si Y"<<endl;
                        cin>>X>>Y;

                        cout<<"Diferenta de livrari dintre curierul cu codul "<<arrC[X].getCodCurier()<<" si "<<arrC[Y].getCodCurier()<<" este "<<(arrC[X]-arrC[Y]).getLivrariInUltimeleLuni()<<endl;
                        
                    }

                    if(modCurier==4)
                    {
                        cout<<"Introduceti curierul X si luna Z"<<endl;
                        cin>>X>>Z;

                        cout<<"Acum "<<Z<<" luni "<<"curierul cu codul "<<arrC[X].getCodCurier()<<" a efectuat "<<arrC[X][Z]<<" livrari"<<endl;
                        
                    }

                    if(modCurier != 1 && modCurier != 2 && modCurier != 3 && modCurier != 4)
                    {
                        cout<<"Treceti la functionalitate? (3-da)"<<endl;
                        cin>>funcCurier;

                        break;
                    }
                }
            }



            if(funcCurier==3)// se afiseaza codurile curierilor care isi termina contractul pe aceeasi data
            {

                cout<<"---------------------------------------------------------------"<<endl;

                for(int i=0;i<nrCurier-1;i++)
                    for(int j=i+1;j<nrCurier;j++)
                    {
                        if(strcmp(arrC[i].getDataFinalizareContract(),arrC[j].getDataFinalizareContract())==0)
                            cout<<"Curierii "<<arrC[i].getCodCurier()<<" si "<<arrC[j].getCodCurier()<<" isi termina contractul pe aceeasi data";
                    }
                cout<<endl<<endl;

                for(int i=0;i<nrCurier;i++)
                    arrC[i].~Curier();

            }

        }
}


void metodeClient()
{
    int nrClient,tipClient,citireClient,afisareClient,tipClienti, funcClient,modClient,X,Y,Z;

    cout<<"Creati un obiect sau mai multe? (1-unul  n-mai multe)"<<endl;
    cin>>nrClient;

    if(nrClient==1)
    {
        cout<<"Ce tip de client inregistrati?"<<endl;
        cout<<"1-Fidelitate de un an"<<endl<<"2-Fidelitate de 3 ani"<<endl;

        cin>>tipClient;

        if(tipClient==1)
        {
            ClientFidelDeUnAn c;

            cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu  1-da)"<<endl;

            cin>>citireClient;

            if(citireClient==0)
            {
                c.~ClientFidelDeUnAn();
                cout<<"Obiect distrus!"<<endl;   
            }
            else
            {
                cin>>c;
                cout<<endl<<"Afisati clientul?  (0-nu   1-da)"<<endl;
                cin>>afisareClient;

                if(afisareClient==0)
                {
                    c.~ClientFidelDeUnAn();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cout<<c;
                    c.~ClientFidelDeUnAn();
                }
            }
        }
        else if(tipClient==2)
        {
            ClientFidelDe3Ani c;

            cout<<"Obiect creat!"<<endl<<"Cititi obiectul? (0-nu  1-da)"<<endl;

            cin>>citireClient;

            if(citireClient==0)
            {
                c.~ClientFidelDe3Ani();
                cout<<"Obiect distrus!"<<endl;   
            }
            else
            {
                cin>>c;
                cout<<endl<<"Afisati clientul?  (0-nu   1-da)"<<endl;
                cin>>afisareClient;

                if(afisareClient==0)
                {
                    c.~ClientFidelDe3Ani();
                    cout<<"Obiect distrus!"<<endl;
                }
                else
                {
                    cout<<c;
                    c.~ClientFidelDe3Ani();
                }
            }

        }
    }
    else
    {
        cout<<"Creati si cititi "<<nrClient<<" clienti"<<endl;

        Client* listaClienti[nrClient];

        int evidentaClienti[nrClient];

        for(int i=0;i<nrClient;i++)
        {
            cout<<"Ce tip de client inregistrati?"<<endl;
            cout<<"1-Fidelitate de un an"<<endl<<"2-Fidelitate de 3 ani"<<endl;

            cin>>tipClienti;
            if(tipClienti==1)
            {
                listaClienti[i] = new ClientFidelDeUnAn();
                evidentaClienti[i]=1;
                cin>>*listaClienti[i];
            }


            else if(tipClienti==2)
            {
                listaClienti[i] = new ClientFidelDe3Ani();
                evidentaClienti[i]=2;
                cin>>*listaClienti[i];
            }
        }

        cout<<"---------------------------------------------------------------"<<endl;

        cout<<"Exista cititi mai multi clienti"<<endl<<"Ii afisati sau aplicati metode?  (1-afisare  2-modificare atribute)"<<endl;
        // cout<<""<<endl;
        cin>>funcClient;

        if(funcClient == 1)     
        {
            for(int i=0;i<nrClient;i++)
                cout<<*listaClienti[i]<<endl;

            
            cout<<"Obiectele au fost afisate!";
        }

        if(funcClient==2)
        {
            cout<<"-----1.-----"<<endl;
            cout<<"|"<<endl;
            cout<<"--->";
            cout<<"Pentru clientii fideli de un an, aplicatia le afla bugetul alocat pentru o comanda, fara reduceri"<<endl;
            cout<<"|"<<endl;
            cout<<"--->";
            cout<<"Pentru clientii fideli de 3+ ani, aplicatia calculeaza totalul de cupoane al clientului"<<endl<<endl;

            cout<<"-----2-----"<<endl;
            cout<<"|"<<endl;
            cout<<"--->";
            cout<<"Pentru clientii fideli de un an, aplicatia le creste bugetul, cu un procentaj"<<endl;
            cout<<"|"<<endl;
            cout<<"--->";
            cout<<"Pentru clientii fideli de 3+ ani,aplicatia le creste bugetul, cu un procentaj cu 10% mai mare"<<endl<<endl;

            cout<<"-----3-----"<<endl<<"Cresteti varsta unui client cu un an"<<endl<<endl;

            cout<<"-----4-----"<<endl<<"Pentru 2 clienti cu acelasi grad de fidelitate, aflati daca au acelasi buget"<<endl;


            while(true)
            {
                cout<<"Ce accesati?"<<endl;
                cin>>modClient;

                if(modClient==1)
                {
                    cout<<"Introduceti clientul X"<<endl;
                    cin>>X;

                    listaClienti[X]->metodaClient();

                }
                
                if(modClient==2)
                {
                    cout<<"Introduceti clientul X si discountul Z"<<endl;
                    cin>>X>>Z;

                    listaClienti[X]->modificareBugetCuDiscount(Z);

                }

                if(modClient==3)
                {
                    cout<<"Introduceti clientul X"<<endl;
                    cin>>X;

                    cout<<"Noua varsta a clientului este "<<(++*listaClienti[X])<<endl;
                }

                if(modClient==4)
                {
                    cout<<"Introduceti clientii X si Y"<<endl;
                    cin>>X>>Y;

                    if(evidentaClienti[X] == evidentaClienti[Y])
                    {
                        if(listaClienti[X] != listaClienti[Y])
                            cout<<"Clientii au acelasi buget"<<endl;
                        else
                            cout<<"Clientii nu au acelasi buget"<<endl;
                    }
                    else
                    {
                        cout<<"Clientii nu sunt de acelasi tip"<<endl;
                    }
                }

                if(modClient!=1 && modClient!=2 && modClient!=3 && modClient!=4){
                    break;
                }
            }
        }
    }
}



void meniuAngajat()
{
    int optAng;
    cout<<"Accesati metodele clasei? (1-da  else-nu)"<<endl;

    cin>>optAng;

    if(optAng==1)
        metodeAngajat();
    else
        cout<<"Meniu inchis";
}


void meniuSistem()
{
    int optSis;
    cout<<"Accesati metodele clasei? (1-da  else-nu)"<<endl;

    cin>>optSis;

    if(optSis==1)
        metodeSistem();
    else
        cout<<"Meniu inchis";
}



void meniuDepartament()
{
    int optDep;
    cout<<"Accesati metodele clasei? (1-da  else-nu)"<<endl;

    cin>>optDep;

    if(optDep==1)
        metodeDep();
    else
        cout<<"Meniu inchis";
}

void meniuCurier()
{
    int optCurier;
    cout<<"Accesati metodele clasei? (1-da  else-nu)"<<endl;

    cin>>optCurier;

    if(optCurier==1)
        metodeCurier();
    else
        cout<<"Meniu inchis";
}



void meniuClient()
{
    int optClient;
    cout<<"Accesati metodele clasei? (1-da  else-nu)"<<endl;

    cin>>optClient;

    if(optClient==1)
        metodeClient();
    else
        cout<<"Meniu inchis";

}


int main()
{
    int optiune;
    cout<<"Pentru ce clasa efectuati operatii?"<<endl;
    cout<<"1-Angajat"<<endl<<"2-Sistem"<<endl<<"3-Departament"<<endl<<"4-Curier"<<endl<<"5-Client"<<endl;
    cin>>optiune;
    

    if(optiune==1) meniuAngajat();
    if(optiune==2) meniuSistem();
    if(optiune==3) meniuDepartament();
    if(optiune==4) meniuCurier();
    if(optiune==5) meniuClient();
    if(optiune != 1 && optiune != 2 && optiune != 3 && optiune != 4 && optiune != 5)
        cout<<"Numar introdus gresit.";

    return 0;
}