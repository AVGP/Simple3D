/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#include "S3DPoint.h"

S3DPoint::S3DPoint()
{
	x=y=z=0;
}

S3DPoint::S3DPoint(double px,double py,double pz)
{
	x=px;
	y=py;
	z=pz;
}

void S3DPoint::move(double dx,double dy,double dz)
{
	x += dx;
	y += dy;
	z += dz;
}

void S3DPoint::draw(S3DDevice *d,S3DSurface w,S3DContext g)
{
	SetPixel(g,PLANAR_DISTANCE*(x/z),PLANAR_DISTANCE*(y/z),color);
}

double S3DPoint::getZ()
{
	return z;
}
