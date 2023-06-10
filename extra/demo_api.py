#server
# Run with
#   uvicorn demo_fastapi_2:meine_coole_rest_api --port 8000 --reload
# or, if uvicorn is not in PATH, run as
#   python3 -m uvicorn demo_fastapi_2:meine_coole_rest_api --port 8000  --reload

# Import magic
try:
  import schiffeversenken
except ImportError as e:
  print(f"Importing the shared library 'schiffeversenken' did not work.")
  print(f"Is (a link to) the shared library 'schiffeversenken.____.so' in the same directory as this python script?")
  print(f"The import caused the following exception '{e}'")
  print(f"Exiting")
  exit(1)

from schiffeversenken import board
from schiffeversenken import Spieler
from schiffeversenken import Game
import os
from fastapi import FastAPI
import uvicorn

# Mit diesem Objekt wird der Webservice konfiguriert
meine_coole_rest_api = FastAPI()

# Füge den Pfad '/' hinzu
# Wenn dieser Pfad ausgewählt wird, soll die darunter stehende Funktion ausgeführt werden
# Die Rückgabe der Funktion wird den Nutzer:innen (typischerweise als) JSON-Objekt übertragen
@meine_coole_rest_api.get("/")
async def run_game():
    return 
    {
      "Game" : run_game()
    }


if __name__ == '__main__':
  this_python_file = os.path.basename(__file__)[:-3]
  instance = uvicorn.run(f"{this_python_file}:meine_coole_rest_api", host="127.0.0.1", port=8000, log_level="info", reload=True)
