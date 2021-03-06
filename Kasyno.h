#ifndef KASYNO
#define KASYNO

#ifdef _WIN32   // dodanie thread w przyjaznej dla windowsowców wersji
#include <Windows.h>
#else
#include <unistd.h> // przyjazne dla linuxiarzy 
#endif

#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"
#include <vector>

#define ILOSCKART 52
#define MAXGRACZY 3
#define MAXBOTOW 3
#define MAXWSZYSTKICHGRACZY MAXBOTOW + MAXGRACZY
#define WYGRYWAJACEPKT 21


class Kasyno
{
    private:
        Karta talia[ILOSCKART];
        Gracz** gracze;
        int iloscGraczy = MAXGRACZY; 
        int iloscBotow = MAXBOTOW;
        int iloscWszystkichGraczy;
    public:
        Kasyno(); // przygotuj talie 52 kart
        ~Kasyno();
        void tasuj(); // zamienia parę kart 100 razy
        void pokazTale();
        Karta* dajKarte(); // tak żeby kasyno nie wydało 2 razy tej samej karty
        virtual void graj(); //*// // rozdaje graczą po 2 karty i każe im pokazać rękę
        void decyzja_o_Passowaniu();
        void rozdaj_karty_grajacym(int _ile);
        void wyswietl_reke_grajacych();
        virtual void inicjalizacja_graczy(); //*//
        virtual void wybor_odwagi();   
        int ile_graczy_pozostalo();
        virtual void okresl_zwyciezce();
        virtual void zapisz_stan_gry_txt();
        void wybor_ilosci_graczy(int& _ilosc);
        void alokacja_graczy(); 
        void zwalnianie_pamieci();     
        bool rozpocznij_nowa_gre(); // możliwość rozpoczęcia nowej gry przez kasyno
        void oddaj_karty_do_banku();

        friend class SymulacjaKasyna;
};

void swapCard(Karta& A, Karta& B);
void wybor_ilosci_graczy(int& _ilosc);


#endif