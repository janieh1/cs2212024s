/**
 *  @file imgtree-private.h
 *  @description student-defined functions for binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN, EVEN IF YOU DO NOT ADD ANYTHING TO IT
 * 
 *  Usage: As this file is included entirely into imgtree.h by the #include statement on line 214
 *  you only need to write the function signature,
 *  e.g.
 *  void MyOwnSpecialFunction(int fave_num, ImgTreeNode* nd);
 * 
 *  and add/complete your implementation in imgtree.cpp
 */

void RenderRecur(unsigned int scale, ImgTreeNode* nd, PNG& targetimg) const;
void ClearRecur(ImgTreeNode* &nd);
int BetterMidpoint(int optimal, int newX, int midpoint);
unsigned int CountLeavesRecur(ImgTreeNode* nd) const;
void FlipHorizontalRecur(ImgTreeNode* & nd);
ImgTreeNode* CopyRecur(ImgTreeNode* nd);
void PruneRecur(double pct, double tol, ImgTreeNode* &nd);
void CountLeavesWithColour(ImgTreeNode* nd, double tol, RGBAPixel avgColour, double& leavesTotal, double& goodLeaves);
bool CanBePruned(ImgTreeNode* nd, double tol, RGBAPixel avgColour);
void GetAllLeaves(ImgTreeNode* nd, vector<ImgTreeNode*>& leaves);
unsigned int LeavesWithColour(ImgTreeNode* nd, double tol, RGBAPixel avgColour);