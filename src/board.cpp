#include "../include/board.hpp"
#include <iostream>

//Unbedingt noch auf mehr Ausnahmen testen und diese beheben. Fuehrt sonst zu Speicher Fehlern

using namespace std;
namespace ProjectAlpha2{


        /**
         * @brief Construct a new board::board object
         * leere Matrix wird erstellt
         */
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

        /**
         * @brief Funktion welche das Brett druckt
         * 
         */
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
            cout << endl;  
        }

        /**
         * @brief Funktion welche ueberprueft ob ein gegebenes Schiff gesetzt werden kann
         * 
         * @param c x-Koordinate an welcher das Schiff anfaengt
         * @param r y-Koordinate an welcher das Schiff anfaengt
         * @param isHorizontal Angabe ob das Schiff Horizontal oder Vertikal ist
         * @return true Schiff kann gesetzt werden
         * @return false Schiff kann nicht gesetzt werden
         */
        bool board::canSetShip(int c, int r, int isHorizontal)  //Überprüft, ob Eingabe korrekt ist
        {
            if(isHorizontal == 1){

                for (int i = 0; i < 4; ++i) //Prüft, ob nicht schon an dieser Stelle ein Ship gesetzt wurde // AUSNAHME
                {
                    if(matrix[r][c] == SHIP)
                    {
                        return false; 
                    }
                    c = c + 1;
                }
               
            }
            else{
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
        

        /**
         * @brief Funktion welche angibt ob über das Brett bereits gewonnen wurde
         * 
         * @return true Alle Hits gesetzt der Spieler hat gewonnen
         * @return false Noch nicht alle Hits gesetzt der Spieler hat noch nicht gewonnen
         */
        bool board::winner() //Testet, ob alle S(SHIPS) getroffen wurden 
        {   
            int h =0; // Counter für Anzahl der getroffenen Schiffe

            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    if(matrix[r][c]==HIT)
                    { 
                        h++; //Counter wird bei jedem Hit erhöht
                    }
                } 
            }  
            if(h==16)    //Überprüft ob maximal Anzahl von Hits erreicht wurden, also alle Schiffe vollständig getroffen wurden
            { 
                return false; //Endet Spiel
            }
                return true; // true, falls noch kein Sieg
        }

        /**
         * @brief Funktion welche ueberprueft ob ein angegebener Schuss ein Schiff getroffen hat
         * Außerdem Markiert die Funktion auch auf dem Gegnerbrett ob ein Schiff zerstoert wurde oder die Bombe nicht getroffen hat
         * @param r x-Koordinate
         * @param c y-Koordinate
         * @return true Schiffsteil wurde getroffen
         * @return false Kein Schiffsteil wurde getroffen
         */
        bool board::isHit(int r, int c) //Überpüft ob Eingabe ein Hit ist
        {
            if(matrix[r][c] == NOHIT || matrix[r][c] == DESTROYED)       //Teste ob Eingabe korrekt ist, also Koordinate wurde nicht schon bereits eingegeben
            {      
                cout << endl << " Input incorrect. Please try again.";
                return false;
            }
            if(matrix[r][c] == SHIP)  //Überprüft ob Hit ist
            { 
                matrix[r][c] = DESTROYED;  // wird als Kaputt makiert
                //setD(r, c);
                    cout << endl<< "Hit! Continue";
                    return true;
            }
            else
            {
                matrix[r][c] = NOHIT; //sonst als Nohit makiert
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

        /**
         * @brief Hilfsfunktion um einen Hit im Board zu markieren
         * 
         * @param r x-Koordinate
         * @param c y-Koordinate
         */
        void board::setH(int r, int c){
            matrix[r][c] = HIT;
        }

        /**
         * @brief Hilfsfunktion um einen Miss im Board zu markieren
         * 
         * @param r x-Koordinate
         * @param c y-Koordinate
         */
        void board::setM(int r, int c){
            matrix[r][c] = MISS;
        }

        void board::setD(int r, int c){
            matrix[r][c] = DESTROYED;
        }

        void board::setO(int r, int c){
            matrix[r][c] = NOHIT;
        }




}