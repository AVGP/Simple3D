/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#ifndef _S3DRect_
#define _S3DRect_

#include "S3DPoint.h"
#include "S3DPrimitive.h"

class S3DRect : public S3DPrimitive
{
	private:
		S3DPoint vertices[4];
		unsigned long color;
	public:
		S3DRect(S3DPoint points[4]);
		S3DRect(S3DPoint a, S3DPoint b, S3DPoint c, S3DPoint d);

		void move(double dx, double dy, double dz);
		void rotate(double rx, double ry, double rz);

		void draw(S3DDevice *d,S3DSurface w,S3DContext g);
		void setColor(unsigned long c);
		unsigned long getColor();
		S3DPoint *getPoints();
		double getZ();

};

#endif
