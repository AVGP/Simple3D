/**
* @file S3DZBuffer.h
* @brief Contains the definition of S3DZBuffer.
*/
#ifndef _S3D_ZBUFFER_H_
#define _S3D_ZBUFFER_H_

#include "global.h"

/**
* @class S3DZBuffer
* @brief This class is responsible for z-buffering.
*
* This class is the foundation of the z-buffering.
* Its used to determine, if a pixel should be drawn or not
* and is used in S3DLine and S3DPoint to check and update the
* z-buffer, before/after the actual drawing. Simple3D manages
* to keep the z-buffer clean and passes the reference to the
* entities.
*/
class S3DZBuffer
{
	public:
	  S3DZBuffer(int w, int h);
	  int getPoint(int x,int y);
	  void setPoint(int x,int y,int z);
	  void clear();
	private:
	  int *buffer;
	  int width,height;
};
#endif
