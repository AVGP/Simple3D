#include "Simple3D.h"
#include <iostream>

Simple3D::Simple3D(int width, int height,std::string title,int argc, char **argv)
{
	for(int i=0;i<argc;i++)
	{
		if(argv[i][1] == 'D') options |= S3DOptionDebug;
		if(argv[i][1] == 'A') options |= S3DOptionDrawAxis;
	}
	//This is temporary...hopefully :D
	options |= S3DOptionDrawAxis;
	
	disp = XOpenDisplay((char *)0);
	screen = DefaultScreen(disp);
	
	backColor = BlackPixel(disp,screen);
	foreColor = WhitePixel(disp,screen);
	
	this->width  = (unsigned int)width;
	this->height = (unsigned int)height;
	
	window = XCreateSimpleWindow(disp,DefaultRootWindow(disp),0,0,width,height,0,backColor,0);
	
	if(options & S3DOptionDebug)
	  std::cout << "Window: " << window << std::endl;
	
	XSetStandardProperties(disp,window,title.c_str(),title.c_str(),None,NULL,0,NULL);
	XMapWindow(disp,window);
	XSelectInput(disp, window, StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask);

	gc = XCreateGC(disp,window,0,0);

	XColor color;

	XSetForeground(disp,gc,foreColor);
	XSetBackground(disp,gc,backColor);
	
	backbuffer = XCreatePixmap(disp,window,width,height,24);

	zbuffer = new S3DZBuffer(width,height);
}

Simple3D::~Simple3D()
{
	delete zbuffer;
	XFreePixmap(disp,backbuffer);
	XDestroyWindow(disp,window);
}

void Simple3D::render()
{
	XClearWindow(disp,window);
	
	if(options & S3DOptionDrawAxis)
	{
	  	XSetForeground(disp,gc,foreColor);
		int hx = width/2;
		int hy = height/2;
		XDrawLine(disp,backbuffer,gc,0,hy,width,hy);
		XDrawLine(disp,backbuffer,gc,hx,0,hx,height);
		XDrawLine(disp,backbuffer,gc,0,0,width,height);
	}
	
	//sorting entities for using the painter's algorithm
	reOrderEntities();
	//And lets go!
	
	std::list<S3DPrimitive *>::iterator iter = entityList.begin();
	while(iter != entityList.end())
	{
		double dx = width/2;
		double dy = height/2;
		S3DPrimitive *p = *(iter);
		p->move(dx,dy,2*PLANAR_DISTANCE);
		p->draw(disp,backbuffer,gc,zbuffer);
		p->move(-1*dx,-1*dy,-2*PLANAR_DISTANCE);
		++iter;
	}
	
	XCopyArea(disp,backbuffer,window,gc,0,0,width,height,0,0);
	XSetForeground(disp,gc,backColor);
	XFillRectangle(disp,backbuffer,gc,0,0,width,height);
	XSetForeground(disp,gc,foreColor);
	XFlush(disp);
	XEvent e;
	e.type = Expose;
	XSendEvent(disp,window,true,ExposureMask,&e);
	zbuffer->clear();
}

void Simple3D::setBackColor(S3DColor c)
{
	XSetBackground(disp,gc,RGB(c.r,c.g,c.b));
}
void Simple3D::setForeColor(S3DColor c)
{
	XSetForeground(disp,gc,RGB(c.r,c.g,c.b));	
}

S3DEvent Simple3D::getEvent()
{
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
}

void Simple3D::appendEntity(S3DPrimitive *p)
{
	entityList.push_back(p);
}

void Simple3D::reOrderEntities()
{
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

