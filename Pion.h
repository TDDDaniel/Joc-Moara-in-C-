#ifndef PionH
#define PionH
#include <System.hpp>

class Pion {
protected:
	int codCuloare;
	int pozitieTabel;
	bool esteActiv;
	int idUnic;

public:
	Pion(int id, int culoare); // Doar prototipul
	Pion();
    virtual ~Pion() {} // Destructor virtual pentru mostenire

    void SetPozitie(int index); // Se termina cu punct si virgula
    int GetPozitie();
    void EliminaPiesa();
    bool VerificaDacaEInJoc();
    int GetCuloare();

    virtual String GetTipObiect();
};
#endif
