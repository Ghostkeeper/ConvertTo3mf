/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include "detect_file_type.hpp" //The definitions for this file.
#include "obj.hpp" //To detect OBJ files.
#include "stl_binary.hpp" //To detect binary STL files.

namespace convertto3mf {

FileType detect_file_type(const std::string& filename) {
	float highest_probability = 0.0;
	FileType result = FileType::OBJ;

	const float obj_probability = Obj::is_obj(filename);
	if(obj_probability > highest_probability) {
		highest_probability = obj_probability;
		result = FileType::OBJ;
	}

	const float stl_binary_probability = StlBinary::is_stl_binary(filename);
	if(stl_binary_probability > highest_probability) {
		highest_probability = stl_binary_probability;
		result = FileType::STL_BINARY;
	}

	return result;
}

}