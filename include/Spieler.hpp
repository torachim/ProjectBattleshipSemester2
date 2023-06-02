#pragma once 
#include "SpielerInterface.hpp"
#include "board.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace ProjectAlpha2{

    class Spieler : public SpielerInterface {

        public:
            Spieler(board boardS_, board boardL_, std::string Name_);       //Spieler erstellen
            void shoot ();                                                  //Shoot Funktion als Spielerfunktion
            void setShips ();                                               //Funktion um die Schiffe zu setzen
            std::string getName();                                          //Funktion um den Namen eines Spielers zu bekommen
            void setEnBoard (board Enemyboard);                             //Funktion um das Gegnerboard festzulegen
            board getSBoard();                                              //Funktion welche das Board mit den Schiffen zurueckgibt
            board getLBoard();                                              //Funktion welche das Board ohne Schiffe zurueckgibt
            void winnercontrol();
            bool getwinner();
            
        
        private:
            std::string Name;
            board boardS;                           //Board mit Schiffen
            board boardL;                           //Board ohne Schiffe
            std::shared_ptr<board> geg_brett;       //Pointer welcher auf das Gegnerische Brett zeigt
            bool isWinner;

    };
}