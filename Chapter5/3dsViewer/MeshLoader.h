#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

struct Face {
	unsigned short a, b, c, flags;
};

class TextureMap {
public:
	std::string filename;
	float UVscale[2];
	float UVoffset[2];
	float rotation_angle;
	float rgbLumAlphaTint1[3];
	float rgbLumAlphaTint2[3];
	float rgbTint[3];	
	float blur_percent;
};

class Material {
public:
	Material(const std::string& n) {
		name = n;
		ambient[0]=0;
		ambient[1]=0;
		ambient[2]=0;
		diffuse[0]=0;
		diffuse[1]=0;
		diffuse[2]=0;
		specular[0]=0;
		specular[1]=0;
		specular[2]=0;
		shininess =0;
		shininess_strength =0; 
		transparency_percent=0;
		transparency_falloff=0;
		reflection_blur_percent=0;
		self_illum=0; 
	} 

	std::string name;	
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shininess;
	float shininess_strength; 
	float transparency_percent, transparency_falloff, reflection_blur_percent, self_illum;
	vector<TextureMap*> textureMaps; 
	vector<int> face_ids;
	vector<unsigned short> sub_indices; //list of indices sorted by material
};
 
class C3dsMesh {
public:
	C3dsMesh(const std::string& n="") {
		name = n;
		transform = glm::mat4(1);
		pMaterial = 0;
	}
	~C3dsMesh() {
		vertices.clear();
		uvs.clear();
		faces.clear(); 

	}
	 
	std::string name;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<Face> faces; //list of all faces of the mesh 
	//vector<Material*> materials;
	Material* pMaterial;
	glm::mat4 transform;
}; 

namespace MeshLoader
{ 
	bool Load3DS(const std::string& filename, std::vector<C3dsMesh*>& meshes, std::vector<Material*>& materials);

};

