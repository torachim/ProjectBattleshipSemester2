#pragma once
#include<iostream>

namespace ProjectAlpha2{

    class SpielerInterface{

        public:
            virtual void shoot (int x, int y) = 0;
            virtual void setShips (int c, int r, bool isHorizontal) = 0;
            virtual std::string getName() = 0;
    };
}