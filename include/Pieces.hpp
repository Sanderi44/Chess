#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
#include <Location.hpp>




class Piece
{
public:
	std::string _name;
	bool _team;
	Location _location;
	bool first_turn{true};
	std::string color_symbol;



	Piece();
	virtual ~Piece();
	void setTeam(bool color);
	bool getTeam();
	void setName(std::string name);
	std::string getName();
	void move(int new_x, int new_y);
	void printInfo();
	void setLocation(int x, int y);
	Location getLocation();


	virtual bool isMoveValid(int new_x, int new_y)=0;
	virtual bool isKing();
	virtual bool isQueen();
	virtual bool isRook();
	virtual bool isBishop();
	virtual bool isKnight();
	virtual bool isPawn();

	virtual std::string symbol()=0;

};



class King : public Piece
{
public:
	King(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	std::string symbol();
	bool isKing();
};

class Queen : public Piece
{
public:
	Queen(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	std::string symbol();
	bool isQueen();
};

class Rook : public Piece
{
public:
	Rook(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	std::string symbol();
	bool isRook();
};

class Bishop : public Piece
{
public:
	Bishop(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	std::string symbol();
	bool isBishop();
};

class Knight : public Piece
{
public:
	Knight(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	std::string symbol();
	bool isKnight();
};

class Pawn : public Piece
{
public:
	Pawn(bool color, std::string name, int x, int y);
	bool isMoveValid(int new_x, int new_y);
	bool isPawn();
	std::string symbol();
};






#endif