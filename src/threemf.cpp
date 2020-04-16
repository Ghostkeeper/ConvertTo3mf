/*
 * Command line application to convert models to 3MF.
 * Copyright (C) 2020 Ghostkeeper
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for details.
 * You should have received a copy of the GNU Affero General Public License along with this library. If not, see <https://gnu.org/licenses/>.
 */

#include <cstdio> //To remove any existing file before writing the new one.
#include <unordered_map> //To make vertices unique and track their indices.

#include "threemf.hpp"

namespace convertobjto3mf {

void ThreeMF::export_to_file(const std::string& filename, const Model& model) {
	ThreeMF threemf;
	threemf.fill_from_model(model);
	std::remove(filename.c_str()); //Remove any old archive if one exists.
	threemf.write(filename);
}

void ThreeMF::fill_from_model(const Model& model) {
	for(const Mesh& mesh : model.meshes) {
		std::unordered_map<Point3, size_t> vertex_to_index; //For each unique vertex, tracks the index within the vertex list.
		vertex_to_index.reserve(10000); //It's unknown how many unique vertices there will be and the vertices are spread around many tiny vectors, so just guess at 10k to start with.
		vertices.emplace_back();
		std::vector<Point3>& mesh_vertices = vertices.back();
		mesh_vertices.reserve(10000);
		triangles.emplace_back();
		std::vector<std::array<size_t, 3>>& mesh_triangles = triangles.back();
		mesh_triangles.reserve(mesh.faces.size()); //Would be correct if all faces are triangles. If not, it'll need to reserve more, but for most models this would be fine.

		for(const Face& face : mesh.faces) {
			//Each face is a triangle fan. We need to convert this into individual triangles.
			if(face.vertices.size() < 3) { //Not enough vertices to form a triangle. Lines and points are not saved.
				continue;
			}

			const Point3 first = face.vertices[0]; //As per the triangle fan, the first vertex is always repeated for each triangle.
			if(vertex_to_index.find(first) == vertex_to_index.end()) { //Not yet in our mesh. Need to create an index and store it in the vertex list.
				vertex_to_index.emplace(first, mesh_vertices.size());
				mesh_vertices.push_back(first);
			}
			Point3 last = face.vertices[1]; //As per the triangle fan, the last vertex is repeated for the next triangle.
			if(vertex_to_index.find(last) == vertex_to_index.end()) {
				vertex_to_index.emplace(last, mesh_vertices.size());
				mesh_vertices.push_back(last);
			}
			for(size_t i = 2; i < face.vertices.size(); ++i) {
				const Point3 vertex = face.vertices[i];
				if(vertex_to_index.find(vertex) == vertex_to_index.end()) {
					vertex_to_index.emplace(vertex, mesh_vertices.size());
					mesh_vertices.push_back(vertex);
				}
				std::array<size_t, 3> triangle = {vertex_to_index[first], vertex_to_index[last], vertex_to_index[vertex]};
				mesh_triangles.push_back(triangle);
				last = vertex; //The new last vertex.
			}
		}
	}
}

void ThreeMF::write(const std::string& filename) const {
	int ziperror = 0;
	zip_t* archive = zip_open(filename.c_str(), ZIP_CREATE, &ziperror);

	//Writing [Content_Types].xml.
	std::string content_types_data(u8"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
			"<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\" />"
			"<Default Extension=\"model\" ContentType=\"application/vnd.ms-package.3dmanufacturing-3dmodel+xml\" />"
		"</Types>");
	constexpr int no_free_after_use = false;
	zip_source_t* content_types = zip_source_buffer(archive, content_types_data.c_str(), content_types_data.length(), no_free_after_use);
	zip_file_add(archive, u8"[Content_Types].xml", content_types, ZIP_FL_ENC_UTF_8);

	//Writing rels.
	zip_dir_add(archive, u8"_rels", ZIP_FL_ENC_UTF_8);
	std::string rels_data(u8"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
		"<Relationship Target=\"/3D/3dmodel.model\" Id=\"rel_3dmodel\" Type=\"http://schemas.microsoft.com/3dmanufacturing/2013/01/3dmodel\" />"
	"</Relationships>");
	zip_source_t* rels = zip_source_buffer(archive, rels_data.c_str(), rels_data.length(), no_free_after_use);
	zip_file_add(archive, u8"_rels/.rels", rels, ZIP_FL_ENC_UTF_8);

	zip_close(archive);
}

}