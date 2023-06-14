#client
# Start demo_api in background first
import time
import requests
from schiffeversenken import board
from schiffeversenken import Spieler
from schiffeversenken import Game
from pprint import pprint # Bei größeren Dicts sollte man pprint(...) statt print(...) verwenden

base_api_url = "http://127.0.0.1:8000"
bS, bL = board(), board()   #Lokale Bretter

#Funktion um die Lokalen Bretter zu belegn
def Hilfebrett(x : int, y : int, Richtung : int):
  k = Richtung
  if int(k) == 0:
    i = 0
    while (i < 4):
      xi = int(x) - 1
      yi = int(y) - 1
      bS.Schiffsetzen(xi, yi)
      y = int(y) + 1
      i = i + 1
  elif int(k) == 1:
    i = 0
    while (i < 4):
      xi = int(x) - 1
      yi = int(y) - 1
      bS.Schiffsetzen(xi, yi)
      x = int(x) + 1
      i = int(i) + 1


#Funktion welche Konntrolliert ob eingegebene Schiffe nicht über das Brett hinausragen
def kontrolleSchiffe(x_Koordinate, y_Koordinate, Richtung):
  if int(Richtung) == 0: #wenn Gesetztes horizontal ist
    if int(y_Koordinate) + 4 <= 10: #kontrolliert ob gesetztes Schiff nicht über Brett hinausläuft
      return True
    else:
      return False
  else:
    if int(x_Koordinate) +4 <= 10:
      return True
    else:
      return False

#Funktion welche das Setzen von Schiffen über Konsolen Eingaben ermöglicht
def eingabeSchiffe():
    print("Bitte gebe die x-Koordinate deines Schiffes an [1-10]")
    x_Koordinate = input()      #Eingabe x Koordinate
    while True:
      try:                      #Ausnahmen    
        while int(x_Koordinate) < 1 or int(x_Koordinate) > 10:
          print("Fehlerhafte Eingabe! Bitte eine Zahl zwischen 1 und 10 eingeben")
          x_Koordinate = input() #erneute Abfrage
        break
      except:
        x_Koordinate = input("Es wurde keine Zahl übergeben. Gebe eine Zahl zwischen 1 und 10 ein \n")

    print("Bitte gebe die y-Koordinate deines Schiffes an [1-10]")
    y_Koordinate = input()      #Eingaben y Koordinate
    while True:
      try:                      #Ausnahmen
        while int(y_Koordinate) < 1 or int(y_Koordinate) > 10:
          print("Fehlerhafte Eingabe! Bitte eine Zahl zwischen 1 und 10 eingeben")
          y_Koordinate = input()
        break
      except:
        y_Koordinate = input("Es wurde keine Zahl übergeben. Gebe eine Zahl zwischen 1 und 10 ein \n")

    print("Bitte Gebe die Richtung des Schiffes 0[Vertikal] 1[Horrizontal]")
    Richtung = input()        #Eingabe Richtung
    while True:
      try:                    #Ausnahmen
        while int(Richtung) < 0 or int(Richtung) > 1:
          print("Falsche Eingabe bitte 0[Vertikal] oder 1[Horrizontal] eingeben")
          Richtung = input()
        break
      except:
        Richtung = input("Es wurde keine Zahl übergebn. Gebe 0[Vertikal], 1[Horrizontal]")

    if (kontrolleSchiffe(x_Koordinate, y_Koordinate, Richtung) == True):
      response = requests.get(f"{base_api_url}/Spiel/Schiffkontrolle/{x_Koordinate}/{y_Koordinate}/{Richtung}").json()  #Kontrolle ob an der selben Stelle nicht bereits ein anderes Schiff liegt
      if(response["Status"]):
        Hilfebrett(x_Koordinate, y_Koordinate, Richtung)
        response = requests.get(f"{base_api_url}/Spiel/Schiffesetzen/{x_Koordinate}/{y_Koordinate}/{Richtung}").json()  #Setzen des Schiffes auf den Server
        print(response["information"])

      else:
        print("Schiff setzen nicht möglich! Bitte erneut versuchen")
        eingabeSchiffe()

    else:
      print("Schiff setzen nicht möglich! Bitte versuche es erneut")
      eingabeSchiffe() 

  
#Funktion welche einen Schuss über Konsolen Eingabe ermöglicht  
def eingabeSchuss():
    print("Bitte gebe einen Schuss an!")
    print("Bitte gebe eine X-Koordinate für den Schuss an [1-10]")
    x_Koordinate = input()    #Eingabe x Koordinate
    while True:
      try:                    #Ausnahme   
        while int(x_Koordinate) < 1 or int(x_Koordinate) > 10:
          print("Fehlerhafte Eingabe bitte erneut versuchen!")
          x_Koordinate = input()
        break
      except:
        x_Koordinate = input("Es wurde keine Zahl übergebn. Bitte gebe eine Zahl [1-10] ein")
    print("Bitte gebe eine y_Koordinate für deinen Schuss an [1-10]")
    y_Koordinate = input()      #Eingabe y Koordinate
    while True:
      try:                      #Ausnahme
        while (int(y_Koordinate) < 1 or int(y_Koordinate) > 10):
          print("Fehlerhaft Eingabe bitte erneut Versuchen!")
          y_Koordinate = input()
        break
      except:
        y_Koordinate = input("Es wurde keine Zahl übergeben. Bitte gebe eine Zahl [1-10] ein")
    response = requests.get(f"{base_api_url}/Spiel/Schussmoeglich/{x_Koordinate}/{y_Koordinate}").json() #Pruefen ob Stelle nicht bereits beschossen
    if(response["Status"]):    
      response = requests.get(f"{base_api_url}/Spiel/shoot/{x_Koordinate}/{y_Koordinate}").json()   #Schuss auf dem Server
      print(response["information"])
      if(response["Status"]):             #Lokale Markierung des Schusses
        x = int(x_Koordinate) - 1
        y = int(y_Koordinate) - 1
        bL.SetzeH(x, y)
      else:
        x = int(x_Koordinate) - 1
        y = int(y_Koordinate) - 1
        bL.setzeM(x, y)  
    else:
      print(response["information"])
      eingabeSchuss()




         

def main():
  base_api_url = "http://127.0.0.1:8000"

  #Willkomen
  response = requests.get(base_api_url).json()
  print(response["information"])

  #Drucken der Regeln
  print("Den nachfolgenden Link für die Regeln im Browser öffnen")
  print("file:///Users/torgerau/Desktop/Uni%20Stuff/POOSE/projekt2torgesnehpreet/UML/Regeln.html")

  #Eingabe des Namens
  username = input("Bitte gebe deinen Namen ein:")
  response = requests.get(f"{base_api_url}/addPlayer/{username}").json() # spieler erstellen

  #Abfrage ob genug Spieler vorhande
  while(not response["Status"]):
    print(response["information"])
    response = requests.get(f"{base_api_url}/addPlayer/{username}").json()
    time.sleep(5.0)
  print(response["information"])
  time.sleep(5.0)


  #Setzen der Schiffe
  t = False
  while(not t):
    response = requests.get(f"{base_api_url}/Spiel/Setzen/{username}").json()
    if(response["Status"] == True):
      print(response["information"])
      i = 0
      while (i < 4):# 4 schiffe setzten
        eingabeSchiffe()
        bS.print_board()
        i = i + 1
    else:
      print(response["information"])
    time.sleep(5.0)
    response = requests.get(f"{base_api_url}/Spiel/starten").json() 
    if(response["Status"]):
      t = True
      print(response["information"])
  

  #Schießen
  response = requests.get(f"{base_api_url}/Spiel/getGame").json()
  while (response["Status"]):
    response = requests.get(f"{base_api_url}/Spiel/Schießen/{username}").json() # schiff setzten
    if(response["Status"]):
      print(response["information"])
      eingabeSchuss()
      bL.print_board()
      response = requests.get(f"{base_api_url}/Spiel/KontrolleWinner/{username}").json()
    else:
      print(response["information"])
      time.sleep(5.0)
    response = requests.get(f"{base_api_url}/Spiel/getGame").json()

  #Spielende
  response = requests.get(f"{base_api_url}/Spiel/End/{username}").json()
  print(response["information"])










    


  #response = requests.get(f"{base_api_url}/Spiel/Spieler/{username}").json()
  #pprint(response["information"])


  

if __name__ == '__main__':
  main()

