#include "Bot.h"

std::string Bot::get_odwaga() {
    if (odwaga == zachowawczy)
        return "zachowawczy";
    else if (odwaga == normalny)
        return "normalny";
    else if (odwaga == ryzykujacy)
        return "ryzykujacy";
}

/*
void Bot::set_nazwa(int numer) {
    char nazwaBota[5];
    strcpy(nazwaBota,"Bot ");
    nazwaBota[3] = std::__int_to_char(numer);
    this->Gracz::set_nazwa(nazwaBota); // 5 znakow z /0;

}
*/

void Bot::set_graDalej() {
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
