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

/projekt2torgesnehpreet/UML/UML battleship.png

## Regeln

Jeder Spieler setzt zu Beginn je 4 Schiffe mit einer Groeße von je 4 Bloecken auf ein Feld welches durch eine 10x10 Matrix dargestellt wird. Die Schiffe werden gesetzt in dem man die Anfangskoordinaten angibt (jeweils in x und y von 1-10) und die Richtung in welche das Schiff gerichtet sein soll (mit 1 und 0 für Horizontal und Vertikal). Nachdem alle Schiffe gesetzt wurden versuchen die Spieler jeweils alle Schiffe des anderen zu zerstoeren. Dazu gibt man die Koordinaten an wo man ein Teil eines Schiffes vermutet. Landet man einen Treffer so wird das auf der Karte mit einem H gekennzeichnet (M bei einem Miss) und man darf nochmal raten. Trifft man nicht ist der Gegner dran. Hinweise dafuer dass ein Schiff komplett zerstoert wurde existieren nicht. Wer als erstes alle Schiffe des Gegners zerstoert hat beendet das Spiel und gewinnt. 

## Implementierung

Implementiert wird das Spiel ueber jeweil zwei 10x10 Matrizen pro Spieler. Auf einer sieht man seine eigenen Schiffe und den Status der Schuess des Gegners und auf der anderen sieht man erstmal nur leere Felder und dann immer den Status seiner eigenen abgegebenen Schiffe. 
Funktionen:
- [ ] printBoardS -> Druckt das Board auf welchem seine eigenen Schiffe markiert sind
- [ ] printBoardG -> Druckt das Board mit dem Status seiner Schuesse
- [ ] printBoard -> Druckt jeweils die beiden oben beschriebenen Bretter
- [ ] setShips -> Funktion mit welcher die Schiffe gesetzt werden
- [ ] canSetShip -> Funktion die prueft ob das gewählte Schiff ueberhaupt gesetzt werden kann also nicht aus dem Brett ragen wuerde o.ä.
- [ ] shot -> Funktion mit welcher auf Koordinaten auf dem gegnerischen Brett geschossen werden kann
- [ ] isHit -> Prueft ob der Schuss erlaupt ist also ob der Schuss nicht auf ein bereits geschossenes Feld geht und ob er ein Treffer war
- [ ] winner -> Prueft ob man nach einem Treffer schon gewonnen hat oder ob man nochmal schießen darf
- [ ] printRules -> Druckt auf Wunsch die Regeln des Spiels

