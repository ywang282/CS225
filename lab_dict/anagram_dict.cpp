/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> //for sort()
#include <fstream>
#include <iostream>t
using std::string;
using std::vector;
using std::ifstream;
using namespace std;
/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
	vector<std::string> list;
	ifstream words(filename);
	string word;
	if(words.is_open()) {
   		 while(getline(words, word)) {
        		list.push_back(word);
    		}
	}
	for(size_t i=0;i<list.size();i++){
   	
    string word=list[i];
   	sort(word.begin(),word.end());
    dict[word].push_back(list[i]);


    for(int j=0;j<dict[word].size()-1;j++){
      if(dict[word][j].compare(list[i])==0){
        dict[word].pop_back();
      }
    }
   
   	
  }
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
   for(size_t i=0;i<words.size();i++){
   	  string word=words[i];
   	  sort(word.begin(),word.end());
      dict[word].push_back(words[i]);
     for(int j=0;j<dict[word].size()-1;j++){
          if(dict[word][j].compare(words[i])==0){

                 dict[word].pop_back();
        
          }
    }
  }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
	string sorted=word;
	sort(sorted.begin(),sorted.end());
	auto lookup=dict.find(sorted);
	if(lookup!=dict.end()){
		return lookup->second;
	}
	else{
		vector<string> out;
		return out;
	}
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> out;
    for(auto it=dict.begin();it!=dict.end();it++){
    	if((it->second).size()>=2){
    		out.push_back(it->second);
    	}
    }
    return out;
}


