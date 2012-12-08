# Makefile for ECpp3d.

CXX=g++
CXXFLAGS= -g

FRAMEWORKS= -framework OpenGL -framework IOKit -framework Cocoa
LIBS= -L"/opt/X11/lib" -L"/usr/local/lib" -lecpp3d -lGLFW -L. $(FRAMEWORKS)
HEADERS = -I"/opt/X11/include" -I"/usr/local/include" -Ilib/


NAMES=$(notdir $(basename $(wildcard src/ECpp3d*.cpp)))
OBJ_DIR=obj
SRC_DIR=src
SRC=$(addprefix $(SRC_DIR)/,$(addsuffix .cpp,$(NAMES)))
OBJ=$(addprefix $(OBJ_DIR)/,$(addsuffix .obj,$(NAMES)))



all: libecpp3d.a bin/test1
	@echo $(NAMES) 
	@echo $(OBJ) 
	@echo $(SRC)	
	

clean:
	@find obj/ -iname *.obj -exec rm {} \;
	@find bin/  -exec rm {} \;
	@find . -iname *.a -exec rm {} \;

libecpp3d.a : $(OBJ)
	@echo "DONE COMPILING"
	@ar rcs libecpp3d.a $?

bin/test1 : obj/test1.obj libecpp3d.a
	@echo "BUILDING" $<	
	@LD_LIBRARY_PATH=.; $(CXX) $(CXXFLAGS) $(LIBS) $(HEADERS) obj/test1.obj -o bin/test1
	@echo "DONE BUILDING" $<

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.cpp
	@echo "COMPILING" $<
	@$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

.PHONY: all