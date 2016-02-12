# CS225 Fall 2014 MP5 Makefile

OBJS   	  = main.o       quadtree.o      png.o rgbapixel.o quadtree_given.o
OBJS_ASAN = main-asan.o  quadtree-asan.o png.o rgbapixel.o quadtree_given.o

EXENAME = mp5

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer


all : $(EXENAME) $(EXENAME)-asan

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(EXENAME)-asan : $(OBJS_ASAN)
	$(LD) $(OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@


%-asan.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $*-asan.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $*.o

main.o:           main.cpp png.h rgbapixel.h quadtree.h quadtree_given.h
main-asan.o:      main.cpp png.h rgbapixel.h quadtree.h quadtree_given.h
quadtree.o:       quadtree.cpp quadtree.h quadtree_given.h png.h rgbapixel.h
quadtree_given.o: quadtree_given.cpp quadtree.h quadtree_given.h png.h rgbapixel.h
png.o:            png.cpp png.h rgbapixel.h
rgbapixel.o:      rgbapixel.cpp rgbapixel.h

clean:
	-rm -f *.o $(EXENAME) $(EXENAME)-asan mp5.out out*.png

tidy: clean
	-rm -rf ./doc

