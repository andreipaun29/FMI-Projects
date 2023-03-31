
// DataCalendaristica este interconectata prin agregare de DataOra
public class DataOra {
    // variabile
    private DataCalendaristica datacal;
    private int ora,minut;

    // constructori
    public DataOra()
    {
        datacal=new DataCalendaristica();
        ora=0;
        minut=0;
    }
    public DataOra(final int an,final int luna,final int zi)
    {
        datacal=new DataCalendaristica(an,luna,zi);
        ora=0;
        minut=0;
    }
    public DataOra(final int an,final int luna, final int zi, final int ora,final int minut)
    {
        datacal=new DataCalendaristica(an,luna,zi);
        this.ora=ora;
        this.minut=minut;
    }
    public DataOra(DataOra d)
    {
        this.datacal=new DataCalendaristica(d.datacal);
        this.ora=d.ora;
        this.minut=d.minut;
    }

    // get si set pentru variabilele private
    public void Set(int an, int luna, int zi, int ora, int minut)
    {
        this.datacal.set(an, luna, zi);
        this.ora = ora;
        this.minut = minut;
        this.datacal.calculeazaZiDinSaptamana(datacal.getAn(), datacal.getLuna(), datacal.getZi());
    }
    public void setData(DataCalendaristica dc)
    {
        datacal = dc;
    }
    public DataCalendaristica getdata() { return datacal; }
    public int getAn() { return datacal.getAn(); }
    public int getLuna() { return datacal.getLuna(); }
    public int getZi() { return datacal.getZi(); }
    public int getZiSapt() { return datacal.getZiSapt(); }
    public int getOra() { return ora; }
    public int getMinut() { return minut; }
    public void setAn(int an) { datacal.setAn(an); }
    public void setLuna(int luna) { datacal.setLuna(luna); }
    public void setZi(int zi) { datacal.setZi(zi); }
    public void setZiSapt(int zisapt) { datacal.setZiSapt(zisapt); }
    public void setOra(int ora) { this.ora = ora; }
    public void setMinut(int minut) { this.minut = minut; }

    public void calculeazazidinsaptamana(int an,int luna,int zi)
    {
        datacal.calculeazaZiDinSaptamana(an, luna, zi);
    }

    public boolean validare()
    {
        return datacal.validareData() && ora<23 && minut<60;
    }
    public String toString()
    {
        return datacal.toString()+"\n"+"Ora de plecare este: "+this.ora+":"+this.minut;
    }

}
