#server
# Run with
#   uvicorn demo_fastapi_2:meine_coole_rest_api --port 8000 --reload
# or, if uvicorn is not in PATH, run as
#   python3 -m uvicorn demo_api:rapi --port 8000  --reload
# 


# Import magic
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

playerList, playerName = [], [] 
player1 = None
player2 = None
Schiffzaehler1, Schiffzaehler2  = 0, 0
counter = 0
game = False
b1S, b1L, b2S, b2L = board(), board(), board(), board()

@rapi.get("/")
async def Hauptnachricht():
  txtNachricht = f"Willkommen bei Schiffeversenken.\n In diesem Spiel befinden sich aktuell {len(playerName)} Spieler."
  return {"information": txtNachricht}

#Spieler hinzufuegen
@rapi.get("/addPlayer/{userName}")
async def Spielerhinzufuegen(userName : str):
  global player1, player2, game, playerName, playerList, b1S, b1L, b2S, b2L
  if(userName not in playerName and len(playerName) <= 1):
    if (not game):
      playerName.append(userName)
    else:
      return{"information": "Spiel hat schon gestartet",
             "status": False}
    
  if (len(playerName) == 2):
    player1 = Spieler(b1S, b1L, playerName[0])
    player2 = Spieler(b2S, b2L, playerName[1])
    playerList.append(player1)
    playerList.append(player2)
    return {"information": "Spiel startet",
            "Status": True}
  else:
    return {"information": "Warte auf andere Spieler...",
            "Status": False}
  
@rapi.get("/Spiel/Setzen/{userName}")
async def Setzen(userName : str):
  global counter, playerName
  txt = userName, "setze deine Schiffe"
  if (userName == playerName[0] and counter == 0):
    return {"information" : txt,
            "Status": True}
  elif (userName == playerName[1] and counter == 1):
    return {"information" : txt,
            "Status": True}
  else:
    return {"information": "Der Gegner sitzt gerade seine Schiffe. Bitte warten",
            "Status": False}

@rapi.get("/Spiel/Schiffesetzen/{x_Koordinate}/{y_Koordinate}/{Richtung}")
async def set_Schiff(x_Koordinate : int, y_Koordinate : int, Richtung : int):
  global counter, playerList, Schiffzaehler1, Schiffzaehler2, player1, player2, b1L, b1S, b2L, b2S, game
  if (counter == 0):
    if(Richtung == 1):
      i = 0
      while (i < 4):
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b1S.Schiffsetzen(x, y)
        x_Koordinate = x_Koordinate + 1
        i = i +1
    elif(Richtung == 0):
      i = 0
      while(i < 4):
        x = x_Koordinate - 1
        y = y_Koordinate - 1
        b1S.Schiffsetzen(x, y)
        y_Koordinate = y_Koordinate + 1
        i = i + 1
    Schiffzaehler1 = Schiffzaehler1 + 1
    if (Schiffzaehler1 == 4):
      if(Schiffzaehler2 == 4):
        game == True
      counter = 1
    return {"information" : "Schiff gesetzt",
            "Status" : True}
  elif(counter == 1):
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
    return {"information": "Schiff gesetzt",
            "Status" : True}
  
@rapi.get("/Spiel/Schiffkontrolle/{x_Koordinate}/{y_Koordinate}/{Richtung}")
async def SchipControl(x_Koordinate : int, y_Koordinate : int, Richtung : int):
  global playerList, counter, player1, player2, b1L, b1S, b2L, b2S
  print("In der Funktion")
  x = x_Koordinate - 1
  y = y_Koordinate - 1
  if(counter == 0):
    if(b1S.can_set_ship(x, y, Richtung) == True):
      print("In True")
      return {"Status" : True}
    elif(b1S.can_set_ship(x, y, Richtung) == False):
      print("In False")
      return {"Status" : False}
  elif(counter == 1):
    if(b2S.can_set_ship(x, y, Richtung) == True):
      return {"Status" : True}
    elif(b2S.can_set_ship(x, y, Richtung) == False):
      return {"Status" : False}
    
@rapi.get("/Spiel/Schießen/{userName}")
async def WerIstdran(userName : str):
  global counter, playerName
  txt = userName, "Du bist dran! Wage einen Schuss"
  if (userName == playerName[0] and counter == 0):
    return {"information" : txt,
            "Status" : True}
  elif (userName == playerName[1] and counter == 1):
    return {"information" : txt,
            "Status" : True}
  else:
    return {"information" : "Der Gegner ist gerade dran. Bitte warte auf deinen Zug",
            "Status" : False}
  
@rapi.get("/Spiel/KontrolleWinner/{userName}")
async def Gewonnen(userName : str):
  global playerName, player1, player2, b1L, b2L, game
  if(userName == playerName[0]):
    if(not b1L.winner()):
      game = False
      return {"Status" : True}
    else:
      return {"Status" : False}
  else:
    if(not b2L.winner()):
      game = False
      return {"Status" : True}
    else:
      return{"Status" : False}


@rapi.get("/Spiel/starten")
async def Starten():
  global game
  if(game == True):
    return {"information" : "Gleich geht es los",
            "Status" : True}
  else:
    return {"information" : "Bitte Warten",
            "Status" : False}
  


@rapi.get("/Spiel/shoot/{x_Koordinate}/{y_Koordinate}")
async def Schießen(x_Koordinate : int, y_Koordinate : int):
  global playerList, playerName, b1L, b1S, b2L, b2S, counter
  x = x_Koordinate - 1
  y = y_Koordinate - 1
  if(counter == 0):
    if(b2S.is_hit(x, y)):
      b1L.SetzeH(x, y)
      return {"information" : "Treffer gelandet!",
              "Status" : True}
    else:
      b1L.setzeM(x, y)
      counter = 1
      return {"information" : "Kein Treffer! Der Gegner ist dran",
              "Status" : False}
  elif(counter == 1):
    if(b1S.is_hit(x, y)):
      b2L.SetzeH(x, y)
      return {"information" : "Treffer gelandet!",
              "Status" : True}
    else:
      b2L.setzeM(x, y)
      counter = 0
      return {"information" : "Kein Treffer! Der Gegner ist dran",
              "Status" : False}
    
@rapi.get("/Spiel/getGame")
async def getGame():
  global game
  if(game == True):
    return {"Status" : True}
  else:
    return {"Status" : False}




  



if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:rapi", host="127.0.0.1", port=8000, log_level="info", reload=True)
