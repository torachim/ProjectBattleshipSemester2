#include "../include/board.hpp"
#include <iostream>

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


        void board::printBoardS() //druckt das Board, worauf die eigenen Schiffe und die Hits und Misses des Gegenspielers abgebildet sind
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


        void board::printBoardG() //druckt das Board, wo nur die eigenen Hits und Misses 
        {
            for (int r = 0; r < rows; r++)
            {
                cout<<endl;
                for (int c = 0; c < columns; c++)
                {
                    if(matrix[r][c]==SHIP){
                        cout<<LEER<< " " ;   // verdeckt alle mit SHIP gekennzeichneten Stellen
                    }
                    else{
                    cout<< matrix[r][c] << " " ;
                    }
                }
            }
        }


        void board::printBoard() // druckt beide Boards aus
        {
            printBoardS();
            cout << endl;
            printBoardG();
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


        void board::setShips()
        {
            int x;  // Variable für Column Eingabe
            int y;  // Variable für Row Eingabe
            bool isHorizontal; // Entscheidet in welche Richtung das Ship geht

            cout << endl <<"Enter starting coordinate x (1-10): " ; //Abfrage der Anfangskoordinate
            cin >> x ;
            cout << endl <<"Enter starting coordinate y (1-10): " ;
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
                    matrix[r][c] = SHIP; // wird durch S gekennzeichnet 
                    c = c + 1;
                    }
                }
                else //Setzt ein vertikales Schiff
                {
                    for (int i = 0; i < 4; ++i) 
                    {
                    matrix[r][c] = SHIP;
                    r = r + 1;
                    }
                }
                printBoardS();  // druckt Spielfeld mit seinen eigenen Schiffen aus
            }
            else
            {
                cout<< endl << "Input incorrect. Please try again."; //Erneute eingabe, falls Fehler bei vorheriger Eingabe
                setShips();
            }  
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
                printBoard();
                cout<<endl<< "Congratulations, you are the WINNER!"<<endl << "GAMEOVER";
                return false; //Endet Spiel
            }
                return true; // true, falls noch kein Sieg
        }


        void board::isHit(int r, int c) //Überpüft ob Eingabe ein Hit ist
        {
            if(matrix[r][c] == HIT || matrix[r][c] == MISS)       //Teste ob Eingabe korrekt ist, also Koordinate wurde nicht schon bereits eingegeben
            {      
                cout << endl << " Input incorrect. Please try again.";
                shot();  // dann neuer Versuch
            }
            if(matrix[r][c] == SHIP)  //Überprüft ob Hit ist
            { 
                matrix[r][c] = HIT;  // wird als Hit makiert
                bool noWin = winner(); //überprüft ob Spiel gewonnen wurde
                if(noWin)
                {
                    printBoard();
                    cout << endl<< "Hit! Continue";
                    shot(); // Spieler ist wieder dran, wenn es ein Hit war
                }
            }
            else
            {
                matrix[r][c] = MISS; //sonst als Miss makiert
                printBoard();
                cout<<endl<< "Miss! It's your opponent's turn";
                // anderer Spieler ist dran
            }
        }


        void board::shot()  //Funktion für Angriff
        { 
            int x;
            int y;

            cout << endl <<"Wage einen Schuss!";//Abfrage nach einem Rateversuch
            cout << endl <<"Enter x coordinate: "; 
            cin >> x;
            cout << endl <<"Enter y coordinate: ";
            cin >> y;

            int r = y-1; // da bei der Eingabe bei 1 begonnen wird, aber Indizes der Matrix bei 0 beginnen
            int c = x-1;

            isHit(r, c);
        }


        void board::printRules() // Auflistung der Spielregeln
        {
            bool i = false; 
            while(!i)
            {

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
                    throw logic_error("Falsche Eingabe bitte starte das Spiel neu!"); //Überprüft das nur J und N eingegeben werden
                }
            }
        }


}