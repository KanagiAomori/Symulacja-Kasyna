#include "SymulacjaKasyna.h"
#include <string.h>

void SymulacjaKasyna::graj() {
    
    static int nrRundy = 0;
    int ileRozdac = 2;                      // poczatkowe rozdanie

    // można w dodatkową funkcję zamknąć
    std::ifstream fp;
    fp.open("./WynikiSymulacji/ZapisSymulacji.txt",std::ios::out | std::ios::trunc);
    fp.close();
    iloscGraczy = 0;
    std::cout << "|| Ilosc Graczy Wirtualnych ||"  << std::endl;
    wybor_ilosci_graczy(iloscBotow);        // ustaw ilosc graczy wirtualnych
    iloscWszystkichGraczy = iloscGraczy + iloscBotow;
    wybor_odwagi(); // trzeba przenieść
    this->inicjalizacja_symulacji();

    for(int i = 0; i < iloscPowtorzenPetli; i++){
        this->inicjalizacja_graczy();   // ustawienie ilosci graczy i ich nazw oraz ilosci graczy wirtualnych
        nrRundy++;  // w sumie to samo co i ale trzyma się z resztą programu
        this->tasuj();  // tasuj przed każdą rundą
            
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

        this->oddaj_karty_do_banku();   // zwrócenie wszystkich kart od graczy
        this->zwalnianie_pamieci(); // zwolnienie pamięci na graczy po zakończeniu i przebiegów gier
        std::cout << "Koniec Rundy " << "(" <<  nrRundy << ")" << std::endl;
    }
    this->zapis_podsumowania_txt();
    delete[] odwagaGraczy;
}

void SymulacjaKasyna::inicjalizacja_symulacji() {
    int i = 0;
    std::cout << "wybierz ile gier ma zostac zasymulowanych" << std::endl;
    std::cin >> iloscPowtorzenPetli;    // dodaj zabezpieczenie
    histogramWygranych = new unsigned int [iloscWszystkichGraczy];
    for (i = 0; i < iloscWszystkichGraczy; i++){
        histogramWygranych[i] = 0;
    }

}

void SymulacjaKasyna::inicjalizacja_graczy() {
    int i;
    char _nazwa[MAXNAZWAGRACZA];    
    alokacja_graczy();
    for (i = 0; i < iloscWszystkichGraczy; i++){    // przypisanie graczom kasyna
        gracze[i]->set_mojeKasyno(this);
        gracze[i]->set_odwaga(odwagaGraczy[i]);
    }

    for (i = 0; i < iloscBotow; i++){ // ustaw nazwy botow
        strcpy(_nazwa, "Bot  ");
        _nazwa[3] = i + '1';
        gracze[i + iloscGraczy]->set_nazwa(_nazwa);
    }
    
}

void SymulacjaKasyna::zapisz_stan_gry_txt() {
    static int numerRundy = 1;
    int i, j;
    
    std::ofstream fp;
    std::string fileName("./WynikiSymulacji/ZapisSymulacji.txt");
    fp.open(fileName, std::ifstream::app); // otwarcie pliku w trybie zapisywania output -> do pliku
    
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

void SymulacjaKasyna::zapis_podsumowania_txt() {
    int i = 0;
    std::ofstream fp;
    std::string fileName("./WynikiSymulacji/Statystyki.csv");
    fp.open(fileName, std::ifstream::out | std::ios::trunc);
    if (fp.is_open()){
        fp << "Dane do utworzenia histogramu:" << std::endl;
        fp << "; ilosc wygranych" << std::endl;
        for(i = 0; i < iloscWszystkichGraczy; i++){
            fp << gracze[i]->get_nazwa() << ";" << histogramWygranych[i] << std::endl;
        }
        fp.close();
    }
}

void SymulacjaKasyna::okresl_zwyciezce() {
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
            if (this->gracze[i]->get_wartoscReki() == maxWartoscReki){
                std::cout << "||* zwyciezył - " << this->gracze[i]->get_nazwa() << " *||" << std::endl;  // zwycięzca
                histogramWygranych[i]++;
            }
    }
}

void SymulacjaKasyna::wybor_odwagi() {
    int decyzja;
    odwagaGraczy = new ryzyko[iloscGraczy];
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
            odwagaGraczy[i] = zachowawczy;
        if(decyzja == 1)
            odwagaGraczy[i] = normalny;
        if(decyzja == 2)
            odwagaGraczy[i] = ryzykujacy;
    }
}