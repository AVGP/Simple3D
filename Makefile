#Makefile for the Simple3D 3D engine

NAME		= Demo2
LIBNAME		= libsimple3d.so


CC			= gcc
CFLAGS		= -O2 -Wall
CXX			= g++
CXXFLAGS 	= $(CFLAGS)
LIBTOOL		= libtool
LDCONF		= ldconfig


LIBS			= -lm -lX11

SOURCES		= main.cpp Simple3D.cpp S3DMesh.cpp S3DTriangle.cpp S3DLine.cpp S3DPrimitive.cpp S3DPoint.cpp S3DZBuffer.cpp

OBJS		= main.o Simple3D.o S3DMesh.o S3DTriangle.o S3DLine.o S3DPrimitive.o S3DPoint.o S3DZBuffer.o
LIBOBJS		= Simple3D.o S3DMesh.o S3DTriangle.o S3DLine.o S3DPrimitive.o S3DPoint.o S3DZBuffer.o


default: $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LIBS)

lib: $(LIBOBJS)
	$(CXX) -shared -o $(LIBNAME) -W-soname $(LIBOBJS)

debug:
	$(CXX) -g -o $(NAME) $(LIBS) $(SOURCES) $(CXXFLAGS) -D_DEBUG_


mesh:
	$(CC) -o WriteDemoMesh WriteDemoMesh.c $(CFLAGS)
	./WriteDemoMesh


#install & clean stuff
install:
	$(LIBTOOL) --mode=install cp $(LIBNAME) /usr/lib
	$(LDCONF) -n /usr/lib

clean:
	rm -f $(OBJS) $(NAME) $(LIBNAME) WriteDemoMesh

clear:
	rm *~


#OBJS
main.o:
	$(CXX) -c main.cpp $(CXXFLAGS)
Simple3D.o:
	$(CXX) -c Simple3D.cpp $(CXXFLAGS)
S3DMesh.o:
	$(CXX) -c S3DMesh.cpp $(CXXFLAGS)
S3DTriangle.o:
	$(CXX) -c S3DTriangle.cpp $(CXXFLAGS)
S3DLine.o:
	$(CXX) -c S3DLine.cpp $(CXXFLAGS)
S3DPrimitive.o:
	$(CXX) -c S3DPrimitive.cpp $(CXXFLAGS)
S3DPoint.o:
	$(CXX) -c S3DPoint.cpp $(CXXFLAGS)
S3DZBuffer.o:
	$(CXX) -c S3DZBuffer.cpp $(CXXFLAGS)

