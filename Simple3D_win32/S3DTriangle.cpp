/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

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

void S3DTriangle::rotate(double rx,double ry,double rz)
{
//Um den Ursprung positionieren
	double dx = -1.0 * (vertices[0].x + vertices[1].x + vertices[2].x)/3.0;
	double dy = -1.0 * (vertices[0].y + vertices[1].y + vertices[2].y)/3.0;
	double dz = -1.0 * (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;

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

void S3DTriangle::draw(S3DDevice *disp, S3DSurface window, S3DContext gc)
{

	//XSetForeground(disp,gc,color);
    HPEN hPen = CreatePen(PS_SOLID,1,color);
	SelectObject(gc,hPen);
	for(int i=0;i<3;i++)
	{
	    int x_s  = (int)(PLANAR_DISTANCE*(vertices[i].x/vertices[i].z));
	    int y_s  = (int)(PLANAR_DISTANCE*(vertices[i].y/vertices[i].z));
	    int x_e = (int)(PLANAR_DISTANCE*(vertices[(i+1)%3].x/vertices[(i+1)%3].z));
	    int y_e = (int)(PLANAR_DISTANCE*(vertices[(i+1)%3].y/vertices[(i+1)%3].z));
		MoveToEx(gc,x_s,y_s,NULL);
		LineTo(gc,x_e,y_e);
	}

	if(isFilled)
	{
        HBRUSH hBr = CreateSolidBrush(color);
        SelectObject(gc,hBr);

        double dx = (vertices[0].x + vertices[1].x + vertices[2].x)/3.0;
        double dy = (vertices[0].y + vertices[1].y + vertices[2].y)/3.0;
        double dz = (vertices[0].z + vertices[1].z + vertices[2].z)/3.0;

        ExtFloodFill(gc,(int)PLANAR_DISTANCE*(dx/dz),(int)PLANAR_DISTANCE*(dy/dz),color,FLOODFILLBORDER);
//	    FloodFill(gc,vertices[0].x+10,vertices[0].y-10,RGB(255,0,0));//(int)(PLANAR_DISTANCE*(vertices[0].x+30/vertices[0].z)),(int)(PLANAR_DISTANCE*(vertices[0].y-30/vertices[0].z)),color);
		//XFillPolygon(disp,window,gc,p,3,Convex,CoordModeOrigin);
        DeleteObject(hBr);
	}
    DeleteObject(hPen);
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
