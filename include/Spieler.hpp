#pragma once 
#include "SpielerInterface.hpp"
#include "board.hpp"
#include <iostream>

namespace ProjectAlpha2{

    class Spieler : public SpielerInterface {

        public:
            Spieler();
            void shoot (int x, int y);
            void setShips (int c, int r, bool isHorizontal);
            std::string getName();
        
        private:
            std::string Name;


    };
}