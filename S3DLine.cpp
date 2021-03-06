/**
* @file S3DLine.cpp
* @brief Contains the implementation of the S3DLine-Primitive
*/
#include "S3DLine.h"

/**
* @brief Creates a line between two (3D-)Points
* @param[in] a First endpoint of the line
* @param[in] b Second endpoint of the line
*/
S3DLine::S3DLine(S3DPoint a, S3DPoint b)
{
	ends[0] = a;
	ends[1] = b;
	projected = false;
}

/**
* @brief Moves the line (translates it) relative to its coordinates
* @param[in] dx The distance the line is moved in x-direction
* @param[in] dy The distance the line is moved in y-direction
* @param[in] dz The distance the line is moved in z-direction
*/
void S3DLine::move(double dx,double dy,double dz)
{
	ends[0].x += dx;
	ends[0].y += dy;
	ends[0].z += dz;

	ends[1].x += dx;
	ends[1].y += dy;
	ends[1].z += dz;
}

/**
* @brief Scales the line
* @param[in] fx Scaling factor along the x-axis
* @param[in] fy Scaling factor along the y-axis
* @param[in] fz Scaling factor along the z-axis
*
* This method scales the line according to the given factors and translates it,
* to preserve its center's coordinates.
*/
void S3DLine::scale(double fx,double fy,double fz)
{
	for(int i=0;i<2;i++)
	{
		ends[i].x *= fx;
		ends[i].y *= fy;
		ends[i].z *= fz;
	}
	move(-(fx/2.0),-(fy/2.0),-(fz/2.0));
}

/**
* @brief Rotates the line around its center or another anchor point
* @param[in] rx The angle the line should be rotated around the x-axis
* @param[in] ry The angle the line should be rotated around the y-axis
* @param[in] rz The angle the line should be rotated around the z-axis
* @param[in] anchor Optional. The point the line should be rotated around,
* 					instead of its own center. 
*
* This function allows to rotate the line around all three axis in any angle.
* If no anchor-point is passed, the line will be rotated around its own center,
* else it will rotate around the given point.
*/
void S3DLine::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	double dx = 0,dy = 0,dz = 0;
	double cx,cy,cz;
	
	cx = (ends[0].x < ends[1].x ? ends[0].x : ends[1].x)+(abs(ends[0].x-ends[1].x)/2.0);
	cy = (ends[0].y < ends[1].y ? ends[0].y : ends[1].y)+(abs(ends[0].y-ends[1].y)/2.0);
	cz = (ends[0].z < ends[1].z ? ends[0].z : ends[1].z)+(abs(ends[0].z-ends[1].z)/2.0);
	
	if(anchor != NULL)
	{
		//positioning, so we rotate around the anchor-point
		dx = -1.0 * anchor->x;
		dy = -1.0 * anchor->y;
		dz = -1.0 * anchor->z;
	}
	else
	{
		//positioning, so we rotate around the center of the line
		dx = -1.0 * cx;
		dy = -1.0 * cy;
		dz = -1.0 * cz;
	}
	
	for(int i=0;i<2;i++)
	{
		ends[i].x += dx;
		ends[i].y += dy;
		ends[i].z += dz;
	}
	
//Rotation:
	//around z-axis
	double angle_z = rz * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_x = ends[i].x;
	  double o_y = ends[i].y;
	  ends[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  ends[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//around y-axis
	double angle_y = ry * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_x = ends[i].x;
	  double o_z = ends[i].z;
	  ends[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  ends[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//around x-axis
	double angle_x = rx * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_y = ends[i].y;
	  double o_z = ends[i].z;
	  ends[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  ends[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Move it back to its original position.
	
	for(int i=0;i<2;i++)
	{
		ends[i].x -= dx;
		ends[i].y -= dy;
		ends[i].z -= dz;
	}
}

/**
* @brief Draws the line
* @param[in] disp 	The display device, the line will be drawn to
* @param[in] window The surface, the line will be drawn to
* @param[in] gc		The context, the line will be drawn to
* @param zbuffer	Pointer to the S3DZBuffer-Instance of the Simple3D-Instance.
*
* This method is used to draw the line on screen, by using the platform-specific
* way of drawing points on some sort of screen. The meaning and neccessity of disp,
* window and gc may vary between different platforms
*/
void S3DLine::draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer)
{
	int x1,x2,y1,y2,z1,z2;
	//Are the coordinates in ends[] already projected or are they still 3D?
	if(projected)
	{
		x1 = ends[0].x;
		x2 = ends[1].x;

		y1 = ends[0].y;
		y2 = ends[1].y;
	}
	else
	{
		x1 = (int)PLANAR_DISTANCE*(ends[0].x/(ends[0].z/2.0));
		x2 = (int)PLANAR_DISTANCE*(ends[1].x/(ends[1].z/2.0));

		y1 = (int)PLANAR_DISTANCE*(ends[0].y/(ends[0].z/2.0));
		y2 = (int)PLANAR_DISTANCE*(ends[1].y/(ends[1].z/2.0));
	}

	z1 = ends[0].z;
	z2 = ends[1].z;

//This code works, but needs to be changed for z-buffering :(

	int dx  = x2-x1;
	int dy  = y2-y1;
	int err = abs(dx/2);

	XSetForeground(disp,gc,color);
	if(zbuffer->getPoint(x1,y1) > (ends[0].z/2.0))
	{
		XDrawPoint(disp,window,gc,x1,y1);
		zbuffer->setPoint(x1,y1,(ends[0].z/2.0));
	}
	if(zbuffer->getPoint(x2,y2) > (ends[1].z/2.0))
	{
		XDrawPoint(disp,window,gc,x2,y2);
		zbuffer->setPoint(x2,y2,(ends[0].z/2.0));
	}
	int y = y1,x = x1;

	if(abs(dx) > abs(dy) || dy == 0)
	{
		while(x != x2)
		{
			err -= abs(dy);
			if(err < 0)
			{
				y += ((dy > 0) ? 1 : -1);
				err += abs(dx);
			}
			if(zbuffer->getPoint(x,y) > (ends[0].z/2.0))
			{
				XDrawPoint(disp,window,gc,x,y);
				zbuffer->setPoint(x,y,(ends[0].z/2.0));
			}
			x += ((dx > 0) ? 1 : -1);
		}
	}
	else
	{
		while(y != y2)
		{
			err -= abs(dx);
			if(err < 0)
			{
				x += ((dx > 0) ? 1 : -1);
				err += abs(dy);
			}
			if(zbuffer->getPoint(x,y) > (ends[0].z/2.0))
			{
				XDrawPoint(disp,window,gc,x,y);
				zbuffer->setPoint(x,y,(ends[0].z/2.0));
			}
			y += ((dy > 0) ? 1 : -1);
		}
	}

//This is experimental for z-buffering. Not working at the moment!
/*
	int dx  = x2-x1;
	int dy  = y2-y1;
	int dz  = z2-z1;
	int err_1 = abs(dx/2), err_2 = abs(dz/2);

	XSetForeground(disp,gc,color);
	if(zbuffer->getPoint(x1,y1) < (ends[0].z/2.0))
		XDrawPoint(disp,window,gc,x1,y1);
	if(zbuffer->getPoint(x2,y2) < (ends[1].z/2.0))
		XDrawPoint(disp,window,gc,x2,y2);
	int y = y1,x = x1,z = z1;
	if((abs(dx) >= abs(dy) && abs(dx) >= abs(dz)) || dy == 0)
	{
		while(x != x2)
		{
			err_1 -= abs(dy);
			err_2 -= abs(dz);
			
			if(err_1 < 0)
			{
				y += ((dy > 0) ? 1 : -1);
				err_1 += abs(dx);
			}
			
			if(err_2 < 0)
			{
				z += ((dz > 0) ? 1 : -1);
				err_2 += abs(dz);
			}
			
			if(zbuffer->getPoint(x,y) >= (z/2.0))
			{
				XDrawPoint(disp,window,gc,x,y);//PLANAR_DISTANCE*(x/(z/2.0)),PLANAR_DISTANCE*(y/(z/2.0)));
				zbuffer->setPoint(x,y,(z/2.0));
			}
			x += ((dx > 0) ? 1 : -1);
		}
	}
	else if(abs(dy) >= abs(dz))
	{
		while(y != y2)
		{
			err_1 -= abs(dx);
			err_2 -= abs(dz);
			if(err_1 < 0)
			{
				x += ((dx > 0) ? 1 : -1);
				err_1 += abs(dy);
			}
			
			if(err_2 < 0)
			{
				z += ((dz > 0) ? 1 : -1);
				err_2 += abs(dz);
			}
			if(zbuffer->getPoint(x,y) >= (z/2.0))
			{
				zbuffer->setPoint(x,y,(z/2.0));
				XDrawPoint(disp,window,gc,x,y);//PLANAR_DISTANCE*(x/(z/2.0)),PLANAR_DISTANCE*(y/(z/2.0)));
			}
			y += ((dy > 0) ? 1 : -1);
		}
	  
	}
	else
	{
		while(z != z2)
		{
			err_1 -= abs(dx);
			err_2 -= abs(dy);
			if(err_1 < 0)
			{
				x += ((dx > 0) ? 1 : -1);
				err_1 += abs(dy);
			}

			if(err_2 < 0)
			{
				y += ((dy > 0) ? 1 : -1);
				err_2 += abs(dx);
			}

			if(zbuffer->getPoint(x,y) >= (z/2.0))
			{
				zbuffer->setPoint(x,y,(z/2.0));
				XDrawPoint(disp,window,gc,x,y);//PLANAR_DISTANCE*(x/(z/2.0)),PLANAR_DISTANCE*(y/(z/2.0)));
			}
			z += ((dz > 0) ? 1 : -1);
		}
	}
//End of experimental code. Phew. We made it through alive!
*/
}

/**
* @brief Returns the z-coordinate for the center of the line.
*
* This function is used for Z-Buffering and currently also for the painter's algorithm
* to determine the order in which the entities get drawn.
*/
double S3DLine::getZ()
{
	return (ends[0].z < ends[1].z ? ends[0].z : ends[1].z)+(abs(ends[0].z-ends[1].z)/2.0);
}

/**
* @brief Sets the color of the line
* @param[in] c The color (as unsigned long, as produced by the RGB-macro) the line should be drawn in.
*/
void S3DLine::setColor(unsigned long c)
{
	color = c;
}

/**
* @brief Returns the color of the line.
* @return The color (as unsigned long, as produced by the RGB-macro) the line is drawn in.
*/
unsigned long S3DLine::getColor()
{
	return color;
}

/**
* @brief Setting the coordinate mode to projected coordinates.
* @param[in] p Set this to "true", if you used projected 2D-coordinates in the constructor, else set this to false.
*
* The draw-Method usually projects the three-dimensional coordinates to 2D screen-coordinates. This can be suppressed
* by setting the coordinate mode to projected via calling setProjected(true).
*/
void S3DLine::setProjected(bool p)
{
	projected = p;
}
