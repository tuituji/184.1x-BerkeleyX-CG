#Makefile
SRCDIR = ./src

SRCS =  $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(SRCDIR)/test.flex.cc  $(SRCDIR)/test.yy.cc

OBJS = $(SRCS:.cpp=.o)

PROG = raytracer

CCFLAGS =  -g3 -Wall # -O3 
LDFLAGS = -ll
CC 	= g++

all: $(SRCS) $(PROG)


$(PROG): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $@ $(LDFLAGS)


.cpp.o: 
	$(CC) $(CCFLAGS) $< -c -o $@ $(INCFLAGS)

$(SRCDIR)/test.yy.cc: $(SRCDIR)/test.y
	@echo "bisoning"
	bison -d -o $@ $^

$(SRCDIR)/test.yy.hh: $(SRCDIR)/test.yy.cc

$(SRCDIR)/test.flex.cc: $(SRCDIR)/test.l $(SRCDIR)/test.yy.hh
	@echo "flexing"
	flex -o $@ $^ 

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROG) 
	rm -f $(SRCDIR)/test.yy.cc $(SRCDIR)/test.yy.hh $(SRCDIR)/test.flex.cc

# DO NOT DELETE

./src/mesh.o: ./src/mesh.h ./src/shape.h ./src/material.h ./src/geometry.h
./src/mesh.o: ./src/ray.h ./src/bbox.h ./src/scene.h ./src/camera.h
./src/mesh.o: ./src/light.h ./src/primitive.h ./src/bvh.h
./src/sphere.o: ./src/shape.h ./src/material.h ./src/geometry.h ./src/ray.h
./src/sphere.o: ./src/bbox.h
./src/scene.o: ./src/scene.h ./src/camera.h ./src/ray.h ./src/geometry.h
./src/scene.o: ./src/light.h ./src/material.h ./src/shape.h ./src/bbox.h
./src/scene.o: ./src/primitive.h ./src/bvh.h
./src/raytracer.o: ./src/raytracer.h ./src/scene.h ./src/camera.h ./src/ray.h
./src/raytracer.o: ./src/geometry.h ./src/light.h ./src/material.h
./src/raytracer.o: ./src/shape.h ./src/bbox.h ./src/primitive.h ./src/bvh.h
./src/geometry.o: ./src/geometry.h
./src/matrixStack.o: ./src/geometry.h
./src/plane.o: ./src/shape.h ./src/material.h ./src/geometry.h ./src/ray.h
./src/plane.o: ./src/bbox.h
./src/bbox.o: ./src/bbox.h ./src/geometry.h ./src/ray.h
./src/bvh.o: ./src/bvh.h ./src/shape.h ./src/material.h ./src/geometry.h
./src/bvh.o: ./src/ray.h ./src/bbox.h
./src/camera.o: ./src/camera.h ./src/ray.h ./src/geometry.h
./src/main.o: ./src/raytracer.h ./src/scene.h ./src/camera.h ./src/ray.h
./src/main.o: ./src/geometry.h ./src/light.h ./src/material.h ./src/shape.h
./src/main.o: ./src/bbox.h ./src/primitive.h ./src/bvh.h
./src/test.flex.o: ./src/test.yy.hh
./src/test.yy.o: ./src/scene.h ./src/camera.h ./src/ray.h ./src/geometry.h
./src/test.yy.o: ./src/light.h ./src/material.h ./src/shape.h ./src/bbox.h
./src/test.yy.o: ./src/primitive.h ./src/bvh.h ./src/raytracer.h ./src/mesh.h
