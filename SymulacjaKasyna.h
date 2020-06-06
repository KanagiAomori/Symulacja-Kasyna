#include "Kasyno.h"
#include <fstream>

class SymulacjaKasyna : Kasyno {
    private:
        unsigned int iloscPowtorzenPetli;
        unsigned int* histogramWygranych = nullptr;
        ryzyko* odwagaGraczy = nullptr;
    public:
        ~SymulacjaKasyna() { if(histogramWygranych != nullptr) delete[] histogramWygranych; }
        void inicjalizacja_symulacji();
        void graj();
        void inicjalizacja_graczy();
        void zapisz_stan_gry_txt();
        void zapis_podsumowania_txt();
        void okresl_zwyciezce();
        void wybor_odwagi();
        // specjalne podsumowanie symulacji dane na podstawie których można wnioskować statystyczne 
        // na temat doboru określonej strategii gry o sumie zerowej w sposób iterowany
};