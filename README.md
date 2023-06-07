# Projekt2

## Schiffe verseneken

Wir planen eine Implementierung des Spieles Schiffe versenken. Hierbei spielen jeweils 
zwei Spieler gegeneinander. Diese legen auf ihr Feld zuerst die Lage ihrer Schiffe fest ehe sie versuchen die Schiffe des anderen zu zerstören.
Wer als erstes alle Schiffe seines Gegners zerstört hat gewinnt.


## Checkliste

- [ ] Zeitplan anlgen
- [ ] UML Diagramm anlegen
- [ ] hpp zu den entsprechenden Klassen schreiben
- [ ] Implementierung der entsprechenden Klassen schreiben
- [ ] Main Datei zur ausfuehrung des Spiels schreiben
- [ ] Serverkommunikation schreiben


## UML battleship

![Employee data](https://gitlab.cs.uni-bonn.de/raut0/projekt2torgesnehpreet/-/blob/main/UML/UML%20Schiffe%20versenken.png)

/projekt2torgesnehpreet/UML/UML battleship.png

## Regeln

Jeder Spieler setzt zu Beginn je 4 Schiffe mit einer Groeße von je 4 Bloecken auf ein Feld welches durch eine 10x10 Matrix dargestellt wird. Die Schiffe werden gesetzt in dem man die Anfangskoordinaten angibt (jeweils in x und y von 1-10) und die Richtung in welche das Schiff gerichtet sein soll (mit 1 und 0 für Horizontal und Vertikal). Nachdem alle Schiffe gesetzt wurden versuchen die Spieler jeweils alle Schiffe des anderen zu zerstoeren. Dazu gibt man die Koordinaten an wo man ein Teil eines Schiffes vermutet. Landet man einen Treffer so wird das auf der Karte mit einem H gekennzeichnet (M bei einem Miss) und man darf nochmal raten. Trifft man nicht ist der Gegner dran. Hinweise dafuer dass ein Schiff komplett zerstoert wurde existieren nicht. Wer als erstes alle Schiffe des Gegners zerstoert hat beendet das Spiel und gewinnt. 

## Implementierung

Implementiert wird das Spiel ueber jeweil zwei 10x10 Matrizen pro Spieler. Auf einer sieht man seine eigenen Schiffe und den Status der Schuess des Gegners und auf der anderen sieht man erstmal nur leere Felder und dann immer den Status seiner eigenen abgegebenen Schiffe. 
Implementiert wird das Spiel über 3 Klassen:
- [ ] board Spielbretter:
    - [ ] printboard(): Druckt das entsprechende Spielbrett
    - [ ] canSetShip(int r, int c, bool isHorizontal): Prueft ob das gegebene Schiff gestzt werden kann
    - [ ] isHit(int r, int c): Prueft ob ein eingegangener Schuss ein Treffer auf diesem Brett ist
    - [ ] winner(): Prueft ob bereits 16 Hits gesetzt wurden
    - [ ] Schiffesetzen(int r, int c): Setzt ein S fuer Schiff auf einem Brett
    - [ ] SetH(int r, int c): Setzt ein H fuer Hit auf ein Brett
    - [ ] SetM(int r, int c): Setzt ein M fuer Miss auf ein Brett
    - [ ] SetD(int r, int c): Setzt ein X fuer Destroyed auf ein Brett
    - [ ] SetO(int r, int c): Setzt ein O fuer NoHit auf ein Brett

- [ ] Spieler:
    - [ ] Konstruktor(BrettS, BrettL, Name): Ein Spieler erhällt 2 Bretter eins fuer Schiffe eins fuer Hits und einen Namen
    - [ ] shoot(): Funktion um einen Schuss auf den Gegner zu setzen
    - [ ] setShips(): Funktion um eins seiner Schiffe auf sein Brett zu setzen
    - [ ] getName(): Gibt den Namen des entsprechenden Spieler zurueck
    - [ ] setEnboard(Board): Erzeugt einen Pointer auf das gegnerische Schiffbrett
    - [ ] getSBoard(): Gibt das Brett eines Spielers mit seinen Schiffen zurueck
    - [ ] getLBoard(): Gibt das Brett eines Spielers mit den Hits und Misses zurueck
    - [ ] winnercontrol(): Kontrolliert ob der entsprechende Spieler bereits gewonnen hat
    - [ ] getwinner(): Gibt das Bool winner zurueck was anzeigt ob der Spieler schon gewonnen hat

- [ ] game Hier findet das gesammte Spiel statt:
    - [ ] Konstruktor(Spieler1, Spieler2): Erzeugt ein Spiel aus zwei Spielern
    - [ ] printRules(): Druckt die Regeln des Spieles aus
    - [ ] startgame(): In dieser Funktion findet das gesammte Spiel statt erst setzt jeder seine Schiffe und dann wird abwechselnd geschossen bis einer gewonnen hat
    - [ ] endgame(): Beendet das Spiel und ruft den Sieger aus

## Tests
