/**
* @file types.h 
* @brief Defines basic types and structures of Simple3D
* 
* This file holds type definitions, enumerations and structures to keep the platform-dependent types
* the same for Simple3D. 
*/

#ifndef _S3D_TYPES_H_
#define _S3D_TYPES_H_

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} S3DColor;

enum S3DEvent  { S3DEventNotify, S3DEventKeyPress, S3DEventButtonPress, S3DEventQuit, S3DEventNone };
enum S3DOption { S3DOptionDrawAxis = 0x1, S3DOptionDebug = 0x2 };

//Typedefs for keeping an uniform set of types on all the platforms.
typedef Display S3DDevice;
typedef GC S3DContext;
typedef Window S3DSurface;
typedef Pixmap S3DBitmap;

#endif