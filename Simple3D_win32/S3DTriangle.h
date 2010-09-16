/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#ifndef _S3DTriangle_
#define _S3DTriangle_

#include "S3DPoint.h"
#include "S3DPrimitive.h"

class S3DTriangle : public S3DPrimitive
{
	private:
		S3DPoint vertices[3];
		unsigned long color;
	public:
	  S3DTriangle(S3DPoint points[3]);
	  S3DTriangle(S3DPoint a, S3DPoint b, S3DPoint c);

	  void move(double dx,double dy,double dz);
	  void rotate(double rx,double ry,double rz);

	  void draw(S3DDevice *disp,S3DSurface window,S3DContext gc);
	  void setColor(unsigned long c);
	  unsigned long getColor();
	  S3DPoint *getPoints();
	  double getZ();
};

#endif
