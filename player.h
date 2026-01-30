#ifndef playerH
#define playerH
#include "Pion.h" // Legătura de moștenire

class Player : public Pion {
private:
    String nume;
    int pieseRamaseInMana;
    int scor;
    bool esteLaRand;

public:
    // Constructor
    Player(String nume, int culoare);

    // Suprascrierea metodei virtuale (Polimorfism)
    String GetTipObiect() override;

    // Metode de acces și logică
    bool MaiPoatePunePiese();
    void ScadePieseMana();
    void AdaugaPunctScor();
    String GetNume();
    int GetPieseMana();
    void SetRand(bool rand);
    bool GetRand();
};
#endif
