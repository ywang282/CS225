# CS 225 Lab 02
# Written by Jack Toole Fall 2010

EXENAME = sketchify

OBJS = main.o rgbapixel.o png.o sketchify.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -w
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp png.h
	$(CXX) $(CXXFLAGS) main.cpp
	
png.o : png.cpp png.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

sketchify.o : sketchify.cpp
	$(CXX) $(CXXFLAGS) sketchify.cpp

clean : 
	-rm -f *.o $(EXENAME) out.png
