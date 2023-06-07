#pragma once 
#include <iostream>
#include "Spieler.hpp"
#include "gameinterface.hpp"

namespace ProjectAlpha2{

    class Game : public Gameinterface {

        public:
            Game(const Spieler Spieler1_, const Spieler Spieler2_ );        //Ein Game bekommt 2 Spieler uebergeben
            void printrules(char a);                                              //Druckt die Regeln
            void startgame(int x);                                               //Funktion in welcher der Spielablauf durchgegeangen wird
            void endgame();                                                 //Funktion um das Spiel zu beenden

        private:
            Spieler Spieler1;                   //Spieler 1
            Spieler Spieler2;                   //Spieler 2
    };
}