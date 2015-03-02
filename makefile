CFLAG = -Wno-deprecated-declarations -std=c++11
CFRAME = -framework OpenGL -framework GLUT -framework Foundation
CFRAME += $(shell freetype-config --libs)
CINCLUDE = $(shell freetype-config --cflags) 

test: test.cpp minftgl.o
	g++ test.cpp minftgl.o $(CFRAME) $(CFLAG) $(CINCLUDE) -o test.out

minftgl.o: minftgl.cpp
	g++ minftgl.cpp $(CFLAG) $(CINCLUDE) -c
