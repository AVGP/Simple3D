#define _Debug_
#include "Simple3D.h"
#include <iostream>
#include <cstdlib>

int main(int argc,char **argv)
{
	Simple3D *r = new Simple3D(500,500,"Hi there.",argc,argv);
	
	S3DTriangle t(S3DPoint (-50, 0, 150),
				  S3DPoint (  0,0,0),//-50, 50*3),
				  S3DPoint ( 50, 0, 150));

	S3DTriangle u(S3DPoint (-50, 50,100*3),
				  S3DPoint (  0,-50,100*3),
				  S3DPoint ( 50, 50,100*3));
				  
	S3DTriangle v(S3DPoint (-50, 50,150*3),
				  S3DPoint (  0,-50,150*3),
				  S3DPoint ( 50, 50,150*3));
/*
	S3DRect w(S3DPoint( 50, 50,100),
			  S3DPoint(150, 50,100),
			  S3DPoint(150,-50,100),
			  S3DPoint( 50,-50,100));
	
	S3DCube c(S3DPoint(-50,-50,150),
			  S3DPoint( 50,-50,150),
			  S3DPoint( 50,-50, 50),
			  S3DPoint(-50,-50, 50),
			  S3DPoint(-50, 50,150),
			  S3DPoint( 50, 50,150),
			  S3DPoint( 50, 50, 50),
			  S3DPoint(-50, 50, 50));
			  
	S3DTetraeder d(S3DPoint(-50,-50, 50),
				   S3DPoint( 50,-50, 50),
				   S3DPoint(  0,-50,-50),
				   S3DPoint(  0, 50,  0));
*/				   
	S3DMesh mesh("test.s3d");
	mesh.move(-60,-60,0);
			  
	t.setColor(RGB(255,0,0));
	u.setColor(RGB(0,255,0));
	v.setColor(RGB(0,0,255));
/*	w.setColor(RGB(255,255,255));
	c.setColor(RGB(255,255,0));
	d.setColor(RGB(0,255,255));
*/
	t.setFillMode(true);
	u.setFillMode(true);
	v.setFillMode(true);
/*	w.setFillMode(false);
	d.setFillMode(false);
*/
	S3DLine l(S3DPoint(-30,0,20),S3DPoint(30,0,20));
	l.setColor(RGB(255,0,0));

//	r->appendEntity(&w);
	r->appendEntity(&t);
//	r->appendEntity(&u);
//	r->appendEntity(&v);
//	r->appendEntity(&c);
	
	r->appendEntity(&mesh);
	r->appendEntity(&l);
	
//	r->appendEntity(&d);
		
//	d.move(140,-30,0);
	
	S3DPoint *p = new S3DPoint(0,0,10);
	
	while(r->getEvent() != S3DEventButtonPress)
	{
/*		c.rotate(5,5,5);
		c.move(0,0,5);
		d.rotate(5,5,5);
		d.move(0,0,2);
*/
		t.rotate(2,2,2,p);
		u.rotate(0,0,5);
		v.rotate(0,5,0);
//		w.rotate(5,5,5);
		
		l.rotate(0,5,0,p);
		
		mesh.rotate(0,5,0);
		//mesh.move(0,0,5);
//		w.move(0,0,5);
		r->render();
		usleep(100000);
	}
	delete r;
	
	return 0;
}
