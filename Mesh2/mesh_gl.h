#ifndef _MESH_GL_H_
#define _MESH_GL_H_

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>

class MeshGL
{
public:
	int nv;
	float *v;
	int nf;
	GLuint f[100000];
	GLfloat normals[100000];
	int vertexCount;
	int faceCount;
	int nn;
	std::string textureFName;
public:
	MeshGL();
	~MeshGL();
	bool loadPlyFile(std::string fileName);
	void draw();
};

#endif