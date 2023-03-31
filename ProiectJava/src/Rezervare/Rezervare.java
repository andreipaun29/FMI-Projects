package Rezervare;

public abstract class Rezervare {
    protected int nrLocuri;
    protected int index;
    protected float pretTotal;
    protected int idPasager;

    public Rezervare(int nrLocuri, int index, float pretTotal, int idPasager) {
        this.nrLocuri = nrLocuri;
        this.index = index;
        this.pretTotal = pretTotal;
        this.idPasager = idPasager;
    }

    public Rezervare() {
        this.nrLocuri = 0;
        this.index = 0;
        this.pretTotal = 0;
        this.idPasager = 0;
    }

    public int getNrLocuri() {
        return nrLocuri;
    }

    public void setNrLocuri(int nrLocuri) {
        this.nrLocuri = nrLocuri;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public float getPretTotal() {
        return pretTotal;
    }

    public void setPretTotal(float pretTotal) {
        this.pretTotal = pretTotal;
    }

    public int getIdPasager() {
        return idPasager;
    }

    public void setIdPasager(int idPasager) {
        this.idPasager = idPasager;
    }

    public abstract void afisare();
    public abstract float calculeazaPretTotal(float pretBilet);

    public abstract void citesteDate();
}



