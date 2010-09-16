#include "Simple3D.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    MSG messages;
	Simple3D *r = new Simple3D(500,500,"Hi there.",argc,argv);

	S3DTriangle t(S3DPoint (-50, 50, 50),
				  S3DPoint (  0,-50, 50),
				  S3DPoint ( 50, 50, 50));

	S3DTriangle u(S3DPoint (-50, 50,100),
				  S3DPoint (  0,-50,100),
				  S3DPoint ( 50, 50,100));

	S3DTriangle v(S3DPoint (-50, 50,150),
				  S3DPoint (  0,-50,150),
				  S3DPoint ( 50, 50,150));

	S3DRect w(S3DPoint( 50, 50,100),
			  S3DPoint(150, 50,100),
			  S3DPoint(150,-50,100),
			  S3DPoint( 50,-50,100));

	t.setColor(RGB(255,0,0));
	u.setColor(RGB(0,255,0));
	v.setColor(RGB(0,0,255));
	w.setColor(RGB(255,255,0));

	t.setFillMode(true);
	u.setFillMode(true);
	v.setFillMode(true);
	w.setFillMode(true);

	r->appendEntity(&w);
	r->appendEntity(&t);
	r->appendEntity(&u);
	r->appendEntity(&v);

    while (GetMessage (&messages, NULL, 0, 0))
    {

        if(messages.message == WM_TIMER)
        {
            t.rotate(5,0,0);
            u.rotate(0,0,5);
            v.rotate(0,5,0);

            w.rotate(5,5,5);
            w.move(0,0,5);

            r->render();
        }

        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

	return 0;
}
