//
//  InternalNode.hpp
//  HuffmanCoding
//
//  Created by Eunice Oh on 8/6/20.
//  Copyright © 2020 Eunice Oh. All rights reserved.
//

#ifndef InternalNode_hpp
#define InternalNode_hpp

#include <stdio.h>
#include <string>

using namespace std;

class InternalNode{
public:
    InternalNode(char c, int weight);   // Leaf Node Constructor
    InternalNode();                     // Regular Constructor
    //~InternalNode();
    char getLetter();
    int getWeight();
    bool isLeafNode();
    
public:    // private here?
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
