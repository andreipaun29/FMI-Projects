package Rezervare;
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
        System.out.println("RezervareEconomicCuBagaj{" +
                "nrBagaje=" + nrBagaje +
                ", nrLocuri=" + nrLocuri +
                ", index=" + index +
                ", pretTotal=" + pretTotal +
                ", idPasager=" + idPasager +
                '}');
    }

    @Override
    public float calculeazaPretTotal(float pretBilet)    {
        return (float) (this.pretTotal + this.nrBagaje * 10);
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