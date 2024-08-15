/**
 *  @file        twodlinkedlist-given.cpp
 *  @description Contains partial implementation of TwoDLinkedList class
 *               for CPSC 221 PA1
 *               Instructor-implemented functions
 *
 *  THIS FILE WILL NOT BE SUBMITTED
 */

#include "twodlinkedlist.h"

TwoDNode::TwoDNode() {
    // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
    north = nullptr;
    east = nullptr;
    south = nullptr;
    west = nullptr;
}

TwoDNode::TwoDNode(const Block& bdata) {
    // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
    data = bdata;
    north = nullptr;
    east = nullptr;
    south = nullptr;
    west = nullptr;
}

/**
 *  Copy constructor creates a new list as a copy of the data in otherlist
 */
TwoDLinkedList::TwoDLinkedList(const TwoDLinkedList& otherlist) {
    // build the linked node structure using otherlist as a template
    Copy(otherlist);
}

/**
 *  Overloaded assignment operator assigns structure and data of rhs into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
TwoDLinkedList& TwoDLinkedList::operator=(const TwoDLinkedList& rhs) {
    // Re-build any existing structure using rhs as a template

    if (this != &rhs) { // if this list and rhs are different lists in memory
        // release all existing heap memory of this list
        Clear();

        // and then rebuild this list using rhs as a template
        Copy(rhs);
    }

    return *this;
}

/**
 *  Destructor deallocates associated dynamic memory
 */
TwoDLinkedList::~TwoDLinkedList() {
	// Ensure that any existing heap memory is deallocated
	Clear();
}

/**
 *  Parameterized constructor creates a list with blockdimx columns,
 *  blockdimy rows, using color data from img
 *
 *  @param img - input PNG
 *  @param blockdimx - horizontal dimension of the list (in Blocks, i.e. number of columns)
 *  @param blockdimy - vertical dimension of the list (in Blocks, i.e. number of rows)
 *
 *  @pre img has dimensions at least 1x1
 *  @pre 1 <= blockdimx <= PNG's horizontal dimension (in pixels)
 *  @pre 1 <= blockdimy <= PNG's vertical dimension (in pixels)
 */
TwoDLinkedList::TwoDLinkedList(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {
    // THIS IMPLEMENTATION HAS BEEN COMPLETED FOR YOU ALREADY
    Build(img, blockdimx, blockdimy);
}