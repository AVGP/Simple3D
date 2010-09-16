/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#ifndef _S3DPoint_
#define _S3DPoint_

#include "global.h"
#include "S3DPrimitive.h"

class S3DPoint : public S3DPrimitive
{
	public:
		double x;
		double y;
		double z;
		S3DPoint();
		S3DPoint(double x,double y,double z);
		void move(double dx,double dy,double dz);
		void draw(S3DDevice *d,S3DSurface w,S3DContext g);
		void rotate(double rx,double ry,double rz) {};
		double getZ();
};

#endif
