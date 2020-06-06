#include "Karta.h"
#include "Gracz.h"
#include "Kasyno.h"
#include "SymulacjaKasyna.h"
#include "Bot.h"

void menu();

int main(int argc, char** argv)
{
    menu();   
    return 0;
}

void menu() {
    char control;
    bool restart = true;
    Kasyno ZlotaWyspa1; //  Kasyno
    SymulacjaKasyna ZlotaWyspa2;    // symulacja Kasyna
    while (restart){

        system("clear");    // "cls" dla windowsa
        std::cout << "Kasyno - Gra w Oczko" << std::endl;
        std::cout << "(1) Gra w oczko w Kasynie - gracze oraz boty" << std::endl;
        std::cout << "(2) Symulacja (n) przebiegow gry Botow" << std::endl;
        std::cout << "(3) Exit" << std::endl;        
        do {                                                                // wybór ilości graczy
            std::cin >> control;
            if (std::cin.fail() == true){
                std::cout << "Wykryto wprowadzenie błednych danych" << std::endl;
                std::cin.clear();                                                  
                std::cin.ignore(100 , '\n'); 
            }
        } while (std::cin.fail());

        switch (control)
        {
        case '1':
            ZlotaWyspa1.graj(); // gra w kasynie
            break;
        case '2':
            ZlotaWyspa2.graj(); // symulacja
            break;
        case '3':
            restart = false;
            break;
        default:
            std::cout << "Dokonano nieprawidlowego wyboru" << std::endl;
            break;
        }
    }
}