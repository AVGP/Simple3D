#include <stdio.h>
#include <stdlib.h>

#define RGB(r,g,b) ((r << 16) | (g << 8) | b)


#pragma pack(0)
typedef struct
{
	double x;
	double y;
	double z;
} Point;
#pragma pack()


int main(void)
{
	FILE *file = fopen("test.s3d","wb");
	Point meshdata[8];
	
	meshdata[0].x =  50;
	meshdata[0].y =  50;
	meshdata[0].z =  50;
	
	meshdata[1].x =  70;
	meshdata[1].y =  50;
	meshdata[1].z =  50;
	
	meshdata[2].x =  70;
	meshdata[2].y =  70;
	meshdata[2].z =  50;
	
	meshdata[3].x =  50;
	meshdata[3].y =  70;
	meshdata[3].z =  50;

	meshdata[4].x =  50;
	meshdata[4].y =  50;
	meshdata[4].z =  70;
	
	meshdata[5].x =  70;
	meshdata[5].y =  50;
	meshdata[5].z =  70;
	
	meshdata[6].x =  70;
	meshdata[6].y =  70;
	meshdata[6].z =  70;
	
	meshdata[7].x =  50;
	meshdata[7].y =  70;
	meshdata[7].z =  70;

	unsigned long colors[6];

	colors[0] = RGB(255,0,0);
	colors[1] = RGB(0,255,0);
	colors[2] = RGB(0,0,255);
	colors[3] = RGB(255,255,0);
	colors[4] = RGB(0,255,255);
	colors[5] = RGB(255,255,255);

	//Arranging the points, so that 12 triangles for a cube arise:
	//1: 0,1,3
	//2: 1,2,3
	
	//3: 1,5,2 
	//4: 5,6,2
	
	//5: 4,5,6
	//6: 4,6,7
	
	//7: 0,4,7
	//8: 0,3,7
	
	//9:  0,4,1
	//10: 1,5,4
	
	//11: 2,3,7
	//12: 2,6,7
	
	int nPoly = 12;
	fwrite(&nPoly,sizeof(int),1,file);

//1:
	fwrite(&meshdata[0],sizeof(Point),1,file);
	fwrite(&meshdata[1],sizeof(Point),1,file);
	fwrite(&meshdata[3],sizeof(Point),1,file);
	fwrite(&colors[0],sizeof(unsigned long),1,file);
//2:
	fwrite(&meshdata[1],sizeof(Point),1,file);
	fwrite(&meshdata[2],sizeof(Point),1,file);
	fwrite(&meshdata[3],sizeof(Point),1,file);
	fwrite(&colors[0],sizeof(unsigned long),1,file);
//3:
	fwrite(&meshdata[1],sizeof(Point),1,file);
	fwrite(&meshdata[5],sizeof(Point),1,file);
	fwrite(&meshdata[2],sizeof(Point),1,file);
	fwrite(&colors[1],sizeof(unsigned long),1,file);
//4:
	fwrite(&meshdata[5],sizeof(Point),1,file);
	fwrite(&meshdata[6],sizeof(Point),1,file);
	fwrite(&meshdata[2],sizeof(Point),1,file);
	fwrite(&colors[1],sizeof(unsigned long),1,file);
//5:
	fwrite(&meshdata[4],sizeof(Point),1,file);
	fwrite(&meshdata[5],sizeof(Point),1,file);
	fwrite(&meshdata[6],sizeof(Point),1,file);
	fwrite(&colors[2],sizeof(unsigned long),1,file);
//6:
	fwrite(&meshdata[4],sizeof(Point),1,file);
	fwrite(&meshdata[6],sizeof(Point),1,file);
	fwrite(&meshdata[7],sizeof(Point),1,file);
	fwrite(&colors[2],sizeof(unsigned long),1,file);
//7:
	fwrite(&meshdata[0],sizeof(Point),1,file);
	fwrite(&meshdata[4],sizeof(Point),1,file);
	fwrite(&meshdata[7],sizeof(Point),1,file);
	fwrite(&colors[3],sizeof(unsigned long),1,file);
//8:
	fwrite(&meshdata[0],sizeof(Point),1,file);
	fwrite(&meshdata[3],sizeof(Point),1,file);
	fwrite(&meshdata[7],sizeof(Point),1,file);
	fwrite(&colors[3],sizeof(unsigned long),1,file);
//9:
	fwrite(&meshdata[0],sizeof(Point),1,file);
	fwrite(&meshdata[4],sizeof(Point),1,file);
	fwrite(&meshdata[1],sizeof(Point),1,file);
	fwrite(&colors[4],sizeof(unsigned long),1,file);
//10:
	fwrite(&meshdata[1],sizeof(Point),1,file);
	fwrite(&meshdata[5],sizeof(Point),1,file);
	fwrite(&meshdata[4],sizeof(Point),1,file);
	fwrite(&colors[4],sizeof(unsigned long),1,file);
//11:
	fwrite(&meshdata[2],sizeof(Point),1,file);
	fwrite(&meshdata[3],sizeof(Point),1,file);
	fwrite(&meshdata[7],sizeof(Point),1,file);
	fwrite(&colors[5],sizeof(unsigned long),1,file);
//12:
	fwrite(&meshdata[2],sizeof(Point),1,file);
	fwrite(&meshdata[6],sizeof(Point),1,file);
	fwrite(&meshdata[7],sizeof(Point),1,file);
	fwrite(&colors[5],sizeof(unsigned long),1,file);
	
	fclose(file);
	printf("Done. (%d)\n",sizeof(double));
	
	return EXIT_SUCCESS;
}

