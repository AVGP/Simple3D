/**
* @file S3DZBuffer.h Contains implementation of the S3DZBuffer
*/
#include "S3DZBuffer.h"

/**
* @brief Default constructor.
* @param[in] w Width of the buffer (i.e. width of the screen)
* @param[in] h Height of the buffer (i.e. height of the screen)
*
* The constructor is called from within Simple3D on initialization.
* You should not call it yourself.
*/
S3DZBuffer::S3DZBuffer(int w, int h)
{
	buffer = new int[w*h];
	width  = w;
	height = h;
	for(int i=0;i<w*h;i++) buffer[i] = PLANAR_DISTANCE*2;
}

/**
* @brief Gets the z-buffer value for the given coordinates
* @param[in] x The x-coordinate of the point on screen
* @param[in] y The y-coordinate of the point on screen
* @return The z-Buffer value (i.e. the z-coordinate of the drawn point) for the coordinates (x,y)
*/
int S3DZBuffer::getPoint(int x,int y)
{
  
	if(x >= 0 && x < width && y >= 0 && y < height)
	  return buffer[x+(y*width)];
	else
	  return -1;
}

/**
* @brief Sets the z-buffer value for the given coordinates
* @param[in] x The x-coordinate of the point on screen
* @param[in] y The y-coordinate of the point on screen
* @param[in] z The z-value of the point on screen
*/
void S3DZBuffer::setPoint(int x,int y,int z)
{
	if(x >= 0 && x < width && y >= 0 && y < height)
	  buffer[x+(y*width)] = z;
	
}

/**
* @brief Clears the z-buffer.
*/
void S3DZBuffer::clear()
{
	for(int i=0;i<width*height;i++) buffer[i] = 2*PLANAR_DISTANCE;
}
