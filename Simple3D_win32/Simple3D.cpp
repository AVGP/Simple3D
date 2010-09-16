/**
* Simple3D
* Basic, cross-platform 3D-Engine
* (c)2010 by M.Naumann
* Licenced under GPL 2!
*/

#include "Simple3D.h"
#include <iostream>

Simple3D::Simple3D(int width, int height,std::string title,int argc, char **argv)
{
	for(int i=0;i<argc;i++)
	{
		if(argv[i][1] == 'D') options |= S3DOptionDebug;
		if(argv[i][1] == 'A') options |= S3DOptionDrawAxis;
	}

	backColor = RGB(0,0,0);
	foreColor = RGB(255,255,255);

	this->width  = (unsigned int)width;
	this->height = (unsigned int)height;

    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = NULL;
    wincl.lpszClassName = title.c_str();
    wincl.lpfnWndProc = this->WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
    {
        std::cout << "Fuck." << std::endl;
    }

	window = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           title.c_str(),         /* Classname */
           title.c_str(),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           width,                 /* The programs width */
           height,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           NULL,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    ShowWindow(window,SW_SHOW);

	if(options & S3DOptionDebug)
	  std::cout << "Window: " << window << std::endl;

	gc = GetDC(window); //XCreateGC(disp,window,0,0);
	backbuffer = CreateCompatibleDC(gc);
	bitmapBackbuffer = CreateBitmap(width,height,1,32,NULL);
	SelectObject(backbuffer,bitmapBackbuffer);

	//Init Z-Buffer
	zbuffer = (int *)malloc(sizeof(int)*width*height);
	for(int i=0;i<width*height;i++) *(zbuffer+i) = 200000;

	SetTimer(window,1,50,NULL);
}

Simple3D::~Simple3D()
{
	free(zbuffer);
	DeleteObject(bitmapBackbuffer);
}

void Simple3D::render()
{

	RECT r;
	HBRUSH hBg = CreateSolidBrush(backColor);
	HBRUSH hFg = CreateSolidBrush(foreColor);

	r.left   = 0;
	r.top    = 0;
	r.right  = width;
	r.bottom = height;
	FillRect(backbuffer,&r,hBg);

	if(options & S3DOptionDrawAxis)
	{
	    HPEN hPen = CreatePen(PS_SOLID,1,foreColor);
	    SelectObject(backbuffer,hPen);

		int hx = width/2;
		int hy = height/2;
		MoveToEx(backbuffer,0,hy,NULL);
		LineTo(backbuffer,width,hy);

		MoveToEx(backbuffer,hx,0,NULL);
		LineTo(backbuffer,hx,height);

		MoveToEx(backbuffer,0,0,NULL);
		LineTo(backbuffer,width,height);
	}

	//Sortieren für Painter's-Algo
	reOrderEntities();
	//Ausgeben:

	std::list<S3DPrimitive *>::iterator iter = entityList.begin();
	while(iter != entityList.end())
	{
		double dx = width/2;
		double dy = height/2;
		S3DPrimitive *p = *(iter);
		p->move(dx,dy,PLANAR_DISTANCE);
		p->draw(disp,window,backbuffer);
		p->move(-1*dx,-1*dy,-1*PLANAR_DISTANCE);
		++iter;
	}

    BitBlt(gc,0,0,width,height,backbuffer,0,0,SRCCOPY);
}

void Simple3D::setBackColor(S3DColor c)
{
	backColor = RGB(c.r,c.g,c.b);
}
void Simple3D::setForeColor(S3DColor c)
{
	foreColor = RGB(c.r,c.g,c.b);
}

S3DEvent Simple3D::getEvent()
{/*
	XEvent event;
	XNextEvent(disp,&event);
	switch(event.type)
	{
		case MapNotify:
			return S3DEventNotify;
			break;
		case KeyPress:
			return S3DEventKeyPress;
			break;
		case ButtonPress:
			return S3DEventButtonPress;
			break;
		default:
			return S3DEventNone;
			break;
	}
	*/
	return S3DEventNone;
}

void Simple3D::appendEntity(S3DPrimitive *p)
{
	entityList.push_back(p);
}

void Simple3D::updateZBuffer()
{
}

void Simple3D::reOrderEntities()
{
	//
	std::list<S3DPrimitive *>ordered;
	std::list<S3DPrimitive *>::iterator max = entityList.begin();

	while(entityList.size() > 0)
	{
		double maxZ = -1*PLANAR_DISTANCE;
		std::list<S3DPrimitive *>::iterator iter = entityList.begin();
		while(iter != entityList.end())
		{
			S3DPrimitive *p = *(iter);
			if(p->getZ() > maxZ)
			{
				maxZ = p->getZ();
				max  = iter;
			}
			++iter;
		}
		S3DPrimitive *m = *(max);
		ordered.push_back(m);
		entityList.erase(max);
	}
	entityList.swap(ordered);
}

LRESULT CALLBACK Simple3D::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_TIMER:

            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
