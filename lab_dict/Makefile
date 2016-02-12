CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

OBJ_DIR = obj
ANAGRAM_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, anagram_finder.o anagram_dict.o)
FIB_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, fib.o fib_generator.o)
FAC_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, fac.o)
HOMOPHONE_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, homophone_puzzle.o pronounce_dict.o cartalk_puzzle.o)
FIND_COMMON_WORDS_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, find_common_words.o common_words.o)
EXES = anagram_finder fib_generator fac homophone_puzzle find_common_words

all: $(EXES)

$(OBJ_DIR):
	@mkdir -p $@

anagram_finder: $(ANAGRAM_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

fib_generator: $(FIB_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

fac: $(FAC_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

homophone_puzzle: $(HOMOPHONE_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

find_common_words: $(FIND_COMMON_WORDS_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/anagram_finder.o: anagram_finder.cpp anagram_dict.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/fib.o: fib.cpp fib.h | $(OBJ_DIR) 
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/fib_generator.o: fib_generator.cpp fib.h | $(OBJ_DIR) 
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/fac.o: fac.cpp fac.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/homophone_puzzle.o: homophone_puzzle.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/find_common_words.o: find_common_words.cpp common_words.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/common_words.o: common_words.cpp common_words.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/pronounce_dict.o: pronounce_dict.cpp pronounce_dict.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/cartalk_puzzle.o: cartalk_puzzle.cpp cartalk_puzzle.h pronounce_dict.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/anagram_dict.o: anagram_dict.cpp anagram_dict.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(EXES)
