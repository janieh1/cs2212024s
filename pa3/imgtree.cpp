/**
 *  @file imgtree.cpp
 *  @description implementation of a binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "imgtree.h"
// not necessary to include imgtree-private.h since it is already included in imgtree.h

/**
 *  Default constructor creates an empty tree
 */
ImgTree::ImgTree() {
    // complete your implementation below
    root = NULL;
    imgwidth = 0;
    imgheight = 0;

}

/**
 *  Parameterized constructor creates a tree from an input image.
 *  Every leaf in the tree corresponds to a single pixel in the PNG.
 *  Every non-leaf node corresponds to a rectangle of pixels defined
 *  by upper, left, lower, and right image coordinates. A node will
 *  also store the average color over its defined rectangle. Note that
 *  this average MUST be freshly computed from the individual pixels in
 *  the image and NOT by computing a weighted average from the colors
 *  of its direct children, as this would lead to an accumulation of
 *  rounding errors due to the integer nature of RGB color channels.
 *
 *  A non-leaf node's children correspond to a partition of the node's
 *  rectangle into two smaller rectangles, either by a horizontal line
 *  creating an upper rectangle and a lower rectangle, or a vertical line
 *  creating a left rectangle and a right rectangle.
 *
 *  The split is determined as follows:
 *  1. If the current node's rectangle width is the same or larger than its height,
 *     then a vertical line will divide the rectangle into left and right rectangles.
 *     If the current node's rectangle width is smaller than its height,
 *     then a horizontal line will divide the rectangle into upper and lower rectangles.
 *  2. The coordinate of the dividing line is chosen such that combined sum squared
 *     deviations from the mean color in the left/upper and right/lower rectangles is minimal
 *     among all other potential dividing lines of the same orientation.
 *     e.g. for a region (0,0) to (3,2), the candidates are the vertical lines dividing the region into:
 *     - (0,0) to (0,2) and (1,0) to (3,2)
 *     - (0,0) to (1,2) and (2,0) to (3,2)
 *     - (0,0) to (2,2) and (3,2) to (3,2)
 *     The line which produces the minimal combined sum squared scores on the left
 *     and right will be used for the split.
 *  3. In the unlikely event that multiple candidates produce the same score, the one which
 *     most evenly splits the rectangular area will be chosen.
 *  4. In the even more unlikely even that two candidates produce the same score and produce
 *     the same minimal area difference, the one with the smaller coordinate will be chosen.
 */
ImgTree::ImgTree(const PNG& img) {
    // complete your implementation below
    Stats st = Stats(img);
    imgwidth = img.width();
    imgheight = img.height();
    //root = new ImgTreeNode(0, 0, imgheight - 1, imgwidth - 1, st.GetAvg(0, 0, imgheight - 1, imgwidth - 1));
    // then need to build children nodes - recursive
    root = BuildNode(st, 0, 0, img.height() - 1, img.width() - 1);


}

/**
 *  Releases all heap memory associated with this tree, restoring it to an "empty tree" state.
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::Clear() {
    // complete your implementation below
    ClearRecur(root);

}

/**
 *  Copies the supplied parameter tree into this tree. Does not free any memory.
 *  Called by the copy constructor and operator=.
 *  Will be useful to define a recursive helper function for this.
 *  HINT: the helper should allocate a new node, and return a pointer to the allocated node.
 *        See the documention for BuildNode - this should work similarly.
 */
void ImgTree::Copy(const ImgTree& other) {
    // complete your implementation below
    this->root = CopyRecur(other.root);
    this->imgwidth = other.imgwidth;
    this->imgheight = other.imgheight;

}

/**
 *  Recursive helper function for initial construction of the tree. Constructs a single
 *  node according to supplied Stats and the requirements specified by the constructor
 *  documentation, and returns a pointer to the completed node.
 *  @param s - populated Stats object for computing this node's attributes
 *  @param upr - y-coordinate of the upper edge of the node's rectangular region
 *  @param lft - x-coordinate of the left side of the node's rectangular region
 *  @param lwr - y-coordinate of the lower edge of the node's rectangular region
 *  @param rt - x-coordinate of the right side of the node's rectangular region
 *  @return - pointer to a (completed) newly-allocated node for the specified parameters.
 */
ImgTreeNode* ImgTree::BuildNode(Stats& s, unsigned int upr, unsigned int lft, unsigned int lwr, unsigned int rt) {
    // complete your implementation below
    RGBAPixel avgColour = s.GetAvg(upr, lft, lwr, rt);
    ImgTreeNode* newNode = new ImgTreeNode(upr, lft, lwr, rt, avgColour);
    // std::cout << "average red: " << std::to_string(avgColour.r) << std::endl;
    // std::cout << "average green: " << std::to_string(avgColour.g) << std::endl;
    // std::cout << "average blue: " << std::to_string(avgColour.b) << std::endl;
    if (upr == lwr && lft == rt) {
        return newNode;
    }
    unsigned int width = rt - lft + 1;
    unsigned int height = lwr - upr + 1;
    if (width >= height) {
        // SPLIT WITH VERTICAL LINE
        //SplitInfo optimal = SplitInfo(lft, s.GetSumSqDev(upr, lft, lwr, optimalXValue) + s.GetSumSqDev(upr, optimalXValue + 1, lwr, rt));
        unsigned int optimalXValue = lft;
        int midpoint = (rt - lft) / 2;
        double optimalSqSum = s.GetSumSqDev(upr, lft, lwr, optimalXValue) + s.GetSumSqDev(upr, optimalXValue + 1, lwr, rt);
        // iterate through possible x values and compute sq avg, find optimal x and set U/L/L/R and recur
        // new upper = current lower new left = current right
        for (unsigned i = lft; i <= rt; i++) {
            double leftSide = s.GetSumSqDev(upr, lft, lwr, i);
            double rightSide = s.GetSumSqDev(upr, i + 1, lwr, rt);
            if (leftSide + rightSide == optimalSqSum && i != lft) {
                // coord which more evnely splits two sides is chosen
                optimalXValue = BetterMidpoint(optimalXValue, i, midpoint);
                if (optimalXValue == i) {
                    optimalSqSum = leftSide + rightSide;
                }
                continue;
            }
            if (leftSide + rightSide < optimalSqSum) {
                optimalXValue = i;
                optimalSqSum = leftSide + rightSide;
            }
        }
        newNode->A = BuildNode(s, upr, lft, lwr, optimalXValue); // RECURSION
        newNode->B = BuildNode(s, upr, optimalXValue + 1, lwr, rt); // RECURSION
    } else {
        // SPLIT WITH HORIZONTAL LINE
        unsigned int optimalYValue = upr;
        double optimalSqSum = s.GetSumSqDev(upr, lft, optimalYValue, rt) + s.GetSumSqDev(optimalYValue + 1, lft, lwr, rt);
        int midpoint = (lwr - upr) / 2;
        for (unsigned i = upr; i <= lwr; i++) {
            double top = s.GetSumSqDev(upr, lft, i, rt);
            double bottom = s.GetSumSqDev(i + 1, lft, lwr, rt);
            if (top + bottom == optimalSqSum && i != upr) {
                optimalYValue = BetterMidpoint(optimalYValue, i, midpoint);
                if (optimalYValue == i) {
                    optimalSqSum = top + bottom;
                }
                continue;
            }
            if (top + bottom < optimalSqSum) {
                optimalYValue = i;
                optimalSqSum = top + bottom;
            }
        }
        newNode->A = BuildNode(s, upr, lft, optimalYValue, rt); // RECURSION
        newNode->B = BuildNode(s, optimalYValue + 1, lft, lwr, rt); // RECURSION

    }
    return newNode; // REPLACE THIS STUB
}

/**
 *  Produces a PNG of appropriate dimensions and paints every leaf node's rectangle
 *  into the appropriate area of the PNG.
 *  May be called on pruned trees.
 *  @param scaling factor for how large to render the image. Assume this is >= 1.
 *  @return fully-colored PNG, painted from the tree's leaf node data
 */
PNG ImgTree::Render(unsigned int scale) const {
    // complete your implementation below
    PNG targetimg = PNG(imgwidth * scale, imgheight * scale);
    RenderRecur(scale, root, targetimg);
    return targetimg; // REPLACE THIS STUB
}


/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped horizontally when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipHorizontal() {
    // complete your implementation below
    FlipHorizontalRecur(root);
}

/**
 *  Trims subtrees as high as possible in the tree.
 *  A subtree is pruned (all decendants deallocated and child links set to null)
 *  if at least pct (out of 100) of its leaves are within tol of the average
 *  color in the subtree's root.
 *  Assume that this will only be called on trees which have not previously been pruned.
 *  Will be useful to define AT LEAST one recursive helper function for this.
 *  @pre pct is a valid value between 0 and 100
 *  @param pct percentage (out of 100) of leaf node descendants must be within the tolerance threshold
 *             of color difference in order to be pruned
 *  @param tol threshold color difference to qualify for pruning
 */
void ImgTree::Prune(double pct, double tol) {
    // complete your implementation below
    if (root == NULL) {
        return;
    }
    PruneRecur(pct, tol, root);
    //PruneRecur(pct, tol, root->B);
}

/**
 *  Counts the number of leaf nodes in the tree.
 *  Will be useful to define a recursive helper function for this.
 */
unsigned int ImgTree::CountLeaves() const {
    // complete your implementation below
    return CountLeavesRecur(root);
}

/**
 *  ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS BELOW
 */
 int ImgTree::BetterMidpoint(int optimal, int newX, int midpoint) {
    int diffOptimal = abs(midpoint - optimal);
    int diffX = abs(midpoint - newX);
    if (diffOptimal < diffX) {
        return optimal;
    } else if (diffOptimal > diffX) {
        return newX;
    } else {
        return (newX <= optimal) ? newX : optimal;
    }
 }

 void ImgTree::RenderRecur(unsigned int scale, ImgTreeNode* nd, PNG& targetimg) const {
    if (nd == NULL) {
        return;
    }
    if (nd->A == NULL && nd->B == NULL) {
        for (unsigned x = nd->left; x <= nd->right; x++) {
            for (unsigned y = nd->upper; y <= nd->lower; y++) {
                for (unsigned i = 0; i < scale; i++) {
                    for (unsigned j = 0; j < scale; j++) {
                        // RGBAPixel* px = targetimg.getPixel(nd->left + i, nd->upper + j);
                        RGBAPixel* px = targetimg.getPixel(x * scale + i, y * scale + j);
                        *px = nd->avg;
                    }
                }
            }
        }
    } else {
        RenderRecur(scale, nd->A, targetimg);
        RenderRecur(scale, nd->B, targetimg);
    }
}

void ImgTree::ClearRecur(ImgTreeNode* &nd) {
    if (nd == NULL) {
        return;
    }
    ClearRecur(nd->A);
    ClearRecur(nd->B);
    delete nd;
    nd = NULL;

}

unsigned int ImgTree::CountLeavesRecur(ImgTreeNode* nd) const {
    if (nd->A == NULL && nd->B == NULL) {
        return 1;
    } else {
        return CountLeavesRecur(nd->A) + CountLeavesRecur(nd->B);
    }
}

void ImgTree::PruneRecur(double pct, double tol, ImgTreeNode* &nd) {
    // want to get num leaves with avg colour within tolerance
    if (nd == NULL) return;
    // double goodLeaves = (double) LeavesWithColour(nd, tol, nd->avg);
    // double leavesTotal = (double) CountLeavesRecur(nd);
    //PruneRecur(pct, tol, nd->A);
    //PruneRecur(pct, tol, nd->B);
    vector<ImgTreeNode*> leaves;
    GetAllLeaves(nd, leaves);
    double leavesTotal = (double) leaves.size();
    double goodLeaves = 0.0;
    for (ImgTreeNode* i : leaves) {
        if ((nd->avg).dist(i->avg) <= tol) {
            goodLeaves++;
        }
    }
    if ( goodLeaves / leavesTotal >= pct / 100.0 ) {
        ClearRecur(nd->A);
        nd->A = NULL;
        ClearRecur(nd->B);
        nd->B = NULL;
        //nd->A = NULL;
        //nd->B = NULL;
    } else {
        PruneRecur(pct, tol, nd->A);
        PruneRecur(pct, tol, nd->B);
    }
    // PruneRecur(pct, tol, nd->A);
    // PruneRecur(pct, tol, nd->B);
}

unsigned int ImgTree::LeavesWithColour(ImgTreeNode* nd, double tol, RGBAPixel avgColour) {
    if (!nd) return 0;
    if (nd->A == NULL && nd->B == NULL) {
        if (abs(avgColour.dist(nd->avg)) <= tol) {
            return 1;
        } else {
            return 0;
        }

    }
    return LeavesWithColour(nd->A, tol, avgColour) + LeavesWithColour(nd->B, tol, avgColour);
}

void ImgTree::CountLeavesWithColour(ImgTreeNode* nd, double tol, RGBAPixel avgColour, double& leavesTotal, double& goodLeaves) {
    if (nd == NULL) {
        return;
    }
    if (nd->A == NULL && nd->B == NULL) { // then we are at leaf node
        leavesTotal++;
        if (abs(avgColour.dist(nd->avg)) <= tol) {
            goodLeaves++;
        }
    } else {
        CountLeavesWithColour(nd->A, tol, avgColour, leavesTotal, goodLeaves);
        CountLeavesWithColour(nd->B, tol, avgColour, leavesTotal, goodLeaves);
    }
}

bool ImgTree::CanBePruned(ImgTreeNode* nd, double tol, RGBAPixel avgColour) {
    if (nd->A == NULL && nd->B == NULL) {
        return (avgColour.dist(nd->avg) <= tol);
    } else {
        return (CanBePruned(nd->A, tol, avgColour) && CanBePruned(nd->B, tol, avgColour));
    }
}

void ImgTree::GetAllLeaves(ImgTreeNode* nd, vector<ImgTreeNode*>& leaves) {
    if (nd->A == NULL && nd->B == NULL) {
        leaves.push_back(nd);
    } else {
        GetAllLeaves(nd->A, leaves);
        GetAllLeaves(nd->B, leaves);
    }
}

void ImgTree::FlipHorizontalRecur(ImgTreeNode* &nd) {
    if (nd == NULL) {
        return;
    }
    nd->left = imgwidth - nd->left - 1;
    nd->right = imgwidth - nd->right - 1;
    ImgTreeNode* temp = nd->A;
    nd->A = nd->B;
    nd->B = temp;
    FlipHorizontalRecur(nd->A);
    FlipHorizontalRecur(nd->B);
}

ImgTreeNode* ImgTree::CopyRecur(ImgTreeNode* nd) {
    if (nd == NULL) {
        return NULL;
    }
    ImgTreeNode* newNode = new ImgTreeNode(nd->upper, nd->left, nd->lower, nd->right, nd->avg);
    newNode->A = CopyRecur(nd->A);
    newNode->B = CopyRecur(nd->B);
    return newNode;
}