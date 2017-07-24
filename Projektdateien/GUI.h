//---------------------------------------------------------------------------

#ifndef GUIH
#define GUIH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Klassen.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TF_Worm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TTimer *T_Timer1;
        TLabel *L_Countdown;
        TLabel *M_Exit;
        TLabel *GM_Neu;
        TLabel *GM_Pause;
        TLabel *GM_Weiter;
        TLabel *L_Titel1;
        TLabel *L_Titel2;
        TLabel *L_MAnzahl;
        TRadioGroup *MM_WurmAnzahl;
        TLabel *L_MGameMod;
        TRadioGroup *MM_GameMod;
        TButton *MM_IAnzahl;
        TButton *MM_IGameMod;
        TButton *MM_Start;
        TLabel *L_EndPunkte0;
        TLabel *L_EndPunkte1;
        TLabel *L_GameOver;
        TEdit *E_Punkte0;
        TEdit *E_Punkte1;
        void __fastcall T_Timer1Timer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall GM_PauseClick(TObject *Sender);
        void __fastcall GM_WeiterClick(TObject *Sender);
        void __fastcall M_ExitClick(TObject *Sender);
        void __fastcall MM_IAnzahlClick(TObject *Sender);
        void __fastcall MM_IGameModClick(TObject *Sender);
        void __fastcall MM_StartClick(TObject *Sender);
        void __fastcall GM_NeuClick(TObject *Sender);


private:	TSteuerung control;
public:		void createTable();
                void ClearAll();
                void ClearPosition(int px,int py, int breite);
                void zeichne(TColor pfarbe, int px, int py);
                void TimerReset();
                void stoppeTimer();
                void starteTimer();
                void Schneller();
                void Langsamer();
                void LCountdown(AnsiString pCount, bool vis);
                void EPunkte0(AnsiString pPunkte, bool vis);
                void EPunkte1(AnsiString pPunkte, bool vis);
                void LEndPunkte0(AnsiString pPunkte, bool vis);
                void LEndPunkte1(AnsiString pPunkte, bool vis);
                void MenuInfoAnzahl ();
                void MenuInfoGameMod();
                void createMainMenu();
                void terminateMainMenu();
                int gibAnzahlAuswahl();
                int gibGameModAuswahl();

                void createGameMenu();
                void terminateGameMenu();



        __fastcall TF_Worm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF_Worm *F_Worm;
//---------------------------------------------------------------------------
#endif
