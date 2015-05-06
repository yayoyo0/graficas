#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "mesh_gl.h"

MeshGL::MeshGL()
{

}

MeshGL::~MeshGL()
{
	delete this->v;
}

bool MeshGL::loadPlyFile(std::string fileName)
{
	bool flag = false;
	FILE *fp = fopen(fileName.c_str(), "r");
	if (fp == NULL)
	{
		std::cout << "File not found: " << fileName << std::endl;
	}
	else
	{
		flag = true;
		int mode = 0;
		char line[100];
		vertexCount = 0;
		faceCount = 0;
		while (fgets(line, 99, fp))
		{
			std::vector<char *> strToken;
			char * ptrToken = strtok(line, " ");
			while (ptrToken != NULL)
			{
				strToken.push_back(ptrToken);
				ptrToken = strtok(NULL, " ");
			}
			std::vector<char *>::iterator it = strToken.begin();
			if (mode == 0)
			{
				if (strncmp(*it, "element", strlen(*it) - 1) == 0)
				{
					it++;
					if (strncmp(*it, "vertex", strlen(*it) - 1) == 0)
					{
						it++;
						nv = atoi(*it);
						v = new float[nv * 3];
					}
					else if (strncmp(*it, "face", strlen(*it) - 1) == 0)
					{
						it++;
						nf = atoi(*it);
					}
				}
				else if (strncmp(*it, "end_header", strlen(*it) - 1) == 0)
				{
					mode = 1;
				}
			}
			else // mode = 1
			{
				if (vertexCount < nv * 3)
				{
					for (int i = 0; i < 3; i++)
					{
						v[vertexCount] = atof(*it);
						vertexCount++;
						it++;
					}
				}
				else
				{
					int nff = atoi(*it);
					f[faceCount] = nff;
					faceCount++;
					it++;
					for (int i = 0; i < nff; i++)
					{
						f[faceCount] = atoi(*it);
						faceCount++;
						it++;
					}
				}
			}
		}
		fclose(fp);
	}
	return flag;
}

void MeshGL::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v);
	//glNormalPointer(GL_FLOAT,0, normals);
	for (int i = 0; i < faceCount; i = i + f[i] + 1)
	{
		glDrawElements(GL_POLYGON, f[i], GL_UNSIGNED_INT, &f[i + 1]);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
}
