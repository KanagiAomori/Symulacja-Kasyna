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
        void tasuj(); // zamienia parę kart 100 razy
        Karta* dajKarte(); // tak żeby kasyno nie wydało 2 razy tej samej karty

};

