#include "hexcell.h"

/**
 * HexCell constructor. Initializes all walls to be true and path_dist_from_start to 0.
 * @param QR Axial coordinates of the hex cell
 */
HexCell::HexCell(std::pair<int, int> QR) {
    /**
     * @todo Your code here!
     */
    path_dist_from_start = 0; 
    // set all walls to true
    for (int i = 0; i < 6; i++) {
        walls[i] = true;
    }
    qr = QR;
}

/**
 * Gets the side of a neighbour. Each side is represented with an int in [0,5].
 * See above for the definition of the sides
 * @param cell A neighbouring HexCell
 * @return The side of cell
 * REQUIRE: cell is a neighbour of this cell
 */
int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    int q_diff = qr.first - cell->qr.first;
    int r_diff = qr.second - cell->qr.second;
    if (q_diff == 0 && r_diff == 1) {
       return 0;
    } else if (q_diff == -1 && r_diff == 1) {
       return 1;
    } else if (q_diff == -1 && r_diff == 0) {
       return 2;
    } else if (q_diff == 0 && r_diff == -1) {
       return 3;
    } else if (q_diff == 1 && r_diff == -1) {
       return 4;
    } else { // (q_diff == 1 && r_diff == 0)
       return 5;
    }
}