#include "Klassen.h"
#include "GUI.h"

// --- TWurm Operationen -----------------------------------------------------

TWurm::TWurm(int px,int py,char prichtung,TColor pfarbe)
{
 punkte=0; laenge=0;
 x[0]=px;y[0]=py;richtung=prichtung;farbe=pfarbe;
}
TWurm::~TWurm() {}

int TWurm::gibX(int i){return x[i];}
int TWurm::gibY(int i) {return y[i];}
void TWurm::setzeX(int i,int pX) {x[i]=pX;}
void TWurm::setzeY(int i,int pY) {y[i]=pY;}
char TWurm::gibRichtung() {return richtung;}
void TWurm::setzeRichtung(char pRichtung) {richtung=pRichtung;}
int TWurm::gibPunkte() {return punkte;}
void TWurm::setzePunkte(int pPunkte) {punkte=pPunkte;}
int TWurm::gibLaenge() {return laenge;}
void TWurm::setzeLaenge(int pLaenge) {laenge=pLaenge;}
TColor TWurm::gibFarbe() {return farbe;}

// --- KI Operationen --------------------------------------------------------
void TWurm::initKI(TFutter *pFutter1,TFutter *pFutter2,TFutter *pFutter3)
{
 futter[0]=pFutter1;        //Futterobjekte werden übergeben
 futter[1]=pFutter2;
 futter[2]=pFutter3;
 Timer=0;
}
void TWurm::setzeNah(int pNah) {nahesFutter=pNah;}
int TWurm::gibNah() {return nahesFutter;}
void TWurm::setzeTimer(int pTimer) {Timer=pTimer;}
int TWurm::gibTimer() {return Timer;}

void TWurm::ermittleNah()
{//ermittelt den nächsten Futterpunkt, zu dem Wurm gehen soll
 int zahl,abstand[3],i; //differenz zwischen den 3 Futterteilen und Wurm
                        //zahl für die adition der x/y abstände ohne negatives
 for(i=0;i<3;i++)       //für alle 3 futterpunkte
 {
  abstand[i]=500;       //Hoher Abstand, so dass nicht existentes Futter nicht
                        //als nächstes gesehen wird
  if(futter[i]->gibAktiv()==true)   //Falls Futter aktiv
  {
   abstand[i]=futter[i]->gibX()-gibX(0);  //Abstand der X-Werte berechnen
   if(abstand[i]<0) abstand[i]*=-1;    //und falls negativ *-1
   zahl=futter[i]->gibY()-gibY(0);  //das gleiche bei Y werten
   if(zahl<0) zahl*=-1;
   abstand[i]+=zahl;               //Abstand+zahl=abstand
 }}

 for(i=0;i<3;i++)
 {
  if(futter[i]->gibAktiv()==true)   //Falls Futter aktiv
  {
   if(futter[i]->gibTyp()==2) abstand[i]-=10;   //und futter mehr punkte bringt
   if(futter[i]->gibTyp()==3) abstand[i]-=25;   //wird abstand reduziert, dass wurm
 }}                                             //höhere Priorität auf hochpunktiges futter hat

 if((abstand[0]<abstand[1])&&(abstand[0]<abstand[2])) setzeNah(0); //Hier wird ermittelt, welcher abstand der
 if((abstand[1]<abstand[0])&&(abstand[1]<abstand[2])) setzeNah(1); //geringste ist, falls zwei gleich sein sollten
 if((abstand[2]<abstand[0])&&(abstand[2]<abstand[1])) setzeNah(2); //wird der später aufgerufene gesetzt
}

void TWurm::KIRichtung()
{//Falls Futter X kleiner & Wurm nicht entgegengesetzt läuft muss wurm nach oben
 setzeTimer(gibTimer()+1);
 if(gibTimer()<3){
 if((futter[gibNah()]->gibX()<gibX(0))&&(gibRichtung()!='r')) setzeRichtung('l');
 if((futter[gibNah()]->gibX()>gibX(0))&&(gibRichtung()!='l')) setzeRichtung('r');}
 //Falls Futter Y kleiner & Wurm nicht engegengesetzt läuft muss wurm nach links
 if(gibTimer()>=3){
 if((futter[gibNah()]->gibY()<gibY(0))&&(gibRichtung()!='u')) setzeRichtung('o');
 if((futter[gibNah()]->gibY()>gibY(0))&&(gibRichtung()!='o')) setzeRichtung('u');}
 //Noch Timer Reset, dass erst wieder in 3 T_Timer1Timer Ereignissen neue richtung möglich ist
 if(gibTimer()==5)setzeTimer(0);
}

void TWurm::WandZusatz()
{
 //Falls Futterpunkt zB. am linken Rand und Wurm am rechten soll Wurm bei
 //gamemod mit durchgängigen Wänden die Wand als Abkürzung nutzen
 if((futter[gibNah()]->gibX()<70)&&(gibX(0)>330))
 {//Damit Wurm nicht entgegengesetze Richtung einschlägt wird Timer so gesetzt, dass
  if(gibTimer()<3) {setzeTimer(3);return;} //Wurm noch vorher o/u als Richtung hat
  else setzeRichtung('r');   //Dann wird Richtung entsprechend gesetzt
 }
 if((futter[gibNah()]->gibX()>330)&&(gibX(0)<70))
 {
  if(gibTimer()<3) {setzeTimer(3);return;}
  else setzeRichtung('l');
 }
 if((futter[gibNah()]->gibY()<70)&&(gibY(0)>330))
 {//Das gleiche bei Y - Oberer und Unterer Rand
  if(gibTimer()>=3) {setzeTimer(0);return;}
  else setzeRichtung('u');
 }
 if((futter[gibNah()]->gibY()>330)&&(gibY(0)<70))
 {
  if(gibTimer()>=3) {setzeTimer(0);return;}
  else setzeRichtung('o');
 }
}

void TWurm::KISelbst()
{//Verhindert, dass KI mit sich selbst Kollidiert siehe auch TSteuerung::AbfrageSelbst()
 int i,j,k;
 for(i=1;i<=gibLaenge();i++)
 {//Für Alle Teile des Wurmes
  for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
  {for(k=0;k<10;k++)
   {if(((gibX(0)  ==gibX(i)-20)&&
        (gibY(0)+k==gibY(i)))||
       ((gibX(0)+j==gibX(i)+10)&&
        (gibY(0)+k==gibY(i))))
        setzeTimer(3);
    if(((gibY(0)  ==gibY(i)-20)&&
        (gibX(0)+k==gibX(i)))||
       ((gibY(0)+j==gibY(i)+10)&&
        (gibX(0)+k==gibX(i))))
        setzeTimer(0);
}}}}

// ---------------------------------------------------------------------------

// --- TFutter Operationen ---------------------------------------------------

TFutter::TFutter() {setzeAktiv(false);createFutter();}
TFutter::~TFutter() {}
void TFutter::createFutter()
 {
  x=rand() % 340;       //Zufallswerte durch rand() ermittelt
  y=rand() % 340;
  x+=30;                //damit nicht an 0,10
  y+=30;
  Futtertyp();
  setzeAktiv(true);
 }
void TFutter::Futtertyp()
 {
  int futter;
  futter=rand() % 10;    //für die zufallsauswahl welcher futtertyp erstellt wird
  switch (futter)
   {//Je mehr Cases ein Futtertyp hat umso höhere Wahrscheinlichkeit hat dieser auch
    case 0:case 1:case 2:case 3:case 7:case 9:case 10:
    futtertyp=1;
    futterfarbe=clGreen;
    break;
    case 4:case 5:case 6:
    futtertyp=2;
    futterfarbe=clRed;
    break;
    case 8:
    futtertyp=3;
    futterfarbe=clYellow;
    break;
   }            
 }
int TFutter::gibX()   {return x;}
int TFutter::gibY()   {return y;}
int TFutter::gibTyp() {return futtertyp;}
TColor TFutter::gibFarbe() {return futterfarbe;}
bool TFutter::gibAktiv() {return aktiv;}
void TFutter::setzeAktiv(bool pAktiv) {aktiv=pAktiv;}
//----------------------------------------------------------------------------


// --- TSpielEinstellung Operationen -----------------------------------------
TSpielEinstellung::TSpielEinstellung() {gamemod=0;anzahlSpieler=0;}
TSpielEinstellung::~TSpielEinstellung() {}
int TSpielEinstellung::gibGamemod() {return gamemod;}
int TSpielEinstellung::gibAnzahl()  {return anzahlSpieler;}
bool TSpielEinstellung::gibKI() {return KI;}
void TSpielEinstellung::setzeGamemod(int g) {gamemod=g;}
void TSpielEinstellung::setzeAnzahl(int a)  {anzahlSpieler=a;}
void TSpielEinstellung::setzeKI(bool pKI) {KI=pKI;}

//----------------------------------------------------------------------------


// --- TSteuerung Operationen ------------------------------------------------
TSteuerung::TSteuerung() {spiel=new TSpielEinstellung;}
TSteuerung::~TSteuerung() {}

void TSteuerung::setEinstellungen()
{//Spiel Einstellungen werden in die vorgesehene Klasse übergeben und gespeichert
 if(F_Worm->gibAnzahlAuswahl()==0) spiel->setzeAnzahl(0);
 if(F_Worm->gibAnzahlAuswahl()==1) {spiel->setzeAnzahl(1);spiel->setzeKI(true);}
 if(F_Worm->gibAnzahlAuswahl()==2) spiel->setzeAnzahl(1);
 //<-Anzahl der Spieler aus Oberfläche entnehmen und je nach modus weitergeben
 spiel->setzeGamemod(F_Worm->gibGameModAuswahl()); //Das gleiche für Gamemodus
 F_Worm->terminateMainMenu();   //Hauptmenü wird deaktiviert
}

void TSteuerung::createGame()
{
 F_Worm->createTable();   //Oberfläche wird bemalt, Spielfeld erstellt
 F_Worm->TimerReset();    //Timer auf Null setzen(für Countdown(s.Countdown())
 F_Worm->createGameMenu(); //SpielMenüFläche wird erzeugt
 wurm[0]=new TWurm(40,40,'r',clBlue); //Wurmobjekt für Einzelspieler wird erstellt
 //Falls Zwei Spieler, wird zweites Objekt erzeugt
 if(spiel->gibAnzahl()==1) wurm[1]=new TWurm(300,300,'l',clMaroon);
 int w;
 for(w=0;w<=spiel->gibAnzahl();w++)
 {//Je nach Anzahl w der Spieler werden Würmer gezeichnet
  F_Worm->zeichne(wurm[w]->gibFarbe(), wurm[w]->gibX(0), wurm[w]->gibY(0));  //Wurm wird gezeichnet
 }
 int f;
 for(f=0;f<3;f++)   //Alle 3 Futterobjekte werden erstellt
 {futter[f]=new TFutter();}
 if(spiel->gibKI()==true) wurm[1]->initKI(futter[0],futter[1],futter[2]);
 F_Worm->starteTimer();  //Timerstart und somit übergabe zu T_Timer1Timer()
}

void TSteuerung::Countdown()      //Countdown zählt runter bevor spiel startet
{
 if (F_Worm->T_Timer1->Tag<4)  //Bis TimerTag==3 wird 3 angezeigt
 {                       //Je höher die bedingung desto länger die Anzeige
  F_Worm->LCountdown('3',true); //der einzelnen Countdown stadien
  F_Worm->T_Timer1->Tag++;  //wichtig, damit nicht innerhalb milisekunden
  return;               //alles durchgezählt ist
 }
 if (F_Worm->T_Timer1->Tag<8) //bis zu Tag==7 wird 2 angezeigt
 {
  F_Worm->LCountdown('2',true); //Anzeige der Zahl im dafür vorgesehenen Label
  F_Worm->T_Timer1->Tag++;  //Tag erhöhen um in nächste CDStufe zu kommen
  return;   //Operation beendet, wird zurückgegeben bis zum nächsten T_TimerTimer()
 }
 if (F_Worm->T_Timer1->Tag<12) //bis zu Tag==11 wird 1 angezeigt
 {
  F_Worm->LCountdown('1',true);
  F_Worm->T_Timer1->Tag++;
  return; //erforderlich dass nicht immer 1 steht, da Tag<12==Tag<4
 }
 if (F_Worm->T_Timer1->Tag==12) //Bei Tag==12 wird CDLabel unsichtbar
 {
  F_Worm->LCountdown('0',false);
  F_Worm->T_Timer1->Tag++; //noch einmal erhöht
  if(spiel->gibGamemod()==4) GameOver(); //Chuck Norris Modus
  return;
 }
 if (F_Worm->T_Timer1->Tag>6) //und ab da immer gleich der Spielzug gestartet
 {
  int w;      //der wird je nach Anzahl der Spieler 1 o. 2 mal durchlaufen
  for(w=0;w<=spiel->gibAnzahl();w++)
  {Spielzug(w);}
 }
}
//---------------------------------------------------------------------------
                                                         // ===========
void TSteuerung::Spielzug(int w)                         // Spielzug ||
{                                                        // ===========
 int f,i;
 for(f=0;f<=2;f++)
 {//Alle 3 Futterobjekte werden neu gezeichnet
  if(futter[f]->gibAktiv()==true)
   {//Falls sie Aktiv sind
    F_Worm->zeichne(futter[f]->gibFarbe(),futter[f]->gibX(),futter[f]->gibY());
 } }

 for(i=wurm[w]->gibLaenge();i>0;i--)
 {//Alter Wurm wird in kompletter Länge neu übermalt
  F_Worm->ClearPosition(wurm[w]->gibX(i),wurm[w]->gibY(i),10);
 }//Also alte position des einen jetzt neue pos des darauffolgenden Wurmteils
 //Kopf wird immer übermalt auch wenn Laenge=0
 F_Worm->ClearPosition(wurm[w]->gibX(0),wurm[w]->gibY(0),10);

 //KI eingaben wie Richtungsänderung etc.
 if(spiel->gibKI()==true) KIZug();

 Bewegung(w);   //siehe TSteuerung::Bewegung()
 AbfrageWand(w); //siehe TSteuerung::AbfrageWand()
 AbfrageSelbst(w); //siehe TSteuerung::AbfrageSelbst()

 for(i=wurm[w]->gibLaenge();i>0;i--)
 {
  wurm[w]->setzeX(i,wurm[w]->gibX(i-1)); //außerdem wird der komplette Wurm eines nach vorne geschoben
  wurm[w]->setzeY(i,wurm[w]->gibY(i-1)); //indem die werte des Punktes davor an den danach übergeben werden
 }


 for(f=0;f<=2;f++)
 {//für alle drei futterobjekte
  if(futter[f]->gibAktiv()==true)
  {//Falls der jeweilige gerade aktiv ist
   if(AbfrageFutter(wurm[w]->gibX(0),wurm[w]->gibY(0),f)) {Punktgeholt(f,w);}
 }}//wird überprüft ob das Futter gerade vom Wurm gefressen wird und falls ja
 //bekommt der Wurm einen Punkt/Länge je nach Futtertyp

 if (w==0) //Falls gerade die Abfrage über Spieler 1 läuft werden dessen Punkte angezeigt
  {F_Worm->EPunkte0("Punkte: "+IntToStr(wurm[0]->gibPunkte()),true);}
 if (w==1) //ebenso falls Spieler 2 gerade am Zug ist, werden dessen Punkte aktualisiert
  {F_Worm->EPunkte1("Punkte: "+IntToStr(wurm[1]->gibPunkte()),true);}

 for(i=0;i<=wurm[w]->gibLaenge();i++)
  {//Neuer Wurm wird in Kompletter Länge gezeichnet
   F_Worm->zeichne(wurm[w]->gibFarbe(), wurm[w]->gibX(i), wurm[w]->gibY(i));       //Neuen Wurm malen
  }
}

void TSteuerung::Bewegung(int w)
{//Je nach Richtung wird X/Y des Wurmkopfes so verändert, dass es einer bewegung
 //auf der oberfläche gleichkommt
 switch (wurm[w]->gibRichtung())     //Neue Werte je nach Richtung zuweisen
 {
  case 'l':
    wurm[w]->setzeX(0,wurm[w]->gibX(0)-10);
    break;
  case 'o':
    wurm[w]->setzeY(0,wurm[w]->gibY(0)-10);
    break;
  case 'r':
    wurm[w]->setzeX(0,wurm[w]->gibX(0)+10);
   break;
  case 'u':
    wurm[w]->setzeY(0,wurm[w]->gibY(0)+10);
   break;
 }
}

void TSteuerung::AbfrageWand(int w)
{//Je nach Spielmodus-Also hier ob Wände durchlässig oder nicht
 //wird Kollision mit Wand berechnet und Wurm an andere Wand gesetzt
 //oder Spiel beendet
 switch(spiel->gibGamemod())
  {
   case 0:case 2://Bei Spielmodus Endlos und Harte Würmer
     if (wurm[w]->gibX(0)>370)    wurm[w]->setzeX(0,20); //Wurm wird auf andere
     if (wurm[w]->gibX(0)<20)     wurm[w]->setzeX(0,370);//Randseite gesetzt
     if (wurm[w]->gibY(0)>370)    wurm[w]->setzeY(0,20);
     if (wurm[w]->gibY(0)<20)     wurm[w]->setzeY(0,370);
   break;
   case 1:case 3://Bei Spielmodus Harte Wände und Alles Hart
     if (wurm[w]->gibX(0)>370)    GameOver(); //Bei Kollision mit Wand wird
     if (wurm[w]->gibX(0)<20)     GameOver(); //Spiel beendet
     if (wurm[w]->gibY(0)>370)    GameOver();
     if (wurm[w]->gibY(0)<20)     GameOver();
   break;
} }

void TSteuerung::AbfrageSelbst(int w)
{//Falls Wurm mit sich selbst oder anderem Wurm Kollidiert wird je nach Spielmodus
 //bestraft oder aber Spiel beendet
 int i,j,k;
 bool kollision=false;
 for(i=1;i<=wurm[w]->gibLaenge();i++)
 {//Für Alle Teile des Wurmes
  for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
  {//Nicht nur für Punkt(x|y) sondern den kompletten Wurmpunkt
   if(wurm[w]->gibX(0)+j==wurm[w]->gibX(i))
   {//Falls sich Würmer in X Werten berühren
    for(k=0;k<10;k++)
    {//und sich auch noch in Y Werten berühren
     if(wurm[w]->gibY(0)+k==wurm[w]->gibY(i))
     kollision=true; //ist eine Kollision vorhanden
  }}}
  //Das gleiche nochmal mit Y-Wert zuerst für besondere AbfrageSicherheit
  for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
  {for(k=0;k<10;k++)
   {if((wurm[w]->gibX(0)+k==wurm[w]->gibX(i))&&
      (wurm[w]->gibY(0)+j==wurm[w]->gibY(i)))
       kollision=true;
 }}}//--------------------------------------------------------------------
 if (spiel->gibAnzahl()>0)
 {//Bei zwei Spielern die Abfrage nochmal nur mit Werten des anderen Wurmes
  int b; //b ist der wurm, der gerade nicht aktiven Zug macht
  if(w==0) b=1; //b immer Gegenteil von gerade aktivem Wurm
  if(w==1) b=0;
  for (i=0;i<=wurm[b]->gibLaenge();i++)
  {//Für Alle Teile des anderen Wurmes
   for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
   {//Nicht nur für Punkt(x|y) sondern den kompletten Wurmpunkt
    for(k=0;k<10;k++)
    {//Falls sich Würmer an x/y positionen schneiden
     if((wurm[w]->gibX(0)+j==wurm[b]->gibX(i))&&
       (wurm[w]->gibY(0)+k==wurm[b]->gibY(i)))
        kollision=true; //ist eine Kollision vorhanden
   }}
   //Das gleiche nochmal mit Y-Wert zuerst für besondere AbfrageSicherheit
   for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
   {for(k=0;k<10;k++)
    {if((wurm[w]->gibY(0)+j==wurm[b]->gibY(i))&&
       (wurm[w]->gibX(0)+k==wurm[b]->gibX(i)))
        kollision=true;
 }}}}

 switch(spiel->gibGamemod())
 {
  case 0:case 1://Bei Spielmodus Endlos und Harte Wände
  if(kollision==true) Kollision(w);
  break;
  case 2:case 3://Bei Spielmodus Harte Würmer und Alles Hart
  if(kollision==true) GameOver();
  break;
}}

bool TSteuerung::AbfrageFutter(int px, int py, int f)
{
 bool frisst=false;
 int i,j;   //vgl TSteuerung::AbfrageSelbst()
 for(i=0;i<10;i++)      //Abfrage ob irgend ein y Wert mit futter gleich
 {for(j=0;j<10;j++)     //Zusatzabfrage ob irgendein x Wert gleich liegt
  {if(((py+i)==futter[f]->gibY())&&
     ((px+j)==futter[f]->gibX()))
      {frisst=true;}
 }}                  //ziemlich merkwürdiges Problem= zählt immernoch lediglich
                     //wenn Futter Punkt x,y berührt wird
 for (i=0;i<10;i++)  //Problemlösung=Alle futterpunkte werden abgefragt
 {for (j=0;j<10;j++)
  {if (((futter[f]->gibX()+i)==px)&&             //Gleiche Methode wie bei der Wurmpunktabfrage
      ((futter[f]->gibY()+j)==py))
       {frisst=true;}
 }}
 return frisst;
}
void TSteuerung::Punktgeholt(int f, int w)
{                                             //je nach futtertyp werden punkte+Boni verteilt
 if(futter[f]->gibTyp()==1)
 {wurm[w]->setzePunkte(wurm[w]->gibPunkte()+1);  //Bei Futtertyp 1(Grünem Futter)
  wurm[w]->setzeLaenge(wurm[w]->gibLaenge()+1);} //Punkt und Länge um 1 erweitern
 if(futter[f]->gibTyp()==2)
 {wurm[w]->setzePunkte(wurm[w]->gibPunkte()+2);  //Bei Futtertyp 2(Blauem Futter)
  wurm[w]->setzeLaenge(wurm[w]->gibLaenge()+1);} //Punkt um 2, länge um 1 erhöhen
 if(futter[f]->gibTyp()==3)
 {wurm[w]->setzePunkte(wurm[w]->gibPunkte()+2);}  //Bei Futtertyp 3(Gelbem Futter) wird nur Punkt+2 erhöht
 F_Worm->ClearPosition(futter[f]->gibX(),futter[f]->gibY(),10);  //altes Futter wird übermalt
 futter[f]->setzeAktiv(false); //Das gerade gefressene Futter als Inaktiv/gefressen definieren
 newFutter();        //neues Futter wird erstellt
}

void TSteuerung::Taste(int pSteuerung)
{
 switch (pSteuerung)
 {
  case 37:    //Pfeiltaste links
     if (wurm[0]->gibRichtung()!='r') //Falls Wurm nicht entgegengesetzt fährt
      wurm[0]->setzeRichtung('l');   //Richtung Tastendruck entsprechend ändern
     break;
  case 38:   //Pfeiltaste oben
     if (wurm[0]->gibRichtung()!='u')
      wurm[0]->setzeRichtung('o');
     break;
  case 39:  //Pfeiltaste rechts
     if (wurm[0]->gibRichtung()!='l')
      wurm[0]->setzeRichtung('r');
     break;
  case 40: //Pfeiltaste unten
     if (wurm[0]->gibRichtung()!='o')
      wurm[0]->setzeRichtung('u');
     break;
  case 87: //Taste W - Zweiter Spieler oben
     if ((spiel->gibAnzahl()==1)&&   //Nur reagieren falls 2 Spieler aktiv
         (spiel->gibKI()==false))    //und der 2. nicht Computergesteuert ist
     {if (wurm[1]->gibRichtung()!='u')
       wurm[1]->setzeRichtung('o');}
     break;
  case 65: //Taste A - Zweiter Spieler links
     if ((spiel->gibAnzahl()==1)&&
         (spiel->gibKI()==false))
     {if (wurm[1]->gibRichtung()!='r')
       wurm[1]->setzeRichtung('l');}
     break;
  case 83: //Taste S - Zweiter Spieler unten
     if ((spiel->gibAnzahl()==1)&&
         (spiel->gibKI()==false))
     {if (wurm[1]->gibRichtung()!='o')
       wurm[1]->setzeRichtung('u');}
     break;
  case 68: //Taste D - Zweiter Spieler rechts
     if ((spiel->gibAnzahl()==1)&&
         (spiel->gibKI()==false))
     {if (wurm[1]->gibRichtung()!='l')
       wurm[1]->setzeRichtung('r');}
     break;
 }
}

void TSteuerung::newFutter()
{
 int i,f;
 i=rand() % 10;      //Dass Futtertyp zufällig bestimmt wird
 switch(i)
 {           //1-10 als möglichkeit, je mehr Case auf den einen Futtertyp, desto höhere
  case 0:case 1:case 2:case 3:case 4:case 9:case 10:case 7:  //Wahrscheinlichkeit, dass dieser
    if(futter[0]->gibAktiv()==false)   //in aktiviert wird
    {//Hier nur ein Futter erstellen
     futter[0]->createFutter();
     //Abfrage dass Futter nicht unterm Wurm erscheint, wird wiederholt, bis nicht mehr drunter liegt
     if(FutterAufWurm(0)==true) futter[0]->createFutter();
     //Die Abfrage wird leider nur einmal durchlaufen, also geringe Sicherheit,
     //jedoch hat sich bei eingliderung in Schleife
     //while(FutterAufWurm(0)==true)futter[0]->createFutter immer das Problem gestellt, dass Spiel gern hängen geblieben ist
     F_Worm->zeichne(futter[0]->gibFarbe(),futter[0]->gibX(),futter[0]->gibY());
    }
  break;
  case 5:case 6:
    for(f=0;f<=1;f++)
    {//Hier 2 Futter erstellen
     if(futter[f]->gibAktiv()==false)
     {//Falls zb Futter 1 schon aktiv, muss nur noch futter 2 erstellt werden
      futter[f]->createFutter();  //verhindert loses futter mit längst neuen werten auf Oberfläche
      //Für Operation FutterAufWurm siehe TSteuerung::FutterAufWurm()
      if(FutterAufWurm(f)==true) futter[f]->createFutter();
      F_Worm->zeichne(futter[f]->gibFarbe(),futter[f]->gibX(),futter[f]->gibY());
    }}
  break;
  case 8:
    for(f=0;f<=2;f++)
    {//Hier 3 Futter auf Spielfeld erstellen
     if(futter[f]->gibAktiv()==false)
     {
      futter[f]->createFutter(); //siehe TSteuerung::createFutter()
      if(FutterAufWurm(f)==true) futter[f]->createFutter();
      F_Worm->zeichne(futter[f]->gibFarbe(),futter[f]->gibX(),futter[f]->gibY());
    }}
  break;
}}



bool TSteuerung::FutterAufWurm(int f)
{//Hier wird überprüft ob der Futterpunkt direkt auf/unterm Wurm erstellt wird
 //und gegebenenfalls neu erstellt
 int w,i,j,k;
 bool kollision;
 for(w=0;w<=spiel->gibAnzahl();w++)
 {//Abfrage für beide Würmer falls Mehrspieler
  for (i=0;i<wurm[w]->gibLaenge();i++)
  {//Für die komplette länge der Würmer
   for(j=0;j<10;j++)
   {for(k=0;k<10;k++)
    {//Für die komplette Wurmbreite(siehe TSteuerung::AbfrageFutter())
     if(AbfrageFutter(wurm[w]->gibX(i)+j,wurm[w]->gibY(i)+k,f)==true) kollision=true;
   }}
   for(j=0;j<10;j++)
   {for(k=0;k<10;k++)
    {//zweite Sicherheitsabfrage(siehe TSteuerung::AbfrageFutter())
     if(AbfrageFutter(wurm[w]->gibX(i)+k,wurm[w]->gibY(i)+j,f)==true) kollision=true;
   }}
 }}
 return kollision;
}

void TSteuerung::AbfrageKI()
{
 int i,j,k;
 for (i=0;i<=wurm[0]->gibLaenge();i++)
 {//Für Alle Teile des anderen Wurmes
   for(j=0;j<10;j++)    //siehe auch TSteuerung::AbfrageFutter()
    {for(k=0;k<10;k++)
     {//Falls sich Würmer an x/y positionen schneiden
      if(((wurm[1]->gibX(0)==wurm[0]->gibX(i)-30)&&
          (wurm[1]->gibY(0)+j==wurm[0]->gibY(i)+k))||
         ((wurm[1]->gibX(0)+10==wurm[0]->gibX(i)+30)&&
          (wurm[1]->gibY(0)+j==wurm[0]->gibY(i)+k)))
        wurm[1]->setzeTimer(3);
        //Wird Timer so gesetzt, dass KI nur noch andere Richtung wählen kann
      if(((wurm[1]->gibY(0)==wurm[0]->gibY(i)-30)&&
          (wurm[1]->gibX(0)+j==wurm[0]->gibX(i)+k))||
         ((wurm[1]->gibY(0)+10==wurm[0]->gibY(i)+30)&&
          (wurm[1]->gibX(0)+j==wurm[0]->gibX(i)+k)))
        wurm[1]->setzeTimer(0);
}}  }}


void TSteuerung::KIZug()
{
 wurm[1]->ermittleNah();    //nächstes Futter wird anvisiert
 AbfrageKI();      //Kollision mit anderem Wurm wird vermieden
 wurm[1]->KISelbst(); //Kollision mit sich selbst wird verhindert
 //Neue Richtung wird nach 3 Timerereignissen gesetzt
 wurm[1]->KIRichtung();
 wurm[1]->WandZusatz();     //Abkürzung wird gesucht
 //Näheres hierzu in den einzelnen Operationsdefinitionen
}



void TSteuerung::Kollision(int w)
{
 if(wurm[w]->gibLaenge()>0) //Nur wenn der Länge noch was abgezogen werden kann
 {//Wird die Länge um 1 vermindert
  wurm[w]->setzeX(wurm[w]->gibLaenge(),0); //Letztes Array X/Y wert wird geleert
  wurm[w]->setzeY(wurm[w]->gibLaenge(),0); //Also mit 0/0 überschrieben
  wurm[w]->setzeLaenge(wurm[w]->gibLaenge()-1);
  wurm[w]->setzeX(0,wurm[w]->gibX(1)); //der Wurm um eins zurückgesetzt dass er nicht durch
  wurm[w]->setzeY(0,wurm[w]->gibY(1)); //den widerstand einfach hindurch kommt
 }
 if(wurm[w]->gibPunkte()>1) //Nur falls der Spieler noch Punkte hat können abgezogen werden
  wurm[w]->setzePunkte(wurm[w]->gibPunkte()-1);
}

void TSteuerung::GameOver()
{
 F_Worm->stoppeTimer();   //Timer Wird gestoppt
 F_Worm->L_GameOver->Visible=true;     //Spielende GameOverLabel wird angezeigt
 F_Worm->LEndPunkte0("Wurm 1: "+IntToStr(wurm[0]->gibPunkte())+" Kilo", true);
 if(spiel->gibAnzahl()>0) //EndPunktzahl für Spieler 1 und falls vorhanden Spieler 2 anzeigen
 F_Worm->LEndPunkte1("Wurm 2: "+IntToStr(wurm[1]->gibPunkte())+" Kilo", true);
}

void TSteuerung::exit()
{//Spiel beenden/Alle Objekte löschen/Speicher freigeben
 int i;
 for(i=0;i<3;i++)
 {delete futter[i];}
 for(i=0;i<=spiel->gibAnzahl();i++)
 {delete wurm[i];}
 delete spiel;
 }









