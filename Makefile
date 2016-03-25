OPENGLLIB= -lGL -lGLU
GLEWLIB= -lGLEW
GLFWLIB = -lglfw 
LIBS= -lSOIL $(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include 
BIN1=robot
BIN2=01_triangle_dep
SRCS1=robot.cpp shader_util.cpp 
SRCS2=01_triangle_dep.cpp gl_framework.cpp shader_util.cpp 
INCLUDES=gl_framework.hpp shader_util.hpp create.hpp

all: $(BIN1) $(BIN2)

$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS) 

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN1) $(BIN2)
