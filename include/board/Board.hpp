#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <locale>
#include <vector>
#include <algorithm>
#include "pieces/Pieces.hpp"

class Board {
   public:
    std::map<int, std::unique_ptr<Piece> > piece_locations;
    std::map<std::string, std::string> name_to_location;
    std::vector<std::unique_ptr<Piece> > white_taken;
    std::vector<std::unique_ptr<Piece> > black_taken;

    Board(int size);
    bool isCheck(bool team);
    bool hasPiece(int new_x, int new_y);
    int getLocation(int new_x, int new_y);
    std::string getPiecesStringLocation(std::string name);
    std::string getPieceNameAtStringLocation(std::string location);
    void addPiece(
        std::string piece, int new_x, int new_y, std::string color, std::string name);
    void setupPieces();
    bool isLocationValid(int new_x, int new_y);
    void showPieces();
    bool movePiece(std::string color,
                   std::string first_position,
                   std::string second_position);
    bool movePiece(
        std::string color, int x, int y, int new_x, int new_y, std::string name);
    void move(int old_loc, int new_loc);
    void take(int old_loc, int new_loc);

    Location mapStringToLocation(std::string str);
    std::string mapLocationToString(Location location);

   private:
    int ROWS{8};
    int COLS{8};
    std::map<std::string, Location> stringToLocation;
};

#endif
