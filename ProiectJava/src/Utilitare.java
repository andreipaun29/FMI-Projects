import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;


class SortByPret implements Comparator<RutePosibile>
{
    public int compare(RutePosibile a,RutePosibile b)
    {
        return (int)(a.getPrice()-b.getPrice());
    }
}
public class Utilitare {
    public static void setCompanii(ArrayList<CompanieAeriana> ca) throws IOException {
        BufferedReader br=new BufferedReader(
                new FileReader("C:\\Users\\Andrei\\Desktop\\ProiectJava\\CompaniiAeriene.in")
        );
        String s;
        while((s=br.readLine())!=null)
        {
            StringTokenizer s2=new StringTokenizer(s," ");
            String p=s2.nextToken();
            String x=s2.nextToken();
            ca.add(new CompanieAeriana(p,x));
            CompanieAeriana.setNrComp(CompanieAeriana.getNrCompanii()+1);
        }
        br.close();
    }

    public static int setAeroporturi(String[] aeroporturi) throws IOException {
        int i=0;
        BufferedReader br=new BufferedReader(
                new FileReader("C:\\Users\\Andrei\\Desktop\\ProiectJava\\Aeroporturi.in")
        );
        String s;
        while((s=br.readLine())!=null)
        {
            aeroporturi[i++]=s;
        }
        br.close();
        return i;
    }
    public static void setZboruri(ArrayList<CompanieAeriana> ca, String[] aeroporturi,int nraeroporturi)
    {
        //prevent j from going above 10

        for (int j = 0; j < CompanieAeriana.getNrCompanii(); j++)
        //prevent j from going above 10
        if(j<=10)
        {

            System.out.println(j);

            int nrzboruri=70+(int)(Math.random()*50+1);
            ca.get(j).setNrZbor(nrzboruri);
            for (int i = 0; i < nrzboruri; i++)
            {
                String plecare;
                String sosire;
                DataOra d=new DataOra();
                do
                {
                    int index1=(int)(Math.random()*nraeroporturi);
                    int index2=(int)(Math.random()*nraeroporturi);
                    plecare=aeroporturi[index1];
                    sosire=aeroporturi[index2];
                } while (plecare.equals(sosire));
                d.setAn(((int)(Math.random()*2)) + 2023); // 2 ani disponibili pentru rezervari: 2023 si 2024
//                System.out.println(plecare+"-"+sosire+"-"+d.getAn());
                if (i % 5 == 0)
                {
                    // zboara in fiecare zi din 10 in 10 zboruri
                    d.setZi(-1);
                    d.setLuna(-1);
                    d.setZiSapt(-1);
                }
                else
                {
                    d.setLuna((int) (Math.random() * 12 + 1));
                    if (d.getLuna() == 1 || d.getLuna() == 3 || d.getLuna() == 5 || d.getLuna() == 7 || d.getLuna() == 8 || d.getLuna() == 10 || d.getLuna() == 12) {
                        d.setZi((int)(Math.random()*31 + 1));
                    }
                    else {
                        if (d.getLuna() == 4 || d.getLuna() == 6 || d.getLuna() == 9 || d.getLuna() == 11) {
                            d.setZi((int) (Math.random() * 30 + 1));
                        } else //februarie
                        {
                            if (d.getAn() == 2023)
                                d.setZi((int) (Math.random() * 28) + 1);
                            else
                                d.setZi((int) (Math.random() * 29) + 1);
                        }
                    }
                }
                d.calculeazazidinsaptamana(d.getAn(), d.getLuna(), d.getZi());
                d.setOra((int)(Math.random()*24));
                d.setMinut((int)(Math.random()*60));
                int durata = 60+(int)(Math.random()*121); //intre 60 si 180 minute
                int cost = 100+(int)(Math.random()*201); //intre 100 si 300 euro
                Zbor z=new Zbor(plecare,sosire,d,durata,cost);
                ca.get(j).adaugaZbor(z);
                ca.get(j).getZbor(i).setZiSapt(d.getZiSapt());
            }
        }
    }
    private static void sortareDupaPret(ArrayList<RutePosibile> zboruriGasite)
    {
        ArrayList<RutePosibile> zboruriGasiteSort=new ArrayList<RutePosibile>();
        Collections.sort(zboruriGasite, new SortByPret());
    }

    // afisare aeroport disponibil
    public static void afisareAeroporturiDisponibile(String[] aeroporturi,final int nrAeroporturi)
    {
        System.out.println("Aeroporturi disponibile");
        for(int i=0;i<nrAeroporturi;i++)
        {
            System.out.println((i+1)+". "+aeroporturi[i]);
        }
        System.out.println();
    }

    // afisare zboruri
    static public void afisareZboruri(ArrayList<RutePosibile> zboruriGasite)
    {
        System.out.println("//////// zboruri gasite /////// zboruri gasite /////// zboruri gasite");
        sortareDupaPret(zboruriGasite);
        for(int i=0;i<RutePosibile.getNrSol();i++)
        {
            System.out.println();
            System.out.print((i+1)+". ");
            zboruriGasite.get(i).afisaresolutie();

        }

    }
    static public void gasireRuta(int escala, final int nrescale, int nrzboruri, final int nrmaxsolutii, final double pret, DataOra dataorasosire[], DataOra oraplecare[], StringBuffer [] intinerar, StringBuffer[] numecompanii, String alianta, String aerososire, ArrayList<RutePosibile> zborurigasite, ArrayList<CompanieAeriana> ca)
    {
        // verificam daca numar de escale depaseste numarul maxim de escale introduse de client
        if (nrescale<=escala || RutePosibile.getNrSol()>nrmaxsolutii)
        {
            return;
        }
        System.out.println(intinerar[escala+1]);
        System.out.println(aerososire);
        String ultimulAero=intinerar[escala+1].toString();
        if (ultimulAero.equals( aerososire)==true)
        {
            // am gasit o solutie pe care o sa o punem in vectorul de solutii
            RutePosibile r = new RutePosibile(escala, intinerar, pret, dataorasosire, oraplecare, numecompanii);
            zborurigasite.add(r);
            return;
        }
        DataOra dososire = new DataOra(dataorasosire[escala]);
        //Parcurgem fiecare companie aeriana
        for (int i = 0; i < CompanieAeriana.getNrCompanii(); i++)
        if(i<=10)
        {
            if (alianta.equals( ca.get(i).getAlianta())==true)
            {
                //Parcurgem fiecare zbor al companiei aeriene
                nrzboruri=ca.get(i).getNrZbor();
                for (int j = 0; j < nrzboruri; j++)
                {
                    Zbor z=ca.get(i).getZbor(j);
                    if ((intinerar[escala + 1].equals(z.getAeroportPlecare())==false) && // se compara daca aeroportul in care s-ar afla clientul dupa un anumit numar de zboruri este acelasi cu cel din care pleaca zborul j
                            (z.getAn() == dososire.getAn()) &&
                            ((z.getZiSapt() == dososire.getZiSapt()) || (z.getZiSapt() == -1)) && // se verifica daca zborul are loc in ziua din saptamana in care ar ajunge clientul pe acel aeroport
                            (((z.getOra() * 60 + z.getMin()) - (dososire.getOra() * 60 + dososire.getMinut())) > 50)) // escala este de minim 50 minute
                    {
                        //nu permite intoarcerea intr-un aeroport folosit deja in intinerarul curent
                        boolean folosit = false;
                        for (int t = 0; t <= escala + 1; t++)
                        {
                            if (intinerar[t].equals(z.getAeroportSosire()) == true)
                            {
                                folosit = true;
                                break;
                            }
                        }
                        if (!folosit)
                        {
                            // inseram un nou zbor in cadrul cursei
                            intinerar[escala + 2]= new StringBuffer().append( z.getAeroportSosire());
                            dataorasosire[escala + 1] = new DataOra(z.calcsosire());
                            oraplecare[escala+1]=new DataOra(z.getAn(),z.getLuna(),z.getZi());
                            oraplecare[escala + 1].setOra(z.getOra());
                            oraplecare[escala + 1].setMinut(z.getMin());
                            numecompanii[escala + 1]=new StringBuffer().append(ca.get(i).getNume());
                            // cautam un alt zbor care sa completeze cursa
                            gasireRuta(escala + 1, nrescale, nrzboruri, nrmaxsolutii, pret + z.getPret(), dataorasosire, oraplecare, intinerar, numecompanii, alianta, aerososire, zborurigasite, ca);
                        }
                    }
                }
            }
        }
    }
    //Utilizatorul introduce indexul unui aeropot/numarul de escale/zbor iar metoda de mai jos verifica validitatea indexului aeroportului/ numarului de escale/ indexul zborului
    public static int citesteindex(int index, final int valmin, final int valmax, final String mesaj, final String mesajEroare)
    {
        System.out.println(mesaj);
        Scanner scan = new Scanner(System.in);
        index= scan.nextInt();
        while (index < valmin || index > valmax)
        {
            System.out.println(mesajEroare + valmax + mesaj);
            index=scan.nextInt();
        }


        return index;
    }
    // citeste data in care vrea sa plece clientul
    public static void citestedata(DataCalendaristica dataprocesata)
    {
        System.out.println("Sunt disponibili doi ani pentru cautare zboruri: 2023 si 2024.");
        boolean datainvalida = false;
        do
        {
            dataprocesata.citeste();
            System.out.println();
            datainvalida = dataprocesata.validareData();
            if (!datainvalida)
            {
                System.out.println("Data introdusa nu este valida.");
            }
        } while (!datainvalida);
    }
    // Clientul va introduce d daca doreste sa rezerve unul dintre zboruri/ sa continue cautarea de zboruri  si n daca nu
    static public boolean continuiActivitatea(final String mesaj)
    {
        char c;
        Scanner scan=new Scanner(System.in);
        do
        {
            System.out.println(mesaj);
            c=scan.next().charAt(0);
        } while (c != 'd' && c != 'n');
        return (c == 'd');
    }


    public static void inregistrarePasager (ArrayList<Pasager> pasageri, int indexPasager)
    {
        Pasager p = new Pasager();
        // citim datele pasagerului
        p.setId(pasageri.size() + 1);
        p.citeste(indexPasager);



        pasageri.add(p);
    }

    public static void afisarePasageri(ArrayList<Pasager> pasageri)
    {
        for (int i = 0; i < pasageri.size(); i++)
        {
            pasageri.get(i).afiseaza();
        }
    }

}
