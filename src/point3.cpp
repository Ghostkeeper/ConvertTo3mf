/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include "point3.hpp" //The definitions for this class.

namespace convertto3mf {

Point3::Point3(const coord_t x, const coord_t y, const coord_t z) :
		x(x),
		y(y),
		z(z) {};

bool Point3::operator ==(const Point3& other) const {
	return x == other.x && y == other.y && z == other.z;
}

}

namespace std {

size_t hash<convertto3mf::Point3>::operator ()(const convertto3mf::Point3& point) const {
	const size_t x_hash = hash<convertto3mf::coord_t>()(point.x);
	const size_t y_hash = hash<convertto3mf::coord_t>()(point.y);
	const size_t z_hash = hash<convertto3mf::coord_t>()(point.z);
	size_t hash = x_hash;
	hash ^= y_hash + 0x9e3779b97f4a7c15 + (hash << 6) + (hash >> 2);
	hash ^= z_hash + 0x9e3779b97f4a7c15 + (hash << 6) + (hash >> 2);
	return hash;
}

}