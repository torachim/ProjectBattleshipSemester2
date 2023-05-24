//10 mal 10 Feld | 4 Schiffe (4*1 Groß)

#include "boardInterface.hpp"
#include <iostream>
#include<string>
using namespace std;


namespace ProjectAlpha2{

    //class Board : public BoardInterface {

        /*public:
        void board();
        void printBoard(); 
        void setShips();
        bool canSetShip();
        void shot();
        bool winner();
        
    

        private: //Wohin damit ???*/
        const int rows =10 ;
        const int columns =10;
        char matrix [rows][columns]; 
        const char SHIP = 'S';  
        const char HIT = 'H';
        const char MISS ='M';
        const char LEER ='*';
        


        void board() // Erstellt das Board, Funktion vielleicht unnötig
        {
            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    matrix[r][c] = LEER;
                }
            }
        }


        void printBoard() //druckt das Board
        {
            
            for (int r = 0; r < rows; r++)
            {
                cout<<endl; 
                for(int c = 0; c < columns; c ++)
                {
                    cout<< matrix[r][c] << " " ; //druckt jedes Kästchen einzeln
                }
                
            } 
           
        }


        bool canSetShip(int c, int r, bool isHorizontal)  //Überprüft, ob Eingabe korrekt ist
        {
            if(isHorizontal)
            {
                if(c+3 > 9)  //Prüft, ob Ship übers Board hinaus läuft
                {
                    return false;
                }

                for (int i = 0; i < 4; ++i) //Prüft, ob nicht schon an dieser Stelle ein Ship gesetzt wurde
                {
                    if(matrix[r][c] == SHIP)
                    {
                        return false; 
                    }
                    c = c + 1;
                }
            }

            else
            {
                if(r+3 > 9)
                {
                    return false;
                }

                for (int i = 0; i < 4; ++i) 
                {
                    if(matrix[r][c] == SHIP)
                    {
                        return false;
                    }
                    r = r + 1;
                }
            }
            return true;

            return true;
        }

        void setShips()
        {
            int x;  // Variable für Column Eingabe
            int y;  // Variable für Row Eingabe
            bool isHorizontal; // Entscheidet in welche Richtung das Ship geht

            cout << endl <<"Enter starting coordinate x: " ; //Abfrage der Anfangskoordinate
            cin >> x ;
            cout << endl <<"Enter starting coordinate y: " ;
            cin >> y;

            cout << endl << "Enter Orientation(1 for horizontal,0 for vertical): "; //Abfrage der Richtung
            cin >> isHorizontal;

            int c = x -1 ; //  da Index eigentlich bei null beginnt
            int r = y -1 ;

            bool canSet = canSetShip (c, r, isHorizontal);
            if(canSet)  //Überprüft ob Eingabe korrekt
            {
               
                if(isHorizontal) //Setzt ein horizontales Schiff
                {
                    for (int i = 0; i < 4; ++i) //Setzen von vier S (SHIPS)
                    {
                    matrix[r][c] = SHIP; // wird durch S gekennzeichnet (muss später entfernt werden)
                    c = c + 1;
                    }
                }
                

                else
                {
                    for (int i = 0; i < 4; ++i) 
                    {
                    matrix[r][c] = SHIP;
                    r = r + 1;
                    }
                }

                printBoard(); 
            }

            else
            {
                cout<< endl << "Input incorrect. Please try again.";
                setShips();
            }
            
        }


        bool winner() //Testet, ob alle S(SHIPS) getroffen wurden
        {   
            int h =0;

            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    if(matrix[r][c]==HIT)
                    { 
                        h++; 
                    }
                } 
            }  
            if(h==16)    //Überprüft ob maximal Anzahl von Hits erreicht wurden, also alle Schiffe vollständig getroffen wurden
            { 
                printBoard();
                cout<<endl<< "Congratulations, you are the WINNER!"<<endl << "GAMEOVER";
                return false;
            }
                return true;
        }


        void shot(){

            int x;
            int y;

            cout << endl <<"Enter x coordinate: "; //Abfrage nach einem Rateversuch
            cin >> x;
            cout << endl <<"Enter y coordinate: ";
            cin >> y;

            int r = y-1;
            int c = x-1;

            if(matrix[r][c] == HIT){ //Testet, ob Eingabe korrekt ist
                cout<< endl << " Input incorrect. Please try again.";
                shot();
            }

            if(matrix[r][c] == MISS){ //Testet, ob Eingabe korrekt ist
                cout<< endl << " Input incorrect. Please try again.";
                shot();
            }

            if(matrix[r][c] == SHIP) //Überprüft, ob es ein Hit ist
            {   
                    matrix[r][c] = HIT;
                    bool win = winner();
                    if(win) // Testet, ob alle S (SHIPS) getroffen wurden
                    { 
                    printBoard();
                    cout<<endl<< "Hit! Continue"; 
                    shot(); // nach einem Hit ein weiterer Rateversuch
                    }
            }

            else{
                matrix[r][c] = MISS;
                printBoard();
                cout<<endl<< "Miss! It's your opponent's turn";
                //Zum anderen Feld wechseln
            }

        }
         

        void startGame()
        {
            cout<<"START THE GAME:"<<endl; 
            board();
            //Spieler Funktion (pick a player)
            //2 Boards erstellen
            setShips();
            setShips();
            setShips();
            setShips();

            // Feld wechseln
            shot(); // dort wird in der Funktion das Feld gewechselt
        }

   // };

}