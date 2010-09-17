#ifndef _S3D_POINT_H_
#define _S3D_POINT_H_

#include "global.h"

class S3DPoint
{
	public:
		double x;
		double y;
		double z;
		S3DPoint();
		S3DPoint(double x,double y,double z);
		void move(double dx,double dy,double dz);
		void draw(Display *d,Window w,GC g);
		void rotate(double rx,double ry,double rz) {};
		double getZ();
};

#endif