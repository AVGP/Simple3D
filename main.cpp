/* Demo */
#include "Simple3D.h"

int main(int argc,char **argv)
{
	//First, we need to create an instance of the Simple3D-Class to init the Engine and get a window.
	Simple3D *r = new Simple3D(500,500,"Hi there.",argc,argv);
	
	//Now to the fun part: We create 3 triangles:
	S3DTriangle t(S3DPoint (-50, 0, 150),
				  S3DPoint (  0, 0,   0),
				  S3DPoint ( 50, 0, 150));
	t.scale(2,2,2);
	S3DTriangle u(S3DPoint (-50,  0,150),
				  S3DPoint (  0,  0,  0),
				  S3DPoint ( 50,  0,150));
	u.scale(1,1,2);
				  
	S3DTriangle v(S3DPoint (-50, 50,150),
				  S3DPoint (  0,-50,150),
				  S3DPoint ( 50, 50,150));
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
	//We're also capable of loading meshes from a file.
	S3DMesh mesh("test.s3d");
	mesh.move(-60,-60,0);
	mesh.scale(2,2,2);
			  
	//Here we set the colors of the 3 triangles, we just created...
	t.setColor(RGB(255,0,0));
	u.setColor(RGB(0,255,0));
	v.setColor(RGB(0,0,255));
/*	w.setColor(RGB(255,255,255));
	c.setColor(RGB(255,255,0));
	d.setColor(RGB(0,255,255));
*/
	//...and tell the engine we want them filled, not just framed.
	t.setFillMode(true);
	u.setFillMode(true);
	v.setFillMode(true);
/*	w.setFillMode(false);
	d.setFillMode(false);
*/
	//We can also create a single line:
	S3DLine l(S3DPoint(-30,0,20),S3DPoint(30,0,20));
	l.setColor(RGB(255,0,0));

	/*
	* To get these things rendered, we need to tell the Simple3D-Instance, we want them on screen.
	* For this, we just add them to it's list of entities.
	*/
//	r->appendEntity(&w);
	r->appendEntity(&t);
//	r->appendEntity(&u);
//	r->appendEntity(&v);
//	r->appendEntity(&c);
	
	r->appendEntity(&mesh);
	r->appendEntity(&l);
	
//	r->appendEntity(&d);
		
//	d.move(140,-30,0);
	
	//When you see this occuring in a rotate()-call below, it means, the entity is rotating AROUND this point
	//instead of rotating around itself.
	S3DPoint *p = new S3DPoint(0,0,10);
	
	//This is the main loop. In this case, it ends, when a mouseclick occurs.
	while(r->getEvent() != S3DEventButtonPress)
	{
		//Lets have some motion!
/*		c.rotate(5,5,5);
		c.move(0,0,5);
		d.rotate(5,5,5);
		d.move(0,0,2);
*/
		t.rotate(2,2,2);
		t.scale(0.9,0.9,0.9);
		u.rotate(0,2,0);
//		v.rotate(0,5,0);
//		w.rotate(5,5,5);
		
		l.rotate(0,5,0,p);
		
		mesh.rotate(0,5,0);
		//mesh.move(0,0,5);
//		w.move(0,0,5);
		//This brings stuff on screen
		r->render();
		usleep(100000);
	}
	//Clean up by deleting the Simple3D-Instance.
	delete r;
	
	return EXIT_SUCCESS;
}

