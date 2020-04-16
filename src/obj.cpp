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

}