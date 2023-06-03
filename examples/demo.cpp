//#include "../src/board.cpp"
#include "../include/board.hpp"
#include "../include/Spieler.hpp"
#include "../include/game.hpp"
#include <iostream>
#include<string>

using namespace std;

using namespace ProjectAlpha2;


    int main()
    {
        board m;
        board l;
        board k;
        board n;

        Spieler t = Spieler(m , l, "Torge");
        Spieler p = Spieler(k, n, "Gegner");
        
        Game g = Game (t, p);

        g.startgame();
        
    }


//clang++ -std=c++17 -I./include  examples/demo.cpp -o game