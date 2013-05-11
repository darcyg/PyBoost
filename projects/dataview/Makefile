#-----Macros---------------------------------

# set up DIR locations
BOOSTDIR = ../../thirdparty/boost_1_52_0

# set up includes and src files
INCLUDES = -I. -I ../../thirdparty/hiredis -I $(BOOSTDIR) 
SRC = $(wildcard *.cpp) 

# set up compiler options
CXX = g++
CXXFLAGS = $(INCLUDES) -O3 -Wno-deprecated -std=c++0x -Wall -ggdb

BOOST_LIBS = $(BOOSTDIR)/stage/lib/libboost_serialization.a $(BOOSTDIR)/stage/lib/libboost_program_options.a

LFLAGS = $(BOOST_LIBS) -L/usr/local/lib ../../thirdparty/hiredis/libhiredis.a

#-----Suffix Rules---------------------------
# set up C++ suffixes and relationship between .cpp and .o files

#.SUFFIXES: .cpp

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

.cc :
	$(CXX) $(CXXFLAGS) $< -o $@ $(LFLAGS)


#-----File Dependencies----------------------

EXE = main

#$(wildcard ../../src/vfp/*.cpp) $(wildcard ../../src/vfp/*/*.cpp)

OBJ = $(addsuffix .o, $(basename $(SRC)))

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) ../../thirdparty/boost_1_52_0/stage/lib/libboost_serialization.a $(LFLAGS)

clean:
	rm -f $(OBJ) $(EXE) *.cpp~ *.h~ Makefile~
	rm -rf bin
	rm -rf convenient_copy
	rm *.so
	rm *.dylib
	rm -rf bin
