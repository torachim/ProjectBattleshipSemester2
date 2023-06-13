#include "../include/board.hpp"
#include "../include/Spieler.hpp"
#include "../include/game.hpp"
#include <iostream>
#include<string>
#include <pybind11/pybind11.h>



namespace py = pybind11;
using namespace ProjectAlpha2;


  /*  void run_game() 
{
    ProjectAlpha2::board m;
    ProjectAlpha2::board l;
    ProjectAlpha2::board k;
    ProjectAlpha2::board n;

    ProjectAlpha2::Spieler t(m , l, "Torge");
    ProjectAlpha2::Spieler p(k, n, "Gegner");

    ProjectAlpha2::Game g(t, p);

    g.startgame();
}*/

PYBIND11_MODULE(schiffeversenken, m) {

    m.doc() = "Schiffeversenken example";

    py::class_<::board>(m, "board")
        .def(py::init< >())
        .def("print_board", &board::printBoard)
        .def("can_set_ship", &board::canSetShip)
        .def("is_hit", &board::isHit)
        .def("winner", &board::winner)
        .def("Schiffsetzen", &board::Schiffsetzen)
        .def("SetzeH", &board::setH)
        .def("setzeM", &board::setM)
        .def("setzeX", &board::setD)
        .def("setzeO", &board::setO);


    py::class_<::Spieler>(m, "Spieler")
        .def(py::init<board , board , std::string>())
        .def("setShips", &Spieler::setShips)
        .def("Schießen", &Spieler::shoot)
        .def("erhalteName", &Spieler::getName)
        .def("Erhalte_Schiffe_Brett", &Spieler::getSBoard)
        .def("Erhalte_Spielbrett", &Spieler::getLBoard)
        .def("Kontrolle_Sieger", &Spieler::winnercontrol)
        .def("Erhalte_Sieger", &Spieler::getwinner);
        

    py::class_<::Game>(m, "Game")
        .def(py::init<Spieler, Spieler>())
        .def("printRules", &Game::printrules, "Prints the rules");

    
} 

