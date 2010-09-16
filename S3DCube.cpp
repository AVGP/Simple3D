#include "S3DCube.h"

S3DCube::S3DCube(S3DRect *s[6])
{
	for(int i=0;i<6;i++) sides[i] = s[i];
}

S3DCube::S3DCube(S3DPoint edges[8])
{
	for(int i=0;i<8;i++) vertices[i] = edges[i];
	
	sides[0] = new S3DRect(edges[0],edges[1],edges[2],edges[3]);
	sides[1] = new S3DRect(edges[0],edges[4],edges[7],edges[3]);
	sides[2] = new S3DRect(edges[1],edges[5],edges[6],edges[2]);
	sides[3] = new S3DRect(edges[4],edges[5],edges[6],edges[7]);
	sides[4] = new S3DRect(edges[0],edges[1],edges[5],edges[4]);
	sides[5] = new S3DRect(edges[3],edges[2],edges[6],edges[7]);
}

S3DCube::S3DCube(S3DPoint a,S3DPoint b,S3DPoint c,S3DPoint d,S3DPoint e,S3DPoint f,S3DPoint g,S3DPoint h)
{
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
	vertices[3] = d;
	vertices[4] = e;
	vertices[5] = f;
	vertices[6] = g;
	vertices[7] = h;
	
	sides[0] = new S3DRect(vertices[0],vertices[1],vertices[2],vertices[3]);
	sides[1] = new S3DRect(vertices[0],vertices[4],vertices[7],vertices[3]);
	sides[2] = new S3DRect(vertices[1],vertices[5],vertices[6],vertices[2]);
	sides[3] = new S3DRect(vertices[4],vertices[5],vertices[6],vertices[7]);
	sides[4] = new S3DRect(vertices[0],vertices[1],vertices[5],vertices[4]);
	sides[5] = new S3DRect(vertices[3],vertices[2],vertices[6],vertices[7]);
}


void S3DCube::move(double dx,double dy,double dz)
{
	for(int i=0;i<8;i++) vertices[i].move(dx,dy,dz);
	for(int i=0;i<6;i++) sides[i]->move(dx,dy,dz);
}

void S3DCube::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
  //Um den Ursprung positionieren
	double sx = 0;
	double sy = 0;
	double sz = 0;
	
	for(int i=0;i<8;i++)
	{
		sx += vertices[i].x;
		sy += vertices[i].y;
		sz += vertices[i].z;
	}
	
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
		dx = -1*(sx / 8.0);
		dy = -1*(sy / 8.0);
		dz = -1*(sz / 8.0);
	}
	
	for(int i=0;i<8;i++)
	{
		vertices[i].x += dx;
		vertices[i].y += dy;
		vertices[i].z += dz;
	}
	
//Drehen
	//Um Z-Achse
	double angle_z = rz * PI/180.0;
	for(int i=0;i<8;i++)
	{
	  double o_x = vertices[i].x;
	  double o_y = vertices[i].y;
	  vertices[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  vertices[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//Um Y-Achse
	double angle_y = ry * PI/180.0;
	for(int i=0;i<8;i++)
	{
	  double o_x = vertices[i].x;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  vertices[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//Um X-Achse
	double angle_x = rx * PI/180.0;
	for(int i=0;i<8;i++)
	{
	  double o_y = vertices[i].y;
	  double o_z = vertices[i].z;
	  vertices[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  vertices[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Zurückverschieben
	
	for(int i=0;i<8;i++)
	{
		vertices[i].x -= dx;
		vertices[i].y -= dy;
		vertices[i].z -= dz;
	}  
	
	sides[0] = new S3DRect(vertices[0],vertices[1],vertices[2],vertices[3]);
	sides[1] = new S3DRect(vertices[0],vertices[4],vertices[7],vertices[3]);
	sides[2] = new S3DRect(vertices[1],vertices[5],vertices[6],vertices[2]);
	sides[3] = new S3DRect(vertices[4],vertices[5],vertices[6],vertices[7]);
	sides[4] = new S3DRect(vertices[0],vertices[1],vertices[5],vertices[4]);
	sides[5] = new S3DRect(vertices[3],vertices[2],vertices[6],vertices[7]);
	for(int i=0;i<6;i++)
	{
		sides[i]->setColor(color);
		sides[i]->setFillMode(isFilled);
	}
}

void S3DCube::draw(S3DDevice *d,S3DSurface w, S3DContext g)
{
	for(int i=0;i<6;i++) sides[i]->draw(d,w,g);
}

void S3DCube::setColor(unsigned long c)
{
	color = c;
}

unsigned long S3DCube::getColor()
{
	return color;
}

double S3DCube::getZ()
{
	double sum = 0;
	for(int i=0;i<8;i++) sum += vertices[i].z;
	return sum/8.0;
}
