/**
* @file Simple3D.cpp
* @brief Contains the implementation of S3D's core.
*/
#include "Simple3D.h"

/**
* @brief The default constructor. You need to call this to initialize the engine.
* @param[in] width The width of the desired screen.
* @param[in] height The height of the desired screen.
* @param[in] title You can supply a title for a window here.
* @param[in] argc The number of arguments passed to your application (optional)
* @param[in] argv The arguments passed to your application (optional)
*/
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
	
	XSetStandardProperties(disp,window,title.c_str(),title.c_str(),None,NULL,0,NULL);
	XMapWindow(disp,window);
	XSelectInput(disp, window, StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask);

	gc = XCreateGC(disp,window,0,0);

	XSetForeground(disp,gc,foreColor);
	XSetBackground(disp,gc,backColor);
	
	backbuffer = XCreatePixmap(disp,window,width,height,24);

	zbuffer = new S3DZBuffer(width,height);
}

/**
* @brief Destructor. Call this to clean up after you're ready with S3D.
*/
Simple3D::~Simple3D()
{
	delete zbuffer;
	XFreePixmap(disp,backbuffer);
	XDestroyWindow(disp,window);
}

/**
* @brief Renders the entities known to the instance of Simple3D.
*
* You need to call this, when you want to render the entities,
* you have propagated to the engine-instance.
*/
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

/**
* @brief Set the background color
* @param[in] c Color (unsigned int as produced by the RGB-macro) to use as background.
* 
* Call this to set the color used by the engine as background. Default color is black.
*/
void Simple3D::setBackColor(S3DColor c)
{
	XSetBackground(disp,gc,RGB(c.r,c.g,c.b));
}

/**
* @brief Set the background color
* @param[in] c Color (unsigned int as produced by the RGB-macro) to use as background.
* 
* Call this to set the color used by the engine for rendering, when no other color is
* specified. Default color is white. Note: The axis are (if displayed) drawn in this color.
*/
void Simple3D::setForeColor(S3DColor c)
{
	XSetForeground(disp,gc,RGB(c.r,c.g,c.b));	
}

/**
* @brief Obtain an event from the engine's window.
* @return Returns an S3DEvent-structure. When there was no event, S3DEventNone is returned.
*/
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

/**
* @brief Propagate entity to the engine.
* @param[in] p Pointer to the primitive you want to enqueue for rendering.
*
* You need to call this function in order to get an entity on screen. Only
* entities enqueued through this function are rendered.
*/
void Simple3D::appendEntity(S3DPrimitive *p)
{
	entityList.push_back(p);
}

/**
* @brief Reorders entities for correct rendering.
*
* This gets called from inside the engine. You don't need to fiddle with this.
*/
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
