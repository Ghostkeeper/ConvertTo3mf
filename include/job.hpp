/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#ifndef JOB_HPP
#define JOB_HPP

namespace convertobjto3mf {

/*!
 * This class represents a conversion job: One file that needs to be converted.
 */
class Job {
	public:
		/*!
		 * The input file to convert.
		 */
		std::string input_filename;

		/*!
		 * The output file name to store the resulting 3MF file in.
		 */
		std::string output_filename;

		/*!
		 * Construct a new conversion job.
		 */
		Job(const std::string& input_filename, const std::string& output_filename);

		/*!
		 * Starts the conversion process.
		 */
		void run();
};

}

#endif //JOB_HPP