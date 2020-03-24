#ifndef KASYNO
#define KASYNO
#include "Karta.h"
#include "Gracz.h"

#define ILOSCKART 52
#define ILOSCGRACZY 2

class Kasyno
{
    private:
        Karta talia[ILOSCKART];
        Gracz gracze[ILOSCGRACZY];
    public:
        Kasyno(); // przygotuj talie 52 kart
        ~Kasyno();
        void tasuj(); // zamienia parę kart 100 razy
        void pokazTale();
        Karta* dajKarte(); // tak żeby kasyno nie wydało 2 razy tej samej karty
        void graj(); // rozdaje graczą po 2 karty i każe im pokazać rękę
};

void swapCard(Karta& A, Karta& B);

#endif