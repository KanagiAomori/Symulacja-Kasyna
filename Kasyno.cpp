#include "Kasyno.h"
#include <time.h>

// konstruktor kasyna tworzy talie kart oraz graczy
Kasyno::Kasyno() {
    int n = 0;
    for (int i = 0; i < ILOSCKOLOROW; i++){
        for (int j = 0; j < ILOSCWARTOSCI; j++){
            talia[n].setKolor(i);
            talia[n].setWartosc(j);
            talia[n].setJestwBanku(true);
            n++;
        }
    }
    std::cout << "konstruktor obiektu - Kasyno" << std::endl;
}

Kasyno::~Kasyno() {
    std::cout << "destruktor obiektu - Kasyno" << std::endl;
}

void Kasyno::tasuj() {
    srand(time(NULL));
    int Karta1, Karta2;
    for (int i = 0; i < 100; i++){
        Karta1 = rand() % ILOSCKART;
        Karta2 = rand() % ILOSCKART;
        swapCard(talia[Karta1], talia[Karta2]);
    }
}
//sprawdzone
void Kasyno::pokazTale() {
    for(int i = 0; i < ILOSCKART; i++){
       this->talia[i].wypisz();
       std::cout << " w banku?" << this->talia[i].getjestwBanku();
        std::cout << std::endl;
    }    
}

void swapCard(Karta& A, Karta& B) {
    Karta temp = A;
    A = B;
    B = temp;
}

Karta* Kasyno::dajKarte() {  // tak żeby nie wydać 2 razy tej samej karty
    Karta* doWydania = nullptr;
    bool losujDalej = true;
    int losowanie;

    srand(time(NULL));
    while (losujDalej){
        losowanie = rand() % ILOSCKART;
        if (talia[losowanie].getjestwBanku()) {
            doWydania = &(talia[losowanie]);    // jest gitówa 
            losujDalej = false;
        }
    }
    doWydania->setJestwBanku(false);
    return doWydania;
}
// sprawdzone
void Kasyno::graj() {
    static int nrRundy = 0;
    int ileGraczy = 2;  // ilosc graczy
    int ileRozdac = 2;
    Karta* doWziecia;   // karta pobrana przez gracza
    int i,j;
    for (i = 0; i < ileGraczy; i++){            // rozdanie kart graczą 
        for (j = 0; j < ileRozdac; j++){        // po ile kart    
            doWziecia = this->dajKarte();   // pobierz kartę z tali
            if(doWziecia !=nullptr)
                gracze[i].wezKarte(doWziecia);  // asocjacja
            else
                std::cout << "dajKarte nie powiodło sie" << std::endl;
        }
    }
    for (i = 0; i < ileGraczy; i++){    // wyswietla stan Ręki każdego gracza
        std::cout << "gracz [" << i + 1 << "]:" << std::endl;
        gracze[i].wyswietlReke();
    }
    nrRundy++;
    std::cout << "Koniec Rundy " << "(" <<  nrRundy << ")" << std::endl;
}