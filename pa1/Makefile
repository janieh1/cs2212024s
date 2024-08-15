EXETwoDLinkedList = pa1
OBJS  = PNG.o RGBAPixel.o lodepng.o pa1.o twodlinkedlist.o twodlinkedlist-given.o block.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -lpthread -lm

all : pa1

$(EXETwoDLinkedList) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXETwoDLinkedList)

block.o : block.cpp block.h
	$(CXX) $(CXXFLAGS) block.cpp

pa1.o : pa1.cpp twodlinkedlist.h twodlinkedlist-private.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) pa1.cpp

twodlinkedlist.o : twodlinkedlist.cpp twodlinkedlist.h twodlinkedlist-private.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion twodlinkedlist.cpp

twodlinkedlist-given.o : twodlinkedlist-given.cpp twodlinkedlist.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion twodlinkedlist-given.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXETwoDLinkedList)
