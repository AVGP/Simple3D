#ifndef _S3D_ZBUFFER_H_
#define _S3D_ZBUFFER_H_
class S3DZBuffer
{
	public:
	  S3DZBuffer(int w, int h)
	  {
		  buffer = new int[w*h];
		  width  = w;
		  height = h;
		  for(int i=0;i<w*h;i++) buffer[i] = 20000;
	  };
	  int getPoint(int x,int y) { return buffer[x+(y*width)]; };
	  void setPoint(int x,int y,int z) { buffer[x+(y*width)] = z; };
	  void clear() { for(int i=0;i<width*height;i++) buffer[i] = 20000; };
	private:
	  int *buffer;
	  int width,height;
};
#endif
