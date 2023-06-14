#client
# Start demo_api in background first
import time
import requests
from schiffeversenken import board
from schiffeversenken import Spieler
from schiffeversenken import Game
from pprint import pprint # Bei größeren Dicts sollte man pprint(...) statt print(...) verwenden

base_api_url = "http://127.0.0.1:8000"

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
    y_Koordinate = input()
    while True:
      try:
        while int(y_Koordinate) < 1 or int(y_Koordinate) > 10:
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

    if (kontrolleSchiffe(x_Koordinate, y_Koordinate, Richtung) == True):
      response = requests.get(f"{base_api_url}/Spiel/Schiffkontrolle/{x_Koordinate}/{y_Koordinate}/{Richtung}").json()
      if(response["Status"]):
        response = requests.get(f"{base_api_url}/Spiel/Schiffesetzen/{x_Koordinate}/{y_Koordinate}/{Richtung}").json()
        pprint(response["information"])
      else:
        print("Schiff setzen nicht möglich! Bitte erneut versuchen")
        eingabeSchiffe()

    else:
      print("Schiff setzen nicht möglich bitte versuche es erneut")
      eingabeSchiffe() 
  
def eingabeSchuss():
  print("Bitte gebe einen Schuss an!")
  print("Bitte gebe eine X-Koordinate für den Schuss an [1-10]")
  x_Koordinate = input()
  while True:
    try:
      while (int(x_Koordinate) < 1 or int(x_Koordinate) > 10):
        print("Fehlerhafte Eingabe bitte erneut versuchen!")
        x_Koordinate = input()
        break
    except:
      x_Koordinate = input("Es wurde keine Zahl übergebn. Bitte gebe eine Zahl [1-10] ein")

    print("Bitte gebe eine y_Koordinate für deinen Schuss an [1-10]")
    y_Koordinate = input()
    while True:
      try:
        while (int(y_Koordinate) < 1 or int(y_Koordinate) > 10):
          print("Fehlerhaft Eingabe bitte erneut Versuchen!")
          y_Koordinate = input()
          break
      except:
        y_Koordinate = input("Es wurde keine Zahl übergeben. Bitte gebe eine Zahl [1-10] ein")
          

    





           

def main():
  base_api_url = "http://127.0.0.1:8000"
  
  response = requests.get(base_api_url).json()
  pprint(response["information"])

  username = input("Bitte gebe deinen Namen ein:")
  response = requests.get(f"{base_api_url}/addPlayer/{username}").json()

  
  while(not response["Status"]):
    pprint(response["information"])
    response = requests.get(f"{base_api_url}/addPlayer/{username}").json()
    time.sleep(5.0)
  pprint(response["information"])
  time.sleep(5.0)

  t = False
  while(not t):
    response = requests.get(f"{base_api_url}/Spiel/Setzen/{username}").json()
    if(response["Status"] == True):
      pprint(response["information"])
      i = 0
      while (i < 4):
        eingabeSchiffe()
        i = i + 1
      t = True
    else:
      pprint(response["information"])
    time.sleep(5.0)


    


  #response = requests.get(f"{base_api_url}/Spiel/Spieler/{username}").json()
  #pprint(response["information"])


  

if __name__ == '__main__':
  main()

