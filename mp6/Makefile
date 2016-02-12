EXE = photomosaic
EXE_KDTREE = testkdtree
EXE_MAPTILES = testmaptiles

OBJS_DIR = objs
OBJS_DIR_STUDENT = $(OBJS_DIR)/student
OBJS_DIR_PROVIDED = $(OBJS_DIR)/provided

OBJS_STUDENT = maptiles.o
OBJS_PROVIDED = photomosaic.o util.o mosaiccanvas.o sourceimage.o  rgbapixel.o png.o coloredout.o tileimage.o
OBJS_KDTREE_STUDENT = testkdtree.o
OBJS_KDTREE_PROVIDED = coloredout.o
OBJS_MAPTILES_STUDENT = testmaptiles.o
OBJS_MAPTILES_PROVIDED = mosaiccanvas.o sourceimage.o maptiles.o rgbapixel.o png.o coloredout.o tileimage.o

CXX = clang++
LD = clang++
# -msse2 is to try to make floating point arithmetic as uniform as possible across different systems,
# so that output images can be diffed
WARNINGS = -Wall -Werror -Wfatal-errors -Wextra -pedantic
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g $(WARNINGS) -msse2
CXXFLAGS_PROVIDED = -O2
CXXFLAGS_STUDENT = -O0
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all : $(EXE) $(EXE)-asan $(EXE_KDTREE) $(EXE_KDTREE)-asan $(EXE_MAPTILES) $(EXE_MAPTILES)-asan
check : $(EXE_KDTREE) $(EXE_MAPTILES)
	./$(EXE_KDTREE)
	./$(EXE_MAPTILES)

# Pattern rules for object files
$(OBJS_DIR_STUDENT)/%-asan.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_PROVIDED)/%-asan.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $(ASANFLAGS) $< -o $@
$(OBJS_DIR_STUDENT)/%.o: %.cpp | $(OBJS_DIR_STUDENT)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $< -o $@
$(OBJS_DIR_PROVIDED)/%.o: %.cpp | $(OBJS_DIR_PROVIDED)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_PROVIDED) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
$(OBJS_DIR_STUDENT):
	@mkdir -p $(OBJS_DIR_STUDENT)
$(OBJS_DIR_PROVIDED):
	@mkdir -p $(OBJS_DIR_PROVIDED)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_KDTREE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_MAPTILES):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):               $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_STUDENT))          $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan:          $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_STUDENT))          $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_PROVIDED))
$(EXE_KDTREE):        $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_KDTREE_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_KDTREE_PROVIDED))
$(EXE_KDTREE)-asan:   $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_KDTREE_STUDENT))   $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_KDTREE_PROVIDED))
$(EXE_MAPTILES):      $(patsubst %.o, $(OBJS_DIR_STUDENT)/%.o,      $(OBJS_MAPTILES_STUDENT)) $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAPTILES_PROVIDED))
$(EXE_MAPTILES)-asan: $(patsubst %.o, $(OBJS_DIR_STUDENT)/%-asan.o, $(OBJS_MAPTILES_STUDENT)) $(patsubst %.o, $(OBJS_DIR_PROVIDED)/%.o, $(OBJS_MAPTILES_PROVIDED))


# Automatically generated dependencies
$(OBJS_DIR_PROVIDED)/coloredout.o:       coloredout.cpp coloredout.h
$(OBJS_DIR_PROVIDED)/mosaiccanvas.o:     mosaiccanvas.cpp mosaiccanvas.h png.h rgbapixel.h tileimage.h util.h
$(OBJS_DIR_PROVIDED)/photomosaic.o:      photomosaic.cpp png.h rgbapixel.h maptiles.h kdtree.h coloredout.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h mosaiccanvas.h tileimage.h sourceimage.h util.h
$(OBJS_DIR_PROVIDED)/png.o:              png.cpp png.h rgbapixel.h
$(OBJS_DIR_PROVIDED)/rgbapixel.o:        rgbapixel.cpp rgbapixel.h
$(OBJS_DIR_PROVIDED)/sourceimage.o:      sourceimage.cpp sourceimage.h png.h rgbapixel.h
$(OBJS_DIR_PROVIDED)/tileimage.o:        tileimage.cpp tileimage.h png.h rgbapixel.h
$(OBJS_DIR_PROVIDED)/util.o:             util.cpp util.h
$(OBJS_DIR_STUDENT)/maptiles-asan.o:     maptiles.cpp maptiles.h png.h rgbapixel.h kdtree.h coloredout.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h mosaiccanvas.h tileimage.h sourceimage.h
$(OBJS_DIR_STUDENT)/maptiles.o:          maptiles.cpp maptiles.h png.h rgbapixel.h kdtree.h coloredout.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h mosaiccanvas.h tileimage.h sourceimage.h
$(OBJS_DIR_STUDENT)/testkdtree-asan.o:   testkdtree.cpp coloredout.h kdtree.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h
$(OBJS_DIR_STUDENT)/testkdtree.o:        testkdtree.cpp coloredout.h kdtree.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h
$(OBJS_DIR_STUDENT)/testmaptiles-asan.o: testmaptiles.cpp maptiles.h png.h rgbapixel.h kdtree.h coloredout.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h mosaiccanvas.h tileimage.h sourceimage.h
$(OBJS_DIR_STUDENT)/testmaptiles.o:      testmaptiles.cpp maptiles.h png.h rgbapixel.h kdtree.h coloredout.h point.h point.cpp kdtree.cpp kdtree_extras.cpp no_sort.h mosaiccanvas.h tileimage.h sourceimage.h

clean:
	rm -rf {$(EXE),$(EXE_KDTREE),$(EXE_MAPTILES)}{,-asan} objs

tidy: clean
	rm -rf doc

.PHONY: all tidy clean check
