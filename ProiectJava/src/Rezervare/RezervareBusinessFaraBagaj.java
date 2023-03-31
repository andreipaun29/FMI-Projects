package Rezervare;
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
        System.out.println("RezervareBusinessFaraBagaj{" +
                "nrLocuri=" + nrLocuri +
                ", index=" + index +
                ", pretTotal=" + pretTotal +
                ", idPasager=" + idPasager +
                '}');
    }

    @Override
    public float calculeazaPretTotal(float pretBilet)    {
        return (float) (this.pretTotal*1.2);
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
