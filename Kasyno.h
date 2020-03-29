#ifndef KASYNO
#define KASYNO

#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"
#include <vector>

#define ILOSCKART 52
#define ILOSCGRACZY 3
#define MAXBOTOW 3
#define WYGRYWAJACEPKT 21

//class Gracz;    // forward declaration - ważne


class Kasyno
{
    private:
        Karta talia[ILOSCKART];
        Gracz gracze[ILOSCGRACZY];
        Bot* boty;  // dodaj konstruktor 1 - 3 graczy komputerowych
    public:
        Kasyno(int _iloscGraczy = 1, int _iloscBotow = 1); // przygotuj talie 52 kart
        ~Kasyno();
        void tasuj(); // zamienia parę kart 100 razy
        void pokazTale();
        Karta* dajKarte(); // tak żeby kasyno nie wydało 2 razy tej samej karty
        void graj(); // rozdaje graczą po 2 karty i każe im pokazać rękę
        void decyzja_o_Passowaniu();
        void rozdaj_karty_grajacym(int _ile);
        void wyswietl_reke_grajacych();
        int ile_graczy_pozostalo();
        void okresl_zwyciezce();
        
        // do dokonczenia
        void zapisz_stan_gry_txt(); 

        // do napisania 2
        void rozpocznij_nowa_gre(); // możliwość rozpoczęcia nowej gry przez kasyno

        // do napisania 3
        void dodaj_bota();
};

void swapCard(Karta& A, Karta& B);

#endif