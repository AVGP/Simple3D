#ifndef _S3D_Cube_
#define _S3D_Cube_

#include "global.h"
#include "S3DPrimitive.h"
#include "S3DRect.h"

class S3DCube : public S3DPrimitive
{
	private:
		S3DRect *sides[6];
		unsigned long color;
		S3DPoint vertices[8];
	public:
		S3DCube(S3DRect *s[6]);
		S3DCube(S3DPoint edges[8]);
		S3DCube(S3DPoint a,S3DPoint b,S3DPoint c,S3DPoint d,S3DPoint e,S3DPoint f,S3DPoint g,S3DPoint h);

		void move(double dx, double dy, double dz);
		void rotate(double rx, double ry, double rz,S3DPoint *anchor = NULL);
	
		void draw(S3DDevice *d,S3DSurface w,S3DContext g);
		void setColor(unsigned long c);
		unsigned long getColor();
		double getZ();

};

#endif
