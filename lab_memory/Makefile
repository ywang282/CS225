CXX = clang++
ifdef asan
ASANFLAGS = -fsanitize=address
endif
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic $(ASANFLAGS)
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi $(ASANFLAGS)

OBJECTS = main.o letter.o room.o allocator.o fileio.o

allocate : $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o allocate

main.o : main.cpp allocator.h letter.h room.h fileio.h
	$(CXX) $(CXXFLAGS) main.cpp

letter.o: letter.h letter.cpp
	$(CXX) $(CXXFLAGS) letter.cpp

room.o: room.h room.cpp letter.h
	$(CXX) $(CXXFLAGS) room.cpp

allocator.o: allocator.h allocator.cpp room.h letter.h fileio.h
	$(CXX) $(CXXFLAGS) allocator.cpp

fileio.o : fileio.h fileio.cpp room.h
	$(CXX) $(CXXFLAGS) fileio.cpp

clean : 
	-rm -f *.o allocate

tidy: clean
	-rm -rf ./doc
