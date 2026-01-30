#ifndef tablaJocH
#define tablaJocH
const int LIBER = 0;
const int ALB = 1;
const int NEGRU = 2;

struct Punct {
    int x, y;
};

class Tabla {
private:
    int pozitii[24];
    Punct coord[24];

public:
	// Constructor
    Tabla();

    // Metode
    int getPozitie(int index);
    void setPozitie(int index, int jucator);
    Punct getCoord(int index);
	int getPozitieClick(int x, int y);
	bool suntVecini(int i, int j);
	bool verificaMoara(int index, int culoare);
};

#endif
