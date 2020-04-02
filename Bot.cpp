#include "Bot.h"

std::string Bot::get_odwaga() { // pobrania odwagi
    if (odwaga == zachowawczy)
        return "zachowawczy";
    else if (odwaga == normalny)
        return "normalny";
    else    // ryzykujący
        return "ryzykujacy";
}

void Bot::set_graDalej(bool _graDalej) {
    if (odwaga == zachowawczy)
        if (this->get_wartoscReki() > LIMITZACHOWAWCZY)
            this->Gracz::set_graDalej(false);
    else if (odwaga == normalny)
        if (this->get_wartoscReki() > LIMITNORMALNY)
            this->Gracz::set_graDalej(false);
    else if (odwaga == ryzykujacy)
        if (this->get_wartoscReki() > LIMITRYZYKUJACY)
            this->Gracz::set_graDalej(false);
}
