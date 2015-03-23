os_switch: os_switch.cpp
	$(CXX) os_switch.cpp -o os_switch.out

CFLAG = -Wno-deprecated-declarations -std=c++11
OS = $(shell ./os_switch.out)

ifeq ($(OS), apple)
CFRAME = -framework OpenGL -framework GLUT -framework Foundation -framework Python -framework OpenAL 
endif

ifeq ($(OS), $(filter $(OS), freebsd linux))
CFLAGS += -pthread
CFRAME = $(shell pkg-config --libs gl glu python-2.7 openal) -lglut
endif

ifeq ($(OS), win32)
CFRAME = -lpython2.7 
CFRAME += -llibOpenAL32 
CFRAME += -lopengl32 -lglu32 -lglut
#CFLAGS += -D_STDCALL_SUPPORTED -D_M_IX86
endif

CFRAME += $(shell freetype-config --libs)
CINCLUDE = $(shell freetype-config --cflags) 

test: test.cpp minftgl.o
	g++ test.cpp minftgl.o $(CFRAME) $(CFLAG) $(CINCLUDE) -o test.out

minftgl.o: minftgl.cpp
	g++ minftgl.cpp $(CFLAG) $(CINCLUDE) -c
