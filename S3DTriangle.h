/**
* @file S3DTriangle.h
* @brief Contains the definition for S3DTriangle.
*/
#ifndef _S3D_TRIANGLE_H_
#define _S3D_TRIANGLE_H_

#include "S3DPoint.h"
#include "S3DPrimitive.h"
#include "S3DLine.h"
#include "S3DZBuffer.h"

/**
* @class S3DTriangle
* @brief This is the main primitive actually used.
*
* This is the mostly used primitive, because all complex primitives
* base upon triangles. It is platform-independent, because all drawing
* is done using S3DLine.
*/
class S3DTriangle : public S3DPrimitive
{
  private:
	S3DPoint vertices[3];
	unsigned long color;
	bool *boundary;
  public:  
	S3DTriangle(S3DPoint points[3]);
	S3DTriangle(S3DPoint a, S3DPoint b, S3DPoint c);
	  
	void move(double dx,double dy,double dz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor=NULL);
	void scale(double fx,double fy,double fz,bool correction = true);
	  
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void setColor(unsigned long c);
	unsigned long getColor();
	S3DPoint *getPoints();
	double getZ();
};

#endif