#include "hexboard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

/**
 * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard(). The default start_coord and end_coord are (0, 0).
 * @note There is no maze yet! The board is just a beehive for now.
 * @param rad The radius of the board
 */
HexBoard::HexBoard(int rad) {
    /**
     * @todo Your code here!
     */
    radius = rad;
    longest_path_dist = 0;
    start_coord = {0, 0};
    end_coord = {0, 0};
    create_board();
}

// Frees all dynamically allocated memory associated with the board.
HexBoard::~HexBoard() {
    /**
     * @todo Your code here!
     */
    radius = 0;
    longest_path_dist = 0;
    start_coord = {0, 0};
    end_coord = {0, 0};
    for (auto itr = cells.begin(); itr != cells.end(); itr++) {
        delete itr->second;
        itr->second = NULL;
    }
    cells.clear();
}

/**
 * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
 */
void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
    HexCell* origin = new HexCell({0, 0});
    cells[{0, 0}] = origin;
    if (radius == 0) {
        return;
    }
    // create origin then check if it has a neghbour on each side - if yes, don't create. if no, create
    for (int q = -1*radius + 1; q <= radius - 1; q++) {
        for (int r = -1*radius + 1; r <= radius - 1; r++) {
            if (distance({0, 0}, {q, r - 1}) <= radius) {
                create_cells_at_distance({q, r - 1});
            }
            if (distance({0, 0}, {q + 1, r - 1}) <= radius) {
                create_cells_at_distance({q + 1, r - 1});
            }
            if (distance({0, 0}, {q + 1, r}) <= radius) {
                create_cells_at_distance({q + 1, r});
            }
            if (distance({0, 0}, {q, r + 1}) <= radius) {
                create_cells_at_distance({q, r + 1});
            }
            if (distance({0, 0}, {q - 1, r + 1}) <= radius) {
                create_cells_at_distance({q - 1, r + 1});
            }
            if (distance({0, 0}, {q - 1, r}) <= radius) {
                create_cells_at_distance({q - 1, r});
            }
        }
    }



}

void HexBoard::create_cells_at_distance(std::pair<int, int> QR) {
    auto lookup = cells.find(QR);
    if (distance({0, 0}, QR) > radius) {
        return;
    }
    if (lookup == cells.end()) { // if we don't have this cell in the dict yet, add it
        HexCell* cellToAdd = new HexCell(QR);
        cells[QR] = cellToAdd;
    }


}

/**
 * Gets the coordinates of the six neighbours of coord, in the sides order specified in HexCell.h.
 * @param coord The input coordinate.
 */
vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    int q = coord.first;
    int r = coord.second;
    vector<pair<int, int>> ret;
    ret.push_back({q, r - 1});      // N
    ret.push_back({q + 1, r - 1});  // NE
    ret.push_back({q + 1, r});      // SE 
    ret.push_back({q, r + 1});      // S
    ret.push_back({q - 1, r + 1});  // SW
    ret.push_back({q - 1, r});      // NW
    return ret;
}

// vector<pair<int, int>> HexBoard::get_valid_neigh_coords(const pair<int, int>& coord) const {
//     vector<pair<int, int>> all_neighbours = get_neigh_coords(coord);
//     vector<pair<int, int>> valid_neighbours;
//     auto lookup1 = cells.find(coord);
//     if (lookup1 != cells.end()) {
//         HexCell* cell1 = lookup1->second;
//         // check if wall between 2 cells
//         for (int i = 0; i < all_neighbours.size(); i++) {
//             auto lookup2 = cells.find(all_neighbours[i]);
//             if (lookup2 != cells.end()) {
//                 bool is_wall = cell1->walls[cell1->get_neighbour_side(lookup2->second)];
//                 if (distance({0, 0}, all_neighbours[i]) <= radius && !is_wall) {
//                     valid_neighbours.push_back(all_neighbours[i]);
//                 }
//             }
//         }
//     }
//     return valid_neighbours;
// }

/**
 * Link two cells at the given coordinates by setting each cell's wall to false in the other cell's direction.
 * @param coord1 A coordinate of a HexCell to be linked.
 * @param coord2 A coordinate of a HexCell to be linked.
 * @note remember to link both directions!
 * REQUIRE: the two coords are neighbours
 */
void HexBoard::link(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here!
     */
    int neigh1Wall = 0;
    int neigh2Wall = 0;
    vector<pair<int, int>> neighbours_cell1 = get_neigh_coords(coord1);
    for (int i = 0; i < neighbours_cell1.size(); i++) {
        if (neighbours_cell1[i] == coord2) {
            neigh1Wall = i;
            break;
        }
    }
    if (neigh1Wall >= 3) {
        neigh2Wall = neigh1Wall - 3;
    } else {
        neigh2Wall = neigh1Wall + 3;
    }
    auto lookup1 = cells.find(coord1);
    auto lookup2 = cells.find(coord2);
    if (lookup1 != cells.end() && lookup2 != cells.end()) {
        HexCell* cell1 = lookup1->second;
        HexCell* cell2 = lookup2->second;
        cell1->walls[neigh1Wall] = false;
        cell2->walls[neigh2Wall] = false;
    }
}

/**
 * @param coord1 A coordinate of a HexCell
 * @param coord2 A coordinate of a HexCell
 * @return The cell distance (ignoring walls) between coord1 and coord2.
 */
int HexBoard::distance(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (coord1.first == coord2.first) {
        return abs(coord1.second - coord2.second);
    } else if (coord1.second == coord2.second) {
        return abs(coord1.first - coord2.first);
    } else {
        if (((coord1.first - coord2.first) > 0 && (coord1.second - coord2.second) > 0) || ((coord1.first - coord2.first) < 0 && (coord1.second - coord2.second) < 0) ) {
            return abs(coord1.first - coord2.first) + abs(coord1.second - coord2.second);
        } else {
            return max(abs(coord1.first - coord2.first), abs(coord1.second - coord2.second));
        }
        
    }

}

/**
 * @return true if coord is at the edge of the board, false otherwise.
 */
bool HexBoard::is_edge(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace th-e following line.
     */
    return distance({0, 0}, coord) == radius;
}

/**
 * Traverses the board via dfs to generate the maze, updating and keeping track of:
 * A. The largest path distance from start to an edge cell so far (this is not longest_path_dist!)

 * The algorithm goes as follows:
 * 0. Set the start_coord member variable
 * 1. Seed this->rng with seed
 * 2. Add the start_coord to a stack, and mark it as visited
 * 3. While the stack is not empty:

 *   a. Peek the top of the stack (call it curr_coord)
 *   b. Use choose_neighbour to choose the neighbour to visit
 *   c. If the neighbour exists, for that neighbour (call it neigh_cell) do:

 *     i. Link curr_coord with neigh_coord
 *     ii. Push neigh_coord into the stack, and mark it as visited
 *     iii. Update the neigh_cell's path distance to start
 *     iv. If necessary, update length of longest path so far (longest_path_dist)
 *     v. Update the end coordinate only if its path distance to start is strictly greater than the largest path distance from start to an edge cell so far.

 *   d. Otherwise (if choose_neighbour returns nullptr), pop the stack.

 * @param start The {q, r} coordinate of the start of the maze.
 * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
 *                    A small branch_prob means neighbours of the same dist from the start_coord are preferred
 *                    A large branch_prob means neighbours of a different dist from the start_coord are preferred
 * @param seed The seed used for the rng
 * REQUIRE: create_board() is already called
 */
void HexBoard::generate_maze(pair<int, int> start, double branch_prob, int seed) {
    /**
     * @todo Your code here!
     */
    rng.seed(seed);
    int longest_so_far = 0;
    start_coord = start;
    set<pair<int, int>> visited;
    Stack<pair<int, int>> st;
    st.push(start);
    visited.insert(start);

    while (!st.is_empty()) {
        pair<int, int> curr_coord = st.peek();
        HexCell* neigh_cell = choose_neighbour(curr_coord, visited, branch_prob);
        if (neigh_cell != NULL) {
            // if it has a viable neighbour, it is part of the path and we increase the path distance
            longest_so_far++;
            link(curr_coord, neigh_cell->qr);
            st.push(neigh_cell->qr);
            visited.insert(neigh_cell->qr);
            neigh_cell->path_dist_from_start = longest_so_far;
            //end_coord = neigh_cell->qr;
            if (neigh_cell->path_dist_from_start > longest_path_dist) {
                longest_path_dist= neigh_cell->path_dist_from_start;
                end_coord = neigh_cell->qr;
            }
        } else {
            longest_so_far--;
            st.pop();
        }
    }
    // std::cout << "END: " << std::endl;
    // std::cout << "first: " << std::to_string(end_coord.first) << std::endl;
    // std::cout << "second: " << std::to_string(end_coord.second) << std::endl;   
}

/**
 * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

 * REQUIRE: generate_maze must be called already
 */
void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     
    Queue<pair<int, int>> q;
    set<pair<int, int>> visited;
    // q.enqueue(start_coord);
    // visited.insert(start_coord);
    q.enqueue(end_coord);
    visited.insert(end_coord);
    while (!q.is_empty()) {
        pair<int, int> curr_coord = q.peek();
        HexCell* curr_cell = cells[curr_coord];
        q.dequeue();
        if (curr_coord == start_coord) {
            solution.push_back(curr_coord);
            return;
        }
        solution.push_back(curr_coord);
        std::cout << "current: {" << std::to_string(curr_coord.first) << ", " << std::to_string(curr_coord.second) << "}" << std::endl; 
        vector<pair<int, int>> all_neighbours = get_neigh_coords(curr_coord);
        vector<pair<int, int>> valid_neighbours;
        for (int i = 0; i < all_neighbours.size(); i++) {
            pair<int, int> neigh_coord = all_neighbours[i];
            std::cout << "neighbour: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
            HexCell* neigh_cell = cells[neigh_coord]; // DOUBLE CHECK DETERMINATION OF VALID NEIGHBOUR
            if (distance({0, 0}, neigh_coord) <= radius) {
                std::cout << "neighbour within maze: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
                std::cout << std::to_string(curr_cell->walls[curr_cell->get_neighbour_side(neigh_cell)]) << std::endl;
                if (curr_cell->walls[curr_cell->get_neighbour_side(neigh_cell)] && (visited.find(neigh_coord) == visited.end())) {
                    std::cout << "valid neighbour: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
                    q.enqueue(neigh_coord);
                    visited.insert(neigh_coord);
                    valid_neighbours.push_back(neigh_coord);
                }
            }
        }

    }
    */
    set<pair<int, int>> visited;
    Stack<pair<int, int>> st;
    pair<int, int> curr_coord = end_coord; // !!!
    st.push(curr_coord);
    visited.insert(curr_coord);
    while (curr_coord != start_coord) { // !!!
        HexCell* curr_cell = cells[curr_coord];
        vector<pair<int, int>> all_neighbours = get_neigh_coords(curr_coord);
        vector<pair<int, int>> valid_neighbours;
        for (int i = 0; i < all_neighbours.size(); i++) {
            pair<int, int> neigh_coord = all_neighbours[i];
            //std::cout << "neighbour: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
            if (distance({0, 0}, neigh_coord) <= radius) {
                HexCell* neigh_cell = cells[neigh_coord]; // DOUBLE CHECK DETERMINATION OF VALID NEIGHBOUR
                //std::cout << "neighbour within maze: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
                //std::cout << std::to_string(curr_cell->walls[curr_cell->get_neighbour_side(neigh_cell)]) << std::endl;
                if (!curr_cell->walls[curr_cell->get_neighbour_side(neigh_cell)] && (visited.find(neigh_coord) == visited.end())) {
                    //std::cout << "valid neighbour: {" << std::to_string(neigh_coord.first) << ", " << std::to_string(neigh_coord.second) << "}" << std::endl; 
                    //visited.insert(neigh_coord);
                    valid_neighbours.push_back(neigh_coord);
                    //st.push(neigh_coord);
                }
            }
        } 
        if (valid_neighbours.size() == 0) {
            st.pop();
            curr_coord = st.peek();
        } else {
            curr_coord = valid_neighbours[0];
            st.push(curr_coord);
            visited.insert(curr_coord);
        }
    }
    while (!st.is_empty()) {
        solution.push_back(st.peek());
        st.pop();
    }

}

    // pair<int, int> GOAL = end_coord;
    // Queue<pair<int, int>> q;
    // vector<pair<int, int>> soln;
    // q.enqueue(GOAL);
    // while (!q.is_empty()) {
    //     pair<int, int> curr_coord = q.peek();
    //     HexCell* curr_cell = cells[curr_coord];
    //     q.dequeue();
    //     soln.push_back(curr_coord);
    //     vector<pair<int, int>> all_neighbours = get_neigh_coords(curr_coord);
    //     vector<pair<int, int>> valid_neighbours;
    //     for (int i = 0; i < all_neighbours.size(); i++) {
    //         HexCell* neigh_cell = cells[all_neighbours[i]];
    //         if (distance({0, 0}, all_neighbours[i]) <= radius) {
    //             if (curr_cell->walls[curr_cell->get_neighbour_side(neigh_cell)]) {
    //                 q.enqueue(all_neighbours[i]);
    //                 valid_neighbours.push_back(all_neighbours[i]);
    //             }
    //         }
    //     }
    // }
    // for (int i = soln.size() - 1; i >= 0; i--) {
    //     solution.push_back(soln[i]);
    // }