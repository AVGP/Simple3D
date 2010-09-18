/**
* @file S3DPrimitive.h
* @brief Contains the definition of S3DPrimitive
*/
#ifndef _S3DPrimitive_
#define _S3DPrimitive_

#include <vector>
#include "global.h"
#include "S3DPoint.h"
#include "S3DZBuffer.h"

/**
* @class S3DPrimitive
* @brief This class is the base of all primitives in S3D.
*
* This class is the base-class for ALL primitives in S3D.
* It contains the virtual methods, derived primitives need
* to implement. Its the main interface for primitives.
*/
class S3DPrimitive
{
	protected:
		bool isFilled;
		unsigned long color;
	public:
		static unsigned int id_max; //unused at the moment
		unsigned int id;	  		//unused at the moment

		/**
		* @brief Virtual method. Implementations are responsible for drawing the primitive.
		*/
		virtual void draw(S3DDevice *disp,S3DSurface window,S3DContext gc,S3DZBuffer *zbuffer) = 0;
		
		/**
		* @brief Virtual method. Implementations are responsible for rotating the primitive.
		*/
		virtual void rotate(double rx,double ry,double rz, S3DPoint *anchor=NULL) = 0;

		/**
		* @brief Virtual method. Implementations are responsible for moving the primitive.
		*/
		virtual void move(double dx, double dy, double dz) = 0;

		/**
		* @brief Virtual method. Implementations are responsible for return some z-Value the primitive.
		*/
		virtual double getZ() = 0;
		bool getFillMode();
		void setFillMode(bool fill);
		unsigned long getColor();
		void setColor(unsigned long c);
};
#endif

