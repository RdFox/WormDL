//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("SnakeProjekt.res");
USEFORM("GUI.cpp", F_Worm);
USEUNIT("Klassen.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TF_Worm), &F_Worm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
