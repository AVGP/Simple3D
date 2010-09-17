#ifndef _S3D_LINE_H_
#define _S3D_LINE_H_

#include <iostream>
#include <cstdlib>
#include "S3DPrimitive.h"
#include "S3DPoint.h"

class S3DLine : public S3DPrimitive
{
  public:
	S3DLine(S3DPoint a, S3DPoint b);
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void move(double dx,double dy,double dz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor = NULL);
	double getZ() { return (ends[0].z < ends[1].z ? ends[0].z : ends[1].z)+(abs(ends[0].z-ends[1].z)/2.0); };
	void setColor(unsigned long c) { color = c; };
	unsigned long getColor() { return color; };
	void setProjected(bool p) { projected = p; };
	  
  private:
	S3DPoint ends[2];
	bool projected;
};

#endif
