#pragma once
#include <iostream>

namespace ProjectAlpha2{

    class Gameinterface {

        public:
            virtual void printrules() = 0;
            virtual void startgame() = 0;
            virtual void endgame() = 0;
    };
}