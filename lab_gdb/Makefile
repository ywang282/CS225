EXENAME = lab_gdb

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -w
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
MSANFLAGS = -fsanitize=memory

MAIN_OBJS_ALL 	= png.o rgbapixel.o blockpng.o
MAIN_OBJS 		= $(MAIN_OBJS_ALL) main.o
MAIN_OBJS_ASAN 	= $(MAIN_OBJS_ALL) main-asan.o
MAIN_OBJS_MSAN 	= $(MAIN_OBJS_ALL:.o=-msan.o) main-msan.o

all: $(EXENAME) $(EXENAME)-asan $(EXENAME)-msan

$(EXENAME) : $(MAIN_OBJS)
	$(LD) $(LDFLAGS) $(MAIN_OBJS) -o $@

$(EXENAME)-asan : $(MAIN_OBJS_ASAN)
	$(LD) $(LDFLAGS) $(ASANFLAGS) $(MAIN_OBJS_ASAN) -o $@

$(EXENAME)-msan : $(MAIN_OBJS_MSAN)
	$(LD) $(LDFLAGS) $(MSANFLAGS) $(MAIN_OBJS_MSAN) -o $@

%-asan.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $*-asan.o

%-msan.o : %.cpp
	$(CXX) $(CXXFLAGS) $(MSANFLAGS) $< -o $*-msan.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $*.o

main.o:      blockpng.h png.h rgbapixel.h  list.h list.cpp list_given.h list_given.cpp
main-asan.o: blockpng.h png.h rgbapixel.h  list.h list.cpp list_given.h list_given.cpp
main-msan.o: blockpng.h png.h rgbapixel.h  list.h list.cpp list_given.h list_given.cpp
blockpng.o:  blockpng.h png.h rgbapixel.h
png.o:       png.h rgbapixel.h
rgbapixel.o: rgbapixel.h

clean:
	-rm -f *.o reverse*.png $(EXENAME) $(EXENAME)-asan $(EXENAME)-msan
