/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include <iostream> //To show the help contents in the stdcout.

#include "job.hpp" //To start conversion jobs.
#include "main.hpp" //Definitions for this file.

/*!
 * Entry point into the program.
 *
 * This will parse the input parameters and decides what to do based on those.
 *
 * If the input arguments are wrong, it will show the help.
 */
int main(int argc, char** argv) {
	if(argc < 2) { //Not enough arguments.
		convertobjto3mf::show_help();
		return 1;
	}
	//The 0th argument is the executable name. We're not interested in that.
	//The first argument is required to be the input filename.
	const std::string input_filename(argv[1]);

	//For the default output filename, take the input with the file extension changed.
	std::string output_filename = input_filename;
	int extension_start = output_filename.rfind('.');
	if(extension_start >= 0) { //Remove the extension if there is one.
		output_filename = output_filename.substr(0, extension_start);
	}
	output_filename += ".3mf"; //Add a new extension.

	//Parse the rest as optional parameters.
	for(size_t i = 2; i < argc; ++i) {
		std::string argument(argv[i]);
		if(argument.find("--output=") == 0) {
			output_filename = argument.substr(9);
		}
	}

	convertobjto3mf::Job job(input_filename, output_filename);
	job.run();

	return 0;
}

namespace convertobjto3mf {

void show_help() {
	std::cout << "Convert 3D models to 3MF.\n"
		"Usage:\n"
		"  convertobjto3mf filename [--output=output_filename]\n"
		"\n"
		"Required parameters:\n"
		"  * filename: The name of the input file to convert to 3MF.\n"
		"\n"
		"Optional parameters:\n"
		"  * --output=output_filename: Store the resulting 3MF file in the specified location. By default, the result will be stored in the same location as the input file, but with the file extension changed to .3mf." << std::endl;
}

}