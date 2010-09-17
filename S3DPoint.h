/**
* @file S3DPoint.h Contains definitions of S3DPoint.
*/
#ifndef _S3D_POINT_H_
#define _S3D_POINT_H_

#include "global.h"
/**
* @class S3DPoint
* @brief This class is used for representing 3d-coordinates.
*
* This class is a representation of a point in 3D-space,
* thus a coordinate-triplet (x,y,z), that can be drawn
* though its not a primitive itself.
*/
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