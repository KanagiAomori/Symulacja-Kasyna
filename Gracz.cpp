#include "Gracz.h"

Gracz::Gracz(){
    std::cout << "konstruktor obiektu - Gracz" << std::endl;
}

Gracz::~Gracz(){
    std::cout << "destruktor obiektu - Gracz" << std::endl;
}
// sprawdzone
void Gracz::wezKarte(Karta* _karta){
    if (iloscPosiadanychKart < MAXKARTGRACZA){  // [ograniczenie] gracz może posiadać max 10 kart 
        kartyNaRece.push_back(_karta);  // dodaj karte na renke <vector>
        iloscPosiadanychKart = kartyNaRece.size();  // aktualizuj ilosc kart na rence
        this->set_WartoscReki();    // ustaw wartosc renki
    }
    else { 
        std::cout << "Gracz ma maxymalną przysługującą mu ilość kart: " << MAXKARTGRACZA << std::endl;
    }
}
// sprawdzone
void Gracz::set_WartoscReki(){
    wartoscReki = 0;
    for (Karta *karta : kartyNaRece){   // iteruj vector elementów *karata
        wartoscReki += karta->getWartosc();
    }
}
// sprawdzone
void Gracz::wyswietlReke(){
    std::cout << "|| karty: ";
    for (int i = 0; i < kartyNaRece.size(); i++) // karty i kolory
        kartyNaRece[i]->wypisz();
    std::cout << "|| wartosc kart: " << this->get_wartoscReki() << " || ";
    std::cout << "ilosc kart: " << this->get_iloscPosiadanychKart()  << " ||"<< std::endl;
}
