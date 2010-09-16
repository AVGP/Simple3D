#include "S3DTetraeder.h"

S3DTetraeder::S3DTetraeder(S3DPoint points[4])
{
	isFilled = false;
	color = RGB(255,255,255);
	for(int i=0;i<4;i++) vertices[i] = points[i];
}

S3DTetraeder::S3DTetraeder(S3DPoint a, S3DPoint b,S3DPoint c,S3DPoint d)
{
	isFilled = false;
	color = RGB(255,255,255);
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
	vertices[3] = d; 
}

void S3DTetraeder::move(double dx,double dy,double dz)
{
	for(int i=0;i<4;i++)
	{
		vertices[i].x += dx;
		vertices[i].y += dy;
		vertices[i].z += dz;
	}
}

void S3DTetraeder::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
//Um den Ursprung positionieren
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
		dx = -1.0 * (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x)/4.0;
		dy = -1.0 * (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y)/4.0;
		dz = -1.0 * (vertices[0].z + vertices[1].z + vertices[2].z + vertices[3].z)/4.0;
	}
	
	for(int i=0;i<4;i++)
	{
		vertices[i].x += dx;
		vertices[i].y += dy;
		vertices[i].z += dz;
	}
	
//Drehen
	//Um Z-Achse
	double angle_z = rz * PI/180.0;
	for(int i=0;i<4;i++)
	{
	  double o_x = vertices[i].x;
	  double o_y = vertices[i].y;
	  vertices[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  vertices[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//Um Y-Achse
	double angle_y = ry * PI/180.0;
	for(int i=0;i<4;i++)
	{
	  double o_x = vertices[i].x;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  vertices[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//Um X-Achse
	double angle_x = rx * PI/180.0;
	for(int i=0;i<4;i++)
	{
	  double o_y = vertices[i].y;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  vertices[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Zurückverschieben
	
	for(int i=0;i<4;i++)
	{
		vertices[i].x -= dx;
		vertices[i].y -= dy;
		vertices[i].z -= dz;
	}
}

void S3DTetraeder::draw(S3DDevice *d,S3DSurface w,S3DContext g)
{
	XSetForeground(d,g,color);
	for(int i=0;i<3;i++)
	{
		XDrawLine(d,w,g,
			PLANAR_DISTANCE*(vertices[i].x/vertices[i].z),
			PLANAR_DISTANCE*(vertices[i].y/vertices[i].z),
			PLANAR_DISTANCE*(vertices[(i+1)%3].x/vertices[(i+1)%3].z),
			PLANAR_DISTANCE*(vertices[(i+1)%3].y/vertices[(i+1)%3].z));
	}
	double x = PLANAR_DISTANCE*(vertices[3].x/vertices[3].z);
	double y = PLANAR_DISTANCE*(vertices[3].y/vertices[3].z);
	
	for(int i=0;i<3;i++)
	{ 
		XDrawLine(d,w,g,x,y,
			PLANAR_DISTANCE*(vertices[i].x/vertices[i].z),
			PLANAR_DISTANCE*(vertices[i].y/vertices[i].z));	  
	}
	
	
	if(isFilled)
	{
		XPoint p[4];
		for(int i=0;i<4;i++)
		{
			p[i].x = PLANAR_DISTANCE*(vertices[i].x/vertices[i].z);
			p[i].y = PLANAR_DISTANCE*(vertices[i].y/vertices[i].z);
		}
		XFillPolygon(d,w,g,p,4,Complex,CoordModeOrigin);
	}

}

void S3DTetraeder::setColor(unsigned long c)
{
	color = c;
}

unsigned long S3DTetraeder::getColor()
{
	return color;
}

S3DPoint *S3DTetraeder::getPoints()
{
	return vertices;
}

double S3DTetraeder::getZ()
{
	double sum = 0;
	for(int i=0;i<4;i++) sum += vertices[i].z;
	
	return (sum/4.0);
}