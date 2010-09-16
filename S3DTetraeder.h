#ifndef _S3DTetraeder_
#define _S3DTetraeder_

#include "global.h"
#include "S3DPrimitive.h"
#include "S3DPoint.h"

class S3DTetraeder : public S3DPrimitive
{
	private:
		S3DPoint vertices[4];
		unsigned long color;
	public:
		S3DTetraeder(S3DPoint points[4]);
		S3DTetraeder(S3DPoint a, S3DPoint b, S3DPoint c, S3DPoint d);
		
		void move(double dx, double dy, double dz);
		void rotate(double rx, double ry, double rz,S3DPoint *anchor = NULL);
		
		void draw(S3DDevice *d,S3DSurface w,S3DContext g);
		void setColor(unsigned long c);
		unsigned long getColor();
		S3DPoint *getPoints();
		double getZ();  
};

#endif
