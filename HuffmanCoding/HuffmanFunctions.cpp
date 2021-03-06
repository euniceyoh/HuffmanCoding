
/*
File: HuffmanFunctions.cpp

This is the implementation for creating a Huffman coding tree, and compressing and decompressing text.
*/

#include "HuffmanFunctions.hpp"
#include "InternalNode.hpp"
#include <iostream>
#include <string>
#include <map>
#include <queue>

//#define DEBUGGING

using namespace std;

/*
 Function:
 Usage:
 
 Stores character and its associated frequencies (weight) in a map.
 */

void create_frequency_table(map<char,int> &charFreq, string text)
{
    for(char c: text)
    {
        map<char,int>::iterator itr = charFreq.find(c);
        if(itr != charFreq.end())
        {
            charFreq[c] += 1;
        } else {
            charFreq[c] = 1;
        }
    }
}

/*
 Function:
 Usage:
 
 Display the map of characters and its associated freqeuncies. Used to debug.
 */

void display_frequency(map<char,int> freqMap)
{
    for(map<char,int>::iterator itr = freqMap.begin(), end = freqMap.end(); itr != end; ++itr)
    {
        cout << itr->first << "-->" << itr->second << endl;
    }
}

/*
 Debugging
 need to add to header file too
 */

//void displayPriorityQueue(priority_queue<InternalNode *, vector<InternalNode> *, node_cmp> nodeQueue)
//{
//    cout << "Order of Nodes: " << endl;
//
//    while(!nodeQueue.empty())
//    {
//        InternalNode * aNode = nodeQueue.top();
//        cout << aNode->getLetter() << " -> " << aNode-> getWeight() << endl;
//        nodeQueue.pop();
//    }
//}

/*
 Function:
 Usage:
 
 8/26 Update: included parameter for map
 
 Returns root node ...
 */

InternalNode * create_huffman_tree(map<char,int> charFreq, string test)
{
    priority_queue<InternalNode *, vector<InternalNode *>, node_cmp> nodeQueue;
    
    // pushing each leafNode into queue
    for(map<char,int>::iterator itr = charFreq.begin(), end = charFreq.end(); itr!=end; ++itr)
    {
        InternalNode * leafNode = new InternalNode(itr->first, itr->second); // itr->first = char; itr->second = weight;
        nodeQueue.push(leafNode);
    }
    
    // next step: loop through the priority queue
    // pop the first two nodes
    
    while(nodeQueue.size() > 1)
    {
        InternalNode * childA = nodeQueue.top();
        nodeQueue.pop();
        InternalNode * childB = nodeQueue.top();
        nodeQueue.pop();
        
        InternalNode * parentNode = new InternalNode();
        parentNode->_leftChild = childA;
        parentNode->_rightChild = childB;
        
        childA->_parent = parentNode;
        childB->_parent = parentNode;
        
        parentNode->setWeight(childA->_weight + childB->_weight);
        
        #ifdef DEBUGGING
        cout << "Parent Weight: " << parentNode->_weight << endl;
        #endif
        
        nodeQueue.push(parentNode);
    }
    
    return nodeQueue.top();
}

/*
 Function:
 Usage:
 
 Prints leaf nodes
 */

void display_tree(InternalNode * root)
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

/*
 Function:
 Usage:
 
 root, map, string
 
 follows every root-to-leaf path, indicating a 0 for a left edge or a 1 for a right edge
 maps contains every unique character and associated code
 
 */

void compressing(InternalNode * root, map<char,string> &encoding, string code)
{
    if(root == NULL)
    {
        return;
    }
    
    if(root->_parent != NULL) // if node is not the root
    {
        InternalNode * p = root->_parent;
        if(root == p->_leftChild) // if node is a left child, append 0
        {
            code += '0';
        } else if(root == p->_rightChild) // or if node is right child, append 1
        {
            code += '1';
        }
    }
    
    if(root->isLeafNode()) // reached a leaf node
    {
        encoding[root->getLetter()] = code;
        code = "";
    }
    
    compressing(root->_leftChild, encoding, code);
    compressing(root->_rightChild, encoding, code);
}


// prints character codes
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
        
        cout << "Char: " << c << "\t" << " Weight: " << weight << "\t" << " Code: " << code << "\t" << " Cost: " << cost << endl;
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
