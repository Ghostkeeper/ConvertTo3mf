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

namespace convertobjto3mf {

Model Obj::import(const std::string filename) {
	Obj obj; //Store the OBJ file in its own representation.

	std::vector<std::string> lines = obj.preprocess(filename);
	obj.load_vertices(lines);

	return Model();
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
		}
		size_t last = line.find_last_not_of(" \t\n\r\f");
		line = line.substr(first, (last - first + 1));

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

void Obj::load_vertices(const std::vector<std::string>& lines) {
	for(const std::string& line : lines) {
		if(line.find("v ") != 0) { //Not a vertex on this line.
			continue;
		}

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

		char* end;
		const double x = strtod(x_str.c_str(), &end);
		if(end) {
			continue;
		}
		const double y = strtod(y_str.c_str(), &end);
		if(end) {
			continue;
		}
		const double z = strtod(z_str.c_str(), &end);
		if(end) {
			continue;
		}

		//Successfully parsed a vertex! Let's store it now that everything is safe.
		vertices.emplace_back(x, y, z);
	}
}

}