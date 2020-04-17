#Command line application to convert models to 3MF.
#Copyright (C) 2020 Ghostkeeper
#This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
#You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13) #Oldest version it was tested with.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") #Finding dependencies.

#Release configuration.
set(CONVERTTO3MF_VERSION_MAJOR 0 CACHE STRING "Major release version. This must be incremented if there are changes that are not backwards compatible.")
set(CONVERTTO3MF_VERSION_MINOR 0 CACHE STRING "Minor release version. This must be incremented if there are changes that are not forwards compatible.")
set(CONVERTTO3MF_VERSION_PATCH 1 CACHE STRING "Patch release version. This must be incremented for every release where there are no changes to the API.")

project(convertto3mf VERSION ${CONVERTTO3MF_VERSION_MAJOR}.${CONVERTTO3MF_VERSION_MINOR}.${CONVERTTO3MF_VERSION_PATCH} DESCRIPTION "Command line application to convert 3D models to 3MF.")

#Dependencies.
find_package(libzip REQUIRED)

#Sources.
set(convertto3mf_sources
	"main.cpp"
	"detect_file_type.cpp"
	"job.cpp"
	"obj.cpp"
	"point3.cpp"
	"threemf.cpp"
)
set(convertto3mf_source_paths "")
foreach(f IN LISTS convertto3mf_sources)
	list(APPEND convertto3mf_source_paths ${CMAKE_CURRENT_SOURCE_DIR}/src/${f})
endforeach()

#The main target.
add_executable(convertto3mf ${convertto3mf_source_paths})
target_link_libraries(convertto3mf "${LIBZIP_LIBRARY}")
target_include_directories(convertto3mf PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(convertto3mf PRIVATE "${LIBZIP_INCLUDE_DIR}")