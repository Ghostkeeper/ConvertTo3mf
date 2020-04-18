Convert To 3MF
====
This is a simple command-line application that converts 3D models to the 3D Manufacturing Format, otherwise known as 3MF.

Installation
----
As there is no stable release for this application yet, the only way to install this is to compile the application yourself.

Compilation
----
In order to compile this application, you'll need the following dependencies:
* A C++ compiler. I've tested this only on GCC version 9.2.1 so far, but there are no weird compiler-specific quirks in this code as far as I know.
* The [CMake](https://cmake.org) build system.
* [libzip](https://libzip.org), a library to create zip archives. This library needs to be installed on your computer.

Compilation is a very basic CMake workflow. To compile the application, you need to navigate a terminal to the source folder and execute the following commands.

```
mkdir build
cd build
cmake ..
make
```

This will create the executable in the new `build` directory.

Usage
----
You call ConvertTo3mf in the following manner:

```
convertto3mf filename [--output=output_filename]
```

Required parameters:
* `filename`: The file containing a 3D model to convert to 3MF.

Optional parameters:
* `--output=output_filename`: Store the resulting 3MF file in the specified location. By default, the result will be stored in the same location as the input file, but with the file extension changed to .3mf.

Support
----
This application currently supports the following input model formats:
* Wavefront OBJ (faces, vertices).
* Binary STL (triangles, vertices).
* ASCII STL (multiple meshes, faces, vertices).

The application will automatically detect which file type is contained in the file, even if the extension is incorrect.

The 3MF features supported are:
* Content types.
* Relationships.
* Multiple meshes in one build.
* Meshes with indexed vertices.