/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str) 
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), 
                        std::back_inserter(ret),
                        std::ptr_fun< int, int >(&std::ispunct));
    return ret;
}

/**
 * Constructs a CommonWords object from a vector of filenames. 
 * file_word_maps is a vector of maps, where each element of the vector represents a different file,
 * and the map hashes a word in the file to the number of time that word has been seen.
 * common is a map of words in all files that hashes to how many files it appeared in.
 * @param filenames The vector of strings where the strings are the filenames to read in.
 */
CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes common, mapping a word to the number of documents it shows up in.
 */
void CommonWords::init_common() 
{
    for(size_t i=0;i<file_word_maps.size();i++){
    	for(auto it=file_word_maps[i].begin();it!=file_word_maps[i].end();it++){
    		common[it->first]++;
    	}
    }
    
}

/**
 * Initializes file_word_maps, having each index hold a map going from the word 
 * seen in that file to the number of times the word has been seen
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames) 
{
    // vector is equal to number of files given
    file_word_maps.resize(filenames.size());

    // go through all files
    for(size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);
        for(size_t j=0;j<words.size();j++){
        	file_word_maps[i][words[j]]++;
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. Vector contains all words that appear in all
 * files >= n times. I.e. the word must appear in all files more than 
 * n times.
 */
vector< string > CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
     for(auto it=common.begin();it!=common.end();it++){
     	if(it->second==file_word_maps.size()){
	     	bool get=true;
	     	for(size_t i=0;i<file_word_maps.size();i++){
	     		auto count_itr=file_word_maps[i].find(it->first);
	     		if(count_itr->second<n){
	     			get=false;
	     		}
	     	}
	     	if(get){
	     		out.push_back(it->first);
	     	}
	}
     }
       
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector< string > CommonWords::file_to_vector(const string& filename) const {
    ifstream words(filename);
    vector<string> out;

    if(words.is_open()) {
        std::istream_iterator<std::string> word_iter(words);
        while(!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
