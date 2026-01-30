//---------------------------------------------------------------------------

#ifndef MoaraH
#define MoaraH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "tablaJoc.h"
#include "tablaJoc.h"
#include "player.h"
#include "Pion.h"
//---------------------------------------------------------------------------
class TWindowMoara : public TForm
{
__published:	// IDE-managed Components
	TImage *TablaFundal;
	TButton *btnStart;
	TButton *Button1;
	TLabel *lblStatus;
	TLabel *lblPieseNegre;
	TLabel *lblPieseAlbe;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btnStartClick(TObject *Sender);

private:	// User declarations
Tabla *tabla;
	Player *p1;
    Player *p2;
	Player *jucatorCurent;
    bool trebuieSaElimine;
   //	void __fastcall GestionareClickPunct(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall GestionareClickPunct(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall PunctDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
void __fastcall PunctDragDrop(TObject *Sender, TObject *Source, int X, int Y);

public:		// User declarations
	__fastcall TWindowMoara(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowMoara *WindowMoara;
//---------------------------------------------------------------------------
#endif
