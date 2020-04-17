/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector> //To store a number of meshes.

#include "mesh.hpp" //To store the meshes.

namespace convertto3mf {

/*!
 * This is a data structure that holds the data from a 3D model.
 *
 * A model consists of an arbitrary number of separate meshes, which are groups
 * of faces, which are groups of vertices.
 */
class Model {
	public:
	/*!
	 * All of the meshes within this model.
	 */
	std::vector<Mesh> meshes;
};

}

#endif //MODEL_HPP