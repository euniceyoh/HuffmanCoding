
/*
 File: InternalNode.cpp
 
 This is the implementation for a Huffman tree node.
 */

#include "InternalNode.hpp"
#include <iostream>
#include <queue>
#include <map>

using namespace std;

/*
 Function:
 Usage:
 
 Constructs a leaf node
 */

InternalNode::InternalNode(char c, int weight)
{
    _letter = c;
    _weight = weight;
    _leftChild = NULL;
    _rightChild = NULL;
    _parent = NULL;
    
}

/*
 Function:
 Usage:
 
 Constructs an internal node
 */

InternalNode::InternalNode()
{
    _letter = NULL; // letter should be empty
    _parent = NULL;
}

/*
 Functions:
 Usage:
 
 Returns value of respective data members
 */

char InternalNode::getLetter()
{
    return _letter;
}

int InternalNode::getWeight(){
    return _weight;
}

/*
 Functions:
 Usage:
 
 */

void InternalNode::setWeight(int w){
    _weight = w;
}

/*
 Function:
 Usage:
 
 Returns true if a node is a leaf node
 */

bool InternalNode::isLeafNode(){
    if(_leftChild == NULL && _rightChild == NULL)
    {
        return true;
    }
    return false;
}

/*
 Function:
 Usage:
 
 */

bool node_cmp::operator()(const InternalNode * nodeA,
                          const InternalNode * nodeB) const
{
    return nodeA->_weight > nodeB->_weight;
}




