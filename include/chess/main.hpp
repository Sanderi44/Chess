#ifndef MAIN_HPP
#define MAIN_HPP



#include <iostream>
#include "board/Board.hpp"
// #include <function.hpp>


class Inputs
{
public:
	Board * _board;
	Inputs(Board * board);
	~Inputs();
	std::pair<std::string, std::string> readMove();
};






#endif
