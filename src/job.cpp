/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include <iostream> //To communicate progress via stdcout.

#include "job.hpp" //The definitions for this file.

namespace convertobjto3mf {

Job::Job(const std::string& input_filename, const std::string& output_filename) :
		input_filename(input_filename),
		output_filename(output_filename) {};

void Job::run() {
	std::cout << "Converting " << input_filename << " to " << output_filename << std::endl;
}

}