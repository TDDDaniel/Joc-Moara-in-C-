//---------------------------------------------------------------------------
#pragma hdrstop

#include "tablaJoc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

										   // Constructorul: Aici definim toate coordonatele
Tabla::Tabla() {
	for (int i = 0; i < 24; i++) {
		pozitii[i] = LIBER;
	}
// --- PATRATUL EXTERIOR (0-7) ---
	// Folosim valorile tale: X(30, 360, 700) si Y(35, 300, 565)
	coord[0] = {30, 35};   coord[1] = {350, 35};  coord[2] = {700, 35};  // Sus
	coord[3] = {710, 365};                                               // Dreapta mijloc
	coord[4] = {710, 700}; coord[5] = {355, 620}; coord[6] = {30, 700};   // Jos
	coord[7] = {30, 365};                                              // Stanga mijloc

	// --- PATRATUL MIJLOCIU (8-15) ---
	// Proporție: ~100 pixeli distanță de exterior
	coord[8] = {130, 135};   coord[9] = {355, 135}; coord[10] = {585, 135}; // Sus
	coord[11] = {585, 380};                                               // Dreapta mijloc
	coord[12] = {585, 600}; coord[13] = {360, 490}; coord[14] = {130, 610}; // Jos
	coord[15] = {130, 370};                                               // Stanga mijloc

	// --- PATRATUL INTERIOR (16-23) ---
	// Proporție: ~200 pixeli distanță de exterior
	coord[16] = {230, 265}; coord[17] = {355, 265}; coord[18] = {480, 265}; // Sus
	coord[19] = {480, 375};                                                // Dreapta mijloc
	coord[20] = {480, 485}; coord[21] = {230, 365};  coord[22] = {230, 365}; // Jos
	coord[23] = {230, 485};    /*    */
}

int Tabla::getPozitie(int index) {
	if (index >= 0 && index < 24)
		return pozitii[index];
	return -1;
}

void Tabla::setPozitie(int index, int jucator) {
    if (index >= 0 && index < 24)
        pozitii[index] = jucator;
}

Punct Tabla::getCoord(int index) {
    if (index >= 0 && index < 24)
        return coord[index];
    return {0, 0};
}

int Tabla::getPozitieClick(int x, int y) {
    const int R = 25; // Raza de sensibilitate
    for (int i = 0; i < 24; i++) {
        int dx = x - coord[i].x;
        int dy = y - coord[i].y;
        if (dx * dx + dy * dy <= R * R)
            return i;
    }
    return -1;
}

bool Tabla::suntVecini(int i, int j) {
    // Lista de adiacenta pentru cele 24 de puncte
    static const int vecini[24][4] = {
        {1, 7, -1, -1},    {0, 2, 9, -1},    {1, 3, -1, -1},    // Exterior Sus
        {2, 4, 11, -1},    {3, 5, -1, -1},   {4, 6, 13, -1},    // Exterior Dreapta/Jos
        {5, 7, -1, -1},    {0, 6, 15, -1},                      // Exterior Stanga
        {9, 15, -1, -1},   {1, 8, 10, 17},   {9, 11, -1, -1},   // Mijloc Sus
        {3, 10, 12, 19},   {11, 13, -1, -1}, {5, 12, 14, 21},   // Mijloc Jos
        {13, 15, -1, -1},  {7, 8, 14, 23},                      // Mijloc Stanga
        {17, 23, -1, -1},  {9, 16, 18, -1},  {17, 19, -1, -1},  // Interior Sus
        {11, 18, 20, -1},  {19, 21, -1, -1}, {13, 20, 22, -1},  // Interior Jos
        {21, 23, -1, -1},  {15, 16, 22, -1}                     // Interior Stanga
    };

    for (int k = 0; k < 4; k++) {
        if (vecini[i][k] == j) return true;
    }
    return false;
}

bool Tabla::verificaMoara(int index, int culoare) {
    // Exista exact 16 combinatii posibile de moara
    static const int moriPosibile[16][3] = {
		// Orizontale (Exterior, Mijloc, Interior)
        {0, 1, 2}, {2, 3, 4}, {4, 5, 6}, {6, 7, 0},         // Exterior
        {8, 9, 10}, {10, 11, 12}, {12, 13, 14}, {14, 15, 8},   // Mijloc
		{16, 17, 18}, {18, 19, 20}, {20, 21, 22}, {22, 23, 16}, // Interior
        // Verticale (Liniile de legatura)
        {1, 9, 17}, {3, 11, 19}, {5, 13, 21}, {7, 15, 23}
    };

    // Verificam doar cele 16 linii
    for (int i = 0; i < 16; i++) {
        bool contineIndex = false;
        for (int j = 0; j < 3; j++) {
            if (moriPosibile[i][j] == index) contineIndex = true;
        }

        if (contineIndex) {
            // Verificam daca toate cele 3 pozitii au culoarea jucatorului
            if (pozitii[moriPosibile[i][0]] == culoare &&
                pozitii[moriPosibile[i][1]] == culoare &&
                pozitii[moriPosibile[i][2]] == culoare) {
                return true;
			}
        }
    }
    return false;
}
