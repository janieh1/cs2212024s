/**
 * @file twodlinkedlist.cpp
 * @author your name(s)
 *
 * Defines a two-dimensional null-terminated doubly-linked list containing rectangular image pieces
 *  for CPSC 221 PA1
 *
 * COMPLETE THE FUNCTION BODIES IN THIS FILE AND SUBMIT TO PRAIRIELEARN
 */

#include "twodlinkedlist.h"

/**
 *  Deallocates any associated dynamic memory and sets private attributes appropriately
 *
 *  @post this list is empty
 */
void TwoDLinkedList::Clear() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    TwoDNode* ptr = northwest;
    vector<TwoDNode*> westernNodes(GetBlockDimensionY(), nullptr);
    int i = 0;
    while (ptr) {
        westernNodes[i] = ptr;
        ptr = ptr->south;
        i++;
    }
    for (int i = 0; i < (int) westernNodes.size(); i++) {
        TwoDNode* currNode = westernNodes[i];
        while (currNode) {
            currNode->north = nullptr;
            currNode->south = nullptr; 
            currNode->west = nullptr;
            TwoDNode* nextNode = currNode->east;
            currNode->east = nullptr;
            delete currNode;
            currNode = nextNode;
        }
    }
    northwest = nullptr;
    southeast = nullptr;
}

/**
 *  Copies the data and structure of otherlist into this list
 *
 *  @post this list is a physically separate copy of otherlist
 */
void TwoDLinkedList::Copy(const TwoDLinkedList& otherlist) {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    if (!otherlist.northwest) {
        northwest = nullptr;
        southeast = nullptr;
        return;
    }
    // create vector of pointers to the easternmost nodes in each row:
    vector<TwoDNode*> westernNodes;
    TwoDNode* otherlistPtrSouth = otherlist.northwest;
    while (otherlistPtrSouth) {
        TwoDNode* otherlistPtrEast = otherlistPtrSouth;
        TwoDNode* ptrWest = nullptr;
        TwoDNode *newNodeEast;
        TwoDNode* westernNodeFirst = new TwoDNode(otherlistPtrEast->data);
        westernNodeFirst->west = ptrWest;
        westernNodes.push_back(westernNodeFirst);
        //newNode = westernNodeFirst;
        ptrWest = westernNodeFirst;
        while (otherlistPtrEast->east) {
            newNodeEast = new TwoDNode(otherlistPtrEast->east->data);
            newNodeEast->west = ptrWest;
            ptrWest->east = newNodeEast;
            otherlistPtrEast = otherlistPtrEast->east;
            ptrWest = newNodeEast;
        }
        // newNodeEast->west = newNode;
        // newNodeEast->east = nullptr;
        otherlistPtrSouth = otherlistPtrSouth->south;
    }
    // now we have to iteratate through this vector and connect the north/south pointers of each node
    for (int i = 0; i < (int) westernNodes.size() - 1; i++) {
        TwoDNode* curr = westernNodes[i];
        TwoDNode* southern = westernNodes[i + 1];
        TwoDNode* northern = i == 0 ? nullptr : westernNodes[i - 1];
        while (southern) {
            curr->north = northern;
            curr->south = southern;
            southern->north = curr;
            northern = i == 0 ? nullptr : northern->east;
            curr = curr->east;
            southern = southern->east;
        }
    }
    // westernNodes is now a vector with all pointers set - we need to set northwest and southeast of the TwoDLinkedList
    northwest = westernNodes[0];
    southeast = northwest;
    while (southeast->east) {
        southeast = southeast->east;
    }
    while (southeast->south) {
        southeast = southeast->south;
    }
	
}

/**
 *  Default constructor creates an empty list
 */
TwoDLinkedList::TwoDLinkedList() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
	northwest = nullptr;
    southeast = nullptr;
}

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
void TwoDLinkedList::Build(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    Block* newBlock;
    vector<vector<Block>> blocks;
    for (unsigned i = 0; i < img.height(); i += img.height() / blockdimy) {
        vector<Block> row;
        for (unsigned j = 0; j < img.width(); j += img.width() / blockdimx) {
            newBlock = new Block();
            newBlock->Build(img.width() / blockdimx,img.height() / blockdimy, i, j, img);
            row.push_back(*newBlock);
            delete newBlock;
            newBlock = nullptr;
        }
        blocks.push_back(row);
    }
    // we will now have a 2D matrix of blocks - construct an array of linked lists (for each row)
    // vector<TwoDNode*> westernNodes(blocks.size(), new TwoDNode()); // stores a ptr to westernmost node in each row
    vector<TwoDNode*> westernNodes(blocks.size(), nullptr); // stores a ptr to westernmost node in each row
    for (int i = 0; i < (int) blocks.size(); i++) { // for each row of blocks
        TwoDNode* currentNode;
        TwoDNode* westernNode;
        TwoDNode* easternNode;
        TwoDNode* head = new TwoDNode(blocks[i][0]); // set first in array
        head->west = nullptr;
        westernNodes[i] = head;
        currentNode = head;
        westernNode = nullptr;
        for (int j = 0; j < (int) blocks[i].size() - 1; j++) {
            TwoDNode* newNode = new TwoDNode(blocks[i][j + 1]); // create the eastern node
            easternNode = newNode;
            currentNode->east = easternNode;
            currentNode->west = westernNode;
            westernNode = currentNode;
            if (j == (int) blocks[i].size() - 2) {
                easternNode->west = currentNode;
                easternNode->east = nullptr;
            }
            currentNode = easternNode;
        }
    } // we will now have westernNodes: an array of pointers to the westernmost node in each row
    // now we have to iteratate through this vector and connect the north/south pointers of each node
    for (int i = 0; i < (int) westernNodes.size() - 1; i++) {
        TwoDNode* curr = westernNodes[i];
        TwoDNode* southern = westernNodes[i + 1];
        TwoDNode* northern = i == 0 ? nullptr : westernNodes[i - 1];
        while (southern) {
            curr->north = northern;
            curr->south = southern;
            southern->north = curr;
            northern = i == 0 ? nullptr : northern->east;
            curr = curr->east;
            southern = southern->east;
        }
    }
    // westernNodes is now a vector with all pointers set - we need to set northwest and southeast of the TwoDLinkedList
    northwest = westernNodes[0];
    southeast = northwest;
    while (southeast->east) {
        southeast = southeast->east;
    }
    while (southeast->south) {
        southeast = southeast->south;
    }
    for (int i = 0; i < (int) westernNodes.size() - 1; i++) {
        westernNodes[i] = nullptr;
    }
}

/**
 *  Returns the horizontal dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionX() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    unsigned int dimX = 0;
    TwoDNode* ptr = northwest;
    while (ptr != nullptr) {
        dimX++;
        ptr = ptr->east;
    }
    return dimX;
}

/**
 *  Returns the vertical dimension of this list (in blocks)
 */
unsigned int TwoDLinkedList::GetBlockDimensionY() const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    unsigned int dimY = 0;
    TwoDNode* ptr = northwest;
    while (ptr != nullptr) {
        dimY++;
        ptr = ptr->south;
    }
    return dimY;
}

/**
 *  Places this lists's color data into a PNG of appropriate dimensions
 *  @param scale - integer multiplier for dimensions. 0 = scale by 0.5.
 */
PNG TwoDLinkedList::Render(unsigned int scale) const {
    // REPLACE THE LINE BELOW WITH YOUR IMPLEMENTATION
    PNG* targetImage;
    TwoDNode* ptrCol;
    TwoDNode* ptrRow = northwest;
    Block blockToDraw = ptrRow->data;
    unsigned int blockDimX = GetBlockDimensionX(); // number of blocks per row
    unsigned int blockDimY = GetBlockDimensionY(); // number of blocks per col
    unsigned int blockWidth = blockToDraw.GetWidth(); // block width in pixels
    unsigned int blockHeight = blockToDraw.GetHeight(); // block height in pixels
    

    if (scale < 1) { // still need to go through each node and render the block inside, just need to set the upper and left
        targetImage = new PNG(blockDimX * blockWidth / 2, blockDimY * blockHeight / 2);
        for (int i = 0; ((i < (int) blockDimY * blockHeight / 2) && ptrRow); i += targetImage->height() / blockDimY) {
            ptrCol = ptrRow;
            for (int j = 0; ((j < (int) blockDimX * blockWidth / 2) && ptrCol); j += targetImage->width() / blockDimX) {
                blockToDraw = ptrCol->data;
                blockToDraw.Render(scale, j, i, *targetImage); // i = upper, j = left img coordinates to draw block on
                ptrCol = ptrCol->east;
            }
            ptrRow = ptrRow->south;
        }
        PNG toRet = *targetImage;
        delete targetImage;
        targetImage = nullptr;
        return toRet;
    }
    targetImage = new PNG(blockDimX * blockWidth * scale, blockDimY * blockHeight * scale);
    for (int i = 0; (i < (int) blockDimY * blockHeight * scale && ptrRow); i += targetImage->height() / blockDimY) {
        ptrCol = ptrRow;
        for (int j = 0; (j < (int) blockDimX * blockWidth * scale && ptrCol); j += targetImage->width() / blockDimX) {
            blockToDraw = ptrCol->data;
            blockToDraw.Render(scale, j, i, *targetImage); // i = upper, j = left img coordinates to draw block on
            ptrCol = ptrCol->east;
        }
        ptrRow = ptrRow->south;
    }
    PNG toRet = *targetImage;
    delete targetImage;
    targetImage = nullptr;
    return toRet;
    //return PNG();
}

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
void TwoDLinkedList::FlipHorizontal() {
    // COMPLETE YOUR IMPLEMENTATION BELOW
    TwoDNode* ptr = northwest;
    TwoDNode* ptrNW = northwest;
    TwoDNode* ptrSE = southeast;

    TwoDNode* eastern = northwest;
    while (eastern) {
        ptr = NULL;
        TwoDNode* currNode = eastern;
        while (currNode) {
            ptr = currNode->west;
            currNode->west = currNode->east;
            currNode->east = ptr;
            currNode->data.FlipHorizontal();
            currNode = currNode->west;
        }
        eastern = eastern->south;
    }
    while (ptrNW->west) {
        ptrNW = ptrNW->west;
    }
    northwest = ptrNW;
    while (ptrSE->east) {
        ptrSE = ptrSE->east;
    }
    southeast = ptrSE;
}

vector<vector<Block*>> TwoDLinkedList::GenerateBlocks(PNG& img, unsigned int blockdimx, unsigned int blockdimy) {
    vector<vector<Block*>> blocks;
    for (unsigned i = 0; i < blockdimy; i += img.height() / blockdimy) {
        vector<Block*> row;
        for (unsigned j = 0; j < blockdimx; j += img.width() / blockdimx) {
            Block* newBlock = new Block();
            newBlock->Build(blockdimx, blockdimy, i, j, img);
            row.push_back(newBlock);
        }
        blocks.push_back(row);
    }
    return blocks;
}

TwoDNode* TwoDLinkedList::BuildRecursive(vector<vector<Block*>> blocks, int i, int j, TwoDNode* currentNode, unsigned int blockdimx, unsigned int blockdimy, PNG& img) {
    if (i >= (int) blockdimy|| j >= (int) blockdimx) {
        return nullptr;
    }
    TwoDNode* newNode = new TwoDNode(*blocks[i][j]);
    newNode->west = currentNode;
    newNode->north = currentNode;
    newNode->east = BuildRecursive(blocks, i, j + 1, newNode, blockdimx, blockdimy, img);
    newNode->south = BuildRecursive(blocks, i + 1, j, newNode, blockdimx, blockdimy, img);
    return newNode;
}

