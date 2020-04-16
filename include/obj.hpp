/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef OBJ_HPP
#define OBJ_HPP

namespace convertobjto3mf {

class Model;

/*!
 * Collection of functions for handling Wavefront OBJ files.
 */
class Obj {
public:
	/*!
	 * Read an OBJ file, storing it in memory as a `Model` instance.
	 */
	static Model import(const std::string filename);
};

}
#endif //OBJ_HPP