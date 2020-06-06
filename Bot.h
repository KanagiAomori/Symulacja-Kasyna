#ifndef BOT
#define BOT

#ifdef _WIN32   // dodanie thread w przyjaznej dla windowsowców wersji
#include <Windows.h>
#else
#include <unistd.h> // przyjazne dla linuxiarzy 
#endif

#include "Gracz.h"

#define LIMITZACHOWAWCZY 14
#define LIMITNORMALNY 16
#define LIMITRYZYKUJACY 18


class Bot : public Gracz    // klasa Bot dziedziczy po klasie Gracz
{
    public:
        void set_nazwa(int numer);
        std::string get_odwaga_str();
        void set_graDalej(bool _graDalej) ;
};

#endif