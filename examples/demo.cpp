
//#include "../src/board.cpp"
#include "../include/board.hpp"
#include <iostream>
#include<string>

using namespace std;

using namespace ProjectAlpha2;


    int main()
    {
        
        std::cout <<"WILLKOMMEN BEI SCHIFFEVERSENKEN"<<endl;
        std::cout <<"WILLST DU DIR NOCMAL DIE REGELN ANSCHAUEN? J/N"<<endl;
        char a;
        cin >> a;
        if (a == *"J" || a == *"N"){
            board b;
            if(a == *"J"){
                b.printRules();
            }
                //Spieler Funktion (pick a player)
                //2 Boards erstellen
            b.setShips();
            b.setShips();
            b.setShips();
            b.setShips();

                // Feld wechseln
            b.shot(); // dort wird in der Funktion das Feld gewechselt
        }    
        else
        {
            throw logic_error("Verbotene Eingabe bitte Spiel neu starten!");
        }
    }


//clang++ -std=c++17 -I./include  examples/demo.cpp -o game