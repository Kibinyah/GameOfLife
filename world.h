/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include <string>
#include <iostream>
#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
    private:
        Grid currentGrid;
        Grid nextGrid;
    public:
        World();
        World(unsigned int squaresize);
        World(unsigned int width, unsigned int height);
        World(Grid initial_state);
        //~World();

        int get_width() const;
        int get_height() const;
        int get_total_cells() const;
        int get_alive_cells() const;
        int get_dead_cells() const;
};