// 10 mal 10 Feld | 4 Schiffe (4*1 Groß)
#pragma once
#include "boardInterface.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace ProjectAlpha2 {

class board : public boardInterface {

public:
  board();
  //void printBoardS();
  //void printBoardG();
  void printBoard();
  //void setShips();
  bool canSetShip(int c, int r, bool isHorizontal);
  bool isHit(int r, int c);
  //void shot();
  bool winner();
  //void printRules();
  void Schiffsetzen(int r, int c);
  void setH(int r, int c);
  void setM(int r, int c);

private: 
  const int rows = 10;
  const int columns = 10;
  char matrix[10][10];
  const char SHIP = 'S';
  const char HIT = 'H';
  const char MISS = 'M';
  const char DESTROYED = 'X';
  const char NOHIT = 'O';
  const char LEER = '*';
};
}

