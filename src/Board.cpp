#include "board/Board.hpp"

Board::Board(int size) {

    ROWS = size;
    COLS = size;

    std::cout << "Creating new board of size " << ROWS << " by " << COLS << std::endl;

    // setup pieces
    setupPieces();
}

Location Board::mapStringToLocation(std::string str) {
    Location loc;
    loc.x = -1;
    loc.y = -1;
    // std::cout << str << std::endl;
    auto it = stringToLocation.find(str);
    if (it == stringToLocation.end()) {
        std::cout << "Invalid string " << str << std::endl;
        return loc;
    }
    loc = it->second;
}

std::string Board::mapLocationToString(Location location) {
    auto it = stringToLocation.begin();
    // Iterate through the map
    while (it != stringToLocation.end()) {
        // Check if value of this entry matches with given value
        if (it->second == location) {
            // Yes found
            return it->first;
        }
        // Go to next entry in map
        it++;
    }
    return std::string("");
}

int Board::getLocation(int new_x, int new_y) { return new_x + new_y * COLS; }

bool Board::hasPiece(int new_x, int new_y) {
    int board_location = getLocation(new_x, new_y);
    auto it = piece_locations.find(board_location);
    if (it != piece_locations.end()) {
        return true;
    }
    return false;
}

void Board::addPiece(
    std::string piece, int new_x, int new_y, std::string color, std::string name) {
    std::locale loc;
    std::string lc_piece = "";
    std::string lc_color = "";
    for (std::string::size_type i = 0; i < piece.length(); ++i) {
        lc_piece += std::tolower(piece[i], loc);
    }
    for (std::string::size_type i = 0; i < color.length(); ++i) {
        lc_color += std::tolower(color[i], loc);
    }
    // std::cout << "Found a " << lc_color << " " << lc_piece << std::endl;
    bool team;
    if (lc_color.find("white") != std::string::npos) {
        team = false;
    } else {
        team = true;
    }

    int board_location = getLocation(new_x, new_y);
    std::string location_str = mapLocationToString(Location(new_x, new_y));
    // std::cout << "Location: " << new_x << ", " << new_y << " = " << board_location <<
    // std::endl;

    if (lc_piece.find("king") != std::string::npos) {
        piece_locations.insert(std::make_pair(
            board_location, std::unique_ptr<Piece>(new King(team, name, new_x, new_y))));
    } else if (lc_piece.find("queen") != std::string::npos) {
        piece_locations.insert(std::make_pair(
            board_location, std::unique_ptr<Piece>(new Queen(team, name, new_x, new_y))));
    } else if (lc_piece.find("rook") != std::string::npos) {
        piece_locations.insert(std::make_pair(
            board_location, std::unique_ptr<Piece>(new Rook(team, name, new_x, new_y))));
    } else if (lc_piece.find("bishop") != std::string::npos) {
        piece_locations.insert(
            std::make_pair(board_location,
                           std::unique_ptr<Piece>(new Bishop(team, name, new_x, new_y))));
    } else if (lc_piece.find("knight") != std::string::npos) {
        piece_locations.insert(
            std::make_pair(board_location,
                           std::unique_ptr<Piece>(new Knight(team, name, new_x, new_y))));
    } else if (lc_piece.find("pawn") != std::string::npos) {
        piece_locations.insert(std::make_pair(
            board_location, std::unique_ptr<Piece>(new Pawn(team, name, new_x, new_y))));
    } else {
        std::cout << "Invalid piece " << lc_piece << std::endl;
    }
    std::cout << "Inserting " << name << " at " << location_str << std::endl;
    name_to_location.insert(std::pair<std::string, std::string>(name, location_str));
}

void Board::move(int old_loc, int new_loc) {
    // auto value = piece_locations[old_loc];
    piece_locations.insert(
        std::make_pair(new_loc, std::move(piece_locations.at(old_loc))));
    piece_locations.erase(old_loc);
}

void Board::take(int old_loc, int new_loc) {
    if (piece_locations.at(old_loc)->getTeam()) {
        black_taken.push_back(std::move(piece_locations.at(new_loc)));
    } else {
        white_taken.push_back(std::move(piece_locations.at(new_loc)));
    }
    piece_locations.erase(new_loc);
    move(old_loc, new_loc);
}

bool isCheck(bool team) { return false; }

void Board::setupPieces() {
    stringToLocation.insert(std::make_pair(std::string("A1"), Location(0, 0)));
    stringToLocation.insert(std::make_pair(std::string("A2"), Location(1, 0)));
    stringToLocation.insert(std::make_pair(std::string("A3"), Location(2, 0)));
    stringToLocation.insert(std::make_pair(std::string("A4"), Location(3, 0)));
    stringToLocation.insert(std::make_pair(std::string("A5"), Location(4, 0)));
    stringToLocation.insert(std::make_pair(std::string("A6"), Location(5, 0)));
    stringToLocation.insert(std::make_pair(std::string("A7"), Location(6, 0)));
    stringToLocation.insert(std::make_pair(std::string("A8"), Location(7, 0)));

    stringToLocation.insert(std::make_pair(std::string("B1"), Location(0, 1)));
    stringToLocation.insert(std::make_pair(std::string("B2"), Location(1, 1)));
    stringToLocation.insert(std::make_pair(std::string("B3"), Location(2, 1)));
    stringToLocation.insert(std::make_pair(std::string("B4"), Location(3, 1)));
    stringToLocation.insert(std::make_pair(std::string("B5"), Location(4, 1)));
    stringToLocation.insert(std::make_pair(std::string("B6"), Location(5, 1)));
    stringToLocation.insert(std::make_pair(std::string("B7"), Location(6, 1)));
    stringToLocation.insert(std::make_pair(std::string("B8"), Location(7, 1)));

    stringToLocation.insert(std::make_pair(std::string("C1"), Location(0, 2)));
    stringToLocation.insert(std::make_pair(std::string("C2"), Location(1, 2)));
    stringToLocation.insert(std::make_pair(std::string("C3"), Location(2, 2)));
    stringToLocation.insert(std::make_pair(std::string("C4"), Location(3, 2)));
    stringToLocation.insert(std::make_pair(std::string("C5"), Location(4, 2)));
    stringToLocation.insert(std::make_pair(std::string("C6"), Location(5, 2)));
    stringToLocation.insert(std::make_pair(std::string("C7"), Location(6, 2)));
    stringToLocation.insert(std::make_pair(std::string("C8"), Location(7, 2)));

    stringToLocation.insert(std::make_pair(std::string("D1"), Location(0, 3)));
    stringToLocation.insert(std::make_pair(std::string("D2"), Location(1, 3)));
    stringToLocation.insert(std::make_pair(std::string("D3"), Location(2, 3)));
    stringToLocation.insert(std::make_pair(std::string("D4"), Location(3, 3)));
    stringToLocation.insert(std::make_pair(std::string("D5"), Location(4, 3)));
    stringToLocation.insert(std::make_pair(std::string("D6"), Location(5, 3)));
    stringToLocation.insert(std::make_pair(std::string("D7"), Location(6, 3)));
    stringToLocation.insert(std::make_pair(std::string("D8"), Location(7, 3)));

    stringToLocation.insert(std::make_pair(std::string("E1"), Location(0, 4)));
    stringToLocation.insert(std::make_pair(std::string("E2"), Location(1, 4)));
    stringToLocation.insert(std::make_pair(std::string("E3"), Location(2, 4)));
    stringToLocation.insert(std::make_pair(std::string("E4"), Location(3, 4)));
    stringToLocation.insert(std::make_pair(std::string("E5"), Location(4, 4)));
    stringToLocation.insert(std::make_pair(std::string("E6"), Location(5, 4)));
    stringToLocation.insert(std::make_pair(std::string("E7"), Location(6, 4)));
    stringToLocation.insert(std::make_pair(std::string("E8"), Location(7, 4)));

    stringToLocation.insert(std::make_pair(std::string("F1"), Location(0, 5)));
    stringToLocation.insert(std::make_pair(std::string("F2"), Location(1, 5)));
    stringToLocation.insert(std::make_pair(std::string("F3"), Location(2, 5)));
    stringToLocation.insert(std::make_pair(std::string("F4"), Location(3, 5)));
    stringToLocation.insert(std::make_pair(std::string("F5"), Location(4, 5)));
    stringToLocation.insert(std::make_pair(std::string("F6"), Location(5, 5)));
    stringToLocation.insert(std::make_pair(std::string("F7"), Location(6, 5)));
    stringToLocation.insert(std::make_pair(std::string("F8"), Location(7, 5)));

    stringToLocation.insert(std::make_pair(std::string("G1"), Location(0, 6)));
    stringToLocation.insert(std::make_pair(std::string("G2"), Location(1, 6)));
    stringToLocation.insert(std::make_pair(std::string("G3"), Location(2, 6)));
    stringToLocation.insert(std::make_pair(std::string("G4"), Location(3, 6)));
    stringToLocation.insert(std::make_pair(std::string("G5"), Location(4, 6)));
    stringToLocation.insert(std::make_pair(std::string("G6"), Location(5, 6)));
    stringToLocation.insert(std::make_pair(std::string("G7"), Location(6, 6)));
    stringToLocation.insert(std::make_pair(std::string("G8"), Location(7, 6)));

    stringToLocation.insert(std::make_pair(std::string("H1"), Location(0, 7)));
    stringToLocation.insert(std::make_pair(std::string("H2"), Location(1, 7)));
    stringToLocation.insert(std::make_pair(std::string("H3"), Location(2, 7)));
    stringToLocation.insert(std::make_pair(std::string("H4"), Location(3, 7)));
    stringToLocation.insert(std::make_pair(std::string("H5"), Location(4, 7)));
    stringToLocation.insert(std::make_pair(std::string("H6"), Location(5, 7)));
    stringToLocation.insert(std::make_pair(std::string("H7"), Location(6, 7)));
    stringToLocation.insert(std::make_pair(std::string("H8"), Location(7, 7)));

    addPiece("Rook", 7, 0, "White", "WR1");
    addPiece("Knight", 7, 1, "White", "WKn1");
    addPiece("Bishop", 7, 2, "White", "WB1");
    addPiece("Queen", 7, 3, "White", "WQ");
    addPiece("King", 7, 4, "White", "WK");
    addPiece("Bishop", 7, 5, "White", "WB2");
    addPiece("Knight", 7, 6, "White", "WKn2");
    addPiece("Rook", 7, 7, "White", "WR2");

    addPiece("Pawn", 6, 0, "White", "WP1");
    addPiece("Pawn", 6, 1, "White", "WP2");
    addPiece("Pawn", 6, 2, "White", "WP3");
    addPiece("Pawn", 6, 3, "White", "WP4");
    addPiece("Pawn", 6, 4, "White", "WP5");
    addPiece("Pawn", 6, 5, "White", "WP6");
    addPiece("Pawn", 6, 6, "White", "WP7");
    addPiece("Pawn", 6, 7, "White", "WP8");

    addPiece("Rook", 0, 7, "Black", "BR1");
    addPiece("Knight", 0, 6, "Black", "BKn1");
    addPiece("Bishop", 0, 5, "Black", "BB1");
    addPiece("Queen", 0, 4, "Black", "BQ");
    addPiece("King", 0, 3, "Black", "BK");
    addPiece("Bishop", 0, 2, "Black", "BB2");
    addPiece("Knight", 0, 1, "Black", "BKn2");
    addPiece("Rook", 0, 0, "Black", "BR2");

    addPiece("Pawn", 1, 7, "Black", "BP1");
    addPiece("Pawn", 1, 6, "Black", "BP2");
    addPiece("Pawn", 1, 5, "Black", "BP3");
    addPiece("Pawn", 1, 4, "Black", "BP4");
    addPiece("Pawn", 1, 3, "Black", "BP5");
    addPiece("Pawn", 1, 2, "Black", "BP6");
    addPiece("Pawn", 1, 1, "Black", "BP7");
    addPiece("Pawn", 1, 0, "Black", "BP8");
    showPieces();
}

void Board::showPieces() {
    std::cout << std::endl;
    int COL_WIDTH = 6;
    std::string ROW_NAMES[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    std::string COL_NAMES[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    std::cout << std::endl;
    std::cout << "W = White, B = Black" << std::endl;
    std::cout << "K = King, Q = Queen, B = Bishop, H = Knight, R = Rook, P = Pawn"
              << std::endl;

    std::cout << "                           Black" << std::endl;
    std::cout << "           ";
    for (int j = 0; j < COLS; j++) {
        std::cout << "  " << ROW_NAMES[j] << "    ";
    }
    std::cout << std::endl;
    std::cout << "          ";
    for (int j = 0; j < COLS; j++) {
        std::cout << "-------";
    }
    std::cout << std::endl;

    for (int i = 0; i < ROWS; i++) {
        std::cout << "        ";
        std::cout << COL_NAMES[i] << " ";
        for (int j = 0; j < COLS; j++) {
            if (hasPiece(i, j)) {
                std::string name = piece_locations[getLocation(i, j)]->getName();
                int len = name.length();
                std::cout << "| ";
                // std::cout << " ";
                std::cout << name;
                for (int l = 0; l < COL_WIDTH - len - 1; l++) {
                    std::cout << " ";
                }
            } else {
                std::cout << "|      ";
            }
        }
        std::cout << "|";
        std::cout << std::endl;
        std::cout << "          ";
        for (int j = 0; j < COLS; j++) {
            std::cout << "-------";
        }
        std::cout << std::endl;
    }
    std::cout << "                           White" << std::endl;
}

std::string Board::getPiecesStringLocation(std::string name) {
    if (name_to_location.find(name) != name_to_location.end()) {
        return name_to_location.at(name);
    }
    return std::string("");
}

std::string Board::getPieceNameAtStringLocation(std::string location) {
    for (auto it = name_to_location.begin(); it != name_to_location.end(); it++) {
        if (it->second == location) {
            return it->first;
        }
    }
    return std::string("");
}

bool Board::movePiece(std::string color, std::string name, std::string second_position) {
    std::string first_position = getPiecesStringLocation(name);
    std::cout << first_position << std::endl;
    Location cur_loc = mapStringToLocation(first_position);
    std::cout << cur_loc.x << ", " << cur_loc.y << std::endl;
    Location new_loc = mapStringToLocation(second_position);
    std::cout << new_loc.x << ", " << new_loc.y << std::endl;
    if (cur_loc.x == -1 || new_loc.x == -1) {
        std::cout << "Invalid string location" << std::endl;
        return false;
    }
    return movePiece(color, cur_loc.x, cur_loc.y, new_loc.x, new_loc.y, name);
}

bool Board::movePiece(
    std::string color, int x, int y, int new_x, int new_y, std::string name) {

    // Check if there is a piece there
    if (!hasPiece(x, y)) {
        std::cout << "You do not have a piece at " << x << ", " << y << std::endl;
        return false;
    }
    int current_location = getLocation(x, y);
    int new_location = getLocation(new_x, new_y);

    // piece_locations[current_location]->printInfo();
    // Check if that piece is on the correct team
    std::locale loc;
    std::string lc_color = "";
    for (std::string::size_type i = 0; i < color.length(); ++i) {
        lc_color += std::tolower(color[i], loc);
    }
    bool team;
    if (lc_color.find("white") != std::string::npos) {
        team = false;
    } else {
        team = true;
    }

    if (piece_locations[current_location]->getTeam() != team) {
        std::cout << "The piece at " << x << ", " << y << " is not " << lc_color
                  << std::endl;
        return false;
    }

    if (new_x > ROWS || new_x < 0 || new_y > COLS || new_y < 0) {
        std::cout << "This move is not on the board!" << std::endl;
        return false;
    }
    if (new_x == x && new_y == y) {
        std::cout << "You cannot move nowhere!" << std::endl;
        return false;
    }

    // Need to figure out if you are in check
    bool isPlayerChecked = false;    // isCheck(team);
    std::cout << "Checked? " << isPlayerChecked << std::endl;

    // Need to figure out if this is a special move
    // 1. Castling - right or left
    // 2. En Passant - captured pawn must move 2 squares and to where there is an adjacent
    // pawn, then it can be taken by going diagonal
    // 3. Pawn Promotion - pawn can be changed to queen, rook, knight or bishop when it
    // gets to the other side

    // Check if this is a valid move for that piece
    if (!piece_locations[current_location]->isMoveValid(
            new_x, new_y, hasPiece(new_x, new_y))) {
        std::cout << "This move violates the rules of "
                  << piece_locations[current_location]->getName() << std::endl;
        return false;
    }
    // std::cout <<"hello\n";

    // Check if your own piece is in the new location
    if (hasPiece(new_x, new_y) && piece_locations[new_location]->getTeam() == team) {
        std::cout << "Cannot move to this location because you already have "
                  << piece_locations[new_location]->getName() << " there" << std::endl;
        return false;
    }

    // If it is not a knight, check whether any other pieces are in the way
    if (!piece_locations[current_location]->isKnight()) {
        int delta_x = abs(new_x - x);
        int delta_y = abs(new_y - y);
        if (delta_x == 0 && delta_y > 0) {
            // Vertical move

            int m = 1;
            if (new_y < y) {
                m = -1;
            }
            for (int i = 1; i < delta_y; i++) {
                if (piece_locations.find(getLocation(x, y + m * i)) !=
                    piece_locations.end()) {
                    std::cout << "Cannot move to this location because you have "
                              << piece_locations[getLocation(x, y + m * i)]->getName()
                              << " in the way" << std::endl;
                    return false;
                }
            }
        } else if (delta_x > 0 && delta_y == 0) {
            // Horizontal move
            int m = 1;
            if (new_x < x) {
                m = -1;
            }
            for (int i = 1; i < delta_y; i++) {
                if (piece_locations.find(getLocation(x + m * i, y)) !=
                    piece_locations.end()) {
                    std::cout << "Cannot move to this location because you have "
                              << piece_locations[getLocation(x + m * i, y)]->getName()
                              << " in the way" << std::endl;
                    return false;
                }
            }
        } else if (delta_x > 0 && delta_y == 0) {
            // Diagonal move
            int m = 1;
            int n = 1;
            if (new_x < x) {
                m = -1;
            }
            if (new_y < y) {
                n = -1;
            }

            for (int i = 1; i < delta_y; i++) {
                if (piece_locations.find(getLocation(x + m * i, y + n * i)) !=
                    piece_locations.end()) {
                    std::cout
                        << "Cannot move to this location because you have "
                        << piece_locations[getLocation(x + m * i, y + n * i)]->getName()
                        << " in the way" << std::endl;
                    return false;
                }
            }
        }
    }

    // Need to figure out if this new move is a check and return false of your own player

    if (hasPiece(new_x, new_y) && piece_locations[new_location]->getTeam() != team) {
        std::string takee =
            getPieceNameAtStringLocation(mapLocationToString(Location(new_x, new_y)));
        std::cout << takee << std::endl;
        take(current_location, new_location);
        piece_locations[new_location]->setLocation(new_x, new_y);
        name_to_location.at(name) = mapLocationToString(Location(new_x, new_y));
        name_to_location.at(takee) = mapLocationToString(Location(-1, -1));
        std::cout << "Nice Take!" << std::endl;
        return true;
    }
    move(current_location, new_location);
    name_to_location.at(name) = mapLocationToString(Location(new_x, new_y));
    piece_locations[new_location]->setLocation(new_x, new_y);

    return true;
}

bool Board::isLocationValid(int new_x, int new_y) {}
