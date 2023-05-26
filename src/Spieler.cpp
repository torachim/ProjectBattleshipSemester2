#include "../include/Spieler.hpp"
#include "board.cpp"
#include "../include/board.hpp"
#include <iostream>
#include <memory>

using namespace std;
namespace ProjectAlpha2{

    Spieler::Spieler(board boardS_, board boardL_, string Name_) : boardS(boardS_), boardL(boardL_), Name(Name_)
    {
    }

    string Spieler::getName(){
        return Name;
    }

    void Spieler::setShips(){

            int x;  // Variable für Column Eingabe
            int y;  // Variable für Row Eingabe
            bool isHorizontal; // Entscheidet in welche Richtung das Ship geht

            cout << endl <<"Enter starting coordinate x (1-10): " ; //Abfrage der Anfangskoordinate
            cin >> x ;
            if(x > 10 || x < 1){
                cout << endl << "Input incorrect! Please try again!";
                setShips();
            }
            cout << endl <<"Enter starting coordinate y (1-10): " ;
            cin >> y;
            if(y > 10 || y < 1){
                cout << endl << "Input incorret! Please try again!";
                setShips();
            }

            cout << endl << "Enter Orientation(1 for horizontal,0 for vertical): "; //Abfrage der Richtung
            cin >> isHorizontal;
        
            int c = x -1 ; //  da Index eigentlich bei null beginnt
            int r = y -1 ;

            bool canSet = boardS.canSetShip (c, r, isHorizontal);
            if(canSet)  //Überprüft ob Eingabe korrekt
            { 
                if(isHorizontal) //Setzt ein horizontales Schiff
                {
                    for (int i = 0; i < 4; ++i) //Setzen von vier S (SHIPS)
                    {
                    boardS.Schiffsetzen(r, c);
                    }
                }
                else //Setzt ein vertikales Schiff
                {
                    for (int i = 0; i < 4; ++i) 
                    {
                    boardS.Schiffsetzen(r, c);
                    }
                }
                boardS.printBoardS();  // druckt Spielfeld mit seinen eigenen Schiffen aus
            }
            else
            {
                cout<< endl << "Input incorrect. Please try again."; //Erneute eingabe, falls Fehler bei vorheriger Eingabe
                setShips();
            }  
        }

}

