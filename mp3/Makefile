EXENAME = mp3test

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer
MSANFLAGS = -fsanitize=memory

MAIN_OBJS = main.o png.o rgbapixel.o blockpng.o
MAIN_OBJS_ASAN = main-asan.o png.o rgbapixel.o blockpng.o
MAIN_OBJS_MSAN = main-msan.o png-msan.o rgbapixel-msan.o blockpng-msan.o

CODE_CLN = *.o $(EXENAME) $(EXENAME)-asan

IMAG_CLN = waterfall*.png unshuffled*.png reverse*.png merge*.png split*.png

all: $(EXENAME)

$(EXENAME) : main.o png.o rgbapixel.o blockpng.o
	$(LD) $(MAIN_OBJS) $(LDFLAGS) -o $(EXENAME)
	$(LD) $(MAIN_OBJS_ASAN) $(LDFLAGS) $(ASANFLAGS) -o $(EXENAME)-asan
	$(LD) $(MAIN_OBJS_MSAN) $(LDFLAGS) $(MSANFLAGS) -o $(EXENAME)-msan

main.o: main.cpp list.h list_given.h list.cpp list_given.cpp blockpng.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) main.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) main.cpp -o main-asan.o
	$(CXX) $(CXXFLAGS) $(MSANFLAGS) main.cpp -o main-msan.o

png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp
	$(CXX) $(CXXFLAGS) $(MSANFLAGS) png.cpp -o png-msan.o

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
	$(CXX) $(CXXFLAGS) $(MSANFLAGS) rgbapixel.cpp -o rgbapixel-msan.o

blockpng.o: blockpng.cpp blockpng.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) blockpng.cpp
	$(CXX) $(CXXFLAGS) $(MSANFLAGS) blockpng.cpp -o blockpng-msan.o

clean:
	-rm -f $(CODE_CLN) $(IMAG_CLN)
