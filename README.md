# Huffman Coding Implementation

### Data Structures Involved or Implemented: 
* Binary Tree
* Priority Queue
* Map 

### Time Complexity: 
* O(n*log(n)) 

### Huffman Coding Attributes:   
1. Compresses Data: reduces number of bits needed to represent data 
1. A form of **lossless compression**, meaning no details are lost while compressing
1. Has **variable-length encoding**, whereas in fixed-length encoding, each character has the same length (number of bits) or the same amount of space is used to store each character
   * Fixed-Length Ex: ASCII Codes uses 8 bits (1 byte) for each character 
1. A **greedy algorithm**: combines the **smallest nodes first**, which assigns most rarely used character a longer bit pattern 
   * results in globally optimal encoding tree, yields a minimal per-character encoding/compression
1. Useful when **data is repeated**: fewer bits are used to encode more frequent letters than to encode those less frequent 
1. Has **prefix property**: no bit-sequence of a character is the prefix of any other bit sequence encoding

### Resources: 
* https://www2.cs.duke.edu/csed/poop/huff/info/
* https://demo.tinyray.com/huffman
* http://rosettacode.org/wiki/Huffman_coding#C.2B.2B
* https://en.wikipedia.org/wiki/Binary_tree
* https://en.wikipedia.org/wiki/Priority_queue
* https://en.wikipedia.org/wiki/Huffman_coding
* https://en.wikipedia.org/wiki/Heap_(data_structure)#Implementation
* http://pages.cs.wisc.edu/~vernon/cs367/notes/11.PRIORITY-Q.html
