/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

namespace convertobjto3mf {

/*!
 * This is the actual data structure used to represent coordinates.
 *
 * For arbitrary models we're using doubles here. This could have some rounding
 * errors, but those will be very small so most likely they won't be serialised
 * to the output file.
 */
typedef double coord_t;

}

#endif //VERTEX_HPP