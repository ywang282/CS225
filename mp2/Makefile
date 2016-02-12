TESTIMAGE_EXENAME = testimage
TESTSCENE_EXENAME = testscene

TESTIMAGE_OBJS = testimage.o png.o rgbapixel.o image.o
TESTSCENE_OBJS = testscene.o png.o rgbapixel.o image.o scene.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(TESTIMAGE_EXENAME) $(TESTSCENE_EXENAME)

$(TESTIMAGE_EXENAME) : $(TESTIMAGE_OBJS)
	$(LD) $(TESTIMAGE_OBJS) $(LDFLAGS) -o $(TESTIMAGE_EXENAME)

$(TESTSCENE_EXENAME) : $(TESTSCENE_OBJS)
	$(LD) $(TESTSCENE_OBJS) $(LDFLAGS) -o $(TESTSCENE_EXENAME)

testimage.o : testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp png.h rgbapixel.h image.h scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp


scene.o : scene.cpp scene.h image.h
	$(CXX) $(CXXFLAGS) scene.cpp

image.o : image.cpp image.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(TESTIMAGE_OBJS) $(TESTSCENE_OBJS) 
