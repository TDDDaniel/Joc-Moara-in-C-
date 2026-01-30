

//---------------------------------------------------------------------------

#pragma hdrstop

#include "player.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// Constructorul: observă cum apelăm constructorul clasei de bază Pion(0, culoare)
Player::Player(String nume, int culoare) : Pion(0, culoare) {
    this->nume = nume;
    this->pieseRamaseInMana = 9;
    this->scor = 0;
    this->esteLaRand = (culoare == 1); // Jucătorul cu ALB (1) începe de obicei
}

// Implementarea polimorfică a metodei
String Player::GetTipObiect() {
    return "Obiect de tip: Jucatorul " + nume;
}

bool Player::MaiPoatePunePiese() {
    return pieseRamaseInMana > 0;
}

void Player::ScadePieseMana() {
    if(pieseRamaseInMana > 0) pieseRamaseInMana--;
}

void Player::AdaugaPunctScor() {
    scor++;
}

String Player::GetNume() {
    return nume;
}

int Player::GetPieseMana() {
    return pieseRamaseInMana;
}

void Player::SetRand(bool rand) {
	esteLaRand = rand;
}

bool Player::GetRand() {
    return esteLaRand;
}
