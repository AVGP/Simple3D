#include "S3DMesh.h"

S3DMesh::S3DMesh(const char *file)
{
	std::ifstream stream;
	stream.open(file,std::ios::in|std::ios::binary);
	int polygon_count = 0,j=0;
	stream.read((char *)&polygon_count,sizeof(int));
	double x_min=0,x_max=0,y_min=0,y_max=0,z_min=0,z_max=0;
	
	while(!stream.eof() && j < polygon_count)
	{
		double coords[3];
		S3DPoint vertices[3];
		unsigned long color;
		for(int i=0;i<3;i++)
		{
			stream.read((char *)coords,sizeof(double)*3);
			vertices[i] = *(new S3DPoint(coords[0],coords[1],coords[2]));
			
			if(j == 0 && i == 0) //Init
			{
				x_min = coords[0];
				x_max = x_min;
				y_min = coords[1];
				y_max = y_min;
				z_min = coords[2];
				z_max = z_min;
			}
			else
			{
				if(coords[0] < x_min) 		x_min = coords[0];
				else if(coords[0] > x_max) 	x_max = coords[0];
				
				if(coords[1] < y_min) 		y_min = coords[1];
				else if(coords[1] > y_max) 	y_max = coords[1];
				
				if(coords[2] < z_min) 		z_min = coords[2];
				else if(coords[2] > z_max) 	z_max = coords[2];
			}
		}
		stream.read((char *)&color,sizeof(unsigned long));
		unsigned char c_r = (color >> 16) & 0xFF;
		unsigned char c_g = (color >> 8)  & 0xFF;
		unsigned char c_b = color & 0xFF;

		S3DTriangle t(vertices);
		t.setColor(color);
		t.setFillMode(true);
		polygons.push_back(t);
		j++;
	}
	center.x = x_min + ((x_max - x_min)/2.0);
	center.y = y_min + ((y_max - y_min)/2.0);
	center.z = z_min + ((z_max - z_min)/2.0);
	reorderTriangles();
}

void S3DMesh::draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer)
{
	for(int i=0;i<polygons.size();i++)
	{
		polygons[i].draw(disp,window,gc,zbuffer);
	}
}

void S3DMesh::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	for(int i=0;i<polygons.size();i++)
	{
		polygons[i].rotate(rx,ry,rz,&center);
	}
	reorderTriangles();
}

void S3DMesh::move(double dx,double dy,double dz)
{
	center.x += dx;
	center.y += dy;
	center.z += dz;

	for(int i=0;i<polygons.size();i++)
	{
		polygons[i].move(dx,dy,dz);
	}
}

void S3DMesh::reorderTriangles()
{
	std::vector<S3DTriangle> reordered;
	std::vector<S3DTriangle>::iterator max = polygons.begin();
	while(polygons.size() > 0)
	{
		double maxZ = -1*PLANAR_DISTANCE;
		std::vector<S3DTriangle>::iterator iter = polygons.begin();
		while(iter != polygons.end())
		{
			S3DTriangle p = *(iter);
			if(p.getZ() > maxZ)
			{
				maxZ = p.getZ();
				max  = iter;
			}
			++iter;
		}
		S3DTriangle m = *(max);
		reordered.push_back(m);
		polygons.erase(max);
	}
	polygons.swap(reordered);
}
