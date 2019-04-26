//
// Created by barto on 26.04.19.
//

#include "Dimension.hpp"

bool Dimension::isInside(const Point& point) const {
	return (positiveLessThan(point.x, height) && positiveLessThan(point.y, width));
}

bool Dimension::positiveLessThan(int value, int max) const {
	return (0 <= value && value < max);
}
