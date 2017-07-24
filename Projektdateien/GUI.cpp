//---------------------------------------------------------------------------
#include <vcl.h>           	//visuelle Komponentenbibliothek einbinden
#pragma hdrstop            	//Compilerdirektive Ende Bibliothekseinbindungen
#include "gui.h"           	//Headerdatei einbinden

//---------------------------------------------------------------------------
#pragma package(smart_init)	//Compilerdirektive Initialisierungsart
#pragma resource "*.dfm"   	//Compilerdirektive Oberflächenaufbau in gui.dfm speichern

TF_Worm *F_Worm;           	//globale Deklaration Oberflächenobjekt F_Worm


//----- EIGENE OBERFLÄCHEN FUNKTIONEN ---------------------------------------
//---------------------------------------------------------------------------

// Spielfeldfunktionen ------------------------------------

void TF_Worm::createTable()
     {
      F_Worm->Canvas->Brush->Color=clBlack;                //Schwarzer Rand wird erstellt
      F_Worm->Canvas->FillRect(Rect(0,0,400,425));
      F_Worm->Canvas->Brush->Color=clWhite;                //Weißes Spielfeld wird auf Rand gesetzt
      F_Worm->Canvas->FillRect(Rect(20,20,380,380));
     }


// Löschfunktionen ----------------------------------------

void TF_Worm::ClearAll()
     {
      F_Worm->Canvas->Brush->Color = clWhite;              //Komplettes Spielfeld wird übermalt
      F_Worm->Canvas->FillRect(Rect(20, 20, 380, 380));
     }
void TF_Worm::ClearPosition(int px,int py, int breite)
     {
      F_Worm->Canvas->Brush->Color = clWhite;              //Nur Punkt an Koordinaten-Koordinaten+10
      F_Worm->Canvas->FillRect(Rect(px,py,px+breite,py+breite));    //wird übermalt
     }

// Wurmfunktionen -----------------------------------------

void TF_Worm::zeichne(TColor pfarbe, int px, int py)
 {
  F_Worm->Canvas->Brush->Color = pfarbe;
  F_Worm->Canvas->FillRect(Rect(px, py, px+10, py+10));
 }


// Timerfunktionen ----------------------------------------
void TF_Worm::TimerReset()
 {
  F_Worm->T_Timer1->Interval=100;
  F_Worm->T_Timer1->Tag=0;
 }

void TF_Worm::stoppeTimer()
 {
  F_Worm->T_Timer1->Enabled = false;
 }
void TF_Worm::starteTimer()
 {
  F_Worm->T_Timer1->Enabled = true;
 }
void TF_Worm::Schneller()
 {
  F_Worm->T_Timer1->Interval-=50;
 }
void TF_Worm::Langsamer()
 {
  F_Worm->T_Timer1->Interval+=50;
 }

// Meldefunktionen ----------------------------------------
void TF_Worm::LCountdown(AnsiString pCount, bool vis)
 {
  L_Countdown->Caption = pCount;
  L_Countdown->Visible = vis;
 }
void TF_Worm::EPunkte0(AnsiString pPunkte,bool vis)
 {
  E_Punkte0->Text = pPunkte;
  E_Punkte0->Visible=vis;
 }
void TF_Worm::EPunkte1(AnsiString pPunkte,bool vis)
 {
  E_Punkte1->Text = pPunkte;
  E_Punkte1->Visible=vis;
 }
void TF_Worm::LEndPunkte0(AnsiString pPunkte, bool vis)
 {
  L_EndPunkte0->Caption = pPunkte;
  L_EndPunkte0->Visible = vis;
 }
void TF_Worm::LEndPunkte1(AnsiString pPunkte, bool vis)
 {
  L_EndPunkte1->Caption = pPunkte;
  L_EndPunkte1->Visible = vis;
 }
void TF_Worm::MenuInfoAnzahl()
 {
  ShowMessage("1 Wurm ~ 1 Spieler \n ->Einfacher Singleplayer \n\n2 Würmer ~ 1 Spieler\n  ->Ein Spieler gegen einen Computergesteuerter Wurm\n\n2 Würmer ~ 2 Spieler\n  ->Spieler gegen Spieler");
 }
void TF_Worm::MenuInfoGameMod()
 {
  ShowMessage("Endlos\n  -> Wurm geht nie kaputt\n\nHarte Wände\n  -> Wände undurchlässig\n\nHarte Würmer\n  -> Falls Kollision mit Wurm Spiel verloren\n\nAlles Hart\n  -> Harte Wände + Harte Würmer\n\nCuck Norris Mode\n  -> Only Chuck Norris could win!");
 }

// Menüfunktionen -----------------------------------------
// Main Menu
void TF_Worm::createMainMenu()
 {
  F_Worm->Canvas->Brush->Color=clWhite;
  F_Worm->Canvas->FillRect(Rect(0,0,400,425));
  L_Titel1     -> Visible = true;
  L_Titel2     -> Visible = true;
  L_MAnzahl    -> Visible = true;
  L_MGameMod   -> Visible = true;
  M_Exit       -> Visible = true;   M_Exit       -> Enabled = true;
  MM_WurmAnzahl-> Visible = true;   MM_WurmAnzahl-> Enabled = true;
  MM_GameMod   -> Visible = true;   MM_GameMod   -> Enabled = true;
  MM_IAnzahl   -> Visible = true;   MM_IAnzahl   -> Enabled = true;
  MM_IGameMod  -> Visible = true;   MM_IGameMod  -> Enabled = true;
  MM_Start     -> Visible = true;   MM_Start     -> Enabled = true;
 }
void TF_Worm::terminateMainMenu()
 {
  F_Worm->Canvas->Brush->Color=clWhite;
  F_Worm->Canvas->FillRect(Rect(0,0,400,425));
  L_Titel1     -> Visible = false;
  L_Titel2     -> Visible = false;
  L_MAnzahl    -> Visible = false;
  L_MGameMod   -> Visible = false;
  M_Exit       -> Visible = false;   M_Exit       -> Enabled = false;
  MM_WurmAnzahl-> Visible = false;   MM_WurmAnzahl-> Enabled = false;
  MM_GameMod   -> Visible = false;   MM_GameMod   -> Enabled = false;
  MM_IAnzahl   -> Visible = false;   MM_IAnzahl   -> Enabled = false;
  MM_IGameMod  -> Visible = false;   MM_IGameMod  -> Enabled = false;
  MM_Start     -> Visible = false;   MM_Start     -> Enabled = false;
 }

int TF_Worm::gibAnzahlAuswahl()  {return MM_WurmAnzahl->ItemIndex;}

int TF_Worm::gibGameModAuswahl() {return MM_GameMod->ItemIndex;}

// Game Menu
void TF_Worm::createGameMenu()
 {
  GM_Pause -> Visible = true;   GM_Pause -> Enabled = true;
  GM_Weiter-> Visible = true;   GM_Weiter-> Enabled = true;
  GM_Neu   -> Visible = true;   GM_Neu   -> Enabled = true;
  M_Exit   -> Visible = true;   M_Exit   -> Enabled = true;
 }
void TF_Worm::terminateGameMenu()
 {
  E_Punkte0-> Visible = false;
  E_Punkte1-> Visible = false;
  GM_Pause -> Visible = false;   GM_Pause -> Enabled = false;
  GM_Weiter-> Visible = false;   GM_Weiter-> Enabled = false;
  GM_Neu   -> Visible = false;   GM_Neu   -> Enabled = false;
  M_Exit   -> Visible = false;   M_Exit   -> Enabled = false;
  L_EndPunkte0->Visible=false;   L_EndPunkte1->Visible=false;
  L_GameOver->Visible = false;
 }




//---------------------------------------------------------------------------
// Ende der eigenen Oberflächenfunktionen -----------------------------------
// Ereignisse der Oberfläche ------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TF_Worm::TF_Worm(TComponent* Owner): TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_Worm::T_Timer1Timer(TObject *Sender)
{
 control.Countdown();
}
//---------------------------------------------------------------------------


void __fastcall TF_Worm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
control.Taste(Key);
}
//---------------------------------------------------------------------------


void __fastcall TF_Worm::GM_PauseClick(TObject *Sender)
{
 stoppeTimer();
}
//---------------------------------------------------------------------------

void __fastcall TF_Worm::GM_WeiterClick(TObject *Sender)
{
 starteTimer();
}
//---------------------------------------------------------------------------

void __fastcall TF_Worm::M_ExitClick(TObject *Sender)
{
 control.exit();
 Application->Terminate();
}
//---------------------------------------------------------------------------



void __fastcall TF_Worm::MM_IAnzahlClick(TObject *Sender)
{
 MenuInfoAnzahl();
}
//---------------------------------------------------------------------------

void __fastcall TF_Worm::MM_IGameModClick(TObject *Sender)
{
 MenuInfoGameMod();
}
//---------------------------------------------------------------------------

void __fastcall TF_Worm::MM_StartClick(TObject *Sender)
{
 control.setEinstellungen();
 control.createGame();
}
//---------------------------------------------------------------------------

void __fastcall TF_Worm::GM_NeuClick(TObject *Sender)
{
 stoppeTimer();
 terminateGameMenu();
 createMainMenu();
}
//---------------------------------------------------------------------------

