#server
# Run with
#   uvicorn demo_fastapi_2:meine_coole_rest_api --port 8000 --reload
# or, if uvicorn is not in PATH, run as
#   python3 -m uvicorn demo_api:rapi --port 8000  --reload

try:
  import schiffeversenken
except ImportError as e:
  print(f"Importing the shared library 'schiffeversenken' did not work.")
  print(f"Is (a link to) the shared library 'schiffeversenken.____.so' in the same directory as this python script?")
  print(f"The import caused the following exception '{e}'")
  print(f"Exiting")
  exit(1)

from schiffeversenken import board, Spieler, Game
import os
from fastapi import FastAPI
import uvicorn

# Mit diesem Objekt wird der Webservice konfiguriert
rapi = FastAPI()

playerList, playerName = [], []   #Liste fuer Spieler und namen
player1 = None    #Spieler
player2 = None
Sieger = None   #Prueft ob einer schon gewonnen hat
Schiffzaehler1, Schiffzaehler2  = 0, 0    #Zaehler fuer die gesetzten Schiffe
counter = 0         #Zahelt wer dran ist 0 Spieler1 1 Spieler2
game = False        #Gibt an ob ein Game bereits läuft
b1S, b1L, b2S, b2L = board(), board(), board(), board() #Bretter jeweils 2 füer Schiffe und 2 für Schüsse

#Gibt Willkommen Nachricht us
@rapi.get("/")
async def Hauptnachricht():
  txtNachricht = f'Willkommen bei Schiffeversenken.\nIn diesem Spiel befinden sich aktuell {len(playerName)} Spieler.'
  return {"information": txtNachricht}

#Spieler hinzufuegen
@rapi.get("/addPlayer/{userName}")
async def Spielerhinzufuegen(userName : str):
  global player1, player2, game, playerName, playerList, b1S, b1L, b2S, b2L
  if(userName not in playerName and len(playerName) <= 1):
    if (not game): #falls Spiel noch nicht begonnen
      playerName.append(userName)
    else:
      return{"information": 'Spiel hat schon gestartet',
             "status": False}
    
  if (len(playerName) == 2):
    player1 = Spieler(b1S, b1L, playerName[0]) #Zuordung Brett zu Player
    player2 = Spieler(b2S, b2L, playerName[1])
    playerList.append(player1)
    playerList.append(player2)
    return {"information": 'Spiel startet',
            "Status": True} #Beide Spieler haben Namen eingegeben
  else:
    return {"information": 'Warte auf andere Spieler...',
            "Status": False}


#Prueft welcher Spieler mit setzen der Schiffe dran ist 
@rapi.get("/Spiel/Setzen/{userName}")
async def Setzen(userName : str):
  global counter, playerName
  txt = userName, 'Setze deine Schiffe'
  if (userName == playerName[0] and counter == 0):
    return {"information" : txt, #setzte schiffe
            "Status": True}
  elif (userName == playerName[1] and counter == 1):
    return {"information" : txt,
            "Status": True}
  else:
    return {"information": 'Der Gegner sitzt gerade seine Schiffe. Bitte warten',
            "Status": False} # falls man nicht dran ist


#Setzt die Schiffe auf das entsprechende Brett b1S fuer Spieler 1 und b2S fuer Spieler 2
@rapi.get("/Spiel/Schiffesetzen/{x_Koordinate}/{y_Koordinate}/{Richtung}")
async def set_Schiff(x_Koordinate : int, y_Koordinate : int, Richtung : int):
  global counter, playerList, Schiffzaehler1, Schiffzaehler2, player1, player2, b1L, b1S, b2L, b2S, game
  if (counter == 0): # welche person dran ist
    if(Richtung == 1): #horizontales schiff
      i = 0
      while (i < 4): # schiffe länge 4 werden gestetzt
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b1S.Schiffsetzen(x, y) # Funktion die das Schiff setzt
        x_Koordinate = x_Koordinate + 1
        i = i +1
    elif(Richtung == 0): # vertikales Schiff
      i = 0
      while(i < 4):
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b1S.Schiffsetzen(x, y)
        y_Koordinate = y_Koordinate + 1
        i = i + 1
    Schiffzaehler1 = Schiffzaehler1 + 1 # counter für schiffe
    if (Schiffzaehler1 == 4):
      if(Schiffzaehler2 == 4):
        game == True # beginn spieles
      counter = 1
    return {"information" : 'Schiff gesetzt',
            "Status" : True}
  elif(counter == 1): # selbes prinzip für anderen Spieler
    if(Richtung == 1):
      i = 0
      while (i < 4):
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b2S.Schiffsetzen(x, y)
        x_Koordinate = x_Koordinate + 1
        i = i +1
    elif(Richtung == 0):
      i = 0
      while(i < 4):
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b2S.Schiffsetzen(x, y)
        y_Koordinate = y_Koordinate + 1
        i = i + 1
    Schiffzaehler2 = Schiffzaehler2 + 1
    if (Schiffzaehler2 == 4):
      if (Schiffzaehler1 == 4):
        game = True
      counter = 0
    return {"information": 'Schiff gesetzt',
            "Status" : True}


#Kontrolliert ob an der Stelle an der ein Schiff gesetzt werden soll nicht schon eins liegt
@rapi.get("/Spiel/Schiffkontrolle/{x_Koordinate}/{y_Koordinate}/{Richtung}")
async def SchipControl(x_Koordinate : int, y_Koordinate : int, Richtung : int):
  global playerList, counter, player1, player2, b1L, b1S, b2L, b2S
  x = x_Koordinate - 1
  y = y_Koordinate - 1
  if(counter == 0):
    if(b1S.can_set_ship(x, y, Richtung) == True): # aufrufen can set ship funktion
      return {"Status" : True}
    elif(b1S.can_set_ship(x, y, Richtung) == False):
      return {"Status" : False}
  elif(counter == 1):
    if(b2S.can_set_ship(x, y, Richtung) == True):
      return {"Status" : True}
    elif(b2S.can_set_ship(x, y, Richtung) == False):
      return {"Status" : False}


#Prueft welcher Spieler mit schießen dran ist
@rapi.get("/Spiel/Schießen/{userName}")
async def WerIstdran(userName : str): #kontrolliert wer dran ist
  global counter, playerName
  txt = userName, 'Du bist dran! Wage einen Schuss'
  if (userName == playerName[0] and counter == 0):
    return {"information" : txt, # falls player1 dran ist
            "Status" : True} 
  elif (userName == playerName[1] and counter == 1):
    return {"information" : txt, #falls player2 dran ist
            "Status" : True}
  else:
    return {"information" : 'Der Gegner ist gerade dran. Bitte warte auf deinen Zug',
            "Status" : False}


#Prueft ob ein Spieler bereits gewonnen hat
@rapi.get("/Spiel/KontrolleWinner/{userName}")
async def Gewonnen(userName : str):
  global playerName, player1, player2, b1L, b2L, game, Sieger
  if(userName == playerName[0]):
    if(not b1L.winner()): # guckt ob es eienen Gewinner gibt, gewonnen wurde
      game = False # gibt Zustand des Spieles zurück, beendung des Spieles
      Sieger = playerName[0]
      return {"Status" : True}
    else:
      return {"Status" : False}
  else:
    if(not b2L.winner()):
      game = False
      Sieger = playerName[1]
      return {"Status" : True}
    else:
      return{"Status" : False}


#Startet den Ablauf das geschossen werden kann
@rapi.get("/Spiel/starten")
async def Starten(): #Start des Spieles
  global game
  if(game == True):
    return {"information" : 'Gleich geht es los',
            "Status" : True}
  else:
    return {"information" : 'Bitte Warten',
            "Status" : False}
  

#Schießt auf das Gegner Brett und prueft ob ein Schiff getroffen wurde
@rapi.get("/Spiel/shoot/{x_Koordinate}/{y_Koordinate}")
async def Schießen(x_Koordinate : int, y_Koordinate : int): #Eingabe Koordinaten = schuss Koordinate
  global playerList, playerName, b1L, b1S, b2L, b2S, counter
  x = x_Koordinate - 1 # index anpassung
  y = y_Koordinate - 1
  if(counter == 0): # guckt wer dran ist
    if(b2S.is_hit(x, y)): # funk due guckt , ob es ein Hit gab
      b1L.SetzeH(x, y) # makierung hit 
      return {"information" : 'Treffer gelandet!',
              "Status" : True}
    else:
      b1L.setzeM(x, y) # makierung miss
      counter = 1
      return {"information" : 'Kein Treffer! Der Gegner ist dran',
              "Status" : False}
  elif(counter == 1): # anderer Spieler selbes Prinzip
    if(b1S.is_hit(x, y)):
      b2L.SetzeH(x, y)
      return {"information" : 'Treffer gelandet!',
              "Status" : True}
    else:
      b2L.setzeM(x, y)
      counter = 0
      return {"information" : 'Kein Treffer! Der Gegner ist dran',
              "Status" : False}


#Gibt die Variable game zurueck
@rapi.get("/Spiel/getGame")
async def getGame(): # kontrolliert ob Spiele begonnen hat , beendet wurde
  global game
  if(game == True):
    return {"Status" : True}
  else:
    return {"Status" : False}

#Gibt zurueck ob jemand das Spiel gewonnen hat   
@rapi.get("/Spiel/End/{userName}")
async def endgame(userName : str):
  global Sieger, playerName
  txts = 'Glückwunsch', userName, 'Du hast Gewonnen. Schön gespielt' # Ausgabe für sieger
  txtv = 'Schade', userName, 'Du hast leider Verloren. Versuch es doch mit einer Revanche' # Ausgabe für verlierer
  if(userName == Sieger):
    return {"information" : txts,
            "Status": True}
  else:
    return {"information" : txtv,
            "Status" : False}

#Prueft ob den Punkt auf den geschossen werden sollte nicht schon geschossen wurde  
@rapi.get("/Spiel/Schussmoeglich/{x_Koordinate}/{y_Koordinate}")
async def Schusstest(x_Koordinate : int, y_Koordinate : int):
  global counter, b1L, b1S, b2L, b2S
  x = x_Koordinate - 1
  y = y_Koordinate - 1
  txt = "Schuss nicht möglich, da auf diese Koordinate bereits geschossen wurde"
  if(counter == 0):
    if(b1L.pruefe(x, y)): # funk die überprüft, wo schon geschossen wurde
      return {"Status" : True}
    else:
      return {"information" : txt, 
              "Status" : False}
  else:
    if(b2L.pruefe(x, y)):
      return {"Status" : True}
    else:
      return {"information" : txt ,
              "Status" : False}
  


if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:rapi", host="127.0.0.1", port=8000, log_level="info", reload=True)
