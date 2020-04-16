/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef POINT3_HPP
#define POINT3_HPP

#include "coordinate.hpp" //To represent coordinates.

namespace convertobjto3mf {

/*!
 * This is a data structure that represents a 3-dimensional point.
 *
 * The dimensions in this data structure are called X, Y and Z.
 */
struct Point3 {
	coord_t x;
	coord_t y;
	coord_t z;

	/*!
	 * Creates a new point, filling in the coordinates.
	 */
	Point3(const coord_t x, const coord_t y, const coord_t z);

	/*!
	 * Compares two points for equality.
	 * \param other The point to compare to.
	 * \return `true` if the points are identical, or `false` if they aren't.
	 */
	bool operator ==(const Point3& other) const;
};

}

#endif //POINT3_HPP