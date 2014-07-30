INCFLAGS += -I 	./vecmath/include/

LINKFLAGS  = -lglut -lGL -lGLU -lGLEW
#LINKFLAGS += -L /mit/6.837/public/lib -lvecmath

CFLAGS    = -g3 -Wall
CC        = g++
SRCS      = $(wildcard ./src/*.cpp)
#SRCS     += $(wildcard vecmath/src/*.cpp)
OBJS      = $(SRCS:.cpp=.o)
PROG      = glviewer

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

# DO NOT DELETE

./src/Matrix2f.o: ./src/Matrix2f.h ./src/Vector2f.h
./src/Vector3f.o: ./src/Vector3f.h ./src/Vector2f.h
./src/Vector2f.o: ./src/Vector2f.h ./src/Vector3f.h
./src/MatrixStack.o: ./src/MatrixStack.h ./src/vecmath.h ./src/Matrix2f.h
./src/MatrixStack.o: ./src/Matrix3f.h ./src/Matrix4f.h ./src/Quat4f.h
./src/MatrixStack.o: ./src/Vector2f.h ./src/Vector3f.h ./src/Vector4f.h
./src/light.o: ./src/glviewer.h ./src/vecmath.h ./src/Matrix2f.h
./src/light.o: ./src/Matrix3f.h ./src/Matrix4f.h ./src/Quat4f.h
./src/light.o: ./src/Vector2f.h ./src/Vector3f.h ./src/Vector4f.h
./src/light.o: ./src/MatrixStack.h
./src/Matrix3f.o: ./src/Matrix3f.h ./src/Matrix2f.h ./src/Quat4f.h
./src/Matrix3f.o: ./src/Vector3f.h
./src/Matrix4f.o: ./src/Matrix4f.h ./src/Matrix2f.h ./src/Matrix3f.h
./src/Matrix4f.o: ./src/Quat4f.h ./src/Vector3f.h ./src/Vector4f.h
./src/Vector4f.o: ./src/Vector4f.h ./src/Vector2f.h ./src/Vector3f.h
./src/Quat4f.o: ./src/Quat4f.h ./src/Matrix3f.h ./src/Vector3f.h
./src/Quat4f.o: ./src/Vector4f.h
./src/main.o: ./src/vecmath.h ./src/Matrix2f.h ./src/Matrix3f.h
./src/main.o: ./src/Matrix4f.h ./src/Quat4f.h ./src/Vector2f.h
./src/main.o: ./src/Vector3f.h ./src/Vector4f.h ./src/glviewer.h
./src/main.o: ./src/MatrixStack.h
