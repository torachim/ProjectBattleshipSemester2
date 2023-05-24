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

            //return true;
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

            cout << endl <<"Wage einen Schuss!";

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

        void printRules(){
            bool i = false;
            while(!i){
                cout << "REGELN SCHIFFE VERSENKEN \n \n";
                cout << "Gespielt wird auf einem 10x10 Feld. \n Jeder Spieler setzt zu Beginn 4 Schiffe \n Diese nehmen jeweils 4 Felder ein \n";
                cout << "Um die Schhiffe zu setzen wird jeweil die x und y Koordinate (1-10) und danach die Richtung (Horizontal oder Vertikal (0, 1)) angegeben \n";
                cout << "Nachdem die Schiffe gesetzt wurden geht es darum als erster Spiele alle Schiffe des Gegners zu zerstören \n";
                cout << "Dazu werden auch wieder Koordinaten (1-10) angegeben um eines der vier Teile eines Schiffes zu zerstören \n";
                cout << "Landet man einen Treffer darf man nochmal schießen \n Wenn man nicht trifft ist der Gegner mit schießen dran \n";
                cout << "Treffer werden auf der Karte mit H Misses mit M gekennzeichnet \n Eine Meldung das man ein Schiff zerstört hat gibt es nicht eine extra Herausforderung \n";
                cout << "Wer als erstes alle Schiffe seines Gegners zerstört hat gewinnt und beendet das Spiel! \n";
                cout << "Willst du die Regeln nochmal lesen? J/N"<<endl;
                char a;
                cin >> a;
                if (a == *"J" || a == *"N"){
                    if(a == *"N"){
                        i = true;
                    }
                }
                else{
                    throw logic_error("Falsche Eingabe bitte starte das Spiel neu!");
                }

        }
        }
         

        void startGame()
        {
            cout <<"WILLKOMMEN BEI SCHIFFEVERSENKEN"<<endl;
            cout <<"WILLST DU DIR NOCMAL DIE REGELN ANSCHAUEN? J/N"<<endl;
            char a;
            cin >> a;
            if (a == *"J" || a == *"N"){
                if(a == *"J"){
                    printRules();
                }
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
            throw logic_error("Verbotene Eingabe bitte Spiell neu starten!");
        }

   // };

}