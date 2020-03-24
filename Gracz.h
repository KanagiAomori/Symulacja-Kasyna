#ifndef GRACZ
#define GRACZ

#include <vector>
#include "Karta.h"

#define MAXKARTGRACZA 10

class Gracz
{
    private:
        int iloscPosiadanychKart = 0;   // ?
        int wartoscReki = 0;
        std::vector <Karta*> kartyNaRece;
        //Karta* kartyNaRece = nullptr; // karty w posiadaniu gracza max 10
    public:
        Gracz();
        ~Gracz();
        void wezKarte(Karta* _karta);
        void wyswietlReke(); // wyswietla karty w posiadaniu gracza
        void set_WartoscReki();
        int get_wartoscReki() { return wartoscReki; }
        int get_iloscPosiadanychKart() { return iloscPosiadanychKart; }
};

#endif