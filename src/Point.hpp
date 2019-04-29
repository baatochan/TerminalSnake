//
// Created by a19stude on 4/17/19.
//

#ifndef TERMINALSNAKE_POINT_HPP
#define TERMINALSNAKE_POINT_HPP

#include <functional>

struct Point {
	int x;
	int y;

	bool operator ==(const Point& other) const;

	bool operator !=(const Point& other) const;
};

// Hack in a hash implementation for Point
namespace std {
	template<> struct hash<Point> {
		std::size_t operator ()(const Point& v) const noexcept {
			const std::size_t hx = std::hash<int>{}(v.x);
			const std::size_t hy = std::hash<int>{}(v.y);
			return hx ^ (hy << 8 * (sizeof(std::size_t) - sizeof(int)));
		}
	};
}

#endif //TERMINALSNAKE_POINT_HPP
