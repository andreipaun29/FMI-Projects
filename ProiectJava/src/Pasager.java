import Rezervare.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
public class Pasager {

    private int id;
    private String nume;
    private String prenume;
    private String varsta;

    public record ZborInregistrat(String Pret, String Ruta, String Ore, String Companii ){
        public ZborInregistrat(String Pret, String Ruta, String Ore, String Companii) {
            this.Pret = Pret;
            this.Ruta = Ruta;
            this.Ore = Ore;
            this.Companii = Companii;
        }

    }

//    public RutePosibile rutePosibile = new RutePosibile();




    List<ZborInregistrat> zboruri = new ArrayList<ZborInregistrat>();

    ArrayList<Rezervare> rezervari = new ArrayList<Rezervare>();

    public Pasager() {
        id = 0;
        nume = "";
        prenume = "";
        varsta = "";
    }

    public Pasager(int id, String nume, String prenume, String varsta) {
        this.id = id;
        this.nume = nume;
        this.prenume = prenume;
        this.varsta = varsta;
    }


    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNumePasager() {
        return nume;
    }

    public void setNumePasager(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public String getVarsta() {
        return varsta;
    }

    public void setVarsta(String varsta) {
        this.varsta = varsta;
    }

    public void setZbor(ZborInregistrat zbor){
        zboruri.add(zbor);
    }

    public void citeste(int indexPasager){

        System.out.println("Introduceti numele pasagerului " + indexPasager + ": " );
        //read a string
        Scanner in = new Scanner(System.in);
        nume = in.next();
        System.out.println("Introduceti prenumele pasagerului " + indexPasager + ": ");
        prenume = in.next();
        System.out.println("Introduceti varsta pasagerului " + indexPasager + ": ");
        varsta = in.next();


        //choose the type of the ticket
        System.out.println("Introduceti tipul de bilet: ");
        System.out.println("1. Bilet loc business cu bagaj");
        System.out.println("2. Bilet loc business fara bagaj");
        System.out.println("3. Bilet loc economic cu bagaj");
        System.out.println("4. Bilet loc economic fara bagaj");

        int tipBilet = in.nextInt();


        switch (tipBilet) {
            case 1:
                RezervareBusinessCuBagaj b1 = new RezervareBusinessCuBagaj();
                b1.citesteDate();
                b1.setIdPasager(this.id);
                rezervari.add(b1);
                break;
            case 2:
                RezervareBusinessFaraBagaj  b2 = new RezervareBusinessFaraBagaj ();
                b2.citesteDate();
                b2.setIdPasager(this.id);
                rezervari.add(b2);
                break;
            case 3:
                RezervareEconomicCuBagaj b3 = new RezervareEconomicCuBagaj();
                b3.citesteDate();
                b3.setIdPasager(this.id);
                rezervari.add(b3);
                break;
            case 4:
                RezervareEconomicFaraBagaj b4 = new RezervareEconomicFaraBagaj();
                b4.citesteDate();
                b4.setIdPasager(this.id);
                rezervari.add(b4);
                break;
            default:
                System.out.println("Nu ati introdus un numar valid");
                break;
        }




    }

    public void  afiseaza(){
        System.out.println("Numele pasagerului este: " + nume);
        System.out.println("Prenumele pasagerului este: " + prenume);
        System.out.println("Varsta pasagerului este: " + varsta);
        System.out.println("Rezervarile pasagerului sunt: ");

        for (Rezervare rezervare : rezervari) {
            System.out.println("Rezervarea este: ");
            rezervare.afisare();

        }

        //afisare zboruri
        int i = 0;
        for (ZborInregistrat zbor : zboruri) {
            System.out.println("------------Zborul pasagerului " + i++ + " este --------------");
            // cut the last 5 characters from zb.Pret
            StringBuffer sb = new StringBuffer(zbor.Pret);
            sb.delete(sb.length() - 5, sb.length()); // delete last 5 characters
            Float pret = Float.parseFloat(sb.toString());


            System.out.print("Pretul final al biletului pentru locul solicitat este: " );
            System.out.println( rezervari.get(i-1).calculeazaPretTotal(pret));
            System.out.println("Ruta este: " + zbor.Ruta);
            System.out.println("Orele escalelor: " + zbor.Ore);
            System.out.println("Companiile aeriene: " + zbor.Companii);
            System.out.println("--------------------------------------------------------");
            i++;
            System.out.println('\n');
        }

    }




}

