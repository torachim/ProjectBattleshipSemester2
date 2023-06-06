#include <iostream>
#include "../include/game.hpp"
//#include "../include/Spieler.hpp"
#include <memory>



using namespace std;
namespace ProjectAlpha2{

    /**
     * @brief Construct a new Game:: Game object
     * 
     * @param Spieler1_ Teilnehmender Spieler
     * @param Spieler2_ Teilnehmender Gegner
     */
    Game::Game(const Spieler Spieler1_, const Spieler Spieler2_) : Spieler1(Spieler1_), Spieler2(Spieler2_)
    {        
    }

    /**
     * @brief Funktion welche die Regeln von unserem Schiffeversenken druckt
     * 
     */
    void Game::printrules(){
            bool i = false;     //Bool um die regeln im Falle nochmal zu drucken
            while(!i)
            {
                //Block Regeln
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
                    if(a == *"N"){              //eingabe wenn man die Regeln nicht nocchmal sehen will
                        i = true; 
                    }
                }
                else{
                    throw logic_error("Falsche Eingabe bitte starte das Spiel neu!"); //Überprüft das nur J und N eingegeben werden
                }
            }
    }

    /**
     * @brief Funktion in welcher das Spiel abläuft
     * 
     */
    void Game::startgame(){
        cout << "WILLKOMMEN BEI SCHIFFEVERSENKEN" << endl;
        cout << "MÖCHTEST DU: \nEIN SPIEL STARTEN (1) \nDIE REGELN SEHEN (2) \nEINGABE(1/2)" << endl;       //Eingabe ob man die Regeln sehen will oder direkt starten will
        int x;
        cin >> x;
        if (x == 1 || x == 2){
            if (x == 2){
                printrules();                   //Bei entsprechender Eingabe werden die Regeln gedruckt
            }
            cout << "DAS SPIEL STARTET" << endl;                                                //Das Spiel startet
            cout << Spieler1.getName() << " DU BIST DRAN! SETZE DEINE SCHIFFE" << endl;         
            for(int i = 0; i < 4; i++){                                                         //Der erste Spieler setzzt 4 Schiffe
                Spieler1.setShips();
            }
            cout << Spieler2.getName() << " DU BIST DRAN SETZE DEINE SCHIFFE" << endl;
            for(int i = 0; i < 4; i++){                                                         //Der zweite Spieler setzt seine 4 Schiffe
                Spieler2.setShips();
            }
            Spieler2.setEnBoard(Spieler1.getSBoard());                              //Spieler 2 erhällt das gegnerische Brett mit Schiffen als geg_Brett
            Spieler1.setEnBoard(Spieler2.getSBoard());                              //Spieler 1 erhällt das gegnerische Brett mit Schiffen als geg_Brett
            //while Schleife um zu schießen. Abbruch wenn einer der einer der beiden Spieler gewonnen hat
            bool ongoing = true;
            while(ongoing == true){
                cout << Spieler1.getName() << " Du bist dran" << endl;
                Spieler1.shoot();                                               //Spieler 1 schießt
                if(Spieler1.getwinner() == true)
                {                               //Wenn er gewonnen hat wird die Abbruchbedingung gesetzt
                    ongoing = false;
                }
                else
                {

                    cout << Spieler2.getName() << " Du bist dran" << endl;
                    Spieler2.shoot();                                           //Spieler 2 schießt
                    if(Spieler2.getwinner() == true){                           //Wenn er gewonnen hat wird die Abbruchbedingung gesetzt
                        ongoing = false;
                    }        
                }

            }
            endgame();                          //Spiel wird ueber die endgame Funktion beendet
        }
        else{
            throw logic_error("Falsche Eingabe bitte Spiel neu starten!");      //Ausnahme wenn bei der Anfangseingabe weder eine 1 noch eine 2 eingegeben wird
        }
    }

    /**
     * @brief Funktion welche das Spiel beendet und den Sieger kuehrt
     * 
     */
    void Game::endgame(){
        if(Spieler1.getwinner() == true){                                               //Wenn Spieler1 gewonnen hat wird er als Sieger ausgegeben
            cout << Spieler1.getName() << " Glueckwunsch du hast gewonnen" << endl;
        }
        else{                                                                           //Wenn nicht wird Spieler 2 als Sieger ausgegeben
            cout << Spieler2.getName() << " Glueckwunsch du hast gewonnen" << endl;
        }
    }



}