/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include <iostream> //To give progress updates.
#include <fstream> //To read the ASCII STL files.
#include <regex> //To match with the syntax of STL to detect the file format.

#include "stl_ascii.hpp" //Definitions for this file.

namespace convertto3mf {

float StlAscii::is_stl_ascii(const std::string& filename) {
	float probability = 1.0 / 3.0; //Final result.
	//Probability of a file extension being different from the contents of the file. Probably an overestimation but we want to let the magic number determine it more.
	constexpr float probability_incorrect_extension = 0.01;
	//Probability of a line being inconsistent with its file type, like there being "solid" in the file if it's not ASCII STL, or gibberish even though it is ASCII STL.
	constexpr float probability_incorrect_line = 0.01;

	//File extension plays a role in likelihood.
	if(filename.find_last_of(".stl") == filename.length() - 4) { //Ends in .stl
		probability = 1 - probability_incorrect_extension;
	} else {
		probability = probability_incorrect_extension;
	}

	//Read 1kB from the file to see if the file appears to be correctly formatted for ASCII STL.
	std::ifstream file_handle(filename);
	file_handle.seekg(0, file_handle.end);
	size_t sample_size = file_handle.tellg();
	file_handle.seekg(file_handle.beg);
	sample_size = std::min(sample_size, size_t(1024)); //Limit to 1kB.
	char sample_chars[sample_size];
	file_handle.read(sample_chars, sample_size);
	std::string sample(sample_chars); //We've read up to 1kB from this file now.

	//Match a line with this regex that matches on the possible lines of ASCII STL.
	const std::regex correct_line("^\\s*$|\\s*solid.*|\\s*facet\\s*|\\s*facet normal .*|\\s*outer loop\\s*|\\s*vertex .*|\\s*endloop\\s*|\\s*endfacet\\s*|\\s*endsolid\\s*");
	size_t correct_lines = 0;
	size_t lines_found = 0;
	size_t line_start = 0;
	size_t line_end = 0;
	while((line_end = sample.find('\n', line_start)) != sample.npos) {
		std::string line = sample.substr(line_start, line_end - line_start);
		lines_found++;
		if(std::regex_match(line, correct_line)) {
			correct_lines++;
		}
		line_start = line_end + 1;
	}
	for(size_t i = 0; i < lines_found; ++i) {
		if(i < correct_lines) { //This line was correct.
			probability = 1.0 - ((1.0 - probability) * probability_incorrect_line);
		} else { //This line was incorrect.
			probability *= probability_incorrect_line;
		}
	}

	return probability;
}

Model StlAscii::import(const std::string& filename) {
	std::cout << "Importing ASCII STL file: " << filename << std::endl;
	StlAscii stl; //Store the STL in its own representation.

	return Model(); //TODO.
}

}