/*
 * Filename: HCNode.hpp
 * Description: Implements the HCNode class for nodes in a Huffman
 *              compression tree
 */

#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>
#include <iomanip>

using namespace std;

/* 
 * Class name: HCNode
 * Instance Variables: weight (weight of symbol)
 *                     c0 (pointer to 0 child)
 *                     c1 (pointer to 1 child)
 *                     p (pointer to parent)
 *                     leaf (boolean indicating if node is leaf)
 * Description: Implements HCNode class                    
 * Public Methods: constructor, less than comparator <
 * Private Methods: None                    
*/

class HCNode {
    friend bool comp(HCNode* one, HCNode* other);

public:
    int weight;  // weight of symbol 
    HCNode* c0;  // pointer to '0' child
    HCNode* c1;  // pointer to '1' child
    HCNode* p;   // pointer to parent
    bool leaf;   // boolean indicating if node is leaf 

    // constructor
    HCNode(int mass,
      HCNode* c0 = 0,
      HCNode* c1 = 0,
      HCNode* p = 0)
        : weight(mass), c0(c0), c1(c1), p(p), leaf(false) { }

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically.
     */
    bool operator<(const HCNode& other) {
        // if counts are different, just compare counts
            return this->weight > other.weight;
    }
};

/** For printing an HCNode to an ostream
 *  Possibly useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak));
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" ;
    stm << setw(10) << &n;
    stm << "; l:" << setw(10) << n.c0;
    stm << "; r:" << setw(10) << n.c1;
    stm << "; p:" << setw(10) << n.p;
    stm << "; w:" << n.weight << "]";
    return stm;
}

/* Ignore */
bool comp(HCNode* one, HCNode* other);


#endif // HCNODE_HPP
