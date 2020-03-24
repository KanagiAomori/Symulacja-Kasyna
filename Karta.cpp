#include "Karta.h"

const std::string kolory[] = { "Karo","Kier", "Pik", "Trefl" };   // 4 el   // po ludzku nie działa bo to windowsowe aaaaa
const char figury[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K', 'A' };  // 13 el
const int wartosci[] = { 2,   3,   4,   5,   6,   7 ,  8,   9,  10,   2,   3,   4,  11 };   // 13 el

Karta::Karta(int _kolor, int _wartosc) {
    setKolor(_kolor);
    setWartosc(_wartosc);
}

void Karta::setKolor(int _kolor) {
    if (_kolor < 4) {
        kolor = kolory[_kolor];
    }
}

void Karta::setWartosc(int _wartosc) {
    if (_wartosc < 14) {
        figura = figury[_wartosc];
        wartosc = wartosci[_wartosc];
    }
}

void Karta::setJestwBanku(bool _jestwBanku){
    this->jestwBanku = _jestwBanku;
}