# Makefile for ECpp3d.

CXX=g++
CXXFLAGS= -g

FRAMEWORKS= -framework OpenGL -framework IOKit -framework Cocoa
LIBS= -L"/usr/local/lib" -lecpp3d -ljpeg -lGLFW -L. $(FRAMEWORKS)
HEADERS = -I"/usr/local/include" -Ilib/


NAMES=$(notdir $(basename $(wildcard src/*.cpp)))
OBJ_DIR=obj
SRC_DIR=src
TEST_DIR=test
SRC=$(addprefix $(SRC_DIR)/,$(addsuffix .cpp,$(NAMES)))
OBJ=$(addprefix $(OBJ_DIR)/,$(addsuffix .obj,$(NAMES)))



all: libecpp3d.a bin/test1 bin/test2 bin/test3 bin/test4
	

clean:
	@find obj/ -iname *.obj -exec rm {} \;
	@find bin/ -iname * -exec rm {} \;
	@find . -iname *.a -exec rm {} \;

libecpp3d.a : $(OBJ)
	@echo "DONE COMPILING"
	@ar rcs libecpp3d.a $?

bin/% : obj/%.obj libecpp3d.a
	@echo "BUILDING" $<	
	@LD_LIBRARY_PATH=.; $(CXX) $(CXXFLAGS) $(LIBS) $(HEADERS) $< -o $@ 
	@echo "DONE BUILDING" $<

$(OBJ_DIR)/%.obj: $(TEST_DIR)/%.cpp
	@echo "COMPILING TEST" $<
	@$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.cpp
	@echo "COMPILING" $<
	@$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

.PHONY: all
