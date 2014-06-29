#Makefile

EXE	 = raytracer
SRCS =  camera.cpp main.cpp plane.cpp scene.cpp test.flex.cpp geometry.cpp mesh.cpp raytracer.cpp sphere.cpp test.yy.cpp

HEADERS =  camera.h light.h mesh.h ray.h scene.h transform.h geometry.h material.h primitive.h raytracer.h shape.h

CCFLAGS =  -g3 -Wall # -O3 
LDFLAGS = -ll
CC 	= g++

OBJS	= $(SRCS:.cpp=.o)

all: $(EXE)

test.yy.cpp: test.y
	@echo "bisoning"
	bison -d -o $@ $^

test.yy.hpp: test.yy.cpp

test.flex.cpp: test.l test.yy.hpp
	@echo "flexing"
	flex -o $@ $^ 
	
%.o:%.cpp  $(HEADERS)
	$(CC) -c $< $(CCFLAGS)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: depend
depend: 
	makedepend -Y $(SRCS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE) test.yy.cpp test.yy.hpp test.flex.cpp core *~ *#

