//
//  HuffmanFunctions.cpp
//  HuffmanCoding
//
//  Created by Eunice Oh on 8/8/20.
//  Copyright © 2020 Eunice Oh. All rights reserved.
//

#include "HuffmanFunctions.hpp"
#include "InternalNode.hpp"
#include <iostream>
#include <string>
#include <map>
#include <queue>

//#define DEBUGGING

using namespace std;

void create_frequency_table(map<char,int> &charFreq, string text)
{
    // inserting unique chars & their weight in map
    for(int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        map<char,int>::iterator itr = charFreq.find(c);
        if(itr != charFreq.end())
        {
            charFreq[c] += 1;
        } else {
            charFreq[c] = 1;
        }
    }
}

// iterate through map that contain codes
void display_frequency(map<char,int> freqMap)
{
    for(map<char,int>::iterator itr = freqMap.begin(), end = freqMap.end(); itr != end; ++itr)
    {
        cout << "Char: " << itr->first << " Frequency: " << itr->second << endl;
    }
}

InternalNode * create_huffman_tree(string test) // change into file
{
    // data structures:
        priority_queue<InternalNode *, vector<InternalNode *>, node_cmp> nodeQueue;
        map<char,int> charFreq;
        
        // inserting unique chars & their weight in map
        for(int i = 0; i < test.length(); i++)
        {
            char c = test[i];
            map<char,int>::iterator itr = charFreq.find(c);
            if(itr != charFreq.end())
            {
                charFreq[c] += 1;
            } else {
                charFreq[c] = 1;
            }
        }
        
    #ifdef DEBUGGING
        // print contents of map
        for(map<char,int>::iterator itr = charFreq.begin(), end = charFreq.end(); itr!=end; ++itr)
        {
            cout << itr->first << "-->" << itr->second << endl;
        }
        
    #endif
    
    // pushing each leafNode into queue
    for(map<char,int>::iterator itr = charFreq.begin(), end = charFreq.end(); itr!=end; ++itr)
    {
        InternalNode * leafNode = new InternalNode(itr->first, itr->second);
        // another way to construct object:
        // InternalNode node(itr->first, itr->second);
        nodeQueue.push(leafNode);
    }
      
    #ifdef DEBUGGING // if NOT defined
        cout << "Order of Nodes: " << endl;
        
        while(!nodeQueue.empty())
        {
            cout << nodeQueue.top()->_letter << endl;
            nodeQueue.pop();
        }
        
    #endif
    
    // next step: loop through the priority queue
    // pop the first two nodes
    
    while(nodeQueue.size() > 1)
    {
        InternalNode * childA = nodeQueue.top();
        nodeQueue.pop();
        InternalNode * childB = nodeQueue.top();
        nodeQueue.pop();
        
        #ifdef DEBUGGING
        cout << "Child Weights: " << childA->_weight << " " << childB->_weight << endl;
        #endif
        
        InternalNode * parentNode = new InternalNode();
        parentNode->_leftChild = childA;
        childA->_parent = parentNode;
        
        parentNode->_rightChild = childB;
        childB->_parent = parentNode;
        
        parentNode->_weight = childA->_weight + childB->_weight; // can use -> to call a function
        
        #ifdef DEBUGGING
        cout << "Parent Weight: " << parentNode->_weight << endl;
        #endif
        
        nodeQueue.push(parentNode);
    }
    
    return nodeQueue.top();
}

// only print leaf nodes
// kinda useless now
void display_tree(InternalNode * root) // should root be part of class definition?
{
    if(root == NULL)
    {
        return;
    }
    
    if(root->_parent != NULL)
    {
        InternalNode * p = root->_parent;
        if(root == p->_leftChild)
        {
            cout << "Left from Parent" << endl;
        } else if(root == p->_rightChild)
        {
            cout << "Right from Parent" << endl;
        }
    }

    // reached a leaf node
    if(root->isLeafNode())
    {
        cout << "Reached A Leaf Node: " <<  root->_letter << endl;
    }
    
    display_tree(root->_leftChild);
    display_tree(root->_rightChild);
}

// follows every root-to-leaf path, indicating a 0 for a left edge or a 1 for a right edge
// maps contains every uniqiue character and associated code
void compressing(InternalNode * root, map<char,string> &encoding, string code)
{
    if(root == NULL)
    {
        return;
    }
    
    //cout << "Weight: " << root->_weight << endl;
    
    if(root->_parent != NULL) // if node is not the root
    {
        InternalNode * p = root->_parent;
        if(root == p->_leftChild) // if node is a left child, append 0
        {
            code += '0';
            //cout << "Left" << endl;
        } else if(root == p->_rightChild) // or if node is right child, append 1
        {
            code += '1';
            //cout << "Right" << endl;
        }
    }
    
    if(root->isLeafNode()) // reached a leaf node
    {
        //cout << "Reached A Leaf Node: " << root->_letter << endl;
        //cout << code << endl;
        encoding[root->_letter] = code;
        code = "";
    }
    compressing(root->_leftChild, encoding, code);
    compressing(root->_rightChild, encoding, code);
}


// print character codes
void display_encodings(map<char,string> encodings)
{
    for(map<char,string>::iterator itr = encodings.begin(), end = encodings.end(); itr != end; ++itr)
    {
        cout << "Char: " << itr->first << " Code: " << itr->second << endl;
    }
}

// print character statistics
void display_statistics(map<char,int> frequency, map<char,string> encodings)
{
    int totalCost = 0;
    for(map<char,string>::iterator itr = encodings.begin(), end = encodings.end(); itr != end; ++itr)
    {
        char c = itr->first;
        string code = itr->second;
        
        int weight = frequency[c];
        int cost = (int) code.length() * weight; // costs: code length * character weight
        totalCost += cost;
        
        cout << "Char: " << c << "\t" << " Weight: " << weight << "\t" <<
        " Code: " << code << "\t" << " Cost: " << cost << endl;
    }
    
    cout << "Total Cost: " << totalCost << endl;
}

// returns encoded text for a string
string complete_encoding(map<char,string> encodings, string input)
{
    string toReturn;
    for(int i = 0; i < input.length(); ++i)
    {
        char c = input[i];
        toReturn += encodings[c];
    }
    return toReturn;
}

// returns decoded text for a string
string complete_decoding(InternalNode * root, string code)
{
    InternalNode * findLeafNode = root;
    string decoding;
    
    for(int i = 0; i < code.length(); ++i)
    {
        
        if(code[i] == '0')
        {
            findLeafNode = findLeafNode->_leftChild;
        } else {
            findLeafNode = findLeafNode->_rightChild;
        }
        
        // found leaf node
        if(findLeafNode->isLeafNode())
        {
            decoding += findLeafNode->_letter;
            findLeafNode = root;
        }
    }
    return decoding;
}

