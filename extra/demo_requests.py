#client
# Start demo_api in background first

import requests
from schiffeversenken import board
from schiffeversenken import Spieler
from schiffeversenken import game
from pprint import pprint # Bei größeren Dicts sollte man pprint(...) statt print(...) verwenden

bs = board()
bl = board()

def kontrolleSchiffe(x_Koordinate, y_Koordinate, Richtung):
  if int(Richtung) == 0:
    if int(y_Koordinate) + 4 <= 10:
      return True
    else:
      return False
  else:
    if int(x_Koordinate) +4 <= 10:
      return True
    else:
      return False

def eingabeSchiffe():
    print("Bitte gebe die x-Koordinate deines Schiffes an [1-10]")
    x_Koordinate = input()
    while True:
      try:
        while int(x_Koordinate) < 1 or int(x_Koordinate) > 10:
          print("Fehlerhafte Eingabe! Bitte eine Zahl zwischen 1 und 10 eingeben")
          x_Koordinate = input()
        break
      except:
        x_Koordinate = input("Es wurde keine Zahl übergeben. Gebe eine Zahl zwischen 1 und 10 ein \n")

    print("Bitte gebe die y-Koordinate deines Schiffes an [1-10]")
    y_Kooridinate = input()
    while True:
      try:
        while int(y_Kooridinate) < 1 or int(y_Kooridinate) > 10:
          print("Fehlerhafte Eingabe! Bitte eine Zahl zwischen 1 und 10 eingeben")
          y_Koordinate = input()
        break
      except:
        y_Koordinate = input("Es wurde keine Zahl übergeben. Gebe eine Zahl zwischen 1 und 10 ein \n")

    print("Bitte Gebe die Richtung des Schiffes 0[Vertikal] 1[Horrizontal]")
    Richtung = input()
    while True:
      try:
        while int(Richtung) < 0 or int(Richtung) > 1:
          print("Falsche Eingabe bitte 0[Vertikal] oder 1[Horrizontal] eingeben")
          Richtung = input()
        break
      except:
        Richtung = input("Es wurde keine Zahl übergebn. Gebe 0[Vertikal], 1[Horrizontal]")

    if kontrolleSchiffe(x_Koordinate, y_Koordinate, Richtung) == True:
      x = 0
      while x < 4:
        if Richtung == 0:
          bs.Schiffsetzen(int(x_Koordinate), int(y_Koordinate))
          x_Koordinate = x_Koordinate + 1
          x = x + 1
        else:
          bs.Schiffsetzen(int(x_Koordinate), int(y_Koordinate))
          y_Koordinate = y_Koordinate + 1
          x = x +1
    else:
      print("Schiff setzen nicht möglich bitte versuche es erneut")
      eingabeSchiffe() 





           

def main():
  base_api_url = "http://127.0.0.1:8000"
  
  response = requests.get(base_api_url).json()
  pprint(response["information"])
  

if __name__ == '__main__':
  main()

