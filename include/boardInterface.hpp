#pragma once
#include <iostream>

namespace ProjectAlpha2 { 

    class boardInterface{

        public:
            virtual void printBoard() = 0;
            virtual bool canSetShip(int c, int r, int isHorizontal) = 0;
            virtual bool isHit(int r, int c) = 0;
            virtual bool winner() = 0; 
            virtual void Schiffsetzen(int r, int c) = 0;
    } ;
}