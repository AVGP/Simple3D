/**
* types.h - defines basic types and structures of Simple3D
*/

#ifndef _S3DTypes_
#define _S3DTypes_

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} S3DColor;

enum S3DEvent  { S3DEventNotify, S3DEventKeyPress, S3DEventButtonPress, S3DEventQuit, S3DEventNone };
enum S3DOption { S3DOptionDrawAxis = 0x1, S3DOptionDebug = 0x2 };

//Typen für Cross-Platform-Zeuch
typedef Display S3DDevice;
typedef GC S3DContext;
typedef Window S3DSurface;
typedef Pixmap S3DBitmap;

#endif