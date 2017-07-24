#ifndef KlassenH
#define KlassenH

#include <vcl.h>


////////////////////////////////////////////////////////////////////////////////
// ::ANMERKUNGEN::                                                            //
// ===============                                                            //
// Indexlegende:   w=Wurm (welcher User)                                      //
//                 l=laenge (die einzelnen wurmteile x/y-Array)               //
//                 g=Gamemodus (Schwierigkeitsgrad)                           //
//                 a=anzahl der spieler                                       //
//                 i/j/k=Schleifenindex                                       //
//                 f=Futterarray                                              //
//                                                                            //
// Dieses Programm wurder erstellt von                                        //
//     Dominik Kress; Lisa Schmierer;                                         //
////////////////////////////////////////////////////////////////////////////////

class TFutter
      {
       private: int x,y;
                bool aktiv;
                int futtertyp;       // futtertyp wird bestimmt für Farbe und Bonus
                TColor futterfarbe;  // zum beispiel ob futter schneller, langsamer
                                     // oder kleiner ohne Punktverlust macht
                void Futtertyp();
       public:  TFutter();    ~TFutter();
                void createFutter();
                int gibX();
                int gibY();
                int gibTyp();
                TColor gibFarbe();
                bool gibAktiv();
                void setzeAktiv(bool pAktiv);
      };

class TWurm
      {
        private:  int x[500], y[500];
                  char richtung;
                  int laenge,punkte;
                  TColor farbe;
                  //KI Attribute
                  //------------------------
                  int nahesFutter;     // Attribut das bestimmt zu welchem futter wurm laufen soll
                  int Timer;           // Attribut das den Tag weitergibt
                  TFutter* futter[3];  // Adressübergabe des Futters

        public:   TWurm(int px,int py,char prichtung,TColor pfarbe);
                  ~TWurm();
                  int gibX(int i);
                  int gibY(int i);
                  void setzeX(int i,int pX);
                  void setzeY(int i,int pY);
                  char gibRichtung();
                  void setzeRichtung(char pRichtung);
                  int gibPunkte();
                  void setzePunkte(int pPunkte);
                  int gibLaenge();
                  void setzeLaenge(int pLaenge);
                  TColor gibFarbe();
                  //KI Operationen
                  //-------------------------
                  void initKI(TFutter *pFutter1,TFutter *pFutter2,TFutter *pFutter3);
                  void setzeNah(int pNah);
                  int gibNah();
                  void setzeTimer(int pTimer);
                  // Timer soll verhindern dass Wurm bei jedem Tag x+y Wert verändert
                  //um nicht direkten sondern etwas realistischeren Weg zu wählen
                  int gibTimer();
                  void ermittleNah();
                  void KIRichtung();
                  void WandZusatz();
                  void KISelbst();
       };

class TSpielEinstellung
      {
       private: int gamemod; //Bestimmt ob mit durchlässigen Wänden/Würmern/Alles Hart/...
                int anzahlSpieler;//Wieviele Würmer
                bool KI;   //Ein Wurm Computer gesteuert?
       public: TSpielEinstellung();
               ~TSpielEinstellung();
               int gibGamemod();
               int gibAnzahl();
               bool gibKI();
               void setzeGamemod(int g);
               void setzeAnzahl(int a);
               void setzeKI(bool pKI);
      };

class TSteuerung
      {
       private: TWurm *wurm[2];
                TFutter* futter[3];
                TSpielEinstellung *spiel;
                void Spielzug(int w);
                void Bewegung(int w);
                void AbfrageWand(int w);
                void AbfrageSelbst(int w);
                bool AbfrageFutter(int px, int py, int f);
                void Punktgeholt(int f, int w);
                void newFutter();
                bool FutterAufWurm(int f);
                void AbfrageKI();
                void KIZug();
                void Kollision(int w);
                void GameOver();

       public:  TSteuerung();
                ~TSteuerung();
                void setEinstellungen();
                void createGame();
                void Countdown();
                void Taste(int pSteuerung);
                void exit();
      };

#endif


