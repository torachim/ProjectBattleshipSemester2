#include <gtest/gtest.h>
#include<iostream>
#include "../src/board.cpp"
#include "../include/game.hpp"
#include "../include/Spieler.hpp"

using namespace ProjectAlpha2;

TEST(boardfkt, isHit){
      board m;
      m.Schiffsetzen(1,1);
      EXPECT_EQ(m.isHit(1, 1), true);
      EXPECT_EQ(m.isHit(3,6), false);
}

TEST(boardfkt, canSetShip){
      board m;
      EXPECT_EQ(m.canSetShip(4,6,1), true);
      EXPECT_EQ(m.canSetShip(9,6,1), false); //Ausnahmen beachten
}

TEST(boardfkt, winner){
      board m;
      EXPECT_EQ(m.winner(), true);
}


