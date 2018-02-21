#ifndef BOARD_HPP
#define BOARD_HPP

#include <Pieces.hpp>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <locale>
#include <vector>
#include <algorithm>

class Board
{
public:
	std::map<int, std::unique_ptr<Piece> > piece_locations;
	std::vector<std::unique_ptr<Piece> > white_taken;
	std::vector<std::unique_ptr<Piece> > black_taken;


	Board(int size);
	bool hasPiece(int new_x, int new_y);
	int getLocation(int new_x, int new_y);
	void addPiece(std::string piece, int new_x, int new_y, std::string color, std::string name);
	void setupPieces();
	bool isLocationValid(int new_x, int new_y);
	void showPieces();
	bool movePiece(std::string color, std::string first_position, std::string second_position);
	bool movePiece(std::string color, int x, int y, int new_x, int new_y);
	void move(int old_loc, int new_loc);
	void take(int old_loc, int new_loc);
	bool isCheck(bool team);

	Location mapStringToLocation(std::string str);

private:
	int ROWS{8};
	int COLS{8};
	std::map<std::string, Location > stringToLocation;
};






#endif