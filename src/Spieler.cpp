#include "../include/Spieler.hpp"
#include "../include/board.hpp"
#include <iostream>
#include <memory>

using namespace std;
namespace ProjectAlpha2{

    /**
     * @brief Construct a new Spieler:: Spieler object
     * 
     * @param boardS_ Brett welches die Schiffe dieses Spieler enthalten soll
     * @param boardL_ Brett welches die von dem Spieler gemachten Schuesse enthalten soll
     * @param Name_  Name des Spielers
     */
    Spieler::Spieler(board boardS_, board boardL_, string Name_) : boardS(boardS_), boardL(boardL_), Name(Name_)
    {
        isWinner = false;       //isWinner wird mit false initialiesiert
    }

    /**
     * @brief Funktion welche den Namen eines Spielers zurueckgibt
     * 
     * @return string Name
     */
    string Spieler::getName(){
        return Name;
    }

    /**
     * @brief Funktion welche es dem Spieler ermöglicht Schiffe zu setzen
     * 
     */
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
                    boardS.Schiffsetzen(r, c); //Hilfsfunktion Schiffsetzen wird aufgerufen
                    c = c + 1;  //Hilfsfunktion des Schiffbrettes wird aufgerufen um das entsprechende Schiff zu setzen
                    }
                }
                else //Setzt ein vertikales Schiff
                {
                    for (int i = 0; i < 4; ++i) 
                    {
                    boardS.Schiffsetzen(r, c);  //Hilfsfunktion Schiffsetzen wird aufgerufen
                    r = r + 1;  //Hilfsfunktion des Schiffbrettes wird aufgerufen um das entsprechende Schiff zu setzen
                    }
                }
                boardS.printBoard();  // druckt Spielfeld mit seinen eigenen Schiffen aus
            }
            else
            {
                cout<< endl << "Input incorrect. Please try again."; //Erneute eingabe, falls Fehler bei vorheriger Eingabe
                setShips();
            }  
        }

        /**
         * @brief Funktion mit welcher ein Spieler schießen kann
         * 
         */
        void Spieler::shoot(){
            int x;
            int y;

            cout << endl <<"Wage einen Schuss!";//Abfrage nach einem Rateversuch
            cout << endl <<"Enter x coordinate: "; 
            cin >> x;
            cout << endl <<"Enter y coordinate: ";
            cin >> y;

            int r = y - 1; // da bei der Eingabe bei 1 begonnen wird, aber Indizes der Matrix bei 0 beginnen
            int c = x - 1;
            

            if(geg_brett ->isHit(r, c) == true){            //Abfrage ob bei den gegebenen Koordinaten ein Schiff des Gegners liegt
                boardL.setH(r, c);                          //Wenn ja wird in seinem Brett an den Koordinaten  ein Hit markiert
                boardL.printBoard();
                winnercontrol();                            //Hilfsfunktion wird aufgerufen um zu schauen ob der schießende Spieler gewonnen hat
                if(getwinner() == false){                   //Wenn er noch nicht gewonnen hat...
                    shoot();                                //darf er nochmal schießen
                }
            }  

            else{
                boardL.setM(r, c);                          //Wenn kein Trefer gelandet wurde wird ein Miss gestzt
                boardL.printBoard();
            }
            
        }

        /**
         * @brief Funktion welche die Variable geg_brett setzt
         * 
         * @param EnemyBoard Brett auf welchem die gegnerische Schiffe eingetragen sind
         */
        void Spieler::setEnBoard(board EnemyBoard){
            geg_brett = make_shared<board>(EnemyBoard);     //Pointer auf das Gegnerbrett auf welchem die Schiffe stehen
        }

        /**
         * @brief Funktion welche das Brett mit Schiffen zurueckgibt
         * 
         * @return board 
         */
        board Spieler::getSBoard(){
            return boardS;
        }

        /**
         * @brief Funktion welche das Brett ohne Schiffe sondern mit den Daten zu den Schuessen zurueckgibt
         * 
         * @return board 
         */
        board Spieler::getLBoard(){
            return boardL;
        }

        /**
         * @brief Funktion welche ueberprueft ob ein Spieler bereits gewonnen aht
         * 
         */
        void Spieler::winnercontrol(){
            bool a = boardL.winner();           //Die Winner Hilfsfunktion wird auf dem Board mit den Hits aufgerufen
            if(a == false){                     //Wenn zurueckgegeben wird das alle Hits vorliegen
                isWinner = true;                //Variable isWinner wird auf true gesetzt
            }
        }

        /**
         * @brief Funktion welche die Variablezurueckgibt ib ein Spieler bereits gewonnen hat
         * 
         * @return true Spieler hat gewonnen
         * @return false Spieler hat noch nicht gewonnen
         */
        bool Spieler::getwinner(){
            return isWinner;
        }

}

