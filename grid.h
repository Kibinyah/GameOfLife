/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 969449
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
#include <string>
#include <iostream>
#include <vector>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
private:
    unsigned int width;
    unsigned int height;
    std::vector<Cell> grid;
    //Cell *grid;
public:
    Grid();
    Grid(unsigned int square_size);
    Grid(unsigned int width, unsigned int height);
    //~Grid();
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

    void resize(const unsigned int &square_size);
    void resize(const unsigned int &width, const unsigned int &height);

    unsigned int get_index(unsigned int width, unsigned int height) const;
    Cell get(unsigned int x, unsigned int y) const;
    void set(const unsigned int &x, const unsigned int &y, const Cell &value);

    Cell& operator()(unsigned int width, unsigned int height);
    const Cell& operator()(unsigned int width, unsigned int height) const;

    Grid crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const;
    void merge(const Grid &other, int x0, int y0, bool alive_only = false);

    Grid rotate(int rotation);
    friend std::ostream& operator<<(std::ostream& out, const Grid& g);
};
