/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include <fstream> //To read OBJ files.
#include <string> //To process the content of OBJ files.

#include "obj.hpp" //Definitions for this class.
#include "model.hpp" //To write models.

namespace convertto3mf {

Model Obj::import(const std::string filename) {
	Obj obj; //Store the OBJ file in its own representation.

	std::vector<std::string> lines = obj.preprocess(filename);
	obj.load(lines);
	return obj.to_model();
}

std::vector<std::string> Obj::preprocess(const std::string filename) const {
	std::ifstream file_handle(filename);
	std::vector<std::string> lines; //Result of the pre-processing step.
	lines.reserve(32000); //Most files are going to contain at least this amount of lines. Prevent copying too often when growing.
	for(std::string line; std::getline(file_handle, line);) {
		//Trim whitespace from the line.
		size_t first = line.find_first_not_of(" \t\n\r\f");
		if(first == std::string::npos) {
			line = "";
		} else {
			size_t last = line.find_last_not_of(" \t\n\r\f");
			line = line.substr(first, (last - first + 1));
		}

		//Process line continuation.
		if(!lines.empty() && lines.back()[lines.back().length() - 1] == '\\') { //Previous line had a line continuation.
			lines[lines.size() - 1][lines.back().length() - 1] = ' '; //Turn the backslash into a space.
			lines[lines.size() - 1] += line; //Add the new line.
		} else {
			lines.push_back(line);
		}
	}
	return lines;
}

void Obj::load(const std::vector<std::string>& lines) {
	for(const std::string& line : lines) {
		if(line.find("v ") == 0) { //This line defines a vertex.
			size_t x_start = line.find_first_not_of(' ', 1);
			if(x_start == std::string::npos) {
				continue; //The line was just "v     " with a number of spaces but no X coordinate.
			}
			size_t x_end = line.find(' ', x_start);
			if(x_end == std::string::npos) {
				continue; //There was no space after the X coordinate, meaning that there is no Y coordinate.
			}
			size_t y_start = line.find_first_not_of(' ', x_end);
			if(y_start == std::string::npos) {
				continue; //There were just a number of spaces after the X coordinate, no Y coordinate.
			}
			size_t y_end = line.find(' ', y_start);
			if(y_end == std::string::npos) {
				continue; //There was no space after the Y coordinate, meaning that there is no Z coordinate.
			}
			size_t z_start = line.find_first_not_of(' ', y_end);
			if(z_start == std::string::npos) {
				continue; //There were just a number of spaces after the Y coordinate, no Z coordinate.
			}
			size_t z_end = line.find(' ', z_start);
			if(z_end == std::string::npos) {
				z_end = line.length(); //No spaces after the Z coordinate. That's all right though, just cut it off at the end of the string.
			}

			const std::string x_str = line.substr(x_start, x_end - x_start);
			const std::string y_str = line.substr(y_start, y_end - y_start);
			const std::string z_str = line.substr(z_start, z_end - z_start);

			//Convert everything to our coordinate type.
			char* end;
			const coord_t x = strtod(x_str.c_str(), &end);
			if(*end) { //Not a number.
				continue;
			}
			const coord_t y = strtod(y_str.c_str(), &end);
			if(*end) {
				continue;
			}
			const coord_t z = strtod(z_str.c_str(), &end);
			if(*end) {
				continue;
			}

			//Successfully parsed a vertex! Let's store it now that everything is safe.
			vertices.emplace_back(x, y, z);
		} else if(line.find("f ") == 0) { //This line defines a face.
			std::vector<size_t> vertex_indices; //Resulting indices from this line.
			vertex_indices.reserve(3);
			size_t pos = 1; //Start searching for vertices from here.
			while(pos != std::string::npos) { //For each vertex.
				pos = line.find_first_not_of(' ', pos);
				if(pos == std::string::npos) { //There's just space now, no new vertex.
					break;
				}
				const size_t corner_start = pos;
				pos = line.find(' ', corner_start);
				const size_t corner_end = (pos == std::string::npos) ? line.length() : pos; //If there is no more space, stop at the end of the string.
				const std::string corner = line.substr(corner_start, corner_end - corner_start);

				//For now we're only interested in the index to the vertex, not in normals or texture coordinates.
				size_t vertex_end = corner.find('/');
				if(vertex_end == std::string::npos) {
					vertex_end = corner.length();
				}
				const std::string vertex_index_str = corner.substr(0, vertex_end);

				//Convert to index.
				char* end;
				long vertex_index = strtol(vertex_index_str.c_str(), &end, 10);
				if(*end) { //Not an integer.
					continue;
				}
				if(vertex_index == 0) { //Vertices are 1-indexed. 0 should not occur.
					continue;
				}
				if(vertex_index < 0) { //Negative indices refer to the most recent vertices.
					vertex_index += vertices.size() + 1;
					if(vertex_index < 1) { //Too far back. This would be before the start.
						continue;
					}
				}

				//Index is correct. We can store it.
				vertex_indices.push_back(vertex_index - 1);
			}

			faces.push_back(vertex_indices);
		}
	}
}

Model Obj::to_model() const {
	Model model; //The resulting model.
	model.meshes.emplace_back(); //OBJ files always contain just a single mesh.
	Mesh& mesh = model.meshes.back();

	for(std::vector<size_t> vertex_indices : faces) {
		mesh.faces.emplace_back();
		Face& face = mesh.faces.back();

		//Dereference all the indices from the OBJ file.
		for(size_t vertex_index : vertex_indices) {
			if(vertex_index >= vertices.size()) { //Index doesn't exist.
				continue;
			}
			face.vertices.push_back(vertices[vertex_index]);
		}
	}

	return model;
}

}