#pragma once
#include <iostream>

namespace ProjectAlpha2 { //???

    class boardInterface{

        public:
            virtual void Board();
            virtual void printBoard();
            virtual void setShips();
            virtual bool canSetShip();
            virtual void shot();
            virtual void winner();
        
    } ;
}