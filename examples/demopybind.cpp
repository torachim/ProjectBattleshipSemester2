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
        .def("getSBoard", &Spieler:: getSBoard);
        .def("getLBoard", &Spieler:: getLBoard);
        .def("shoot", &Spieler::shoot);
        .def("getwinner", &Spieler::getwinner);
        

    py::class_<::Game>(m, "Game");
        .def("printRules", &Game::printRules, "Prints the rules");   
    
} 

