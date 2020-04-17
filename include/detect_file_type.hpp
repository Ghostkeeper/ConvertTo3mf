/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef DETECT_FILE_TYPE_HPP
#define DETECT_FILE_TYPE_HPP

#include "obj.hpp" //To detect OBJ files.

namespace convertto3mf {

/*!
 * File types that this application is able to detect and convert into.
 */
enum FileType {
	OBJ
};

/*!
 * Detects the most likely file type for a certain file.
 *
 * This calls upon each available file type to determine what the probability is
 * that it's that file type. Then it picks the type that reports the highest
 * probability.
 */
FileType detect_file_type(const std::string& filename);

}

#endif //DETECT_FILE_TYPE_HPP