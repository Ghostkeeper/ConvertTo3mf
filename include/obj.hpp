/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef OBJ_HPP
#define OBJ_HPP

#include <vector> //To store the data structure contained within the OBJ file format.

#include "point3.hpp" //To store vertices from the OBJ file.

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

protected:
	/*!
	 * The list of vertices found in the OBJ file.
	 */
	std::vector<Point3> vertices;

	/*!
	 * The list of faces found in the OBJ file.
	 *
	 * Each face is a list of indices referring to one of the vertices each.
	 */
	std::vector<std::vector<size_t>> faces;

	/*!
	 * Reads lines from an OBJ file and pre-processes them.
	 *
	 * This combines lines that have a continuation slash between them, and
	 * trims whitespace from these lines.
	 * \param filename The path to the file to read from.
	 * \return A list of lines from the file, slightly pre-processed for easier
	 * parsing.
	 */
	std::vector<std::string> preprocess(const std::string filename) const;

	/*!
	 * Reads all the vertex definitions from a preprocessed OBJ file.
	 *
	 * This puts the vertices in the Obj class.
	 * \param lines The lines from an OBJ file as returned by `preprocess`.
	 */
	void load_vertices(const std::vector<std::string>& lines);

	/*!
	 * Reads all the face definitions from a preprocessed OBJ file.
	 *
	 * This puts the faces in the Obj class.
	 * \param lines The lines from an OBJ file as returned by `preprocess`.
	 */
	void load_faces(const std::vector<std::string>& lines);

	/*!
	 * Converts the OBJ file to a Model class in our internal data format.
	 * \return A 3D model.
	 */
	Model to_model() const;
};

}
#endif //OBJ_HPP