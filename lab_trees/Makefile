#
# USING THIS MAKEFILE:
#
#  'make treefun' - creates test executable
#

EXENAME = treefun

OBJS = 		main.o coloredout.o
OBJS_ASAN = main-asan.o coloredout.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : $(EXENAME) $(EXENAME)-asan

$(EXENAME): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(EXENAME)-asan: $(OBJS_ASAN)
	$(LD) $(LDFLAGS) $(ASANFLAGS) $(OBJS_ASAN) -o $@


%-asan.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $*-asan.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $*.o

main.o: main.cpp binarytree.h binarytree.cpp binarytree_given.cpp coloredout.h random.h
coloredout.o: coloredout.cpp coloredout.h

clean:
	rm -f *.o $(EXENAME)

tidy: clean
	rm -rf ./doc
