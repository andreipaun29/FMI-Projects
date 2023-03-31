import java.util.Scanner;

// data: zi, luna, an
// calculeaza ziua din saptamana corespunzatoare datei
//    0 e miercuri .... 6 e marti
public class DataCalendaristica {

    // variabile
    private int zi,luna,an, ziSaptamana;

    // metoda ce determina numarul de zile de la data de 1.1.0000 pana la data curenta
    private long calculeazaNumarZile(int an, int luna, int zi)
    {
        luna=(luna+9)%12;
        an-=luna/10;
        long nrZile= 365* an+ an/4 -an/100 +an/400+(luna*306+5)/10+(zi-1);
        return nrZile;
    }

    // calculeaza ziua din saptamana a unei date
    public void calculeazaZiDinSaptamana(int an,int luna,int zi)
    {
        // Verificam daca zborul nu se desfasoara zilnic
        if(luna==-1 || zi==-1)
        {
            this.ziSaptamana=-1;
            return;
        }
        long nrZile=calculeazaNumarZile(an,luna,zi);
        this.ziSaptamana=(int)nrZile%7;
    }

    // constrctor fara parametri
    public DataCalendaristica()
    {
        zi=1; luna=1; an=2023; calculeazaZiDinSaptamana(an,luna,zi);
    }
    //constructor cu parametri
    public DataCalendaristica(int an,int luna,int zi)
    {
        this.zi=zi;
        this.an=an;
        this.luna=luna;
        calculeazaZiDinSaptamana(an,luna,zi);
    }
    //constrctor copiere
    public DataCalendaristica(DataCalendaristica d)
    {
        this.zi=d.zi;
        this.luna=d.luna;
        this.an=d.an;
    }

    // metode get si set pentru clasa DataCalendaristica
    void set(final int an,final int luna, final int zi)
    {
        this.zi = zi;
        this.luna = luna;
        this.an = an;
        calculeazaZiDinSaptamana(an,luna,zi);
    }
    final int getAn()
    {
        return an;
    }
    final int getLuna()
    {
        return luna;
    }
    final int getZi()
    {
        return zi;
    }
    final int getZiSapt()
    {
        return ziSaptamana;
    }
    void setAn(int an)
    {
        this.an = an;
    }
    void setLuna(int luna)
    {
        this.luna = luna;
    }
    void setZi(int zi)
    {
        this.zi = zi;
    }
    void setZiSapt(int zisapt)
    {
        this.ziSaptamana = zisapt;
    }

    // valideaza data o data este corecta sau nu
    final public boolean validareData()
    {
        // datele introduse trebuie sa fie din anul curent sau anul urmator
        if(an!=2023 && an!=2024)
            return false;
        // lunile unui an sunt intre 1 si 12
        if(luna<1 || luna>12)
            return false;
        // o luna poate sa aiba maxim 31 de zile
        if(zi<1 || zi>31)
            return false;
        // ianuarie, martie,mai,iulie,august,octombrie si decembrie au 31 de zile
        if(luna==1 || luna==3 || luna==5|| luna==7|| luna==8|| luna==10 ||luna==12)
        {
            if(zi>31)
                return false;
        }
        // aprilie,iunie,septembrie,noiembrie au 30 de zile
        if(luna==4 || luna==6|| luna==9|| luna==11)
        {
            if(zi>30)
                return false;
        }
        if(luna==2 && an==2023 && zi>28)
            return false;
        if(luna==2 && an==2024 && zi>29)
            return false;
        return true;
    }
    public String getZiSaptLitere()
    {
        switch (ziSaptamana) {
            case 0:
                return "miercuri";
            case 1:
                return "joi";
            case 2:
                return "vineri";
            case 3:
                return "sambata";
            case 4:
                return "duminica";
            case 5:
                return "luni";
            case 6:
                return "marti";
        }
        return "luni";
    }
    public String toString()
    {
        return "Ziua plecarii este "+ getZiSaptLitere()+", " + Integer.toHexString(zi) + "."+ Integer.toHexString(luna) + "." + Integer.toHexString(an);
    }
    public void citeste()
    {
        System.out.print("Intoduceti data plecarii (zi luna an): ");
        Scanner scan=new Scanner(System.in);
        zi=scan.nextInt();
        luna=scan.nextInt();
        an=scan.nextInt();
    }
}
