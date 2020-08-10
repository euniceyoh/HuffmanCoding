//
//  InternalNode.cpp
//  HuffmanCoding
//
//  Created by Eunice Oh on 8/6/20.
//  Copyright © 2020 Eunice Oh. All rights reserved.
//

#include "InternalNode.hpp"
#include <iostream>
#include <queue>
#include <map>

using namespace std;

InternalNode::InternalNode(char c, int weight) // leaf node constructor
{
    _letter = c;
    _weight = weight;
    _leftChild = NULL;
    _rightChild = NULL;
    _parent = NULL;
    
}

InternalNode::InternalNode() // regular node constructor
{
    _letter = NULL; // letter should be empty
    _parent = NULL;
}

char InternalNode::getLetter()
{
    return _letter;
}

int InternalNode::getWeight(){
    return _weight;
}

bool InternalNode::isLeafNode(){
    if(_leftChild == NULL && _rightChild == NULL)
    {
        return true;
    }
    return false;
}

bool node_cmp::operator()(const InternalNode * nodeA,
                          const InternalNode * nodeB) const
{
    return nodeA->_weight > nodeB->_weight;
}




