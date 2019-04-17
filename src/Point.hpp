//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_POINT_HPP
#define TERMINALSNAKE_POINT_HPP


struct Point {
	int x;
	int y;

	bool operator ==(const Point& other) const;

	bool operator !=(const Point& other) const;
};


#endif //TERMINALSNAKE_POINT_HPP
