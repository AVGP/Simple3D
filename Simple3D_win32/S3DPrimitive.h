/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#ifndef _S3DPrimitive_
#define _S3DPrimitive_

#include "global.h"
#include <cmath>
#include <iostream>

class S3DPrimitive
{
	protected:
		bool isFilled;
		unsigned long color;
	public:
		static unsigned int id_max;
		unsigned int id;

		virtual void draw(S3DDevice *disp,S3DSurface window,S3DContext gc) = 0;
		virtual void rotate(double rx,double ry,double rz) = 0;
		virtual void move(double dx, double dy, double dz) = 0;
		virtual double getZ() = 0;
//		void destroy();
		bool getFillMode() { return isFilled; };
		void setFillMode(bool fill) { isFilled = fill; };
		unsigned long getColor() { return color; };
		void setColor(unsigned long c);
};


#endif
