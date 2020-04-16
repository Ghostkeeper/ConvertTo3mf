#Command line application to convert models to 3MF.
#Copyright (C) 2020 Ghostkeeper
#This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
#You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.

#This script finds libzip on your computer and figures out what version it is.
#
#The output of this script is the following variables:
# - LIBZIP_INCLUDE_DIR: The include directory for libzip.
# - LIBZIP_LIBRARY: A path to the library of libzip.
# - LIBZIP_VERSION_STRING: The full version string of libzip.
# - LIBZIP_VERSION_MAJOR: Major version number.
# - LIBZIP_VERSION_MINOR: Minor version number.
# - LIBZIP_VERSION_PATCH: Patch version number.

find_package(PkgConfig) #To easily find files on your computer.

#First try with packageconfig to get a beginning of an idea where to search.
pkg_check_modules(PC_LIBZIP QUIET libzip)

find_path(LIBZIP_INCLUDE_DIR NAMES zip.h HINTS ${PC_LIBZIP_INCLUDE_DIRS})
find_library(LIBZIP_LIBRARY NAMES zip)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBZIP DEFAULT_MSG
	LIBZIP_LIBRARY LIBZIP_INCLUDE_DIR)

#Find the version number from zipconf.h
set(LIBZIP_VERSION_MAJOR 0)
set(LIBZIP_VERSION_MINOR 0)
set(LIBZIP_VERSION_PATCH 0)
if(EXISTS "${LIBZIP_INCLUDE_DIR}/zipconf.h")
	file(READ "${LIBZIP_INCLUDE_DIR}/zipconf.h" _libzip_conf)
	if(_libzip_conf)
		string(REGEX REPLACE ".*#define LIBZIP_VERSION \"([0-9]+)\.([0-9]+)\.([0-9]+)\".*" "\\1" LIBZIP_VERSION_MAJOR "${_libzip_conf}")
		string(REGEX REPLACE ".*#define LIBZIP_VERSION \"([0-9]+)\.([0-9]+)\.([0-9]+)\".*" "\\2" LIBZIP_VERSION_MINOR "${_libzip_conf}")
		string(REGEX REPLACE ".*#define LIBZIP_VERSION \"([0-9]+)\.([0-9]+)\.([0-9]+)\".*" "\\3" LIBZIP_VERSION_PATCH "${_libzip_conf}")
	endif()
	unset(_libzip_conf)
endif()
set(LIBZIP_VERSION_STRING ${LIBZIP_VERSION_MAJOR}.${LIBZIP_VERSION_MINOR}.${LIBZIP_VERSION_PATCH})