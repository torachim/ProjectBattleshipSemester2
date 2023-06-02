
//#include "../src/board.cpp"
#include "../include/board.hpp"
#include "../include/Spieler.hpp"
#include "../include/game.hpp"
#include <iostream>
#include<string>

using namespace std;

using namespace ProjectAlpha2;


    int main()
    {
        board m;
        board l;
        board k;
        board n;

        Spieler t = Spieler(m , l, "Torge");
        Spieler p = Spieler(k, n, "Gegner");

        Game g = Game (t, p);

        g.startgame();
        
        /*std::cout <<"WILLKOMMEN BEI SCHIFFEVERSENKEN"<<endl;
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
        }*/
    }


//clang++ -std=c++17 -I./include  examples/demo.cpp -o game