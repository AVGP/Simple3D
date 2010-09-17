#ifndef _S3D_ZBUFFER_H_
#define _S3D_ZBUFFER_H_

#include "global.h"

class S3DZBuffer
{
	public:
	  S3DZBuffer(int w, int h)
	  {
		  buffer = new int[w*h];
		  width  = w;
		  height = h;
		  for(int i=0;i<w*h;i++) buffer[i] = PLANAR_DISTANCE*2;
	  };
	  int getPoint(int x,int y);
	  void setPoint(int x,int y,int z);
	  void clear();
	private:
	  int *buffer;
	  int width,height;
};
#endif
