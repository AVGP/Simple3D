/**
* @file S3DLine.h
* @brief Contains the class-definition (and getter and setter) for S3DLine
*/
#ifndef _S3D_LINE_H_
#define _S3D_LINE_H_

#include "S3DPrimitive.h"
#include "S3DPoint.h"

/**
* @class S3DLine
* @brief Class for the line-primitive in S3D
* 
* This class implements three-dimensional lines as the basis of all other primitives in S3D
* The line is the only primitive that is drawn using platform-dependent functions, all superior
* primitives will use this class to draw themselves.
*/
class S3DLine : public S3DPrimitive
{
  public:
	S3DLine(S3DPoint a, S3DPoint b);
	void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer);
	void move(double dx,double dy,double dz);
	void scale(double fx,double fy,double fz);
	void rotate(double rx,double ry,double rz,S3DPoint *anchor = NULL);
	double getZ();
	void setColor(unsigned long c);
	unsigned long getColor();
	void setProjected(bool p);
	  
  private:
	S3DPoint ends[2];
	bool projected;
};

#endif
