package Rezervare;
import java.util.Arrays;
import java.util.Scanner;
public class RezervareEconomicCuBagaj extends Rezervare {

    private int nrBagaje;

    public RezervareEconomicCuBagaj(int nrLocuri, int index, float pretTotal, int idPasager, int nrBagaje) {
        super(nrLocuri, index, pretTotal, idPasager);
        this.nrBagaje = nrBagaje;
    }

    public RezervareEconomicCuBagaj() {
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



        System.out.println("Rezervare la clasa economica (bagaj)\n" +
                "Numar de bagaje: " + nrBagaje +
                "\n Numar de locuri:" + nrLocuri +
                "\nLocurile rezervate sunt: " + Arrays.toString(seats) +
                "\n idPasager=" + idPasager
        );
    }

    @Override
    public float calculeazaPretTotal(float pretBilet)    {
        return (float) (pretBilet*1.1 + this.nrBagaje * 5 + this.nrLocuri * 2);
    }


    @Override
    public void citesteDate(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Introduceti numarul de bagaje:");
        this.nrBagaje = scanner.nextInt();

        System.out.println("Introduceti numarul de locuri:");
        this.nrLocuri = scanner.nextInt();

        System.out.println("Introduceti indexul:");
        this.index = scanner.nextInt();

    }



}