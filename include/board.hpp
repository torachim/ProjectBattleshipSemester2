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
  void printBoard();                //Funktion welche das entsprechende Board druckt
  bool canSetShip(int r, int c, int isHorizontal);   //Funktion welche ueberprueft ob ein Angegebenes Schiff ueberhaupt gesetzt werden kann
  bool isHit(int r, int c);         //Funktion welche ueberprueft ob ein Schuss ein Shiff trifft oder nicht
  bool winner();                    //Funktion welche für die Ueberpruefung gebraucht wird ob ein Spieler gewonnen hat
  void Schiffsetzen(int r, int c);      //Funktion welche ein S an die entsprechende Stelle fuer ein Schiff setzt
  void setH(int r, int c);              //Funktion welche ein H setzt um einen Hit auf einem Board zu markieren
  void setM(int r, int c);              //Funktion welche ein M setzt um einen Miss zu markieren
  void setD(int r, int c);
  void setO(int r, int c);

private: 
  const int rows = 10;                  //Jedes Brett hat 10 Reihen
  const int columns = 10;               //Jedes Brett hat 10 Spalten
  char matrix[10][10];                  //10 * 10 Matrix als Board
  const char SHIP = 'S';                //Buchstaben repräsentieren bestimmte Sachen auf einem Board
  const char HIT = 'H';
  const char MISS = 'M';
  const char DESTROYED = 'X';
  const char NOHIT = 'O';
  const char LEER = '*';
};
}

