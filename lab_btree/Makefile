CXX = clang++
LD = clang++
CXXFLAGS = -c -g -std=c++1y -stdlib=libc++ -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi
DICT_RACER_OBJS = dict_racer.o
TEST_BTREE_OBJS = test_btree.o
EXES = dict_racer test_btree
RESULT_DIR = results

all: $(EXES)

$(RESULT_DIR):
	@mkdir -p $@

test_btree : $(TEST_BTREE_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

dict_racer : $(DICT_RACER_OBJS) | $(RESULT_DIR)
	$(CXX) $(LDFLAGS) -O3 $^ -o $@

dict_racer.o : dict_racer.cpp btree.h btree_given.cpp btree.cpp benchmark.h
	$(CXX) $(CXXFLAGS) -O3 $< -o $@

test_btree.o : test_btree.cpp btree.h btree_given.cpp btree.cpp
	$(CXX) $(CXXFLAGS) -O0 $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXES) $(TEST_BTREE_OBJS) $(DICT_RACER_OBJS) $(RESULT_DIR)


