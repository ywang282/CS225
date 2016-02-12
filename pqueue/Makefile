CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

EXENAME = test_pqueue
OBJS = tester.o

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXENAME)
	$(LD) $(LDFLAGS) $(ASANFLAGS) $(OBJS) -o $(EXENAME)-asan

tester.o: tester.cpp priority_queue.h priority_queue.cpp
	$(CXX) $(CXXFLAGS) -c tester.cpp

clean:
	-rm -rf *.o $(EXENAME)
	-rm -rf *.o $(EXENAME)-asan

tidy:
	-rm -rf doc
