//
//  main.cpp
//  HuffmanCoding
//
//  Created by Eunice Oh on 8/6/20.
//  Copyright © 2020 Eunice Oh. All rights reserved.
//

#include "InternalNode.hpp"
#include "HuffmanFunctions.hpp"
#include <iostream>
using namespace std;

void destroy_tree(InternalNode * root)
{
    if(root == NULL)
    {
        return;
    }
    destroy_tree(root->_leftChild);
    destroy_tree(root->_rightChild);
    delete root;
}

int main() {
    
    cout << "Enter Text: ";
    string test;
    getline(cin, test);
    
    cout << "Input Text: " << test << endl;
    
    map<char,int> charFreq;
    create_frequency_table(charFreq, test);
    
    InternalNode * root = create_huffman_tree(test);
    
    string bitSequence;
    map<char,string> _encodings;
    compressing(root, _encodings, bitSequence);
    //display_encodings(_encodings);
    display_statistics(charFreq, _encodings);
    
    cout << "Encoded Text: " << endl;
    string encodedText = complete_encoding(_encodings, test);
    cout << encodedText << endl;
    
    cout << "Decoded Text Using Encoded Text: " << endl;
    string decodedText = complete_decoding(root, encodedText);
    cout << decodedText << endl;
    
    destroy_tree(root);
    
    return 0;
}

