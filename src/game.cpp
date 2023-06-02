#include <iostream>
#include "../include/game.hpp"
#include <memory>



using namespace std;
namespace ProjectAlpha2{

    Game::Game(const Spieler Spieler1_, const Spieler Spieler2_) : Spieler1(Spieler1_), Spieler2(Spieler2_)
    {        
    }

    void Game::printrules(){
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

    void Game::startgame(){
        cout << "WILLKOMMEN BEI SCHIFFEVERSENKEN" << endl;
        cout << "MÖCHTEST DU: \nEIN SPIEL STARTEN (1) \nDIE REGELN SEHEN (2) \nEINGABE(1/2)" << endl;
        int x;
        cin >> x;
        if (x == 1 || x == 2){
            if (x == 2){
                printrules();
            }
            cout << "DAS SPIEL STARTET" << endl;
            cout << Spieler1.getName() << " DU BIST DRAN! SETZE DEINE SCHIFFE" << endl;
            for(int i = 0; i < 4; i++){
                Spieler1.setShips();
            }
            cout << Spieler2.getName() << " DU BIST DRAN SETZE DEINE SCHIFFE" << endl;
            for(int i = 0; i < 4; i++){
                Spieler2.setShips();
            }
            Spieler2.setEnBoard(Spieler1.getSBoard());
            Spieler1.setEnBoard(Spieler2.getSBoard());
            //while Schleife um zu schießen. Plan ist eine Kontrolle einzubauen ob einer der Spieler bereits gewonnen hat
            bool ongoing = true;
            while(ongoing == true){
                cout << Spieler1.getName() << " Du bist dran" << endl;
                Spieler1.shoot();
                if(Spieler1.getwinner() == true){
                    ongoing = false;
                }
                else{
                    cout << Spieler2.getName() << " Du bist dran" << endl;
                    Spieler2.shoot();
                    if(Spieler2.getwinner() == true){
                        ongoing = false;
                    }        
                }

            }
            endgame();
        }
        else{
            throw logic_error("Falsche Eingabe bitte Spiel neu starten!");
        }
    }

    void Game::endgame(){
        if(Spieler1.getwinner() == true){
            cout << Spieler1.getName() << " Glueckwunsch du hast gewonnen" << endl;
        }
        else{
            cout << Spieler2.getName() << " Glueckwunsch du hast gewonnen" << endl;
        }
    }



}