CXXFLAGS = -Iinclude
SRCS = src/*.cpp
LIBS = -lGLEW -lglut -lGLU -lGL
CXX = c++
OBJS = src/glut_template.o src/glut_extensions.o

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

myapp: $(OBJS)
	c++ -o myapp $(SRCS) $(CXXFLAGS) $(LIBS)
