#include "pieces/Pieces.hpp"

Piece::Piece() {}

Piece::~Piece() {}

void Piece::setTeam(bool color) {
    _team = color;
    if (_team == 0) {
        color_symbol = "W";
    } else {
        color_symbol = "B";
    }
    // std::cout << "--> Added to Team " << _team << std::endl;
}

bool Piece::getTeam() { return _team; }

void Piece::setName(std::string name) {
    _name = name;
    // std::cout << "--> Named " << _name << std::endl;
}

std::string Piece::getName() { return _name; }

void Piece::setLocation(int x, int y) {
    _location.x = x;
    _location.y = y;
}
void Piece::printInfo() {
    std::cout << std::endl << "Piece Info:" << std::endl;
    std::cout << "--> Name: " << _name << std::endl;
    std::cout << "--> Team: " << _team << std::endl;
    std::cout << "--> Location: " << _location.x << ", " << _location.y << std::endl;
}

bool Piece::isPawn() { return false; }
bool Piece::isKing() { return false; }
bool Piece::isQueen() { return false; }
bool Piece::isKnight() { return false; }
bool Piece::isRook() { return false; }
bool Piece::isBishop() { return false; }

void Piece::move(int new_x, int new_y) {
    first_turn = false;
    _location.x = new_x;
    _location.y = new_y;
}

Location Piece::getLocation() { return _location; }

King::King(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool King::isMoveValid(int new_x, int new_y, bool has_piece) {
    int delta_x = abs(_location.x - new_x);
    int delta_y = abs(_location.y - new_y);

    if (delta_x < 2 && delta_y < 2) {
        return true;
    }
    return false;
}

std::string King::symbol() {
    std::string s = "| K" + color_symbol;
    return s;
}

bool King::isKing() { return true; }

Queen::Queen(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool Queen::isMoveValid(int new_x, int new_y, bool has_piece) {
    int delta_x = abs(_location.x - new_x);
    int delta_y = abs(_location.y - new_y);

    if ((delta_x > 0 && delta_y == 0) || (delta_x == 0 && delta_y > 0) ||
        (delta_x > 0 && delta_y > 0 && delta_x == delta_y)) {
        return true;
    }
    return false;
}
std::string Queen::symbol() {
    std::string s = "| Q" + color_symbol;
    return s;
}
bool Queen::isQueen() { return true; }

Rook::Rook(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool Rook::isMoveValid(int new_x, int new_y, bool has_piece) {
    // Need to add special moves

    int delta_x = abs(_location.x - new_x);
    int delta_y = abs(_location.y - new_y);

    if ((delta_x > 0 && delta_y == 0) || (delta_x == 0 && delta_y > 0)) {
        return true;
    }
    return false;
}
std::string Rook::symbol() {
    std::string s = "| R" + color_symbol;
    return s;
}

bool Rook::isRook() { return true; }

Bishop::Bishop(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool Bishop::isMoveValid(int new_x, int new_y, bool has_piece) {
    // Need to add special moves

    int delta_x = abs(_location.x - new_x);
    int delta_y = abs(_location.y - new_y);

    if (delta_x > 0 && delta_y > 0 && delta_x == delta_y) {
        return true;
    }
    return false;
}

std::string Bishop::symbol() {
    std::string s = "| B" + color_symbol;
    return s;
}
bool Bishop::isBishop() { return true; }

Knight::Knight(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool Knight::isMoveValid(int new_x, int new_y, bool has_piece) {

    int delta_x = abs(_location.x - new_x);
    int delta_y = abs(_location.y - new_y);
    std::cout << delta_x << ", " << delta_y << std::endl;
    std::cout << new_x << " " << new_y << ", " << _location.x << " " << _location.y
              << std::endl;
    if ((delta_x == 2 && delta_y == 1) || (delta_x == 1 && delta_y == 2)) {
        return true;
    }
    return false;
}

std::string Knight::symbol() {
    std::string s = "| H" + color_symbol;
    return s;
}

bool Knight::isKnight() { return true; }

Pawn::Pawn(bool color, std::string name, int x, int y) {
    setTeam(color);
    setName(name);
    setLocation(x, y);
}

bool Pawn::isMoveValid(int new_x, int new_y, bool has_piece) {
    // std::cout << new_x << std::endl;
    int delta_x = new_x - _location.x;
    int delta_y = new_y - _location.y;

    std::cout << delta_x << std::endl;
    std::cout << delta_y << std::endl;
    int m = -1;
    if (_team) {
        m = 1;
    }

    if ((delta_x == m * 1 && delta_y == 0 && !has_piece) ||
        (delta_x == m * 2 && first_turn && delta_y == 0 && !has_piece) ||
        (delta_x == m * 1 && abs(delta_y) == 1 && has_piece)) {
        return true;
    }
    return false;
}

bool Pawn::isPawn() { return true; }

std::string Pawn::symbol() {
    std::string s = "| P" + color_symbol;
    return s;
}
