//
// Created by barto on 26.04.19.
//

#ifndef TERMINALSNAKE_DIMENSION_HPP
#define TERMINALSNAKE_DIMENSION_HPP


#include "Point.hpp"

struct Dimension {
	unsigned int width;
	unsigned int height;

	bool isInside(const Point& point) const;

private:
	bool positiveLessThan(int value, int max) const;
};


#endif //TERMINALSNAKE_DIMENSION_HPP
