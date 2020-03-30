#ifndef BOT
#define BOT

#include "Gracz.h"

#define LIMITZACHOWAWCZY 14
#define LIMITNORMALNY 16
#define LIMITRYZYKUJACY 18
enum ryzyko{ zachowawczy, normalny, ryzykujacy};

class Bot : public Gracz    // klasa Bot dziedziczy po klasie Gracz
{
    private:
        ryzyko odwaga;  // 3 poziomy odwagi - dobiera do określonego poziomu punktów        
    public:
        void set_odwaga(ryzyko _odwaga) { odwaga = _odwaga; };
        void set_nazwa(int numer);
        std::string get_odwaga();
        virtual void set_graDalej() override;
};

#endif