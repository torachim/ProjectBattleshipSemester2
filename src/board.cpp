#include "../include/board.hpp"
#include <iostream>

using namespace std;
namespace ProjectAlpha2{

            board::board() // Erstellt das Board, Funktion vielleicht unnötig
        {
            for (int r = 0; r < rows; r++)
            {
                for(int c = 0; c < columns; c ++)
                {
                    matrix[r][c] = LEER;
                }
            }
        }


        void board::printBoardS() //druckt das Board
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

        void board::printBoardG()
        {
            for (int r = 0; r < rows; r++)
            {
                cout<<endl;
                for (int c = 0; c < columns; c++)
                {
                    if(matrix[r][c]==SHIP){
                        cout<<LEER<< " " ;
                    }
                    else{
                    cout<< matrix[r][c] << " " ;
                    }
                }
            }

        }

        void board::printBoard()
        {
            printBoardG();
            cout << endl;
            printBoardS();
        }


        bool board::canSetShip(int c, int r, bool isHorizontal)  //Überprüft, ob Eingabe korrekt ist
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

        void board::setShips()
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

                printBoardS(); 
            }

            else
            {
                cout<< endl << "Input incorrect. Please try again.";
                setShips();
            }
            
        }


        bool board::winner() //Testet, ob alle S(SHIPS) getroffen wurden
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

        void board::isHit(int r, int c)
        {
            if(matrix[r][c] == HIT || matrix[r][c] == MISS){            //Teste ob Eingabe korrekt ist also koordinate wurde noch nicht versucht
                cout << endl << " Input incorrect. Please try again.";
                shot();
            }

            if(matrix[r][c] == SHIP){
                matrix[r][c] = HIT;
                bool win = winner();
                if(win){
                    printBoard();
                    cout << endl<< "Hit! Continue";
                    shot();
                }
            }

            else{
                matrix[r][c] = MISS;
                printBoard();
                cout<<endl<< "Miss! It's your opponent's turn";
            }
        }


        void board::shot(){

            int x;
            int y;

            cout << endl <<"Wage einen Schuss!";

            cout << endl <<"Enter x coordinate: "; //Abfrage nach einem Rateversuch
            cin >> x;
            cout << endl <<"Enter y coordinate: ";
            cin >> y;


            int r = y-1;
            int c = x-1;

            isHit(r, c);


            /*if(matrix[r][c] == HIT){ //Testet, ob Eingabe korrekt ist
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
            }*/

        }

        void printRules(){
            bool i = false;
            while(!i){
                cout << "\n REGELN SCHIFFE VERSENKEN \n \n";
                cout << "Gespielt wird auf einem 10x10 Feld. \nJeder Spieler setzt zu Beginn 4 Schiffe. \nDiese nehmen jeweils 4 Felder ein. \n";
                cout << "Um die Schhiffe zu setzen wird jeweil die x und y Koordinate (1-10) und danach die Richtung (Horizontal oder Vertikal (0, 1)) angegeben. \n";
                cout << "Nachdem die Schiffe gesetzt wurden geht es darum als erster Spiele alle Schiffe des Gegners zu zerstören. \n";
                cout << "Dazu werden auch wieder Koordinaten (1-10) angegeben um eines der vier Teile eines Schiffes zu zerstören. \n";
                cout << "Landet man einen Treffer darf man nochmal schießen. \nWenn man nicht trifft ist der Gegner mit schießen dran. \n";
                cout << "Treffer werden auf der Karte mit H Misses mit M gekennzeichnet. \nEine Meldung das man ein Schiff zerstört hat gibt es nicht eine extra Herausforderung. \n";
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


}