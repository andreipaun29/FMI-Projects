package Rezervare;
import java.util.Arrays;
import java.util.Scanner;
public class RezervareBusinessFaraBagaj extends Rezervare{

    public RezervareBusinessFaraBagaj(int nrLocuri, int index, float pretTotal, int idPasager) {
        super(nrLocuri, index, pretTotal, idPasager);
    }

    public RezervareBusinessFaraBagaj() {
        super();
    }

    @Override
    public void afisare() {
        //generate a random seat number that starts with index

        String seats[]  = new String[this.nrLocuri];
        String randomSeat = "";

        for(int i = 0; i < this.nrLocuri; i++){
            randomSeat = "";
            //random id from 3 chars [A-Z]
            randomSeat += (char) (65 + (int) (Math.random() * 26));
            //check if the seat is already taken

            randomSeat += (int) (Math.random() * 10);
            randomSeat = this.index + "-" + randomSeat;

            seats[i] = randomSeat;

        }



        System.out.println("Rezervare la clasa de business (fara bagaj)" +
                "\n Numar de locuri:" + nrLocuri +
                "\nLocurile rezervate sunt: " + Arrays.toString(seats) +
                "\n idPasager=" + idPasager
        );
    }

    @Override
    public float calculeazaPretTotal(float pretBilet)    {
        return (float) (pretBilet*1.2 + this.nrLocuri * 5);
    }


    @Override
    public void citesteDate() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Introduceti numarul de locuri:");
        this.nrLocuri = scanner.nextInt();

        System.out.println("Introduceti indexul:");
        this.index = scanner.nextInt();

    }
}
