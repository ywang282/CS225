# MODIFY THIS LINE TO INCLUDE ANY NEW OBJECT FILES YOU CREATE
OBJS =

# YOU DO NOT (AND SHOULD NOT) NEED TO MODIFY THE MAKEFILE BELOW THIS LINE

EXENAME = sort

COMPILER = g++ -fopenmp
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O3 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++ -fopenmp

all: $(EXENAME)

$(EXENAME) : $(OBJS) main.o
	$(LINKER) -o $(EXENAME) $(OBJS) main.o

%.o : %.cpp $(wildcard *.h) $(wildcard *.cpp)
	$(COMPILER) $(COMPILER_OPTS) $(@:.o=.cpp) -o $@

clean:
	-rm -f *.o $(EXENAME)
