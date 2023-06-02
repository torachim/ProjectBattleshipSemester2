#include "../include/board.hpp"
#include <iostream>

//Unbedingt noch auf mehr Ausnahmen testen und diese beheben. Fuehrt sonst zu Speicher Fehlern

using namespace std;
namespace ProjectAlpha2{

        board::board() // Erstellt das Spielfeld
        {
            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    matrix[r][c] = LEER;
                }
            }
        }


        void board::printBoard() //druckt das Board, worauf die eigenen Schiffe und die Hits und Misses des Gegenspielers abgebildet sind
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


        bool board::canSetShip(int c, int r, bool isHorizontal)  //Überprüft, ob Eingabe korrekt ist
        {
            if(isHorizontal)
            {
                if(c+3 > 9)  //Prüft, ob Ship übers Board hinaus läuft
                {
                    return false;
                }
                for (int i = 0; i < 4; ++i) //Prüft, ob nicht schon an dieser Stelle ein Ship gesetzt wurde // AUSNAHME
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
                if(r+3 > 9) // Das selbe nur für Y-Achse
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
        }


        bool board::winner() //Testet, ob alle S(SHIPS) getroffen wurden 
        {   
            int h =0; // Counter für Anzahl der getroffenen Schiffe

            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    if(matrix[r][c]==HIT)
                    { 
                        h++; //Counter wird bei jedem Hitt erhöht
                    }
                } 
            }  
            if(h==16)    //Überprüft ob maximal Anzahl von Hits erreicht wurden, also alle Schiffe vollständig getroffen wurden
            { 
                return false; //Endet Spiel
            }
                return true; // true, falls noch kein Sieg
        }


        bool board::isHit(int r, int c) //Überpüft ob Eingabe ein Hit ist
        {
            printBoard();
            if(matrix[r][c] == NOHIT || matrix[r][c] == DESTROYED)       //Teste ob Eingabe korrekt ist, also Koordinate wurde nicht schon bereits eingegeben
            {      
                cout << endl << " Input incorrect. Please try again.";
                return true;
            }
            if(matrix[r][c] == SHIP)  //Überprüft ob Hit ist
            { 
                matrix[r][c] = DESTROYED;  // wird als Hit makiert
                    cout << endl<< "Hit! Continue";
                    return true;
            }
            else
            {
                matrix[r][c] = NOHIT; //sonst als Miss makiert
                cout<<endl<< "Miss! It's your opponent's turn";
                return false;
                // anderer Spieler ist dran
            }
        }


        /**
         * @brief Hilfsfunktion um ein Schiff in das Board zu setzen
         * 
         * @param r row Koordinate
         * @param c coloumn Koordinate
         */
        void board::Schiffsetzen(int r, int c){
            matrix[r][c] = SHIP;
        }

        void board::setH(int r, int c){
            matrix[r][c] = HIT;
        }

        void board::setM(int r, int c){
            matrix[r][c] = MISS;
        }




}