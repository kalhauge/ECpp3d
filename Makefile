# Makefile for ECpp3d.

CXX=g++
CXXFLAGS= -g

FRAMEWORKS= -framework OpenGL -framework IOKit -framework Cocoa
LIBS= -L"/opt/X11/lib" -L"/usr/local/lib" -lecpp3d -ljpeg -lGLFW -L. $(FRAMEWORKS)
HEADERS = -I"/opt/X11/include" -I"/usr/local/include" -Ilib/


NAMES=$(notdir $(basename $(wildcard src/*.cpp)))
OBJ_DIR=obj
SRC_DIR=src
TEST_DIR=test
SRC=$(addprefix $(SRC_DIR)/,$(addsuffix .cpp,$(NAMES)))
OBJ=$(addprefix $(OBJ_DIR)/,$(addsuffix .obj,$(NAMES)))



all: libecpp3d.a bin/test1 bin/test2 bin/test3
	

clean:
	@find obj/ -iname *.obj -exec rm {} \;
	@find bin/ -iname * -exec rm {} \;
	@find . -iname *.a -exec rm {} \;

libecpp3d.a : $(OBJ)
	@echo "DONE COMPILING"
	@ar rcs libecpp3d.a $?

bin/test1 : obj/test1.obj libecpp3d.a
	@echo "BUILDING" $<	
	@LD_LIBRARY_PATH=.; $(CXX) $(CXXFLAGS) $(LIBS) $(HEADERS) obj/test1.obj -o bin/test1
	@echo "DONE BUILDING" $<

bin/test2 : obj/test2.obj libecpp3d.a
	@echo "BUILDING" $<	
	@LD_LIBRARY_PATH=.; $(CXX) $(CXXFLAGS) $(LIBS) $(HEADERS) obj/test2.obj -o bin/test2
	@echo "DONE BUILDING" $<

bin/test3 : obj/test3.obj libecpp3d.a
	@echo "BUILDING" $<	
	@LD_LIBRARY_PATH=.; $(CXX) $(CXXFLAGS) $(LIBS) $(HEADERS) obj/test3.obj -o bin/test3
	@echo "DONE BUILDING" $<

$(OBJ_DIR)/%.obj: $(TEST_DIR)/%.cpp
	@echo "COMPILING TEST" $<
	@$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.cpp
	@echo "COMPILING" $<
	@$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

.PHONY: all