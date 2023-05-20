//10 mal 10 Feld | 4 Schiffe (4*1 Groß) 

#include <iostream>
#include <ctime>

using namespace std;

const int rows = 10;
const int columns =10;
int matrix [rows][columns];
const char SHIP = 'S';  
const char HIT = 'H';
const char MISS ='M';


void Board() // Erstellt das Board, Funktion vielleicht unnötig
{
     for (int r = 0; r < rows; r++)
     {
        for(int c = 0; c < columns; c ++)
        {
            matrix[r][c] = 0;
        }
     }
}


void printBorad() //druckt das Board
{
    for (int r = 0; r < rows; r++)
     {
        for(int c = 0; c < columns; c ++)
        {
            cout<< matrix[r][c] << " " ; //druckt jedes Kästchen einzeln
        }
     } 
    cout<<endl; 
}


void setShips()
{
    int x;  // Variable für Column Eingabe
    int y;  // Variable für Row Eingabe
    bool isHorizontal; // Entscheidet in welche Richtung das Ship geht

    cout << endl <<"Enter starting coordinate (x,y): " ; //Abfrage der Anfangskoordinate
    cin >> y >> x;

    cout << endl << "Enter Orientation(0 for horizontal,1 for vertical): "; //Abfrage der Richtung
    cin >> isHorizontal;

    if(!canSetShip)  //Überprüft ob Eingabe korrekt
    {
        cout<< "Input incorrect. Please try again.";
        void setShips();
    }
    
    int c = x;
    int r = y;

    if(isHorizontal) //Setzt ein horizontales Schiff
    {
        for (int i = 0; i < 4; ++i) //Setzen von vier S (SHIPS)
        {
        matrix[y][x] = SHIP; // wird durch S gekennzeichnet (muss später entfernt werden)
        x = x + 1;
        }
    }
    

    else
    {
        for (int i = 0; i < 4; ++i) 
        {
        matrix[y][x] = SHIP;
        y = y + 1;
        }
    }

    printBorad(); 
    setShips(); // Funktion 4 mal aufgerufen, da man 4 Ships setzt
    setShips();
    setShips();
}


bool canSetShip(int x, int y, bool isHorizontal)  //Überprüft, ob Eingabe korrekt ist
{
    if(isHorizontal)
    {
        if(x+10 > 10)  //Prüft, ob Ship übers Board hinaus läuft
        {
            return false;
        }

        for (int i = 0; i < 4; ++i) //Prüft, ob nicht schon an dieser Stelle ein Ship gesetzt wurde
        {
            if(matrix[y][x] == SHIP)
            {
                return false; 
            }
        }
    }

    else
    {
        if(y+10 > 10)
        {
            return false;
        }

        for (int i = 0; i < 4; ++i) 
        {
            if(matrix[y][x] == SHIP)
            {
                return false;
            }
        }
    }

}


void shot(){

    int x;
    int y;

    cout << endl <<"Enter coordinate (x,y): "; //Abfrage nach einem Rateversuch
    cin >> y >> x;

    if(matrix[x][y] == SHIP) //Überprüft, ob es ein Hit ist
    {
        matrix[x][y] = HIT;
        printBorad();
        winner(); // Testet, ob alle S (SHIPS) getroffen wurden
        cout<<endl<< "Hit! Continue"; 
        shot(); // nach einem Hit ein weiterer Rateversuch
    }

    else{
        matrix[x][y] = MISS;
        printBorad();
        cout<<endl<< "Miss! It's your opponent's turn";
        //Zum anderen Feld wechseln
    }

    if(matrix[x][y] == HIT){ //Testet, ob Eingabe korrekt ist
        cout<< endl << " Input incorrect. Please try again.";
        shot();
    }

    if(matrix[x][y] == MISS){ //Testet, ob Eingabe korrekt ist
        cout<< endl << " Input incorrect. Please try again.";
        shot();
    }
}

void winner() //Testet, ob alle S(SHIPS) getroffen wurden
{
    int h;
    h = h+1; // Counter für alle Hits eines Spielers

    if(h==16){ //Überprüft ob maximal Anzahl von Hits erreicht wurden, also alle Schiffe vollständig getroffen wurden
        cout<<endl<< "Congratulation, you are the Winner!"<<endl << "GAMEOVER";
        startGame(); // startet nächste Runde
    }
}

void startGame()
{
    cout<<"Start the Game:"; //...
    //Spieler Funktion (pick a player)
    //2 Boards erstellen
    setShips();
    // Feld wechseln
    shot(); // dort wird in der Funktion das Feld gewechselt
}


int main()
{
    startGame();
}