#ifndef BOT
#define BOT

#include "Gracz.h"

enum ryzyko{ zachowawczy, normalny, ryzykujacy};

class Bot : public Gracz    // klasa Bot dziedziczy po klasie Gracz
{
    private:
        ryzyko odwaga;  // 3 poziomy odwagi - dobiera do określonego poziomu punktów        
    public:
        virtual void nadaj_identyfikator( char* _nazwa) { _nazwa = _nazwa; } // Bot1, Bot2, Bot3;
        void set_odwaga(ryzyko _odwaga) { odwaga = _odwaga; };
        
};

#endif