TESTFILLS_OBJS = testFills.o animation.o rgbapixel.o png.o solidColorPicker.o gridColorPicker.o gradientColorPicker.o rainbowColorPicker.o
TESTFILLS_OBJS_ASAN = testFills-asan.o animation.o rgbapixel.o png.o solidColorPicker.o gridColorPicker.o gradientColorPicker.o rainbowColorPicker.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: testFills testStackQueue

testFills: $(TESTFILLS_OBJS)
	$(LD) $(TESTFILLS_OBJS) $(LDFLAGS) -o testFills
	$(LD) $(TESTFILLS_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o testFills-asan

testStackQueue: testStackQueue.o
	$(LD) $(LDFLAGS) testStackQueue.o -o testStackQueue
	$(LD) $(LDFLAGS) testStackQueue-asan.o $(ASANFLAGS) -o testStackQueue-asan

testStackQueue.o: testStackQueue.cpp stack.h ordering_structure.h stack.cpp queue.h queue.cpp
	$(CXX) $(CXXFLAGS) testStackQueue.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) testStackQueue.cpp -o testStackQueue-asan.o

testFills.o: testFills.cpp png.h rgbapixel.h filler.h stack.h ordering_structure.h stack.cpp queue.h queue.cpp solidColorPicker.h colorPicker.h gridColorPicker.h gradientColorPicker.h animation.h filler.cpp rainbowColorPicker.h
	$(CXX) $(CXXFLAGS) testFills.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) testFills.cpp -o testFills-asan.o

png.o: png.h png.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o: rgbapixel.h rgbapixel.cpp
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

animation.o: animation.cpp animation.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) animation.cpp

solidColorPicker.o: solidColorPicker.cpp solidColorPicker.h colorPicker.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) solidColorPicker.cpp

gridColorPicker.o: gridColorPicker.cpp gridColorPicker.h colorPicker.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) gridColorPicker.cpp

gradientColorPicker.o: gradientColorPicker.cpp gradientColorPicker.h colorPicker.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) gradientColorPicker.cpp

rainbowColorPicker.o: rainbowColorPicker.cpp rainbowColorPicker.h colorPicker.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) rainbowColorPicker.cpp

doc: $(wildcard *.h) $(wildcard *.cpp)
	doxygen mp4.doxygen

clean:
	-rm -rf testFills testFills-asan testStackQueue testStackQueue-asan *.o images/ frames/ doc/ testStackQueue.out testFills.out

