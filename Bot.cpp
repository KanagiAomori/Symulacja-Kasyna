#include "Bot.h"

std::string Bot::get_odwaga_str() { // pobrania odwagi
    if (this->get_odwaga() == zachowawczy)
        return "zachowawczy";
    else if (this->get_odwaga() == normalny)
        return "normalny";
    else    // ryzykujący
        return "ryzykujacy";
}

void Bot::set_graDalej(bool _graDalej) {
    if (this->get_odwaga() == zachowawczy)
        if (this->get_wartoscReki() >= LIMITZACHOWAWCZY)
            this->Gracz::set_graDalej(false);
    if (this->get_odwaga() == normalny)
        if (this->get_wartoscReki() >= LIMITNORMALNY)
            this->Gracz::set_graDalej(false);
    if (this->get_odwaga() == ryzykujacy)
        if (this->get_wartoscReki() >= LIMITRYZYKUJACY)
            this->Gracz::set_graDalej(false);
}
