/**
* @file global.h
* @brief Contains basic includes (including platform-dependent) and definitions for the whole library.
*/
#ifndef _S3D_GLOBAL_H_
#define _S3D_GLOBAL_H_

#ifdef _DEBUG_ /* make debug */
	#include <iostream>
#endif

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "types.h"


#define PI 3.14159
#define RGB(r,g,b) ((r << 16) | (g << 8) | b)
#define PLANAR_DISTANCE 300


#define S3DVERSION "0.0.1"
#define S3DVERSION_MAJOR 0
#define S3DVERSION_MINOR 0
#define S3DVERSION_PATCH 1

#endif

