#include "S3DZBuffer.h"

int S3DZBuffer::getPoint(int x,int y)
{
  /*
	if(x >= 0 && x < width && y >= 0 && y < height)
	  return buffer[x+(y*width)];
	else
	  return -1;
	*/
	return 20000;
}

void S3DZBuffer::setPoint(int x,int y,int z)
{/*
	if(x >= 0 && x < width && y >= 0 && y < height)
	  buffer[x+(y*width)] = z;
	*/
}

void S3DZBuffer::clear()
{
	//for(int i=0;i<width*height;i++) buffer[i] = 20000;
}
