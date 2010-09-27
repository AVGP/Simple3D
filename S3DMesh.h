/**
* @file S3DMesh.h
* @brief Contains declarations for S3DMesh
*/
#ifndef _S3D_MESH_H_
#define _S3D_MESH_H_

#include <fstream>
#include <vector>

#include "S3DTriangle.h"

/**
* @class S3DMesh
* @brief This class is used to load a collection of triangles to use it as an entity.
*
* This class allows to load a collection of triangles from a file to get a complex entity.
*/
class S3DMesh : public S3DPrimitive
{
  public:
	S3DMesh(const char *file);
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void move(double dx,double dy,double dz);
	void scale(double fx,double fy,double fz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor = NULL);
	double getZ();
  private:
	std::vector<S3DTriangle> polygons;
	S3DPoint center;
	void reorderTriangles();
};

#endif

