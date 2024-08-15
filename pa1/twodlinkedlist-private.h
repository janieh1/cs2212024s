/**
 *  @file        twodlinkedlist-private.h
 *  @description Student-defined functions of TwoDLinkedList class, for CPSC 221 PA1
 *
 *  THIS FILE WILL BE SUBMITTED.
 *  YOU MAY ADD YOUR OWN PRIVATE MEMBER FUNCTION DECLARATIONS HERE.
 *  IF YOU DO NOT HAVE FUNCTIONS TO ADD, LEAVE THIS BLANK
 */

/**************************************/
/* ADD YOUR PRIVATE DECLARATIONS HERE */
/**************************************/
TwoDNode* BuildRecursive(vector<vector<Block*>> blocks, int i, int j, TwoDNode* currentNode, unsigned int blockdimx, unsigned int blockdimy, PNG& img);
vector<vector<Block*>> GenerateBlocks(PNG& img, unsigned int blockdimx, unsigned int blockdimy);