#pragma once
#include<iostream>
#include "board.hpp"

namespace ProjectAlpha2{

    class SpielerInterface{

        public:
            virtual void shoot () = 0;
            virtual void setShips () = 0;
            virtual std::string getName() = 0;
            virtual void setEnBoard(board EnemyBoard) = 0;
            virtual board getSBoard() = 0;
            virtual board getLBoard() = 0;
            virtual void winnercontrol() = 0;
    };
}