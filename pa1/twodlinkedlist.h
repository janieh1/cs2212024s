/**
 *  @file twodlinkedlist.h
 *  @author CPSC 221
 * 
 *  Defines a two-dimensional null-terminated doubly-linked list containing rectangular image pieces
 *  for CPSC 221 PA1
 * 
 *  THIS FILE WILL NOT BE SUBMITTED
 *  PRIVATE FUNCTIONS MAY BE ADDED TO twodlinkedlist-private.h
 */

#ifndef _TWODLINKEDLIST_H_
#define _TWODLINKEDLIST_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "block.h"

using namespace std;
using namespace cs221util;

class TwoDNode {
	public:
		Block data;
		TwoDNode* north; // pointer to the northern neighbour, if one exists; NULL otherwise
		TwoDNode* east; // pointer to the eastern neighbour, if one exists; NULL otherwise
		TwoDNode* south; // pointer to the southern neighbour, if one exists; NULL otherwise
		TwoDNode* west; // pointer to the western neighbour, if one exists; NULL otherwise

		/**
		 *  Default node constructor assigns appropriate values to the neighbour pointers
		 */
		TwoDNode();

		/**
		 *  Parameterized node constructor assigns data block and appropriate values to the neighbour pointers
		 */
		TwoDNode(const Block& bdata);
};

class TwoDLinkedList {
	private:
		TwoDNode* northwest; // pointer to upper-left node in the 2D list
		TwoDNode* southeast; // pointer to lower-right node in the 2D list

		/**
		 *  Deallocates any associated dynamic memory and sets private attributes appropriately
		 * 
		 *  @post this list is empty
		 */
		void Clear(); // !!!

		/**
		 *  Copies the data and structure of otherlist into this list
		 * 
		 *  @post this list is a physically separate copy of otherlist
		 */
		//void Copy(const TwoDLinkedList& otherlist);

	public:
	    void Copy(const TwoDLinkedList& otherlist);
	    //void Clear();
		/**
		 *  Default constructor creates an empty list
		 */
		TwoDLinkedList();

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
		TwoDLinkedList(PNG& img, unsigned int blockdimx, unsigned int blockdimy);

		/**
		 *  Copy constructor creates a new list as a copy of the data in otherlist
		 */
		TwoDLinkedList(const TwoDLinkedList& otherlist);

		/**
		 *  Overloaded assignment operator assigns structure and data of rhs into this list
		 * 
		 *  @post this list is a physically separate copy of otherlist
		 */
		TwoDLinkedList& operator=(const TwoDLinkedList& rhs);

		/**
		 *  Destructor deallocates associated dynamic memory
		 */
		~TwoDLinkedList();

		/**
		 *  Builds the structure of this list from the provided parameters.
		 *  The dimension of individual blocks will be an even division 
		 *  of the input PNG's dimensions by blockdimx or blockdimy.
		 *  Assume that supplied PNG dimensions will be divisible by
		 *  blockdimx and blockdimy.
		 * 
		 *  @pre PNG horizontal dimension is divisible by blockdimx
		 *  @pre PNG vertical dimension is divisible by blockdimy
		 * 
		 *  Example: PNG dimensions 320x240
		 *           blockdimx = 4
		 *           blockdimy = 2
		 *           The constructed list will have the following Block and node structure:
		 * 
		 *                +-----------+     +-----------+     +-----------+     +-----------+
		 *  northwest --> |           | --> |           | --> |           | --> |           |
		 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
		 *                |           | <-- |           | <-- |           | <-- |           |
		 *                +-----------+     +-----------+     +-----------+     +-----------+
		 *                   |     ^           |     ^           |     ^           |     ^   
		 *                   v     |           v     |           v     |           v     |   
		 *                +-----------+     +-----------+     +-----------+     +-----------+
		 *                |           | --> |           | --> |           | --> |           |
		 *                |  80 x 120 |     |  80 x 120 |     |  80 x 120 |     |  80 x 120 |
		 *                |           | <-- |           | <-- |           | <-- |           | <-- southeast
		 *                +-----------+     +-----------+     +-----------+     +-----------+
		 */
		void Build(PNG& img, unsigned int blockdimx, unsigned int blockdimy);

		/**
		 *  Returns the horizontal dimension of this list (in blocks)
		 */
		unsigned int GetBlockDimensionX() const;

		/**
		 *  Returns the vertical dimension of this list (in blocks)
		 */
		unsigned int GetBlockDimensionY() const;

		/**
		 *  Places this lists's color data into a PNG of appropriate dimensions
		 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
		 */
		PNG Render(unsigned int scale) const;

		/**
		 *  Reorganizes the list and node contents so that a rendered image will be flipped horizontally.
		 *  This must be achieved by pointer manipulation. Do not deallocate any existing nodes, and
		 *  do not allocate any new nodes.
		 *
		 *  Ensure that the integrity of north/south/east/west pointers of all nodes is maintained.
		 *
		 *  You may use up to O(n) time and space complexity, where n is the total number of nodes in the list.
		 *
		 *  Example: A, B, C, D etc. are physical nodes (each at a particular address)
		 *  before:
		 *   northwest -> A <-> B <-> C <-> D
		 *                ^     ^     ^     ^
		 *                v     v     v     v
		 *                E <-> F <-> G <-> H
		 *                ^     ^     ^     ^
		 *                v     v     v     v
		 *                I <-> J <-> K <-> L  <- southeast
		 *
		 *  after:
		 *   northwest -> D <-> C <-> B <-> A
		 *                ^     ^     ^     ^
		 *                v     v     v     v
		 *                H <-> G <-> F <-> E
		 *                ^     ^     ^     ^
		 *                v     v     v     v
		 *                L <-> K <-> J <-> I  <- southeast
		 */
		void FlipHorizontal();

	private:
		// DECLARE YOUR OWN PRIVATE FUNCTIONS IN twodlinkedlist-private.h IF NEEDED
		#include "twodlinkedlist-private.h"

};

#endif