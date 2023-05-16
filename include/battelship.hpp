#include <iostream>
#include <vector>

const int BOARD_SIZE = 10;

enum class CellState {
    Empty,
    Ship,
    Miss,
    Hit
};

class Board {
private:
    std::vector<std::vector<CellState>> grid;
public:
    Board() : grid(BOARD_SIZE, std::vector<CellState>(BOARD_SIZE, CellState::Empty)) {}

    void placeShip(int x, int y) {
        grid[x][y] = CellState::Ship;
    }

    bool attack(int x, int y) {
        if (grid[x][y] == CellState::Ship) {
            grid[x][y] = CellState::Hit;
            return true;
        } else {
            grid[x][y] = CellState::Miss;
            return false;
        }
    }

    void print() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                switch (grid[i][j]) {
                    case CellState::Empty:
                        std::cout << ".";
                        break;
                    case CellState::Ship:
                        std::cout << "S";
                        break;
                    case CellState::Miss:
                        std::cout << "M";
                        break;
                    case CellState::Hit:
                        std::cout << "X";
                        break;
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Board board;
    board.placeShip(2, 3);
    board.placeShip(5, 6);

    while (true) {
        int x, y;
        std::cout << "Enter target coordinates (x y): ";
        std::cin >> x >> y;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            std::cout << "Invalid coordinates. Try again." << std::endl;
            continue;
        }

        bool hit = board.attack(x, y);
        board.print();

        if (hit) {
            std::cout << "You hit a ship!" << std::endl;
        } else {
            std::cout << "You missed." << std::endl;
        }
    }

    return 0;
}
