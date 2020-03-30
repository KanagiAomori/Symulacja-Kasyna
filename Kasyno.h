#ifndef KASYNO
#define KASYNO

#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"
#include <vector>

#define ILOSCKART 52
#define MAXGRACZY 3   // max graczy
#define MAXBOTOW 3
#define MAXWSZYSTKICHGRACZY MAXBOTOW + MAXGRACZY
#define WYGRYWAJACEPKT 21


class Kasyno
{
    private:
        Karta talia[ILOSCKART];
        Gracz* gracze;
        int iloscGraczy = MAXGRACZY; 
        int iloscBotow = MAXBOTOW;
        int iloscWszystkichGraczy;
    public:
        Kasyno(); // przygotuj talie 52 kart
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
        void inicjalizacja_graczy();        
        void rozpocznij_nowa_gre(); // możliwość rozpoczęcia nowej gry przez kasyno
        // do napisania 3
        void dodaj_bota();
};

void swapCard(Karta& A, Karta& B);
void wybor_ilosci_graczy(int& _ilosc);

#endif