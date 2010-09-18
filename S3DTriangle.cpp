/**
* @file S3DTriangle.cpp Contains the implementation of S3DTriangle.
*/
#include "S3DTriangle.h"
#include <iostream>

/**
* @brief Constructor for the triangle.
* @param[in] points Array of three S3DPoints, marking the points,
*			 		the triangle is made of.
*
* Constructs a new instance of S3Triangle based upon the points
* supplied.
*/

S3DTriangle::S3DTriangle(S3DPoint points[3])
{
	isFilled = false;
	for(int i=0;i<3;i++) vertices[i] = points[i];
	id = ++id_max;
}

/**
* @brief Constructor for the triangle.
* @param[in] a First point, the triangle will be build upon.
* @param[in] b Second point, the triangle will be build upon.
* @param[in] c Third point, the triangle will be build upon.
*
* Constructs a new instance of S3Triangle based upon the points
* supplied.
*/
S3DTriangle::S3DTriangle(S3DPoint a, S3DPoint b, S3DPoint c)
{
	isFilled = false;
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}

/**
* @brief Returns an array of the points, the triangle is built upon.
* @return Array of three S3DPoints.
*/
S3DPoint *S3DTriangle::getPoints()
{
	return vertices;
}

/**
* @brief Moves the triangle (translates it) relative to its coordinates
* @param[in] dx The distance the triangle is moved in x-direction
* @param[in] dy The distance the triangle is moved in y-direction
* @param[in] dz The distance the triangle is moved in z-direction
*/
void S3DTriangle::move(double dx,double dy,double dz)
{
	for(int i=0;i<3;i++)
	{
	  vertices[i].move(dx,dy,dz);
	}
}

/**
* @brief Scales the triangle
* @param[in] fx Scaling factor along the x-axis
* @param[in] fy Scaling factor along the y-axis
* @param[in] fz Scaling factor along the z-axis
*
* This method scales the triangle according to the given factors internall,
* its also translated, to preserve its center's coordinates.
* @todo Currently this works for stand-alone triangles, but not for triangles
*		belonging to S3DMesh.
*/
void S3DTriangle::scale(double fx,double fy,double fz)
{
	double o_c[3], n_c[3]; //Saves data about center-point before and after scaling.
	double k_x = 0,k_y = 0,k_z = 0;

	o_c[0] = (vertices[0].x + vertices[1].x + vertices[2].x)/3.0;
	o_c[1] = (vertices[0].y + vertices[1].y + vertices[2].y)/3.0;
	o_c[2] = (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;

	for(int i=0;i<3;i++)
	{
		vertices[i].x *= fx;
		vertices[i].y *= fy;
		vertices[i].z *= fz;
	}
	
	n_c[0] = (vertices[0].x + vertices[1].x + vertices[2].x)/3.0;
	n_c[1] = (vertices[0].y + vertices[1].y + vertices[2].y)/3.0;
	n_c[2] = (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;

	move(-(n_c[0]-o_c[0]),-(n_c[1]-o_c[1]),-(n_c[2]-o_c[2]));
}

/**
* @brief Rotates the triangle around its center or another anchor point
* @param[in] rx The angle the triangle should be rotated around the x-axis
* @param[in] ry The angle the triangle should be rotated around the y-axis
* @param[in] rz The angle the triangle should be rotated around the z-axis
* @param[in] anchor Optional. The point the triangle should be rotated around,
* 					instead of its own center. 
*
* This function allows to rotate the triangle around all three axis in any angle.
* If no anchor-point is passed, the triangle will be rotated around its own center,
* else it will rotate around the given point.
*/
void S3DTriangle::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	double dx = 0,dy = 0,dz = 0;
	if(anchor != NULL)
	{
		//Positioning, to rotate around the anchor
		dx = -1.0 * anchor->x;
		dy = -1.0 * anchor->y;
		dz = -1.0 * anchor->z;
	}
	else
	{
		//Positioning, to rotate around the triangle's center
		dx = -1.0 * (vertices[0].x + vertices[1].x + vertices[2].x)/3.0;
		dy = -1.0 * (vertices[0].y + vertices[1].y + vertices[2].y)/3.0;
		dz = -1.0 * (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;
	}
	
	for(int i=0;i<3;i++)
	{
		vertices[i].x += dx;
		vertices[i].y += dy;
		vertices[i].z += dz;
	}
	
//Rotation
	//around z-axis
	double angle_z = rz * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_x = vertices[i].x;
	  double o_y = vertices[i].y;
	  vertices[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  vertices[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//around y-axis
	double angle_y = ry * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_x = vertices[i].x;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  vertices[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//around x-axis
	double angle_x = rx * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_y = vertices[i].y;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  vertices[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Move back to original position
	
	for(int i=0;i<3;i++)
	{
		vertices[i].x -= dx;
		vertices[i].y -= dy;
		vertices[i].z -= dz;
	}
}

/**
* @brief Draws the triangle
* @param[in] disp 	The display device, the line will be drawn to
* @param[in] window The surface, the line will be drawn to
* @param[in] gc		The context, the line will be drawn to
* @param zbuffer	Pointer to the S3DZBuffer-Instance of the Simple3D-Instance.
*
* Draws the triangle by drawing the triangles it consists of.
* This method does NOT contain platform-specific calls anymore, because it uses
* the underlying triangles to draw the triangle. The meaning and neccessity of disp,
* window and gc may vary between different platforms
*/
void S3DTriangle::draw(S3DDevice *disp, S3DSurface window, S3DContext gc,S3DZBuffer *zbuffer)
{  

	XSetForeground(disp,gc,color);
	for(int i=0;i<3;i++)
	{
		S3DLine l(S3DPoint(vertices[i].x,vertices[i].y,vertices[i].z),
				  S3DPoint(vertices[(i+1)%3].x,vertices[(i+1)%3].y,vertices[(i+1)%3].z));
		l.setColor(color);
		l.draw(disp,window,gc,zbuffer);
	}
		
	if(isFilled)
	{
		//Bounding box
		int l_x = PLANAR_DISTANCE*(vertices[0].x/(vertices[0].z/2.0));
		int l_y = PLANAR_DISTANCE*(vertices[0].y/(vertices[0].z/2.0));
		int r_x = l_x, r_y = l_y;
		for(int i=0;i<3;i++)
		{
			if(l_x > PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0))) l_x = PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0));
			if(r_x < PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0))) r_x = PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0));
	  
			if(l_y > PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0))) l_y = PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0));
			else if(r_y < PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0))) r_y = PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0));
		}
		int w = r_x - l_x + 1,h = r_y - l_y + 1;
		
	boundary = new bool[(w*h)];
	memset((void *)boundary,false,w*h);
	for(int i=0;i<3;i++)
	{
		//Rastering
		int x1 = (int)PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0));
		int x2 = (int)PLANAR_DISTANCE*(vertices[(i+1)%3].x/(vertices[(i+1)%3].z/2.0));

		int y1 = (int)PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0));
		int y2 = (int)PLANAR_DISTANCE*(vertices[(i+1)%3].y/(vertices[(i+1)%3].z/2.0));

		int dx  = x2-x1;
		int dy  = y2-y1;
		int err = abs(dx/2);
		
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
				x += ((dx > 0) ? 1 : -1);
				boundary[(x-l_x)+((y-l_y)*w)] = true;
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
				y += ((dy > 0) ? 1 : -1);

				boundary[(x-l_x)+((y-l_y)*w)] = true;
			}
		}
	}
//finished setting the boundaries.
		
		for(int y=0;y<h;y++)
		{
			int intersects = 0;
			int t_x = -2,f_x1 = -1,f_x2 = -1;
			for(int x=0;x<w;x++)
			{
				if(boundary[x+(y*w)] == true)
				{
					if(abs(x-t_x) > 1)
					{
						intersects++;
						if(intersects == 1) f_x1 = x;
						else if(intersects == 2) f_x2 = x;
					}
					t_x = x;
				}
			}
			if(intersects > 1)
			{
				S3DLine l(S3DPoint(l_x+f_x1,l_y+y,-10),
						  S3DPoint(l_x+f_x2,l_y+y,-10));
				l.setColor(color);
				l.setProjected(true);
				l.draw(disp,window,gc,zbuffer);
			}
		}
	}
	delete[] boundary;
}

/**
* @brief Sets the color the triangle is drawn in.
* @param[in] c Color (unsigned long as produced by the RGB-macro) that will be used to draw the triangle.
*/
void S3DTriangle::setColor(unsigned long c)
{
	color = c;
}

/**
* @brief Returns the color the triangle is drawn in.
* @return Color (unsigned long as produced by the RGB-macro) of the triangle.
*/
unsigned long S3DTriangle::getColor()
{
	return color;
}

/**
* @brief Returns the z-coordinate for the center of the triangle.
*
* This function is used for Z-Buffering and currently also for the painter's algorithm
* to determine the order in which the entities get drawn.
*/
double S3DTriangle::getZ()
{
	return (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;
	
}
