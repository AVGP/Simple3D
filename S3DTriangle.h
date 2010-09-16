#ifndef _S3DTriangle_
#define _S3DTriangle_

#include "S3DPoint.h"
#include "S3DPrimitive.h"
#include "S3DZBuffer.h"

class S3DTriangle : public S3DPrimitive
{
  private:
	S3DPoint vertices[3];
	unsigned long color;
	bool *boundary;//[1000000];
  public:  
	S3DTriangle(S3DPoint points[3]);
	S3DTriangle(S3DPoint a, S3DPoint b, S3DPoint c);
	  
	void move(double dx,double dy,double dz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor=NULL);
	  
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void setColor(unsigned long c);
	unsigned long getColor();
	S3DPoint *getPoints();
	double getZ();
};

#endif