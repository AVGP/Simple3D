/**
* @file Simple3D.h
* @brief Contains the engine's main class definitions.
*/
#ifndef _S3D_H_
#define _S3D_H_

#include <string>
#include <list>
#include "global.h"
#include "S3DZBuffer.h"
/*
#include "S3DTriangle.h"
#include "S3DRect.h"
#include "S3DCube.h"
#include "S3DTetraeder.h"
*/
#include "S3DMesh.h"
#include "S3DLine.h"




/**
* @class Simple3D
* @brief This class is the main class of the engine.
*
* You need to create an instance of this class to use the engine.
* It manages the platform-specific things on initialization, handles events
* and renders primitives to screen.
*/
class Simple3D
{
  private:
	int screen; 			//X11 Screen-Handle
	S3DDevice *disp; 		//X11 Display Instance
	S3DSurface window;		//X11 Window
	S3DContext gc;			//X11 Graphic Context
	
	std::list<S3DPrimitive *> entityList;
	
	unsigned long backColor;
	unsigned long foreColor;
	unsigned int width,height;
	unsigned char options; //Bitmask for options. See types.h for possible values.
	S3DBitmap backbuffer;
	S3DZBuffer *zbuffer;
	
  public:
	Simple3D(int width, int height,std::string title,int argc = 0, char **argv = 0);
	~Simple3D();
	
	void appendEntity(S3DPrimitive *p);
	void render();
	
	void setBackColor(S3DColor c);
	void setForeColor(S3DColor c);
	S3DEvent getEvent();
	void reOrderEntities();

};

#endif

