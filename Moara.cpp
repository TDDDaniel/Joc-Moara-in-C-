#include <vcl.h>
#pragma hdrstop

#include "Moara.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TWindowMoara *WindowMoara;

__fastcall TWindowMoara::TWindowMoara(TComponent* Owner) : TForm(Owner)
{
    tabla = NULL;
    p1 = NULL;
    p2 = NULL;
}

void __fastcall TWindowMoara::Button1Click(TObject *Sender)
{
    Close();
}

void __fastcall TWindowMoara::btnStartClick(TObject *Sender)
{
    lblStatus->Font->Style = TFontStyles() << fsBold;
    lblStatus->Font->Size = 12;
    tabla = new Tabla();
    p1 = new Player("Alb", ALB);
	p2 = new Player("Negru", NEGRU);
    jucatorCurent = p1;
	trebuieSaElimine = false;
    // Inițializăm etichetele cu numărul de piese (9)
	lblPieseAlbe->Caption = "Piese Albe rămase: 9";
    lblPieseNegre->Caption = "Piese Negre rămase: 9";

	lblStatus->Caption = "Rândul lui " + jucatorCurent->GetNume() + ". Plasează o piesă.";

    

    for (int i = 0; i < 24; i++) {
        TShape *p = new TShape(this);
        p->Parent = this;
        p->Shape = stCircle;
		p->Width = 32;
		p->Height = 32;

		Punct c = tabla->getCoord(i);
        p->Left = TablaFundal->Left + c.x - (p->Width / 2);
        p->Top = TablaFundal->Top + c.y - (p->Height / 2);
        p->Tag = i;

        p->OnMouseDown = GestionareClickPunct;
        p->OnDragOver = PunctDragOver;
        p->OnDragDrop = PunctDragDrop;

        p->Brush->Style = bsClear;
        p->Pen->Style = psClear;
        p->Cursor = crHandPoint;
        p->Visible = true;
    }
    lblStatus->Caption = "Rândul lui " + jucatorCurent->GetNume() + ". Plasează o piesă.";
}

void __fastcall TWindowMoara::GestionareClickPunct(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TShape *sh = dynamic_cast<TShape*>(Sender);
    if (!sh || !tabla || !jucatorCurent) return;

    int idx = sh->Tag;

    // --- LOGICA DE ELIMINARE ---
    if (trebuieSaElimine) {
		int culoarePiesaClick = tabla->getPozitie(idx);

		// Verificăm dacă piesa aparține adversarului
		if (culoarePiesaClick != LIBER && culoarePiesaClick != jucatorCurent->GetCuloare()) {

			// VERIFICARE MOARĂ ADVERSAR: Nu putem scoate piesa dacă e în moară
			if (tabla->verificaMoara(idx, culoarePiesaClick)) {
				ShowMessage("Nu poți scoate o piesă dintr-o moară adversă!");
				return;
			}

			// Eliminare reușită: Resetăm vizual și eliberăm locul logic
			sh->Brush->Style = bsClear;
			sh->Pen->Style = psClear;
			sh->DragMode = dmManual;
			tabla->setPozitie(idx, LIBER);

			trebuieSaElimine = false;

			// Schimbăm rândul după ce piesa a fost scoasă
			jucatorCurent = (jucatorCurent == p1) ? p2 : p1;
			lblStatus->Caption = "Rândul lui " + jucatorCurent->GetNume();
		}
		return;
	}

	// --- FAZA 1: PLASARE PIESE ---
	// ... in interiorul GestionareClickPunct ...
if (tabla->getPozitie(idx) == LIBER && jucatorCurent->GetPieseMana() > 0) {
	int col = jucatorCurent->GetCuloare();
	tabla->setPozitie(idx, col); // 1. Ocupam locul in memorie

	// 2. Desenam piesa
	sh->Brush->Style = bsSolid;
	sh->Brush->Color = (col == ALB) ? clWhite : clBlack;
	// ... restul setarilor vizuale ...

	jucatorCurent->ScadePieseMana();

		lblPieseAlbe->Caption = "Piese Albe rămase: " + IntToStr(p1->GetPieseMana());
		lblPieseNegre->Caption = "Piese Negre rămase: " + IntToStr(p2->GetPieseMana());
	// 3. Abia ACUM verificam moara
	if (tabla->verificaMoara(idx, col)) {
		trebuieSaElimine = true;
		lblStatus->Caption = "MOARĂ! Scoate un pion advers.";
	} else {
        jucatorCurent = (jucatorCurent == p1) ? p2 : p1;
        lblStatus->Caption = "Rândul lui " + jucatorCurent->GetNume();
    }
}
}

void __fastcall TWindowMoara::PunctDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    TShape *destinatie = dynamic_cast<TShape*>(Sender);
    TShape *piesaTrasa = dynamic_cast<TShape*>(Source);

    if (destinatie && piesaTrasa && !trebuieSaElimine) {
        int idxSursa = piesaTrasa->Tag;
        int idxDest = destinatie->Tag;

        if (tabla->getPozitie(idxDest) == LIBER) {
            int culoarePiesa = (piesaTrasa->Brush->Color == clWhite) ? ALB : NEGRU;
            if (culoarePiesa == jucatorCurent->GetCuloare() && tabla->suntVecini(idxSursa, idxDest)) {
                Accept = true;
            } else {
                Accept = false;
            }
        }
    }
}

void __fastcall TWindowMoara::PunctDragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
    TShape *destinatie = dynamic_cast<TShape*>(Sender);
    TShape *sursa = dynamic_cast<TShape*>(Source);

    if (destinatie && sursa) {
        int culoare = (sursa->Brush->Color == clWhite) ? ALB : NEGRU;

        // 1. Mutăm piesa vizual
        destinatie->Brush->Style = bsSolid;
        destinatie->Pen->Style = psSolid;
        destinatie->Brush->Color = sursa->Brush->Color;
        destinatie->Pen->Color = sursa->Pen->Color;
        destinatie->DragMode = dmAutomatic;

        // 2. Eliberăm sursa
        sursa->Brush->Style = bsClear;
        sursa->Pen->Style = psClear;
        sursa->DragMode = dmManual;

        // 3. Actualizăm tabla logică
        tabla->setPozitie(sursa->Tag, LIBER);
        tabla->setPozitie(destinatie->Tag, culoare);

        // 4. VERIFICARE MOARĂ DUPĂ MUTARE
        if(tabla->verificaMoara(destinatie->Tag, culoare)) {
            lblStatus->Caption = jucatorCurent->GetNume() + ": MOARĂ! Elimină un pion advers.";
            trebuieSaElimine = true;
            // NU schimbăm jucătorul aici!
        } else {
            // Schimbăm jucătorul DOAR dacă nu a făcut moară
            jucatorCurent = (jucatorCurent == p1) ? p2 : p1;
            lblStatus->Caption = "Rândul lui " + jucatorCurent->GetNume();
        }
    }
}
