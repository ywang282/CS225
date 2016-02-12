# Copyright 2011 University of Illinois at Urbana-Champaign
# CS 225 Lab 04 C++ Object Oriented Programming
# Authors:
#   Simon Krueger <skruege2@illinois.edu>

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

EXEC = lab_inheritance
MAIN_OBJS = main.o png.o rgbapixel.o vector2.o shape.o rectangle.o line.o
MAIN_OBJS_ASAN = main-asan.o png.o rgbapixel.o vector2.o shape.o rectangle.o line.o

TEST_PURE_VIRTUAL = test_pure_virtual
TEST_PURE_VIRTUAL_OBJS = test_pure_virtual.o truck.o rgbapixel.o png.o vector2.o shape.o circle.o rectangle.o line.o
TEST_PURE_VIRTUAL_OBJS_ASAN = test_pure_virtual-asan.o truck.o rgbapixel.o png.o vector2.o shape.o circle.o rectangle.o line.o

TEST_VIRTUAL = test_virtual
TEST_VIRTUAL_OBJS = test_virtual.o shape.o rectangle.o vector2.o rgbapixel.o png.o line.o
TEST_VIRTUAL_OBJS_ASAN = test_virtual-asan.o shape.o rectangle.o vector2.o rgbapixel.o png.o line.o

TEST_DESTRUCTOR = test_destructor
TEST_DESTRUCTOR_OBJS = test_destructor.o rgbapixel.o png.o triangle.o shape.o vector2.o line.o
TEST_DESTRUCTOR_OBJS_ASAN = test_destructor-asan.o rgbapixel.o png.o triangle.o shape.o vector2.o line.o

TEST_SLICING = test_slicing
TEST_SLICING_OBJS = test_slicing.o rgbapixel.o png.o vector2.o flower.o shape.o triangle.o rectangle.o circle.o line.o
TEST_SLICING_OBJS_ASAN = test_slicing-asan.o rgbapixel.o png.o vector2.o flower.o shape.o triangle.o rectangle.o circle.o line.o

TEST_CONSTRUCTOR = test_constructor
TEST_CONSTRUCTOR_OBJS = test_constructor.o circle.o shape.o rgbapixel.o png.o vector2.o line.o
TEST_CONSTRUCTOR_OBJS_ASAN = test_constructor-asan.o circle.o shape.o rgbapixel.o png.o vector2.o line.o

EXECS = $(EXEC) $(TEST_PURE_VIRTUAL) $(TEST_VIRTUAL) \
        $(TEST_DESTRUCTOR) $(TEST_SLICING) \
        $(TEST_CONSTRUCTOR)

PNGS = out.png test_constructor.png test_destructor.png \
       test_pure_virtual.png test_slicing.png test_virtual.png

.PHONY: all
all: $(EXECS)

$(EXEC): main.o $(MAIN_OBJS)
	$(LD) $(MAIN_OBJS) $(LDFLAGS) -o $@
	$(LD) $(MAIN_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan


$(TEST_PURE_VIRTUAL): $(TEST_PURE_VIRTUAL_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(TEST_PURE_VIRTUAL_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan

$(TEST_VIRTUAL): $(TEST_VIRTUAL_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(TEST_VIRTUAL_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan

$(TEST_DESTRUCTOR): $(TEST_DESTRUCTOR_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(TEST_DESTRUCTOR_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan

$(TEST_CONSTRUCTOR): $(TEST_CONSTRUCTOR_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(TEST_CONSTRUCTOR_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan

$(TEST_SLICING): $(TEST_SLICING_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(TEST_SLICING_OBJS_ASAN) $(ASANFLAGS) $(LDFLAGS) -o $@-asan

circle.o: circle.cpp circle.h shape.h drawable.h png.h rgbapixel.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@

flower.o: flower.cpp flower.h shape.h drawable.h png.h rgbapixel.h vector2.h circle.h color.h rectangle.h triangle.h
	$(CXX) $(CXXFLAGS) $< -o $@

line.o: line.cpp line.h drawable.h png.h rgbapixel.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@

main.o: main.cpp png.h rgbapixel.h color.h rectangle.h shape.h drawable.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o main-asan.o

png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

rectangle.o: rectangle.cpp rectangle.h shape.h drawable.h png.h rgbapixel.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@

rgbapixel.o: rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

shape.o: shape.cpp shape.h drawable.h png.h rgbapixel.h vector2.h color.h line.h
	$(CXX) $(CXXFLAGS) $< -o $@

test_constructor.o: test_constructor.cpp png.h rgbapixel.h color.h shape.h drawable.h vector2.h circle.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o test_constructor-asan.o

test_destructor.o: test_destructor.cpp png.h rgbapixel.h color.h shape.h drawable.h vector2.h triangle.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o test_destructor-asan.o

test_pure_virtual.o: test_pure_virtual.cpp truck.h circle.h shape.h drawable.h png.h rgbapixel.h vector2.h rectangle.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o test_pure_virtual-asan.o

test_slicing.o: test_slicing.cpp png.h rgbapixel.h flower.h shape.h drawable.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o test_slicing-asan.o

test_virtual.o: test_virtual.cpp color.h png.h rgbapixel.h rectangle.h shape.h drawable.h vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o test_virtual-asan.o

triangle.o: triangle.cpp triangle.h shape.h drawable.h png.h rgbapixel.h vector2.h line.h
	$(CXX) $(CXXFLAGS) $< -o $@

truck.o: truck.cpp truck.h circle.h shape.h drawable.h png.h rgbapixel.h vector2.h rectangle.h color.h
	$(CXX) $(CXXFLAGS) $< -o $@

vector2.o: vector2.cpp vector2.h
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean: 
	rm -f *.o $(EXECS) $(PNGS) $(patsubst %, %-asan, $(EXECS))
	
