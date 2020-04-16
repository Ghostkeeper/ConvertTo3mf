/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef THREEMF_HPP
#define THREEMF_HPP

#include <string> //To accept a file name.

#include "model.hpp" //To convert from 3D models.

namespace convertobjto3mf {

/*!
 * This class represents a 3MF file.
 *
 * This class can convert from our internal representation to a representation
 * corresponding to how 3MF saves thing, and then save that to a file.
 */
class ThreeMF {
public:
	/*!
	 * Writes a model to a file in the 3MF format.
	 * \param filename The path to the file to write.
	 * \param model The model to write to this file.
	 */
	static void export_to_file(const std::string filename, const Model& model);
};

}

#endif //THREEMF_HPP

