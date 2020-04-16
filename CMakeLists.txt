#Command line application to convert models to 3MF.
#Copyright (C) 2020 Ghostkeeper
#This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
#You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13) #Oldest version it was tested with.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") #Finding dependencies.

#Release configuration.
set(CONVERTOBJTO3MF_VERSION_MAJOR 0 CACHE STRING "Major release version. This must be incremented if there are changes that are not backwards compatible.")
set(CONVERTOBJTO3MF_VERSION_MINOR 0 CACHE STRING "Minor release version. This must be incremented if there are changes that are not forwards compatible.")
set(CONVERTOBJTO3MF_VERSION_PATCH 1 CACHE STRING "Patch release version. This must be incremented for every release where there are no changes to the API.")

project(convertobjto3mf VERSION ${CONVERTOBJTO3MF_VERSION_MAJOR}.${CONVERTOBJTO3MF_VERSION_MINOR}.${CONVERTOBJTO3MF_VERSION_PATCH} DESCRIPTION "Command line application to convert models to 3MF.")

#Dependencies.
find_package(libzip REQUIRED)

#Sources.
set(convertobjto3mf_sources
	"main.cpp"
	"job.cpp"
	"obj.cpp"
	"point3.cpp"
	"threemf.cpp"
)
set(convertobjto3mf_source_paths "")
foreach(f IN LISTS convertobjto3mf_sources)
	list(APPEND convertobjto3mf_source_paths ${CMAKE_CURRENT_SOURCE_DIR}/src/${f})
endforeach()

#The main target.
add_executable(convertobjto3mf ${convertobjto3mf_source_paths})
target_link_libraries(convertobjto3mf "${LIBZIP_LIBRARY}")
target_include_directories(convertobjto3mf PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(convertobjto3mf PRIVATE "${LIBZIP_INCLUDE_DIR}")