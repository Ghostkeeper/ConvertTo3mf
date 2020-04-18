/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef STL_BINARY_HPP
#define STL_BINARY_HPP

#include <string> //To accept filenames.

namespace convertto3mf {

/*!
 * Collection of functions for handling binary STL files.
 */
class StlBinary {
public:
	/*!
	 * Determines the likelihood of this file being a binary STL file.
	 * \param filename The name of the file to check.
	 * \return The likelihood of this file being a binary STL file. This is a
	 * rather arbitrary guess of probability between 0 and 1.
	 */
	static float is_stl_binary(const std::string filename);
};

}

#endif //STL_BINARY_HPP

