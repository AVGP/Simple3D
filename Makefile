default:
#	g++ -o Demo2 -lm -lX11 main.cpp Simple3D.cpp S3DTetraeder.cpp S3DCube.cpp S3DMesh.cpp S3DRect.cpp S3DTriangle.cpp S3DLine.cpp S3DPrimitive.cpp S3DPoint.cpp
	g++ -o Demo2 -lm -lX11 main.cpp Simple3D.cpp S3DMesh.cpp S3DTriangle.cpp S3DLine.cpp S3DPrimitive.cpp S3DPoint.cpp S3DZBuffer.cpp
