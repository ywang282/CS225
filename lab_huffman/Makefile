CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

DECODER = decoder
ENCODER = encoder
PRINTER = print_as_ascii

EXES = $(DECODER) $(ENCODER) $(PRINTER)

ENC_OBJS = huffman_tree.o frequency.o encoder.o encoder_prog.o binary_file_writer.o binary_file_reader.o
ENC_OBJS_ASAN = huffman_tree.o frequency.o encoder.o encoder_prog-asan.o binary_file_writer.o binary_file_reader.o
DEC_OBJS = huffman_tree.o frequency.o decoder.o decoder_prog.o binary_file_writer.o binary_file_reader.o
DEC_OBJS_ASAN = huffman_tree.o frequency.o decoder.o decoder_prog-asan.o binary_file_writer.o binary_file_reader.o
PRINT_OBJS = binary_file_reader.o print_as_ascii.o

all: $(EXES)

$(ENCODER): $(ENC_OBJS)
	$(LD) $(LDFLAGS) $(ENC_OBJS) -o $(ENCODER)
	$(LD) $(LDFLAGS) $(ASANFLAGS) $(ENC_OBJS) -o $(ENCODER)-asan

$(DECODER): $(DEC_OBJS)
	$(LD) $(LDFLAGS) $(DEC_OBJS) -o $(DECODER)
	$(LD) $(LDFLAGS) $(DEC_OBJS) $(ASANFLAGS) -o $(DECODER)-asan
				 
$(PRINTER): $(PRINT_OBJS)
	$(LD) $(LDFLAGS) $(PRINT_OBJS) -o $(PRINTER)

frequency.o: frequency.h frequency.cpp
	$(CXX) $(CXXFLAGS) frequency.cpp

huffman_tree.o: binary_file_reader.h binary_file_writer.h frequency.h huffman_tree.h huffman_tree.cpp
	$(CXX) $(CXXFLAGS) huffman_tree.cpp

binary_file_reader.o: binary_file_reader.h binary_file_reader.cpp
	$(CXX) $(CXXFLAGS) binary_file_reader.cpp

binary_file_writer.o: binary_file_writer.h binary_file_writer.cpp
	$(CXX) $(CXXFLAGS) binary_file_writer.cpp

encoder.o: encoder.h encoder.cpp frequency.h binary_file_writer.h
	$(CXX) $(CXXFLAGS) encoder.cpp

encoder_prog.o: encoder.h encoder_prog.cpp
	$(CXX) $(CXXFLAGS) encoder_prog.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) encoder_prog.cpp -o encoder_prog-asan.o

decoder.o: decoder.h decoder.cpp frequency.h binary_file_reader.h
	$(CXX) $(CXXFLAGS) decoder.cpp

decoder_prog.o: decoder.h decoder_prog.cpp
	$(CXX) $(CXXFLAGS) decoder_prog.cpp
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) decoder_prog.cpp -o decoder_prog-asan.o

print_as_ascii.o: binary_file_reader.h print_as_ascii.cpp
	$(CXX) $(CXXFLAGS) print_as_ascii.cpp

doc: lab_huffman.doxygen
	doxygen lab_huffman.doxygen

tidy:
	-rm -rf *.bin *.txt *.huff

clean:
	-rm -rf *.o $(EXES) decoder-asan encoder-asan doc
