#pragma once
#include <iostream>

namespace ProjectAlpha2{

    class Gameinterface {

        public:
            virtual void printrules(char a) = 0;
            virtual void startgame(int x) = 0;
            virtual void endgame() = 0;
    };
}