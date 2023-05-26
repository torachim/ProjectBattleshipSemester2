#pragma once 
#include "SpielerInterface.hpp"
#include "board.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace ProjectAlpha2{

    class Spieler : public SpielerInterface {

        public:
            Spieler(board boardS_, board boardL_, std::string Name_);
            void shoot ();
            void setShips ();
            std::string getName();
        
        private:
            std::string Name;
            board boardS;                           //Board mit Schiffen
            board boardL;                           //Board ohne Schiffe
            std::shared_ptr<board> geg_brett;       //Pointer welcher auf das Gegnerische Brett zeigt

    };
}