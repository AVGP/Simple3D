/**
* @file S3DMesh.cpp Contains the code for loading an entity from a file and use it. 
*/
#include "S3DMesh.h"

/**
* @brief Constructor for the Mesh, loads data from a file.
* @param[in] file The filename of the file containing the data
*
* Constructs a new instance of S3DMesh and loads data from a file to
* build a series of triangles, ready to be rendered on screen.
*/
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

/**
* @brief Draws the mesh
* @param[in] disp 	The display device, the line will be drawn to
* @param[in] window The surface, the line will be drawn to
* @param[in] gc		The context, the line will be drawn to
* @param zbuffer	Pointer to the S3DZBuffer-Instance of the Simple3D-Instance.
*
* Draws the mesh by drawing the triangles it consists of.
* This method does NOT contain platform-specific calls anymore, because it uses
* the underlying triangles to draw the mesh. The meaning and neccessity of disp,
* window and gc may vary between different platforms
*/
void S3DMesh::draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer)
{
	for(unsigned int i=0;i<polygons.size();i++)
	{
		polygons[i].draw(disp,window,gc,zbuffer);
	}
}

/**
* @brief Rotates the mesh around its center or another anchor point
* @param[in] rx The angle the mesh should be rotated around the x-axis
* @param[in] ry The angle the mesh should be rotated around the y-axis
* @param[in] rz The angle the mesh should be rotated around the z-axis
* @param[in] anchor Optional. The point the mesh should be rotated around,
* 					instead of its own center. 
*
* This function allows to rotate the mesh around all three axis in any angle.
* If no anchor-point is passed, the mesh will be rotated around its own center,
* else it will rotate around the given point.
*/
void S3DMesh::rotate(double rx,double ry,double rz,S3DPoint *anchor)
{
	for(unsigned int i=0;i<polygons.size();i++)
	{
		polygons[i].rotate(rx,ry,rz,&center);
	}
	reorderTriangles();
}

/**
* @brief Scales the mesh
* @param[in] fx Scaling factor along the x-axis
* @param[in] fy Scaling factor along the y-axis
* @param[in] fz Scaling factor along the z-axis
*
* This method scales the mesh according to the given factors.
* Internal its also translated to preserve its center's coordinates.
* @todo Fix this thing. Its fucked up yet.
*/
void S3DMesh::scale(double fx,double fy,double fz)
{
	int z_min = 0,z_max = 0;
	for(unsigned int i=0;i<polygons.size();i++)
	{
		polygons[i].scale(fx,fy,fz);
	}
}

/**
* @brief Moves the mesh (translates it) relative to its coordinates
* @param[in] dx The distance the mesh is moved in x-direction
* @param[in] dy The distance the mesh is moved in y-direction
* @param[in] dz The distance the mesh is moved in z-direction
*/
void S3DMesh::move(double dx,double dy,double dz)
{
	center.x += dx;
	center.y += dy;
	center.z += dz;

	for(unsigned int i=0;i<polygons.size();i++)
	{
		polygons[i].move(dx,dy,dz);
	}
}

/**
* @brief Reorders the triangles of the mesh for correct drawing
* 
* This function only needs to be called from methods changing the
* underlying triangles in any way, to ensure the mesh is displayed
* correctly.
*/
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

/**
* @brief Returns the z-coordinate for the center of the mesh.
*
* This function is used for Z-Buffering and currently also for the painter's algorithm
* to determine the order in which the entities get drawn.
*/
double S3DMesh::getZ()
{
	return center.z;
};

