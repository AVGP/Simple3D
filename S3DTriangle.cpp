#include "S3DTriangle.h"
#include <iostream>

S3DTriangle::S3DTriangle(S3DPoint points[3])
{
	isFilled = false;
	for(int i=0;i<3;i++) vertices[i] = points[i];
	id = ++id_max;
}
S3DTriangle::S3DTriangle(S3DPoint a, S3DPoint b, S3DPoint c)
{
	isFilled = false;
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}

S3DPoint *S3DTriangle::getPoints()
{
	return vertices;
}

void S3DTriangle::move(double dx,double dy,double dz)
{
	for(int i=0;i<3;i++)
	{
	  vertices[i].move(dx,dy,dz);
	}
}

void S3DTriangle::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	double dx = 0,dy = 0,dz = 0;
	if(anchor != NULL)
	{
		//Um den Ankerpunkt positionieren
		dx = -1.0 * anchor->x;
		dy = -1.0 * anchor->y;
		dz = -1.0 * anchor->z;
	}
	else
	{
		//Um den Ursprung positionieren
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
	
//Drehen
	//Um Z-Achse
	double angle_z = rz * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_x = vertices[i].x;
	  double o_y = vertices[i].y;
	  vertices[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  vertices[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//Um Y-Achse
	double angle_y = ry * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_x = vertices[i].x;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  vertices[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//Um X-Achse
	double angle_x = rx * PI/180.0;
	for(int i=0;i<3;i++)
	{
	  double o_y = vertices[i].y;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  vertices[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Zurückverschieben
	
	for(int i=0;i<3;i++)
	{
		vertices[i].x -= dx;
		vertices[i].y -= dy;
		vertices[i].z -= dz;
	}
}

void S3DTriangle::draw(S3DDevice *disp, S3DSurface window, S3DContext gc,S3DZBuffer *zbuffer)
{  

	XSetForeground(disp,gc,color);
	for(int i=0;i<3;i++)
	{
		//XDrawLine(disp,window,gc,PLANAR_DISTANCE*(vertices[i].x/(vertices[i].z/2.0)),PLANAR_DISTANCE*(vertices[i].y/(vertices[i].z/2.0)),PLANAR_DISTANCE*(vertices[(i+1)%3].x/(vertices[(i+1)%3].z/2.0)),PLANAR_DISTANCE*(vertices[(i+1)%3].y/(vertices[(i+1)%3].z/2.0)));
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
		
//TEST
	boundary = new bool[(w*h)];
	memset((void *)boundary,false,w*h);
	for(int i=0;i<3;i++)
	{
		//Rastern
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
				boundary[(x-l_x)+((y-l_y)*w)] = true;// !boundary[(x-l_x)+((y-l_y)*w)];
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

				boundary[(x-l_x)+((y-l_y)*w)] = true;// !boundary[(x-l_x)+((y-l_y)*w)];
			}
		}
	}
//Boundary-Bestimmung Ende
		
		for(int y=0;y<h;y++)
		{
			int intersects = 0;
			int t_x = -2,f_x1 = -1,f_x2 = -1;
			bool inside = false;
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
			if(intersects > 1) XDrawLine(disp,window,gc,l_x+f_x1,l_y+y,l_x+f_x2,l_y+y);
		}
	}
	delete[] boundary;
}

void S3DTriangle::setColor(unsigned long c)
{
	color = c;
}

unsigned long S3DTriangle::getColor()
{
	return color;
}

double S3DTriangle::getZ()
{
	return (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;
	
}
