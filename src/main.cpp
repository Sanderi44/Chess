#include "chess/main.hpp"

Inputs::Inputs(Board *board) { _board = board; }

Inputs::~Inputs() {}

std::pair<std::string, std::string> Inputs::readMove() {
    std::string a, b;
    std::cout << "Enter a move with format: A1 B1" << std::endl;
    std::cin >> a >> b;
    // std::cout << a << " to " << b << std::endl;
    return std::pair<std::string, std::string>(a, b);
}

int main() {
    Board *board = new Board(8);

    Inputs input(board);

    bool turn = false;

    while (true) {
        std::string color = "white";
        if (turn) {
            color = "black";
        }
        std::cout << color << "'s turn!" << std::endl;
        std::pair<std::string, std::string> move = input.readMove();

        // std::string a = "B1";
        // std::string b = "C1";
        // Location location = board->mapStringToLocation(s);
        // // std::cout << s << " -> " << location.x << ", " << location.y << std::endl;
        bool success = board->movePiece(color, move.first, move.second);

        board->showPieces();
        if (success) {
            turn = !turn;
        }
    }
    // board->movePiece("white", 0,3,0,4);

    // board->showPieces();

    return 0;
}
