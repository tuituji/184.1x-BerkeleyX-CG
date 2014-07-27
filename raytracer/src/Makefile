#Makefile
SRCDIR = ./

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

.//mesh.o: mesh.h shape.h material.h geometry.h ray.h bbox.h scene.h camera.h
.//mesh.o: light.h primitive.h bvh.h
.//sphere.o: shape.h material.h geometry.h ray.h bbox.h
.//scene.o: scene.h camera.h ray.h geometry.h light.h material.h shape.h
.//scene.o: bbox.h primitive.h bvh.h
.//raytracer.o: raytracer.h scene.h camera.h ray.h geometry.h light.h
.//raytracer.o: material.h shape.h bbox.h primitive.h bvh.h
.//geometry.o: geometry.h
.//matrixStack.o: geometry.h
.//plane.o: shape.h material.h geometry.h ray.h bbox.h
.//bbox.o: bbox.h geometry.h ray.h
.//bvh.o: bvh.h shape.h material.h geometry.h ray.h bbox.h
.//camera.o: camera.h ray.h geometry.h
.//main.o: raytracer.h scene.h camera.h ray.h geometry.h light.h material.h
.//main.o: shape.h bbox.h primitive.h bvh.h
.//test.flex.o: test.yy.hh
.//test.yy.o: scene.h camera.h ray.h geometry.h light.h material.h shape.h
.//test.yy.o: bbox.h primitive.h bvh.h raytracer.h mesh.h
