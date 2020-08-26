
/*
 File: InternalNode.hpp
 
 This is the interface for a Huffman tree node.
 */

#ifndef InternalNode_hpp
#define InternalNode_hpp

#include <stdio.h>
#include <string>

using namespace std;

class InternalNode{
public:
    InternalNode(char c, int weight);   // Leaf Node Constructor
    InternalNode();                     // Regular Constructor
    //~InternalNode();                  // Destructor
    char getLetter();
    int getWeight();
    void setWeight(int w);
    bool isLeafNode();
    
    
public:
    char _letter;
    int _weight;
    InternalNode * _leftChild;
    InternalNode * _rightChild;
    InternalNode * _parent;
};

struct node_cmp
{
    bool operator() (const InternalNode * nodeA,
                     const InternalNode * nodeB) const;
};

#endif /* InternalNode_hpp */
