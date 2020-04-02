#include <iostream>

#ifndef KARTA
#define KARTA

#define ILOSCKOLOROW 4
#define ILOSCFIGUR 13
#define ILOSCWARTOSCI 13

class Karta {
private:
    std::string kolor;
    char figura;
    int wartosc;
    bool jestwBanku;
public:
    Karta(int _kolor = 0, int _wartosc = 0);
    void setKolor(int _kolor);
    void setWartosc(int _wartosc);
    void setJestwBanku(bool _jestwBanku);
    std::string getKolor() const { return kolor; }
    char getFigura() const { return figura; }
    int getWartosc() const { return wartosc; }
    bool getjestwBanku() const { return jestwBanku; }
    void wypisz() const { std::cout << figura << " " << kolor << " "; }

    friend std::ostream& operator<<(std::ostream& os, const Karta& ka);
};

#endif