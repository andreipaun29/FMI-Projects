
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

import Rezervare.*;
public class Main {
    public static void main(String[] args) throws IOException {
        final int nrzboruri = 120;
        final int nrmaxescale = 6;

        boolean zborIdentificat = true;

        ArrayList<Pasager> pasageri = new ArrayList<Pasager>();
        int indexPasager = 0;

        String password;

        Scanner passScanner = new Scanner(System.in);
        System.out.println("Introduceti parola:");

        password = passScanner.nextLine();

        if(password.equals("avioncumotorpa55")){

            System.out.println("---Admin mode---");

            System.out.println("1. Inregistrare pasager");
            System.out.println("2. Afisare pasageri");

            Scanner scannerOpt = new Scanner(System.in);
            int optiune = scannerOpt.nextInt();

            while(optiune != 0){
                switch(optiune){
                    case 1:

                        Scanner scanner = new Scanner(System.in);
                        //Cati pasageri se inregistreaza?
                        System.out.println("Cati pasageri se inregistreaza?");
                        int nrPasageri = scanner.nextInt();

                        for ( indexPasager = 0; indexPasager < nrPasageri; indexPasager++) {


                            //Inregistrarea pasagerilor

                            Utilitare.inregistrarePasager(pasageri,indexPasager);


                            ArrayList<CompanieAeriana> ca = new ArrayList<CompanieAeriana>();
                            Utilitare.setCompanii(ca); // vectorul ca va fi alocat dinamic si incarcat cu valori
                            int nraeroporturi = 0; // numar total aeroporturi disponibile
                            String[] aeroporturi = new String[40]; // matricea in care vom retine aeroporturile disponibile
                            nraeroporturi = Utilitare.setAeroporturi(aeroporturi); // matricea aeroporturi va fi alocata dinamic si incarcata cu valori
                            Utilitare.setZboruri(ca, aeroporturi, nraeroporturi);
                            DataCalendaristica dataprocesata = new DataCalendaristica(); // data introdusa de utilizator
                            Utilitare.citestedata(dataprocesata);
                            Utilitare.afisareAeroporturiDisponibile(aeroporturi, nraeroporturi);
                            // aeroportul de sosire si de plecare introduse de utilizator din lista afisata
                            int index = 0;
                            index = Utilitare.citesteindex(index, 1, nraeroporturi, "Introduceti aeroportul de plecare: ", "Ati introdus un aeroport care nu exista; valoare intre 1 si ");
                            String aeroplecare, aerososire;
                            aeroplecare = aeroporturi[index - 1];
                            index = Utilitare.citesteindex(index, 1, nraeroporturi, "Introduceti aeroportul de sosire: ", "Ati introdus un aeroport care nu exista; valoare intre 1 si ");
                            aerososire = aeroporturi[index - 1];
                            // utilizatorul introduce numarul maxim de escale, numar care trebuie sa fie mai mic ca 3
                            int nrescale = 0;
                            nrescale = Utilitare.citesteindex(nrescale, 0, nrmaxescale, "Introduceti numarul maxim de escale: ", "Numarul maxim de escale este intre 0 si ");
                            // calculeaza ziua din saptamana pe care a introdus-o clientul( luni/marti...)
                            dataprocesata.calculeazaZiDinSaptamana(dataprocesata.getAn(), dataprocesata.getLuna(), dataprocesata.getZi());
                            //Declaram un vector de solutii in care vom retine primele 50 de solutii gasite care indeplinesc criteriile clientului( numarul maxim de escale+data + aeroport plecare/sosire)
                            final int nrmaxsolutii = 50;
                            ArrayList<RutePosibile> zborurigasite = new ArrayList<RutePosibile>(); // vector in care vom retine solutiile gasite de algoritm
                            RutePosibile.setNrSol(0);
                            //Algoritm de gasire a zborurilor
                            for (int i = 0; i < CompanieAeriana.getNrCompanii(); i++)// Parcurgem fiecare compania aeriana pentru a parcurge toate zborurile disponibile
                                if(i<=10)
                                {
                                    for (int j = 0; j < ca.get(i).getNrZbor(); j++) // Parcurgem zborurile companiei i
                                    {
                                        //Mai jos utilizam operatorul de indexare declarat in cadrul clasei companieaeriana ex: ca[i][j]
                                        Zbor z = ca.get(i).getZbor(j);
                                        //comparam daca aeroportul introdus de client este acelasi cu aeroportul zborului j al companiei i
                                        if ((aeroplecare.equals(z.getAeroportPlecare()) == true) &&
                                                (z.getAn() == dataprocesata.getAn()) &&
                                                ((z.getZiSapt() == dataprocesata.getZiSapt()) || (z.getZiSapt() == -1))) //comparam daca zborul are loc are loc in ziua introdua de client
                                        {
                                            DataOra[] dataorasosire = new DataOra[5]; // vom retine orele de sosire ale zborurilor din care este formata calatoria
                                            dataorasosire[0] = z.calcsosire(); // calculam data sosirii avionului adunand durata si data plecarii
                                            DataOra oraplecare[] = new DataOra[5]; // vom retine orele de plecare ale zborurilor din care este formata calatoria
                                            oraplecare[0] = new DataOra(dataprocesata.getAn(), dataprocesata.getLuna(), dataprocesata.getZi()); // introducem data si ora plecarii pasagerului la drum
                                            oraplecare[0].setOra(z.getOra());
                                            oraplecare[0].setMinut(z.getMin());
                                            StringBuffer[] itinerar = new StringBuffer[5]; // vom retine aeroporturile prin care trece clientul pana la destinatieBu
                                            itinerar[0] = new StringBuffer().append(z.getAeroportPlecare());
                                            itinerar[1] = new StringBuffer().append(z.getAeroportSosire());
                                            StringBuffer[] numecompanii = new StringBuffer[5]; // vom retine numele companiilor ce opereaza zborurile
                                            numecompanii[0] = new StringBuffer().append(ca.get(i).getNume());
                                            if (z.getAeroportSosire().equals(aerososire)) {
                                                //am gasit o solutie valida care indeplineste cerintele clientului asa ca vom pune solutia in vectorul de solutii
                                                RutePosibile r = new RutePosibile(0, itinerar, z.getPret(), dataorasosire, oraplecare, numecompanii);
                                                zborurigasite.add(r);
                                            } else {
                                                //cu ajutorul zborului selectat clientul nu ajunge la destinatie. Vom cauta recursiv zboruri in completarea lui
                                                int a = 1;
                                                Utilitare.gasireRuta(0, nrescale, nrzboruri, nrmaxsolutii, z.getPret(), dataorasosire, oraplecare, itinerar, numecompanii, ca.get(i).getAlianta(), aerososire, zborurigasite, ca);
                                            }
                                        }
                                    }
                                }
                            if (RutePosibile.getNrSol() == 0) {
                                // in cazul in care nu a fost gasit niciun zbor se afiseaza un mesaj
                                System.out.println();
                                System.out.println("Nu a fost gasit nici un zbor!");
                                zborIdentificat = false;
                            } else {
                                // afisare zboruri gasite
                                Utilitare.afisareZboruri(zborurigasite);
                                zborIdentificat = true;

                                //remember all the flights in an array
                                ArrayList<RutePosibile> zborurigasite2 = new ArrayList<RutePosibile>();

                                for (int i = 0; i < RutePosibile.getNrSol(); i++) {
                                    zborurigasite2.add(zborurigasite.get(i));
                                }


                                if (Utilitare.continuiActivitatea("Doriti sa rezervati un zbor? d/n: ")) {
                                    //selectarea unui zbor dintre cele gasite

                                    //remember the index that the user selected
                                    int index2 = 0;
                                    index2 = Utilitare.citesteindex(index, 1, RutePosibile.getNrSol(), "Selectati un zbor: ", "Ati introdus un zbor care nu exista; valoare intre 1 si ");
                                    // System.out.println(index2);


                                    //use afisaresolutie2 from RutePosibile class to get the flight details
                                    Pasager.ZborInregistrat zbor = new Pasager.ZborInregistrat("", "", "", "");
                                    zbor = zborurigasite2.get(index2 - 1).afisaresolutie2();

                                    //add the flight to the passenger
                                    pasageri.get(indexPasager).setZbor(zbor);




                                }
                            }


                        }







                        break;
                    case 2:
                        if(zborIdentificat == true){
                            Utilitare.afisarePasageri(pasageri);

                        }
                        break;
                    default:
                        System.out.println("Optiune invalida!");
                        break;
                }
                System.out.println("1. Inregistrare pasager");
                System.out.println("2. Afisare pasageri");
                System.out.println("0. Exit");
                optiune = scannerOpt.nextInt();
            }



        }
        else{
            System.out.println("---User mode---");
            System.out.println("Bine ati venit! Multumim ca ati ales sa calatoriti cu noi!");



            Scanner scanner = new Scanner(System.in);
            //Cati pasageri se inregistreaza?
            System.out.println("Cati pasageri se inregistreaza?");
            int nrPasageri = scanner.nextInt();

            for ( indexPasager = 0; indexPasager < nrPasageri; indexPasager++) {


                //Inregistrarea pasagerilor

                Utilitare.inregistrarePasager(pasageri,indexPasager);


                ArrayList<CompanieAeriana> ca = new ArrayList<CompanieAeriana>();
                Utilitare.setCompanii(ca); // vectorul ca va fi alocat dinamic si incarcat cu valori
                int nraeroporturi = 0; // numar total aeroporturi disponibile
                String[] aeroporturi = new String[40]; // matricea in care vom retine aeroporturile disponibile
                nraeroporturi = Utilitare.setAeroporturi(aeroporturi); // matricea aeroporturi va fi alocata dinamic si incarcata cu valori
                Utilitare.setZboruri(ca, aeroporturi, nraeroporturi);
                DataCalendaristica dataprocesata = new DataCalendaristica(); // data introdusa de utilizator
                Utilitare.citestedata(dataprocesata);
                Utilitare.afisareAeroporturiDisponibile(aeroporturi, nraeroporturi);
                // aeroportul de sosire si de plecare introduse de utilizator din lista afisata
                int index = 0;
                index = Utilitare.citesteindex(index, 1, nraeroporturi, "Introduceti aeroportul de plecare: ", "Ati introdus un aeroport care nu exista; valoare intre 1 si ");
                String aeroplecare, aerososire;
                aeroplecare = aeroporturi[index - 1];
                index = Utilitare.citesteindex(index, 1, nraeroporturi, "Introduceti aeroportul de sosire: ", "Ati introdus un aeroport care nu exista; valoare intre 1 si ");
                aerososire = aeroporturi[index - 1];
                // utilizatorul introduce numarul maxim de escale, numar care trebuie sa fie mai mic ca 3
                int nrescale = 0;
                nrescale = Utilitare.citesteindex(nrescale, 0, nrmaxescale, "Introduceti numarul maxim de escale: ", "Numarul maxim de escale este intre 0 si ");
                // calculeaza ziua din saptamana pe care a introdus-o clientul( luni/marti...)
                dataprocesata.calculeazaZiDinSaptamana(dataprocesata.getAn(), dataprocesata.getLuna(), dataprocesata.getZi());
                //Declaram un vector de solutii in care vom retine primele 50 de solutii gasite care indeplinesc criteriile clientului( numarul maxim de escale+data + aeroport plecare/sosire)
                final int nrmaxsolutii = 50;
                ArrayList<RutePosibile> zborurigasite = new ArrayList<RutePosibile>(); // vector in care vom retine solutiile gasite de algoritm
                RutePosibile.setNrSol(0);
                //Algoritm de gasire a zborurilor
                for (int i = 0; i < CompanieAeriana.getNrCompanii(); i++)// Parcurgem fiecare compania aeriana pentru a parcurge toate zborurile disponibile
                    if(i<=10)
                    {
                        for (int j = 0; j < ca.get(i).getNrZbor(); j++) // Parcurgem zborurile companiei i
                        {
                            //Mai jos utilizam operatorul de indexare declarat in cadrul clasei companieaeriana ex: ca[i][j]
                            Zbor z = ca.get(i).getZbor(j);
                            //comparam daca aeroportul introdus de client este acelasi cu aeroportul zborului j al companiei i
                            if ((aeroplecare.equals(z.getAeroportPlecare()) == true) &&
                                    (z.getAn() == dataprocesata.getAn()) &&
                                    ((z.getZiSapt() == dataprocesata.getZiSapt()) || (z.getZiSapt() == -1))) //comparam daca zborul are loc are loc in ziua introdua de client
                            {
                                DataOra[] dataorasosire = new DataOra[5]; // vom retine orele de sosire ale zborurilor din care este formata calatoria
                                dataorasosire[0] = z.calcsosire(); // calculam data sosirii avionului adunand durata si data plecarii
                                DataOra oraplecare[] = new DataOra[5]; // vom retine orele de plecare ale zborurilor din care este formata calatoria
                                oraplecare[0] = new DataOra(dataprocesata.getAn(), dataprocesata.getLuna(), dataprocesata.getZi()); // introducem data si ora plecarii pasagerului la drum
                                oraplecare[0].setOra(z.getOra());
                                oraplecare[0].setMinut(z.getMin());
                                StringBuffer[] itinerar = new StringBuffer[5]; // vom retine aeroporturile prin care trece clientul pana la destinatieBu
                                itinerar[0] = new StringBuffer().append(z.getAeroportPlecare());
                                itinerar[1] = new StringBuffer().append(z.getAeroportSosire());
                                StringBuffer[] numecompanii = new StringBuffer[5]; // vom retine numele companiilor ce opereaza zborurile
                                numecompanii[0] = new StringBuffer().append(ca.get(i).getNume());
                                if (z.getAeroportSosire().equals(aerososire)) {
                                    //am gasit o solutie valida care indeplineste cerintele clientului asa ca vom pune solutia in vectorul de solutii
                                    RutePosibile r = new RutePosibile(0, itinerar, z.getPret(), dataorasosire, oraplecare, numecompanii);
                                    zborurigasite.add(r);
                                } else {
                                    //cu ajutorul zborului selectat clientul nu ajunge la destinatie. Vom cauta recursiv zboruri in completarea lui
                                    int a = 1;
                                    Utilitare.gasireRuta(0, nrescale, nrzboruri, nrmaxsolutii, z.getPret(), dataorasosire, oraplecare, itinerar, numecompanii, ca.get(i).getAlianta(), aerososire, zborurigasite, ca);
                                }
                            }
                        }
                    }
                if (RutePosibile.getNrSol() == 0) {
                    // in cazul in care nu a fost gasit niciun zbor se afiseaza un mesaj
                    System.out.println();
                    System.out.println("Nu a fost gasit nici un zbor!");
                    zborIdentificat = false;
                } else {
                    // afisare zboruri gasite
                    Utilitare.afisareZboruri(zborurigasite);
                    zborIdentificat = true;

                    //remember all the flights in an array
                    ArrayList<RutePosibile> zborurigasite2 = new ArrayList<RutePosibile>();

                    for (int i = 0; i < RutePosibile.getNrSol(); i++) {
                        zborurigasite2.add(zborurigasite.get(i));
                    }


                    if (Utilitare.continuiActivitatea("Doriti sa rezervati un zbor? d/n: ")) {
                        //selectarea unui zbor dintre cele gasite

                        //remember the index that the user selected
                        int index2 = 0;
                        index2 = Utilitare.citesteindex(index, 1, RutePosibile.getNrSol(), "Selectati un zbor: ", "Ati introdus un zbor care nu exista; valoare intre 1 si ");
                        // System.out.println(index2);


                        //use afisaresolutie2 from RutePosibile class to get the flight details
                        Pasager.ZborInregistrat zbor = new Pasager.ZborInregistrat("", "", "", "");
                        zbor = zborurigasite2.get(index2 - 1).afisaresolutie2();

                        //add the flight to the passenger
                        pasageri.get(indexPasager).setZbor(zbor);




                    }
                }


            }


            System.out.println("Biletele au fost inregistrate cu succes!");
//            if (zborIdentificat == true) {
//                //afisarea pasagerilor
//                Utilitare.afisarePasageri(pasageri);
//            }

            System.out.println("Treceti in modul administrator pentru a putea vizualiza pasagerii!");
            System.out.println("Introduceti parola: ");
            Scanner sc = new Scanner(System.in);
            String admin = sc.nextLine();


            if (admin.equals("avioncumotorpa55")) {
                //afisarea pasagerilor
                Utilitare.afisarePasageri(pasageri);
            }
            else{
                System.out.println("Nu aveti acces la aceasta functie!");
                System.exit(0);
            }





        }



    }
}