#include "../include/board.hpp"
#include "../include/Spieler.hpp"
#include "../include/game.hpp"
#include <iostream>
#include<string>
#include <pybind11/pybind11.h>



namespace py = pybind11;
using namespace ProjectAlpha2;


    void run_game() 
{
    ProjectAlpha2::board m;
    ProjectAlpha2::board l;
    ProjectAlpha2::board k;
    ProjectAlpha2::board n;

    ProjectAlpha2::Spieler t(m , l, "Torge");
    ProjectAlpha2::Spieler p(k, n, "Gegner");

    ProjectAlpha2::Game g(t, p);

    g.startgame();
}

PYBIND11_MODULE(schiffeversenken, m) {

    m.doc() = "Schiffeversenken Example";

    py::class_<board>(m, "board");
        .def

    py::class_<::Spieler>(m, "Spieler");
    Spieler(board boardS_, board boardL_, std::string Name_); 
        .def(py::init<board boardS_, board boardL)
        .def("setShips", &Spieler::setShips, "Sets a Ship");
        .def("setEnBoard", &Spieler::startgame);

    py::class_<::Game>(m, "Game");
        .def("printRules", &Game::printRules, "Prints the rules");
    
}


/* 

server phyton: 

import socket

def run_game():
    # Implementiere hier den Spielablauf

def start_server():
    host = '127.0.0.1'
    port = 12345

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print(f"Server gestartet. Warte auf Verbindung auf {host}:{port}...")

    while True:
        client_socket, addr = server_socket.accept()
        print(f"Verbindung hergestellt von {addr[0]}:{addr[1]}")

        # Führe das Spiel aus
        run_game()

        client_socket.close()

if __name__ == '__main__':
    start_server()



client Phyton: 

import socket

def start_client():
    host = '127.0.0.1'
    port = 12345

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    print(f"Verbindung hergestellt zu {host}:{port}")

    # Hier können Sie die Logik für den Client implementieren
    # z.B. Anweisungen an den Server senden und die Antworten empfangen

    client_socket.close()

if __name__ == '__main__':
    start_client()
*/ 