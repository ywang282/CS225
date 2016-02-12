#
# USING THIS MAKEFILE:
#
#  'make quackfun' - creates test executable
#

OBJS = main.o exercises.o
OBJS_ASAN = main-asan.o exercises.o
EXENAME = quackfun

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXENAME)
	$(LD) $(LDFLAGS) $(ASANFLAGS) $(OBJS_ASAN) -o $(EXENAME)-asan

main.o : main.cpp quackfun.h quackfun.cpp exercises.h
	$(CXX) $(CXXFLAGS) main.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) main.cpp -o main-asan.o

exercises.o : exercises.cpp exercises.h
	$(CXX) $(CXXFLAGS) exercises.cpp


clean : 
	rm -f *.o $(EXENAME) $(EXENAME)-asan

tidy: clean
	rm -rf ./doc
