/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/
#ifndef _S3D_H_
#define _S3D_H_

#include <cmath>
#include <string>
#include <list>
#include "global.h"
#include "types.h"
#include "S3DTriangle.h"
#include "S3DRect.h"

#include <cstring>
#include <cstdlib>
#include <iostream>

class Simple3D
{
  private:
	S3DDevice *disp; 		// ???
	S3DSurface window;		// Window.
	S3DContext gc;			// Device Context

	std::list<S3DPrimitive *> entityList;

	unsigned long backColor;
	unsigned long foreColor;
	unsigned int width,height;
	unsigned char options; //Bitmaske für Optionen.
	int *zbuffer;
	S3DContext backbuffer;
	HBITMAP bitmapBackbuffer;

	//Win32
	static LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

  public:
	Simple3D(int width, int height,std::string title,int argc = 0, char **argv = 0);
	~Simple3D();

	void appendEntity(S3DPrimitive *p);
	void render();

	void setBackColor(S3DColor c);
	void setForeColor(S3DColor c);
	S3DEvent getEvent();
	void updateZBuffer();
	void reOrderEntities();
};

#endif
