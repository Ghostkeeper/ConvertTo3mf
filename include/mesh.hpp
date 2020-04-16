/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef MESH_HPP
#define MESH_HPP

#include "face.hpp" //To store faces.

namespace convertobjto3mf {

/*!
 * This is a data structure that holds the data from a mesh within a 3D model.
 *
 * A mesh consists of a collection of faces that belong together. The faces are
 * not necessarily all connected to each other.
 */
class Mesh {
	public:
	/*!
	 * All of the faces within this model.
	 */
	std::vector<Face> faces;
};

}

#endif //MESH_HPP