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
counter = 0
game = False
b1S, b1L, b2S, b2L = board(), board(), board(), board()

@rapi.get("/")
async def Hauptnachricht():
  txtNachricht = f"Willkommen bei Schiffeversenken.\n In diesem Spiel befinden sich aktuell {len(playerList)} Spieler."
  return {"information": txtNachricht}

#Spieler hinzufuegen
@rapi.get("/addPlayer/{userName}")
async def Spielerhinzufuegen(userName : str):
  global player1, player2, game, playerName, playerList
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
    return {"information": "Spiel kann gestartet werden",
            "Status": True}
  else:
    return {"information": "Warte auf andere Spieler...",
            "Status": False}

@rapi.get("/Spiel/Spieler/{userName}")
async def Erhalte_Spieler(userName : str):
  global playerList, playerName
  if (userName == playerName[0]):
    t = player1.Erhalte_Schiffe_Brett()
    return{"information": t,
           "Status": True}
  else:
    k = player2.Erhalte_Schiffe_Brett()
    return{"information": k,
           "Status": True}



if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:rapi", host="127.0.0.1", port=8000, log_level="info", reload=True)
