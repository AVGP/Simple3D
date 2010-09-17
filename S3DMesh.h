#ifndef _S3D_MESH_H_
#define _S3D_MESH_H_

#include <fstream>
#include <vector>
#include <iostream>

#include "S3DTriangle.h"

class S3DMesh : public S3DPrimitive
{
  public:
	S3DMesh(const char *file);
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void move(double dx,double dy,double dz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor = NULL);
	double getZ() { return center.z; };
  private:
	std::vector<S3DTriangle> polygons;
	S3DPoint center;
	void reorderTriangles();
};

#endif
