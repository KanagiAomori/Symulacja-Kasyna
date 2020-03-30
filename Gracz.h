#ifndef GRACZ
#define GRACZ

#include <vector>
#include <cstring>
#include "Karta.h"

#define MAXKARTGRACZA 10
#define MAXNAZWAGRACZA 20

class Kasyno; // forward declaration - ważne

class Gracz
{
    private:
        char nazwa[MAXNAZWAGRACZA];
        int iloscPosiadanychKart = 0;   // ?
        int wartoscReki = 0;
        bool graDalej = true;
        Kasyno* mojeKasyno = nullptr;
        std::vector <Karta*> kartyNaRece;
    public:
        Gracz();
        ~Gracz();
        void wezKarte(Karta* _karta);
        void wyswietlReke(); // wyswietla karty w posiadaniu gracza
        void set_WartoscReki();
        void set_mojeKasyno(Kasyno* _mojeKasyno) { mojeKasyno = _mojeKasyno; }
        void set_graDalej(bool _graDalej) { graDalej = _graDalej; }
        void set_nazwa(char* _nazwa) { strcpy(nazwa, _nazwa); }
        int get_wartoscReki() { return wartoscReki; }
        Karta* get_Karta(int index) { return kartyNaRece[index]; }
        int get_iloscPosiadanychKart() { return iloscPosiadanychKart; }
        // if obiekt klasy Bot sprawdza czy nie zostął przekroczony limit pkt definiowany przez odwagę
        virtual bool get_graDalej() { return graDalej; } // akcesor czy gracz spasował
        Kasyno* get_mojeKasyno() { return mojeKasyno; }
        char* get_nazwa() { return nazwa; }
};

#endif