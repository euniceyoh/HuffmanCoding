
/*
 File: HuffmanFunctions.hpp
 
 This is the interface for creating a Huffman coding tree, and compressing and decompressing text.
 */

#ifndef HuffmanFunctions_hpp
#define HuffmanFunctions_hpp

#include "InternalNode.hpp"
#include <map>
#include <queue>
#include <stdio.h>

using namespace std;

void create_frequency_table(map<char,int> &charFreq, string text);
void display_frequency(map<char,int> freqMap);

void displayPriorityQueue(priority_queue<InternalNode *, vector<InternalNode *>, node_cmp> nodeQueue);

InternalNode * create_huffman_tree(map<char,int> charFreq, string test);
void display_tree(InternalNode * root);
void compressing(InternalNode * root, map<char,string> &encoding, string code);
void display_encodings(map<char,string> encodings);
void display_statistics(map<char,int> frequency, map<char,string> encodings);
string complete_encoding(map<char,string> encodings, string input);
string complete_decoding(InternalNode * root, string code);
void destroy_tree(InternalNode * root);

#endif /* HuffmanFunctions_hpp */
