#ifndef LOCATION_HPP
#define LOCATION_HPP

struct Location
{
	int x;
	int y;
	Location(){}
	Location(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
};

#endif