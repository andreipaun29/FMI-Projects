
public class RutePosibile {
    private int nrZboruri;
    private DataOra dataOra;
    private double preturi;
    private StringBuffer[] itinerar;
    private int[] plecareOra;
    private int[] plecareMin;
    private int[] sosireOra;
    private int[] sosireMin;
    private StringBuffer[] companii;
    private static int nrsol;
    static int getNrSol() { return nrsol; }
    static void setNrSol(int nr) { nrsol = nr; }
    double getPrice()
    {
        return preturi;
    }



    Pasager pasager = new Pasager();

    private String tempPret, tempRuta, tempOre, tempCompanii;
    public RutePosibile()
    {
        itinerar=new StringBuffer[5];
        plecareOra=new int[5];
        plecareMin=new int[5];
        sosireMin=new int[5];
        sosireOra=new int[5];
        companii=new StringBuffer[5];
        dataOra=new DataOra();
        preturi=0;
    }
    public void afisaresolutie()
    {
         System.out.println();
         System.out.println("Pret: "+preturi+" euro");

         tempPret = preturi+" euro";


        tempRuta = "";
        for (int j = 0; j <= nrZboruri; j++)
        {
            if (j > 0)
            {
                 System.out.print( "->");
            }
             System.out.print(itinerar[j]);
                //check if this is the last element to not add the arrow
                if (j < nrZboruri)
                {
                    tempRuta = tempRuta + itinerar[j] + "->";
                }
                else
                {
                    tempRuta = tempRuta + itinerar[j];
                }
        }
         System.out.println();
        tempOre = "";
        for (int j = 0; j < nrZboruri; j++)
        {
             System.out.print( plecareOra[j] +":" + plecareMin[j] +"->");
             System.out.print( sosireOra[j] + ":" + sosireMin[j] +" ");

                tempOre = tempOre + plecareOra[j] +":" + plecareMin[j] +"->" + sosireOra[j] + ":" + sosireMin[j] +" ";
        }
         System.out.println();
        tempCompanii = "";
        for (int j = 0; j < nrZboruri; j++)
        {
            if (j > 0)
            {
                 System.out.print( "->");

            }
             System.out.print(companii[j]);
            //check if this is the last element to not add the arrow
            if (j < nrZboruri)
            {
                tempCompanii = tempCompanii + companii[j] + "->";
            }
            else
            {
                tempCompanii = tempCompanii + companii[j];
            }

        }
         System.out.println();
    }


    public Pasager.ZborInregistrat afisaresolutie2()
    {

        Pasager.ZborInregistrat zborInregistrat = new Pasager.ZborInregistrat(tempPret, tempRuta, tempOre, tempCompanii);
        return zborInregistrat;

    }


    public void toStr()
    {
        System.out.println("Pret: "+preturi+" euro");
        for (int j = 0; j <= nrZboruri; j++)
        {
            if (j > 0)
            {
                System.out.print( "->");
            }
            System.out.print(itinerar[j]);
        }
        System.out.println();
        for (int j = 0; j < nrZboruri; j++)
        {
            System.out.print( plecareOra[j] +":" + plecareMin[j] +"->");
            System.out.print( sosireOra[j] + ":" + sosireMin[j] +" ");
        }
        System.out.println();
        for (int j = 0; j < nrZboruri; j++)
        {
            if (j > 0)
            {
                System.out.print( "->");
            }
            System.out.print(companii[j]);
        }
        System.out.println();
    }
    public RutePosibile(int escale, StringBuffer[] itinerar, double pret, DataOra[] dataorasosire, DataOra[] oraplecare, StringBuffer[] numecompanii)
    {
        this.itinerar=new StringBuffer[5];
        this.companii=new StringBuffer[5];
        this.plecareOra=new int[5];
        this.plecareMin=new int[5];
        this.sosireMin=new int[5];
        this.sosireOra=new int[5];
        this.dataOra=new DataOra();
        for (int i = 0; i <= escale + 1; i++)
        {
            //salveaza nume aeroport
            this.itinerar[i]=new StringBuffer(itinerar[i]);
            if (i <= escale)
            {
                //salveaza ora si minute plecare si sosire
                plecareOra[i] = oraplecare[i].getOra();
                plecareMin[i] = oraplecare[i].getMinut();
                sosireOra[i] = dataorasosire[i].getOra();
                sosireMin[i] = dataorasosire[i].getMinut();
                //salveaza nume companie aeriana
                this.companii[i]=new StringBuffer(numecompanii[i]);
            }
        }
        this.nrZboruri=escale+1;
        this.preturi=pret;
        RutePosibile.setNrSol(RutePosibile.getNrSol() + 1);
    }
}
