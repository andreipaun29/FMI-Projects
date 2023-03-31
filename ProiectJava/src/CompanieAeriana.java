import java.util.ArrayList;

public class CompanieAeriana {
    // variabile
    private String nume;
    private String alianta;
    private ArrayList<Zbor> zboruri;
    // Numarul de zboruri efectuate de companie
    private int nrZbor;
    // Numarul total de companii inregistrate
    private static int nrCompanii;

    // metode
    public static void setNrComp(int x)
    {
        nrCompanii = x;
    }
    public static int getNrCompanii()
    {
        return nrCompanii;
    };
    CompanieAeriana()
    {
        nume="";
        alianta="";
        nrZbor=0;
    };

    public void setNrZbor(int nrz)
    {
        nrZbor=nrz;
    }
    public int getNrZbor()
    {
        return nrZbor;
    }
    CompanieAeriana(String numeca, String numeal)
    {
        zboruri = new ArrayList<Zbor>();
        nume=numeca;
        alianta=numeal;
        nrZbor = 0;
    };
    CompanieAeriana(String numeca, String numeal, ArrayList<Zbor> z, int nrzbor)
    {
        nume=numeca;
        alianta=numeal;
        this.nrZbor = nrzbor;
        zboruri= new ArrayList<Zbor>(z);
    };
    CompanieAeriana(CompanieAeriana ca)
    {
        this.nume=ca.nume;
        this.alianta=ca.alianta;
        this.nrZbor=ca.nrZbor;
        this.zboruri=new ArrayList<Zbor>(ca.zboruri);
    };
    void set(String numeca, String numeal)
    {
        nume=numeca;
        alianta=numeal;
    };
    Zbor getZbor(int i)
    {
        return zboruri.get(i);
    };
    String getNume()
    {
        return nume;
    };
    String getAlianta()
    {
        return alianta;
    };
    public void adaugaZbor(Zbor z)
    {
        this.zboruri.add(z);
    }
}
