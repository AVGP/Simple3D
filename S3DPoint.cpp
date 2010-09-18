/**
* @file S3DPoint.cpp
* @brief Contains the implementation of S3DPoint
*/
#include "S3DPoint.h"

/**
* @brief Default constructor.
* 
* Creates a new instance of S3DPoint with coordinates (0,0,0), so the origin.
*/
S3DPoint::S3DPoint()
{
	x=y=z=0;
}

/**
* @brief Mostly used constructor used for creating S3DPoints
* @param[in] px X-Coordinate of the point
* @param[in] py Y-Coordinate of the point
* @param[in] pz Z-Coordinate of the point
*
* Creates an new instance of a three-dimensional point with coordinates (x,y,z).
* Used in every primary to determine coordinates and used in projections.
*/
S3DPoint::S3DPoint(double px,double py,double pz)
{
	x=px;
	y=py;
	z=pz;
}

/**
* @brief Moves the point (translates it) relative to its coordinates
* @param[in] dx The distance the point is moved in x-direction
* @param[in] dy The distance the point is moved in y-direction
* @param[in] dz The distance the point is moved in z-direction
*/
void S3DPoint::move(double dx,double dy,double dz)
{
	x += dx;
	y += dy;
	z += dz;
}

/**
* @brief Draws the point
* @param[in] disp 	The display device, the line will be drawn to
* @param[in] window The surface, the line will be drawn to
* @param[in] gc		The context, the line will be drawn to
* @param zbuffer	Pointer to the S3DZBuffer-Instance of the Simple3D-Instance.
*
* Draws the point using platform-dependent methods. The meaning and neccessity
* of disp, window and gc may vary between different platforms
*/
void S3DPoint::draw(Display *d,Window w,GC g)
{
	XDrawPoint(d,w,g,PLANAR_DISTANCE*(x/z),PLANAR_DISTANCE*(y/z));
}

/**
* @brief Returns the z-coordinate for the point.
*
* This function is used for Z-Buffering and currently also for the painter's algorithm
* to determine the order in which the entities get drawn.
*/
double S3DPoint::getZ()
{
	return z;
}
