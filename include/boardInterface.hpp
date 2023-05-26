#pragma once
#include <iostream>

namespace ProjectAlpha2 { 

    class boardInterface{

        public:
            virtual void printBoardS() = 0;
            virtual void printBoardG() = 0;
            virtual void printBoard() = 0;
            virtual void setShips() = 0;
            virtual bool canSetShip(int c, int r, bool isHorizontal) = 0;
            virtual void isHit(int r, int c) = 0;
            virtual void shot() = 0;
            virtual bool winner() = 0; 
            virtual void printRules() = 0;
            virtual void Schiffsetzen(int c, int r) = 0;
        
    } ;
}