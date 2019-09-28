/* Filename: huffman.cpp
 * Description: The command line program huffman.cpp takes in one parameter, 
 *              an input file name. The input file specified by the input
 *              file name should contain the number of symbols and their
 *              weights in the format:
 *
 *              [number of symbols]
 *              [weight of symbol 1]
 *              [weight of symbol 2]
 *              ...
 *
 *              The program runs the Huffman compression algorithm and 
 *              outputs the maximum and minimum lengths of codewords.
 *
 *
 */

#include "HCTree.hpp"
#include <iostream>

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

using namespace std;

int main(int argc, char** argv) {

	if(argc != EXPECTED_ARGS ){
		cout << "This program requires 2 arguments!" << endl;
		return -1;
	}

	// build Huffman Compression Tree and make codebook
	HCTree* tree = new HCTree();
	tree->build(argv[IN_IDX]);
	tree->makeCodeBook();

	// Output the maximum and minimum lengths of codewords
	cout << "Max Codeword Length: " << tree->maxLength << endl;
	cout << "Min Codeword Length: " << tree->minLength << endl;

	// no memory leaks here
	delete tree;
}


