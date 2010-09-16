/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
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
typedef HWND S3DDevice;
typedef HDC S3DContext;
typedef HWND S3DSurface;
typedef HBITMAP S3DBitmap;

#endif
