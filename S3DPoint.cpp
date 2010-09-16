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

void S3DPoint::draw(Display *d,Window w,GC g)
{
	XDrawPoint(d,w,g,PLANAR_DISTANCE*(x/z),PLANAR_DISTANCE*(y/z));
}

double S3DPoint::getZ()
{
	return z;
}
