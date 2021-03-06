#include "Kasyno.h"
#include <time.h>
#include <limits>
#include <fstream>
#include <stdlib.h>
#include <ostream>


Kasyno::Kasyno() {  // konstruktor kasyna tworzy talie kart oraz graczy
    int n = 0;
    int i;
    for (i = 0; i < ILOSCKOLOROW; i++){ // tworzenie tali
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

void Kasyno::pokazTale() {
    for(int i = 0; i < ILOSCKART; i++){
       this->talia[i].wypisz();
       std::cout << " czy jest w banku: " << this->talia[i].getjestwBanku();
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

void Kasyno::graj() {
    bool restart;
    static int nrRundy = 0;
    int ileRozdac = 2;                      // poczatkowe rozdanie
    std::ifstream fp;
    fp.open("./WynikiSymulacji/ZapisGry.txt",std::ios::out | std::ios::trunc);
    fp.close();
    
    do {
        nrRundy++;
        this->tasuj();  // tasu przed każdą rundą
        this->inicjalizacja_graczy();   // ustawienie ilosci graczy i ich nazw oraz ilosci graczy wirtualnych
            
        this->rozdaj_karty_grajacym(ileRozdac); // rozdanie 2 kart graczą
        this->wyswietl_reke_grajacych();        // i wyświetlenie początkowego stanu gry
        
        while (this->ile_graczy_pozostalo() != 0 ){       
            this->decyzja_o_Passowaniu();           // decyzja o passowaniu
            if (this->ile_graczy_pozostalo()){      // pozostaliGracze != 0     
                this->rozdaj_karty_grajacym(1);     //rozdanie
                this->wyswietl_reke_grajacych();
            }
            else {
                this ->okresl_zwyciezce();          // spawdz czy jest zwycięzca
            }
        }
        this->zapisz_stan_gry_txt();

        this->zwalnianie_pamieci();
        this->oddaj_karty_do_banku();
        std::cout << "Koniec Rundy " << "(" <<  nrRundy << ")" << std::endl;
        restart = this->rozpocznij_nowa_gre();    // menu wyboru
    } while (restart);
}

void Kasyno::decyzja_o_Passowaniu() {
    char decyzja;
    bool powtorz = true;
    int i;

    for (i = 0; i < iloscGraczy; i++){                              // powtórz dla każdego gracza
        if (this->gracze[i]->get_graDalej()){                            // jeżeli gracz gra dalej zapytacj czy chce kontynuować
            std::cout << std::endl << "Gracz udziela odpowiedzi Tak = [t] lub Nie = [n]" << std::endl;
            if (this->gracze[i]->get_wartoscReki() >= WYGRYWAJACEPKT){    // gracz który ma 21 pkt >= passuje
                this->gracze[i]->set_graDalej(false);
                powtorz = false;
            }
            while (powtorz){
                std::cout << "Czy gracz [" << i + 1 << "] gra dalej?" <<std::endl;  // == nie passuje
                std::cin >> decyzja;
                if (std::cin.fail() == true){                                           // wykryto błąd - sprawdzenie flagi błędu
                    std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
                    std::cin.clear();                                                   // restart flagi błędu
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // arg1 - ile znaków usunąć z buffora, arg2 - do jakiego znaku
                }
                else switch (decyzja)
                {
                    case 't':
                        gracze[i]->set_graDalej(true);
                        powtorz = false;
                        break;
                    case 'n':
                        gracze[i]->set_graDalej(false);
                        powtorz = false;
                        break;
                    default:
                        std::cout << "Błędna decyzja wybierz [t] lub [n]" << std::endl;
                        powtorz = true; // powtórz pytanie o pass
                        break;
                }
            }
        }
        powtorz = true;
    }
    for(i = 0; i < iloscBotow; i++) {    // sprawdza czy boty przekroczyły limit
        gracze[i + iloscGraczy]->set_graDalej(false);
    }
}

void Kasyno::rozdaj_karty_grajacym(int _ile) {
    for (int i = 0; i < iloscWszystkichGraczy; i++)               // rozdanie kart graczą 
        for (int j = 0; j < _ile; j++)                  // po ile kart
            if (gracze[i]->get_graDalej())               // jeżeli gracz gra dalej daj mu kartę
                gracze[i]->wezKarte(this->dajKarte());   // asocjacja
}

void Kasyno::wyswietl_reke_grajacych() {
    for (int i = 0; i < iloscWszystkichGraczy; i++)   // wyswietla stan Ręki każdego gracza który nie spasował
        if (gracze[i]->get_graDalej()){      // sprawdza czy gracz jest jeszcze w grze
            std::cout << "|| Gracz [" << i + 1 << "]: " << gracze[i]->get_nazwa() ;
            gracze[i]->wyswietlReke();
        }
    std::cout << std::endl;
}

int Kasyno::ile_graczy_pozostalo() {
    int ile = 0;
    for (int i = 0; i < iloscWszystkichGraczy; i++)
        if (this->gracze[i]->get_graDalej()) // sprawdza czy gracz gra dalej
            ile++;
    return ile;
}

// w sumie dosc obrzydliwa ta funckja
void Kasyno::okresl_zwyciezce() {
    int maxWartoscReki = 0;
    int iloscGraczyz21Pkt = 0, iloscGraczyzWiecej21Pk = 0; 
    int i;

    std::cout << "|| Koniec rundy - zwycięzcy: ||" << std::endl;
    for (i = 0; i < iloscWszystkichGraczy; i++) {
        if (this->gracze[i]->get_wartoscReki() == WYGRYWAJACEPKT)
           iloscGraczyz21Pkt++;
        else
            iloscGraczyzWiecej21Pk++;
    }
    if (iloscGraczyz21Pkt == iloscWszystkichGraczy)
        std::cout << "||* Brak zwyciezcow - wszyscy pozostali gracze maja 21 Pkt *||" << std::endl; // [3] wszyscy przegrali
    else if (iloscGraczyzWiecej21Pk > iloscWszystkichGraczy)
        std::cout << "||* Brak zwyciezcow - wszyscy pozostali gracze wiecej niz 21 Pkt *||" << std::endl;
    else {
        for (i = 0; i < iloscWszystkichGraczy; i++)   // ustalenie max liczby punktów
            if (this->gracze[i]->get_wartoscReki() > maxWartoscReki && this->gracze[i]->get_wartoscReki() <= WYGRYWAJACEPKT)
                maxWartoscReki = this->gracze[i]->get_wartoscReki();        
        for (i = 0; i < iloscWszystkichGraczy; i++)    // pokazanie którzy gracze wygrali
            if (this->gracze[i]->get_wartoscReki() == maxWartoscReki)
                std::cout << "||* zwyciezył - " << this->gracze[i]->get_nazwa() << " *||" << std::endl;  // zwycięzca
    }
}

void Kasyno::zapisz_stan_gry_txt() {
    static int numerRundy = 1;
    int i, j;
    std::ofstream fp;
    fp.open("./WynikiSymulacji/ZapisGry.txt", std::ifstream::app); // otwarcie pliku w trybie zapisywania output -> do pliku
    // operacje
    fp << "Stan Rundy (" << numerRundy << "): " << std::endl;
    fp.setf(std::ios::left);
    fp.width(22);    
    fp << "||Nazwa gracza ";
    fp.width(strlen("|| Wartosc Kart "));
    fp << "||Wartosc Kart ";
    fp.width(strlen("|| Ilosc kart "));
    fp << "||Ilosc kart ";
    fp << "||Karty gracza " << std::endl;
    for (i = 0; i < iloscWszystkichGraczy; i++){    // wyswietla stan Ręki każdego gracza
        fp << *this->gracze[i];
    }
    fp << std::endl;
    fp.close(); // opcjonalnie destruktor ofstream też zamknie plik
    numerRundy++;
}

std::ostream& operator<<(std::ostream& os, Karta& ka) { // przeciążone operatory iostream 
    os <<  ka.getFigura() << " " << ka.getKolor() << ", ";
    return os;
}

std::ostream& operator<<(std::ostream& os, Gracz& gr) {
    os.width(2);
    os << "||";
    os.setf(std::ios::left);
    os.width (20);
    os << gr.get_nazwa();
    os.width(2);
    os << "||";
    os.width(strlen("||Wartosc Kart"));
    os << gr.get_wartoscReki();
    os.width(2);
    os << "||";
    os.width(strlen("||Ilosc kart"));
    os << gr.get_iloscPosiadanychKart();
    os.width(2);
    os << "||";    
    for (int i = 0; i < gr.get_iloscPosiadanychKart(); i++) {
        os << *gr.get_Karta(i);
    }
    os << std::endl; 
    return os;
}

void Kasyno::inicjalizacja_graczy() {
    int i;
    char _nazwa[MAXNAZWAGRACZA];

    std::cout << "|| Ilosc Graczy ||"  << std::endl;
    wybor_ilosci_graczy(iloscGraczy);       // ustaw ilosc graczy
    std::cout << "|| Ilosc Graczy Wirtualnych ||"  << std::endl;
    wybor_ilosci_graczy(iloscBotow);        // ustaw ilosc graczy wirtualnych

    iloscWszystkichGraczy = iloscGraczy + iloscBotow;
    alokacja_graczy();

    for(i = 0; i < iloscWszystkichGraczy; i++)    // przypisanie graczom kasyna
        gracze[i]->set_mojeKasyno(this);

    std::cout << "Wybierz nazwy dla graczy: " << std::endl;    // nazwy dla graczy
    for (i = 0; i < iloscGraczy; i++ ) {
        std::cout << "Nazwa Gracza [" << i << "]: ";
        std::cin >> _nazwa;
        if (std::cin.fail() == true || strlen(_nazwa) > MAXNAZWAGRACZA){
            std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
            std::cin.clear();                                                  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        gracze[i]->set_nazwa(_nazwa);
    }

    for (i = 0; i < iloscBotow; i++){ // ustaw nazwy botow
        strcpy(_nazwa, "Bot  ");
        _nazwa[3] = i + '1';
        gracze[i + iloscGraczy]->set_nazwa(_nazwa);
    }
    wybor_odwagi();
}

void Kasyno::wybor_odwagi() {
    int decyzja;
    ryzyko temp;
    for (int i = 0; i < iloscBotow; i++){
        do {                                                                // wybór ilości graczy
            std::cout << "(1) zachowawczy, (2) normalny, (3) ryzykujacy" << std::endl;
            std::cin >> decyzja;
                if (std::cin.fail() == true){
                    std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
                    std::cin.clear();                                                  
                    std::cin.ignore(100 , '\n'); 
            }
        } while ( !(decyzja >= 1 && decyzja <= 3) );
        --decyzja;  // zmniejszenie o 1 żeby interpretować jako enum
        if(decyzja == 0)
            gracze[i + iloscGraczy]->set_odwaga(zachowawczy);
        if(decyzja == 1)
            gracze[i + iloscGraczy]->set_odwaga(normalny);
        if(decyzja == 2)
            gracze[i + iloscGraczy]->set_odwaga(ryzykujacy);
        std::cout << gracze[i + iloscGraczy]->get_nazwa() << "- "<< gracze[i + iloscGraczy]->get_odwaga_str() << std::endl;
    }
}

void Kasyno::wybor_ilosci_graczy(int& _ilosc) {
    do {                                                                // wybór ilości graczy
        std::cout << "Wybierz ilosc graczy (1 - 3): " << std::endl;
        std::cin >> _ilosc;
        if (std::cin.fail() == true){
            std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
            std::cin.clear();                                                  
            std::cin.ignore(100 , '\n'); 
        }
    } while ( !(_ilosc >= 0 && _ilosc <= MAXGRACZY) );    
}

void Kasyno::alokacja_graczy() {
    int i;
    gracze = new Gracz* [iloscWszystkichGraczy];    // alokujemy sb tablicę wskaźników
    for(i = 0; i < iloscGraczy; i++)
        gracze[i] = new Gracz;
    for(i = 0; i < iloscBotow; i++)
        gracze[i + iloscGraczy] = new Bot;
}


void Kasyno::zwalnianie_pamieci() {
    int i;
    for(i = 0; i < iloscGraczy; i++)
        delete gracze[i];
    for(i = 0; i < iloscBotow; i++)
        delete gracze[i + iloscGraczy];
    delete[] gracze;
}

bool Kasyno::rozpocznij_nowa_gre() {
    int wybor = 0;
    bool powtorz = true, restart = false;
    std::cout << "Koniec rundy:\n (1) Graj dalej\n (2) Oposc kasyno\nWybierz (1) / (2)\n";
    while (powtorz){
        std::cin >> wybor;
        if (std::cin.fail() == true){
            std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
            std::cin.clear();                                                  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        else {
            powtorz = false;
        }
    }
    switch (wybor)
    {
    case 1:
        restart = true;
        break;
    case 2:
        restart = false;
        break;
    default:
        std::cout <<  " nastapil blad menu";
        break;
    }
    system("clear"); // system("cls"); // for windows
    return restart;
}

void Kasyno::oddaj_karty_do_banku() {
    int i;
    for(i = 0; i < ILOSCKART; i++)
        talia[i].setJestwBanku(true);
    /*
    for(i = 0; i < iloscWszystkichGraczy; i++)
            gracze[i]->get_kartyNaRece().clear();
    */
}