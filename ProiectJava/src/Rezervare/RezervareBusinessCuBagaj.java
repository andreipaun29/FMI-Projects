package Rezervare;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Arrays;

public class RezervareBusinessCuBagaj extends Rezervare{

    private int nrBagaje;

    public RezervareBusinessCuBagaj(int nrLocuri, int index, float pretTotal, int idPasager, int nrBagaje) {
        super(nrLocuri, index, pretTotal, idPasager);
        this.nrBagaje = nrBagaje;
    }

    public RezervareBusinessCuBagaj() {
        super();
        this.nrBagaje = 0;
    }

    public int getNrBagaje() {
        return nrBagaje;
    }

    public void setNrBagaje(int nrBagaje) {
        this.nrBagaje = nrBagaje;
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



        System.out.println("Rezervare la clasa de business (bagaj)\n" +
                "Numar de bagaje: " + nrBagaje +
                "\n Numar de locuri:" + nrLocuri +
                "\nLocurile rezervate sunt: " + Arrays.toString(seats) +
                "\n idPasager=" + idPasager
                );
    }


    @Override
    public float calculeazaPretTotal(float pretBilet)    {
        return (float) (pretBilet*1.2 + this.nrBagaje * 10 + this.nrLocuri * 5);
    }

    @Override
    public void citesteDate(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Introduceti numarul de bagaje:");
        this.nrBagaje = scanner.nextInt();

        System.out.println("Introduceti numarul de locuri:");
        this.nrLocuri = scanner.nextInt();

        System.out.println("Introduceti randul dorit:");
        this.index = scanner.nextInt();

    }



}
