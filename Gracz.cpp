#include "Gracz.h"

Gracz::Gracz(){
    std::cout << "konstruktor obiektu - Gracz" << std::endl;
}

Gracz::~Gracz(){
    std::cout << "destruktor obiektu - Gracz" << std::endl;
}

void Gracz::wezKarte(Karta* _karta){
    if (iloscPosiadanychKart < MAXKARTGRACZA){  // [ograniczenie] gracz może posiadać max 10 kart 
        kartyNaRece.push_back(_karta);  // dodaj karte na zzrenke <vector>
        iloscPosiadanychKart = kartyNaRece.size();  // aktualizuj ilosc kart na rence
        this->set_WartoscReki();    // ustaw wartosc renki
    }
    else { 
        std::cout << "Gracz: " << nazwa <<" ma maxymalna przysługująca mu ilość kart: " << MAXKARTGRACZA << std::endl;
    }
}

void Gracz::set_WartoscReki(){
    wartoscReki = 0;
    for (Karta *karta : kartyNaRece){   // iteruj vector elementów *karata
        wartoscReki += karta->getWartosc();
    }
}

void Gracz::wyswietlReke(){
    std::cout << "|| karty: ";
    for (int i = 0; i < kartyNaRece.size(); i++) // karty i kolory
        kartyNaRece[i]->wypisz();
    std::cout << "|| wartosc kart: " << this->get_wartoscReki() << " || ";
    std::cout << "ilosc kart: " << this->get_iloscPosiadanychKart()  << " ||"<< std::endl;
}
