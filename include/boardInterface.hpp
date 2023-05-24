#pragma once
#include <iostream>

namespace ProjectAlpha2 { //???

    class BoardInterface{

        public:
            virtual void board();
            virtual void printBoard();
            virtual void setShips();
            virtual bool canSetShip();
            virtual void shot();
            virtual bool winner();
        
    } ;
}