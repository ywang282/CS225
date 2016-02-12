EXE = testavl

OBJS = coloredout.o main.o
OBJS_ASAN = coloredout.o main-asan.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wfatal-errors -Werror -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : $(EXE) $(EXE)-asan

$(EXE) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(EXE)-asan : $(OBJS_ASAN)
	$(LD) $(OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@

%-asan.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $*-asan.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $*.o

main.o: main.cpp avltree.h avltree_given.cpp avltree.cpp printtree.h coloredout.h
main-asan.o: main.cpp avltree.h avltree_given.cpp avltree.cpp printtree.h coloredout.h

coloredout.o: coloredout.cpp coloredout.h 

clean:
	-rm -f *.o $(EXE) $(EXE)-asan

tidy:
	-rm -rf ./doc
