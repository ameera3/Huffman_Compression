/*
 * Filename: HCTree.hpp
 * Description: Implements a Huffman Compression Tree
 */

#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include <map>
#include <limits>
#include <string.h>
#include "HCNode.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/* 
 * Class name: HCTree
 * Instance Variables: root (root of Huffman compression tree)
 *                     codebook (map storing HCNode pointers and their
 *                               corresponding codewords)
 *                     maxLength (integer representing max length of
 *                                codeword)
 *                     minLength (integer representing min length of 
 *                     		  codeword)                     
 * Description: Implements a Huffman Compression Tree                    
 * Public Methods: constructor, destructor, build, makeCodeBook
 * Private Methods: makeCodeBookHelper, deleteAll                    
 */

class HCTree {

	public:
    		HCNode* root; // root of Huffman compression tree
    		std::map<HCNode*,string> codebook; // map storing HCNode pointers and
                                       		   // their corresponding codewords
    		int maxLength;
    		int minLength;

    		// constructor  
    		HCTree() : root(0), codebook(), maxLength(numeric_limits<int>::min()), 
			minLength(numeric_limits<int>::max()) {}

    		// destructor
    		~HCTree();

    		/** Use the Huffman algorithm to build a Huffman coding trie.
     		  *  Read the input file, populate a weights vector, and use
		  *  it to build the Huffman compression tree.
     		  *  POSTCONDITION:  root points to the root of the tree,
     		  */
    		void build(const char* filename);

    		// makes codebook associating HCNodes to their codewords
    		void makeCodeBook();

	private:    

    		// recursive helper function for makeCodeBook
		// Side Effects: Changes the value of maxLength and minLength
    		void makeCodeBookHelper(HCNode* n, string currentCode);

    		// recursive helper function for delete
    		void deleteAll(HCNode* n);
};

#endif // HCTREE_H
