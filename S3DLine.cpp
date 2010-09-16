#include "S3DLine.h"

S3DLine::S3DLine(S3DPoint a, S3DPoint b)
{
	ends[0] = a;
	ends[1] = b;
}

void S3DLine::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	double dx = 0,dy = 0,dz = 0;
	double cx,cy,cz;
	
	cx = (ends[0].x < ends[1].x ? ends[0].x : ends[1].x)+(abs(ends[0].x-ends[1].x)/2.0);
	cy = (ends[0].y < ends[1].y ? ends[0].y : ends[1].y)+(abs(ends[0].y-ends[1].y)/2.0);
	cz = (ends[0].z < ends[1].z ? ends[0].z : ends[1].z)+(abs(ends[0].z-ends[1].z)/2.0);
	
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
	
//Drehen
	//Um Z-Achse
	double angle_z = rz * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_x = ends[i].x;
	  double o_y = ends[i].y;
	  ends[i].x = cos(angle_z) * o_x - sin(angle_z) * o_y;
	  ends[i].y = sin(angle_z) * o_x + cos(angle_z) * o_y;
	}

	//Um Y-Achse
	double angle_y = ry * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_x = ends[i].x;
	  double o_z = ends[i].z;
	  ends[i].z = cos(angle_y) * o_z - sin(angle_y) * o_x;
	  ends[i].x = sin(angle_y) * o_z + cos(angle_y) * o_x;
	}

	//Um X-Achse
	double angle_x = rx * PI/180.0;
	for(int i=0;i<2;i++)
	{
	  double o_y = ends[i].y;
	  double o_z = ends[i].z;
	  ends[i].z = cos(angle_x) * o_z - sin(angle_x) * o_y;
	  ends[i].y = sin(angle_x) * o_z + cos(angle_x) * o_y;
	}

//Zurückverschieben
	
	for(int i=0;i<2;i++)
	{
		ends[i].x -= dx;
		ends[i].y -= dy;
		ends[i].z -= dz;
	}
}

void S3DLine::draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer)
{
/*
	int x1 = ends[0].x;//(int)PLANAR_DISTANCE*(ends[0].x/(ends[0].z/2.0));
	int x2 = ends[1].x;//(int)PLANAR_DISTANCE*(ends[1].x/(ends[1].z/2.0));

	int y1 = ends[0].y;//(int)PLANAR_DISTANCE*(ends[0].y/(ends[0].z/2.0));
	int y2 = ends[1].y;//(int)PLANAR_DISTANCE*(ends[1].y/(ends[1].z/2.0));

	int z1 = ends[0].z;
	int z2 = ends[1].z;
*/
	int x1 = (int)PLANAR_DISTANCE*(ends[0].x/(ends[0].z/2.0));
	int x2 = (int)PLANAR_DISTANCE*(ends[1].x/(ends[1].z/2.0));

	int y1 = (int)PLANAR_DISTANCE*(ends[0].y/(ends[0].z/2.0));
	int y2 = (int)PLANAR_DISTANCE*(ends[1].y/(ends[1].z/2.0));

	int z1 = ends[0].z;
	int z2 = ends[1].z;

//ORIGINAL

	int dx  = x2-x1;
	int dy  = y2-y1;
	int err = abs(dx/2);

	XSetForeground(disp,gc,color);
	if(zbuffer->getPoint(x1,y1) < (ends[0].z/2.0))
		XDrawPoint(disp,window,gc,x1,y1);
	if(zbuffer->getPoint(x2,y2) < (ends[1].z/2.0))
		XDrawPoint(disp,window,gc,x2,y2);
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
//			if(zbuffer->getPoint(x,y) < (ends[0].z/2.0))
				XDrawPoint(disp,window,gc,x,y);
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
			XDrawPoint(disp,window,gc,x,y);
			y += ((dy > 0) ? 1 : -1);
		}
	}

//TEST
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
//TESTENDE
*/
}
