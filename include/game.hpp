#pragma once 
#include <iostream>
#include "Spieler.hpp"
#include "gameinterface.hpp"

namespace ProjectAlpha2{

    class Game : public Gameinterface {

        public:
            Game(const Spieler Spieler1_, const Spieler Spieler2_ );
            void printrules();
            void startgame();
            void endgame();

        private:
            Spieler Spieler1;
            Spieler Spieler2;
    };
}