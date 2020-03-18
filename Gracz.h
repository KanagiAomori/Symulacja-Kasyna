#include "Karta.h"

#define MAXKARTGRACZA 10

class Gracz
{
    private:
        int iloscPosiadanychKart;   // ?
        Karta* kartyNaRece; // karty w posiadaniu gracza max 10
    public:
        void wezKarte(Karta* _karta);
        void wyswietlReke(); // wyswietla karty w posiadaniu gracza
};