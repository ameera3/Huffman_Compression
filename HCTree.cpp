/*
 * Filename: HCTree.cpp
 * Description: Implements Naive Huffman Compression
 */

#include "HCTree.hpp"
#include "HCNode.hpp"

/* Use the Huffman algorithm to build a Huffman coding tree.
 * PRECONDITION: weights is a vector of ints, such that weights[i] is
 * the weight of symbol i.
 * POSTCONDITION: root points to the root of the tree.
 */

void HCTree::build(const char* filename) {

    // input file stream		
    ifstream * in = new ifstream(filename);

    // used for parsing input file
    string line;	

    // weights vector used to build tree
    vector<int> weights;

    // number of symbols
    unsigned int numSymbols;

    // Raise an error if file can't be read and exit
    if( in->eof() ){
    	cerr << "Failed to read " << filename << "!\n";
	delete in;
	exit(-1);
    }

    // read the number of symbols
    getline(*in, line); 
    numSymbols = stoi(line);

    // populate the weights vector
    while( getline(*in, line) ){
	weights.push_back(stoi(line));
    }

    // check that you parsed input file correctly
    if( weights.size() != numSymbols ){
	cerr << "Incorrect Parse!\n";
        delete in;
	exit(-1);
    }	

    // priority queue that automatically sorts HCNodes according
    // to frequency and symbol
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> myQueue;

    // create a new HCNode for each symbol and push it to the queue
    for(unsigned int i=0; i < weights.size(); ++i) {
    	HCNode* node = new HCNode(weights[i]);
	node->leaf = true;
        myQueue.push(node);
    }        
    
    // merge the two HCNodes with highest priority and let this new
    // merged node be their parent in the tree
    while( myQueue.size() > 1 ) {
        HCNode* node1 = myQueue.top();
        myQueue.pop();
        HCNode* node2 = myQueue.top();
        myQueue.pop();
        HCNode* merged = new HCNode(node1->weight + node2->weight);
        merged->c0 = node2;
        merged->c1 = node1;
        node1->p = merged;
        node2->p = merged;
        myQueue.push(merged);
    }  

    // the root of the Huffman tree is the last node left
    if(myQueue.size() == 1) {
        root = myQueue.top();
        myQueue.pop();
    }

    // no memory leaks here!
    delete in;    

}

/* public method to make codebook after tree is built 
 * If root has a left child, call recursive helper
 * function. Otherwise, the tree is either empty in
 * which case return or the tree only consists of the
 * root in which case we assign the root a codeword of 0
 */ 
void HCTree::makeCodeBook() {

    string currentCode;
    if(root == nullptr) {
        return;
    }
    else if(root->c0 != nullptr) {
        makeCodeBookHelper(root, currentCode);
    }
    else{
        codebook[root] = "0";
    }    
}

/* Recursive helper function for makeCodeBook
 * If node is nullptr, return. Otherwise, store in the
 * codebook the node and the current code. If the node
 * has a left child, recursively call makeCodeBookHelper
 * on left child (append 0 to current code) and right child
 * (append 1 to current code)
 * Side Effects: Changes the value of maxLength and minLength
 */  
void HCTree::makeCodeBookHelper(HCNode* n, string currentCode) {

    if( n == nullptr ) {
        return;
    }
    codebook[n] = currentCode;
    if( (n->leaf) && ((int) currentCode.length() < minLength) ) {
	    minLength = currentCode.length();
    }
    if( (n->leaf) && ((int) currentCode.length() > maxLength) ) {
	    maxLength = currentCode.length();
    }	    
    if( n->c0 != nullptr ){
        makeCodeBookHelper(n->c0, currentCode + "0");
        makeCodeBookHelper(n->c1, currentCode + "1");
    }
}

/* Destructor */
HCTree::~HCTree()
{
    deleteAll(root);
}

/** do a postorder traversal, deleting nodes    
*/
void HCTree::deleteAll(HCNode* n) {
    /* Pseudo Code:
     * if current node is null: return;
     * recursively delete left sub-tree
     * recursively delete right sub-tree
     * delete current node
     */
    if( n == nullptr ) {
        return;
    }
    deleteAll( n->c0 );
    deleteAll( n->c1 );
    delete n;
}


