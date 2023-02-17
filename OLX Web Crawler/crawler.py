from bs4 import BeautifulSoup
import requests
import re


# response = requests.get("https://www.olx.ro/hobby-sport-turism/airsoft/").text

# soup = BeautifulSoup(response,'lxml')

# print(soup.prettify())

number=1
anunturiTextSplit=[]
dictPagini={}

while number <= 25:
    anunturiText=[]
    if number >=2:
        url_contents = requests.get("https://www.olx.ro/d/hobby-sport-turism/?page="+str(number)).text
    else:
        url_contents = requests.get("https://www.olx.ro/d/hobby-sport-turism/").text
        
    soup = BeautifulSoup(url_contents, 'lxml')
    div = soup.find_all("h6")



    for line in div:
        if "lei" not in str(line):
            string=""
            for i in range(len(str(line))):
                if str(line)[i] == ">":
                    try:
                        while str(line)[i] != "<":
                            i+=1
                            if str(line)[i] != "<":
                                string+=str(line)[i]
                    except:
                        pass
                    
            anunturiText.append(string)
    dictPagini[number] = anunturiText

        
    number+=1


moduriDeTransport=[]
arme=[]
cultura=[] #carti, cd-uri, poezii, tablou, enciclopedie
muzica=[] #vioara, chitara,vinil,casete
bani=[] #monede, lei, bancnote?
activitatiMontane=[] #schiuri, ski, mountainbike, snowboard, ghete
imbracaminte=[] #geaca, bluza, pantaloni, parpalac
aparateDeInregistrat=[] #camere/aparate video, foto
fitness=[] #abdomene, gantere, banci fitness, banda alergat/alergare
tigari=[] #tigari, aparat de rulat tigari, scrumiera, aparat de injectat tigari,suport pentru tigari



# print(dictPagini)
for ch in dictPagini:
    anunturiTextSplit=[]
    
    # print(ch,end='\n\n')                                               #UN MOD DE AFISARE (cuvinte separate pentru fiecare pagina)
    for anunt in dictPagini[ch]:
        # anunturiTextSplit.append(anunt.split(" ")) #*1
        
        result1 = re.findall("(\w*cicl\w*)|(\w*neta)",anunt,flags=re.I|re.M)
        if result1:
            moduriDeTransport.append(result1)
            
        result2 = re.findall("(airsoft)|(brice\w*)|(cutit)|(lunet\w*)",anunt,flags=re.I|re.M)
        if result2:
            arme.append(result2)
        
        result3 = re.findall("(cart\w*)|(cd)|(poez\w*)|(tablou\w*)|(encicloped\w*)",anunt,flags=re.I|re.M)
        if result3:
            cultura.append(result3)
        
        result4 = re.findall("(v\w*ara|c\w*ara)|(caset\w*)|(v[iy]n[iy]l\w*)",anunt,flags=re.I|re.M)
        if result4:
            muzica.append(result4)
            
        result5 = re.findall("(mone..)|(le[iu])|(bancnot\w*)",anunt,flags=re.I|re.M)
        if result5:
            bani.append(result5)
            
        result6 = re.findall("(s(k|ch)i\w*)|(snow\w*)|(clapar\w*)",anunt,flags=re.I|re.M)
        if result6:
            activitatiMontane.append(result6)
            
        result7 = re.findall("(g(eaca|eci)\w*)|(pantaloni\w*)|(bluz[ae]\w*)|(tricou\w*)",anunt,flags=re.I|re.M)
        if result7:
            imbracaminte.append(result7)
            
        result8 = re.findall("((aparat|camera)\s*(film)\w*)|((aparat|camera)\s*(digital|digitala)\w*)",anunt,flags=re.I|re.M)
        if result8:
            aparateDeInregistrat.append(result8)
            
        result9 = re.findall("(abdomen\w*)|(ganter\w*)|(banc(i|a)\s*(piept)\w*)|((banda\s*de\s*alerga(t|re)\w*)|(banda\s*alerga(t|re)\w*))",anunt,flags=re.I|re.M)
        if result9:
            fitness.append(result9)
        
        result10 = re.findall("(^tigari\w*)|(scrum\w*)|((aparat\s*de\s*rulat\s*tigari\w*)|(aparat\s*\de\s*injectat\s*tigari\w*))",anunt,flags=re.I|re.M)
        if result10:
            tigari.append(result10)
        # print(anunt,end='\n')  #linie cu linie
    # print(anunturiTextSplit) #*2 cuvinte separate
    # print('\n\n\n')

nrBiciclete=0
nrTriciclete=0
nrMotociclete=0

for line in moduriDeTransport:
    for tupp in line:
        for elem in tupp:
            if "bi" in elem or "Bi" in elem:
                nrBiciclete+=1
            if "tri" in elem or "Tri" in elem:
                nrTriciclete+=1
            if "moto" in elem or "Moto" in elem:
                nrMotociclete+=1        


print("MODURI DE TRANSPORT:\n",f"\tNumar de bicicleta: {nrBiciclete}\n", f"\tNumar de triciclete: {nrTriciclete}\n", f"\tNumar de motociclete: {nrMotociclete}\n", sep = "\n")
    # print(ch, dictPagini[ch],'\n\n', sep='\n\n')    # ALT MOD DE AFISARE

nrPistoale=0
nrBricege=0
nrCutite=0
nrLunete=0

for line in arme:
    for tupp in line:
        for elem in tupp:
            if re.findall("(airsoft)",elem, flags=re.I|re.M):
                nrPistoale+=1
            if re.findall("(briceag)",elem,flags=re.I|re.M):
                nrBricege+=1
            if re.findall("(cutit\w*)",elem,flags=re.I|re.M):
                nrCutite+=1
            if re.findall("(lunet\w*)",elem,flags=re.I|re.M):
                nrLunete+=1
                
print("ARME:\n", f"\tNumar de pistoale airsoft:{nrPistoale}\n", f"\tNumarul de cutite/bricege:{nrCutite+nrBricege}\n",f"\tNumarul de lunete: {nrLunete}\n",sep="\n")


nrCarti=0
nrCd=0
nrEnciclopedii=0
nrPoezii=0
nrTablouri=0

for line in cultura:
    for tupp in line:
        for elem in tupp:
            if re.findall("(cart\w*)",elem,flags=re.I|re.M):
                nrCarti+=1
            if re.findall("(cd\w*)|(cd-\w*)",elem,flags=re.I|re.M):
                nrCd+=1
            if re.findall("(encicloped\w*)",elem,flags=re.I|re.M):
                nrEnciclopedii+=1
            if re.findall("(tablou\w*)",elem,flags=re.I|re.M):
                nrTablouri+=1
            if re.findall("(poez\w*)",elem,flags=re.I|re.M):
                nrPoezii+=1


print("CULTURA:\n",f"\tNumar de carti:{nrCarti}\n",f"\tNumar de enciclopedii:{nrEnciclopedii}\n",f"\tNumar de tablouri:{nrTablouri}\n",f"\tNumar de poezii:{nrPoezii}\n",f"\tNumar de CD-uri:{nrCd}\n",sep="\n")



nrChitara=0
nrVioara=0
nrCasete=0
nrVinil=0


for line in muzica:
    for tupp in line:
        for elem in tupp:
            if re.findall("(v\w*ara|c\w*ara)",elem,flags=re.I|re.M):
                if re.findall("(v\w*ara)",elem,flags=re.I|re.M):
                    nrVioara+=1
                elif re.findall("(ch\w*ara)",elem,flags=re.I|re.M):
                    nrChitara+=1
                    
            if re.findall("(v[iy]n[iy]l\w*)",elem,flags=re.I|re.M):
                nrVinil+=1
            if re.findall("(caset\w*)",elem,flags=re.I|re.M):
                nrCasete+=1
            


print("MUZICA:\n", f"\tNumar de chitare:{nrChitara}\n", f"\tNumarul de vioare:{nrVioara}\n",f"\tNumarul de vinil-uri: {nrVinil}\n",f"\tNumarul de casete:{nrCasete}",sep="\n")


nrMonede=0
nrLei=0
nrBancnote=0

for line in bani:
    for tupp in line:
        for elem in tupp:
            if re.findall("(mone..)",elem,flags=re.I|re.M):
                nrMonede+=1
            if re.findall("(le[iu])",elem,flags=re.I|re.M):
                nrLei+=1
            if re.findall("(bancnot\w*)",elem,flags=re.I|re.M):
                nrBancnote+=1

print("BANI:\n", f"\tNumar de monede:{nrMonede}\n", f"\tNumarul de lei:{nrLei}\n",f"\tNumarul de bancnote: {nrBancnote}\n",sep="\n")


nrSkiuri=0
nrSnowboarduri=0
nrClapari=0

for line in activitatiMontane:
    for tupp in line:
        for elem in tupp:
            if re.findall("(s(k|ch)i\w*)",elem,flags=re.I|re.M):
                nrSkiuri+=1
            if re.findall("(snowboard\w*)",elem,flags=re.I|re.M):
                nrSnowboarduri+=1
            if re.findall("(clapar\w*)",elem,flags=re.I|re.M):
                nrClapari+=1

print("ACTIVITATI MONTANE:\n", f"\tNumar de ski-uri: {nrSkiuri}\n", f"\tNumarul de snowboard-uri: {nrSnowboarduri}\n",f"\tNumarul de clapari: {nrClapari}\n",sep="\n")


nrGeci=0
nrPantaloni=0
nrBluze=0
nrTricouri=0

for line in imbracaminte:
    for tupp in line:
        for elem in tupp:
            if re.findall("(g(eaca|eci)\w*)",elem,flags=re.I|re.M):
                nrGeci+=1
            if re.findall("(pantaloni\w*)",elem,flags=re.I|re.M):
                nrPantaloni+=1
            if re.findall("(bluz[ae]\w*)",elem,flags=re.I|re.M):
                nrBluze+=1
            if re.findall("(tricou\w*)",elem,flags=re.I|re.M):
                nrTricouri+=1

print("IMBRACAMINTE:\n", f"\tNumar de geci: {nrGeci}\n", f"\tNumarul de pantaloni: {nrPantaloni}\n",f"\tNumarul de bluze: {nrBluze}\n",f"\tNumar de tricouri: {nrTricouri}\n",sep="\n")

nrCamereFilm=0
nrCamereDigitale=0
nrPolaroid=0

for line in aparateDeInregistrat:
    for tupp in line:
        for elem in tupp:
            if re.findall("((aparat|camera)\s*(film)\w*)",elem,flags=re.I|re.M):
                nrCamereFilm+=1
            if re.findall("((aparat|camera)\s*(digital|digitala)\w*)",elem,flags=re.I|re.M):
                nrCamereDigitale+=1

print("APARETE DE INREGISTRAT:\n", f"\tNumar de camere pe film: {nrCamereFilm}\n", f"\tNumarul de camere digitale: {nrCamereDigitale}\n",sep="\n")

nrAbdomene=0
nrGantere=0
nrBanciFitness=0
nrBenziAlergare=0

for line in fitness:
    for tupp in line:
        for elem in tupp:
            if re.findall("(abdomen\w*)",elem,flags=re.I|re.M):
                nrAbdomene+=1
            if re.findall("(ganter\w*)",elem,flags=re.I|re.M):
                nrGantere+=1
            if re.findall("(banc(i|a)\s*(piept)\w*)",elem,flags=re.I|re.M):
                nrBanciFitness+=1
            if re.findall("((banda\s*de\s*alerga(t|re)\w*)|(banda\s*alerga(t|re)\w*))",elem,flags=re.I|re.M):
                nrBenziAlergare+=1

print("FITNESS:\n", f"\tNumar de aparate pentru abdomen: {nrAbdomene}\n", f"\tNumarul de gantere: {nrGantere}\n",f"\tNumarul de banci pentru piept: {nrBanciFitness}\n",f"\tNumar de benzi de alergare: {nrBenziAlergare}\n",sep="\n")


nrTigari=0
nrScrumiere=0
nrAparateTigari=0

for line in tigari:
    for tupp in line:
        for elem in tupp:
            if re.findall("(^tigari\w*)",elem,flags=re.I|re.M):
                nrTigari+=1
            if re.findall("(scrum\w*)",elem,flags=re.I|re.M):
                nrScrumiere+=1
            if re.findall("((aparat\s*de\s*rulat\s*tigari\w*)|(aparat\s*\de\s*injectat\s*tigari\w*))",elem,flags=re.I|re.M):
                nrAparateTigari+=1

print("TUTUN:\n", f"\tNumar de tigari: {nrTigari}\n", f"\tNumarul de scrumiere: {nrScrumiere}\n",f"\tNumarul de aparate de facut tigari: {nrAparateTigari}\n",sep="\n")


























#----------------------------------------------------------------------------------------------------------------------------------------------------------------



# for anunt in anunturiText:
#     anunturiTextSplit.append(anunt.split(" "))   #AFISARE PENTRU TOATE CUVINTELE SEPARATE
# print(anunturiTextSplit)


    # print(anunt,end='\n')
             
             
             
             
             
                
#----------------------------------------------------------------------------------------------------------------------------------------------------------------
# for line in div:
#     if "lei" not in str(line):
#         for i in range(len(str(line))):
#             if str(line)[i] == "<" and str(line)[i+1] == "s"  and str(line)[i+2] == "t" and str(line)[i+3] == "r" and str(line)[i+4] == "o" and str(line)[i+5] == "n" and str(line)[i+1] == "s" :
                    
#                 print(str(line)[i+1], end=" ")
        # print(line,end='\n')
        

# str(div).replace(",", "")
# str(div).replace("</strong>", "")


# print(div,end='\n\n')
# print(str(div))


# list = str(div).split("<strong>")
# print(list)