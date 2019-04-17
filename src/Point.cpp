//
// Created by a19stude on 4/17/19.
//

#include "Point.hpp"

bool Point::operator ==(const Point& other) const {
	return (this->x == other.x) && (this->y == other.y);
}

bool Point::operator !=(const Point& other) const {
	return !(*this == other);
}
