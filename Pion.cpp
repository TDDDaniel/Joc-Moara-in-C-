//---------------------------------------------------------------------------

#pragma hdrstop

#include "Pion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// Constructorul cu parametri
Pion::Pion(int id, int culoare) {
	this->idUnic = id;
    this->codCuloare = culoare;
	this->pozitieTabel = -1;
    this->esteActiv = true;
}

// Constructorul default
Pion::Pion() : idUnic(0), codCuloare(0), pozitieTabel(-1), esteActiv(true) {}

void Pion::SetPozitie(int index) {
    pozitieTabel = index;
}

int Pion::GetPozitie() {
    return pozitieTabel;
}

void Pion::EliminaPiesa() {
    esteActiv = false;
    pozitieTabel = -1;
}

bool Pion::VerificaDacaEInJoc() {
    return esteActiv;
}

int Pion::GetCuloare() {
    return codCuloare;
}

String Pion::GetTipObiect() {
    return "Obiect de tip: Piesa de joc";
}
