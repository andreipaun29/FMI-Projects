public class Zbor {

    // variabile
    private String aerop, aerov;
    private DataOra dataOra;
    private int durata;
    private double pret;

    // constructori
    public Zbor()
    {
        dataOra= new DataOra();
        durata=0;
        pret=0.0;
        aerop="";
        aerop="";
    }
    public Zbor(String p,String v, DataOra dora,int durata,int pret)
    {
        aerop=p;
        aerov=v;
        dataOra=new DataOra(dora);
        this.durata=durata;
        this.pret=pret;
    }
    public Zbor(String p, String v)
    {
        aerop=p;
        aerov=v;
        dataOra=new DataOra();
        durata=0;
        pret=0;
    }
    public Zbor(Zbor z)
    {
        this.aerop=z.aerop;
        this.aerov=z.aerov;
        this.dataOra=new DataOra(z.dataOra);
        this.pret=z.pret;
        this.durata=durata;
    }
    public void set(String plecare, String sosire, DataOra d, int dur, int cost)
    {
        aerop=plecare;
        aerov=sosire;
        dataOra=d;
        durata = dur;
        pret = cost;
    }
    public String getAeroportPlecare()
    {
        return aerop;
    }
    public String getAeroportSosire()
    {
        return aerov;
    }
    public double getPret()
    {

        return pret;
    }
    public int getAn()
    {
        return dataOra.getAn();
    }
    public int getLuna()
    {
        return dataOra.getLuna();
    }
    public int getZi()
    {
        return dataOra.getZi();
    }
    public int getZiSapt()
    {
        return dataOra.getZiSapt();
    }
    public int getOra()
    {
        return dataOra.getOra();
    }
    public int getMin()
    {
        return dataOra.getMinut();
    }
    public int getDurata()
    {
        return durata;
    }

    public void setZiSapt(int ziSapt)
    {
        dataOra.setZiSapt(ziSapt);
    }

    public DataOra calcsosire()
    {
        DataOra d=new DataOra(dataOra);
        d.setMinut(dataOra.getMinut() + durata);
        if (d.getMinut() > 59)
        {
            int nrore = d.getMinut() / 60;
            d.setOra(d.getOra() + nrore);
            d.setMinut(d.getMinut() - nrore * 60);
            if (d.getOra() > 23)
            {
                d.setOra(d.getOra() - 24);
                d.setZi(d.getZi() + 1);
                if ((d.getLuna() == 1 || d.getLuna() == 3 || d.getLuna() == 5 || d.getLuna() == 7 || d.getLuna() == 8 || d.getLuna() == 10) && d.getLuna() == 32)
                {
                    d.setLuna(d.getLuna() + 1);
                    d.setZi(1);
                }
                else
                {
                    if ((d.getLuna() == 4 || d.getLuna() == 6 || d.getLuna() == 9 || d.getLuna() == 11) && d.getZi() == 31)
                    {
                        d.setLuna(d.getLuna() + 1);
                        d.setZi(1);
                    }
                    else
                    {
                        if (d.getLuna() == 12 && d.getZi() == 32)
                        {
                            d.setAn(d.getAn() + 1);
                            d.setLuna(1);
                            d.setZi(1);
                        }
                        else
                        {
                            if (d.getLuna() == 2)
                            {
                                if (d.getZi() == 29)
                                {
                                    d.setLuna(d.getLuna() + 1);
                                    d.setZi(1);
                                }
                            }
                        }
                    }
                }
            }
        }
        d.calculeazazidinsaptamana(d.getAn(), d.getLuna(), d.getZi());
        return d;
    }
}
