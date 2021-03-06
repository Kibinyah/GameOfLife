/**
 * Implements a class representing a 2d grid world for simulating a cellular automaton.
 *      - Worlds can be constructed empty, from a size, or from an existing Grid with an initial state for the world.
 *      - Worlds can be resized.
 *      - Worlds can return counts of the alive and dead cells in the current Grid state.
 *      - Worlds can return their current Grid state.
 *
 *      - A World holds two equally sized Grid objects for the current state and next state.
 *          - These buffers are swapped after each update step.
 *
 *      - Stepping a world forward in time applies the rules of Conway's Game of Life.
 *          - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *      - Worlds have a private helper function used to count the number of alive cells in a 3x3 neighbours
 *        around a given cell.
 *
 *      - Updating the world state can conditionally be performed using a toroidal topology.
 *          - Moving off the left edge you appear on the right edge and vice versa.
 *          - Moving off the top edge you appear on the bottom edge and vice versa.
 *
 * @author 969449
 * @date March, 2020
 */
#include "world.h"
#include <utility>

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * World::World()
 *
 * Construct an empty world of size 0x0.
 *
 * @example
 *
 *      // Make a 0x0 empty world
 *      World world;
 *
 */
World::World(){
    currentGrid = 0;
    nextGrid = 0;
}

/**
 * World::World(square_size)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x16 world
 *      World x(16);
 *
 *      // Also make a 16x16 world
 *      World y = World(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the world.
 */

World::World(unsigned int squaresize){
    currentGrid = Grid(squaresize);
    nextGrid = Grid(squaresize);
}

/**
 * World::World(width, height)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 world
 *      World world(16, 9);
 *
 * @param width
 *      The width of the world.
 * @param height
 *      The height of the world.
 */

World::World(unsigned int width, unsigned int height){
    currentGrid = Grid(width,height);
    nextGrid = Grid(width,height);
}

/**
 * World::World(initial_state)
 *
 * Construct a world using the size and values of an existing grid.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 *      // Make a world by using a grid as an initial state
 *      World world(grid);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World bad_world = grid; // All around me are familiar faces...
 *
 * @param initial_state
 *      The state of the constructed world.
 */

World::World(Grid initial_grid){
    currentGrid = std::move(initial_grid);
    nextGrid = Grid(get_width(),get_height());
}

/**
 * World::get_width()
 *
 * Gets the current width of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << world.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << read_only_world.get_width() << std::endl;
 *
 * @return
 *      The width of the world.
 */

unsigned int World::get_width() const {
    return currentGrid.get_width();
}

/**
 * World::get_height()
 *
 * Gets the current height of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << world.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << read_only_world.get_height() << std::endl;
 *
 * @return
 *      The height of the world.
 */
unsigned int World::get_height() const {
    return currentGrid.get_height();
}

/**
 * World::get_total_cells()
 *
 * Gets the total number of cells in the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << world.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << read_only_world.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int World::get_total_cells() const {
    return currentGrid.get_total_cells();
}

/**
 * World::get_alive_cells()
 *
 * Counts how many cells in the world are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << world.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int World::get_alive_cells() const {
    return currentGrid.get_alive_cells();
}

/**
 * World::get_dead_cells()
 *
 * Counts how many cells in the world are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << world.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int World::get_dead_cells() const {
    return currentGrid.get_dead_cells();
}

/**
 * World::get_state()
 *
 * Return a read-only reference to the current state
 * The function should be callable from a constant context.
 * The function should not invoke a copy the current state.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << world.get_state() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << read_only_world.get_state() << std::endl;
 *
 * @return
 *      A reference to the current state.
 */
Grid World::get_state() const{
    return currentGrid;
}

/**
 * World::resize(square_size)
 *
 * Resize the current state grid in to the new square width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 8x8
 *      world.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void World::resize(const unsigned int &square_size){
    currentGrid.resize(square_size);
}

/**
 * World::resize(new_width, new_height)
 *
 * Resize the current state grid in to the new width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 2x8
 *      world.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void World::resize(const unsigned int &width, const unsigned int &height){
    currentGrid.resize(width,height);
}

/**
 * World::count_neighbours(x, y, toroidal)
 *
 * Private helper function to count the number of alive neighbours of a cell.
 * The function should not be visible from outside the World class.
 *
 * Neighbours are considered within the 3x3 square centred around the cell at x,y in the current state grid.
 * Ignore the centre coordinate, a cell is not its own neighbour.
 * Attempt to keep the logic as simple, expressive, and readable as possible.
 *
 * If toroidal = false then skip any neighbours that would be outside of the grid,
 * this assumes the grid is Cell::DEAD outside its bounds.
 *
 * If toroidal = true then correctly wrap out of bounds coordinates to the opposite side of the grid.
 *
 * This function is in World and not Grid because the 3x3 sized neighbourhood is specific to Conway's Game of Life,
 * while Grid is more generic to any 2D grid based cellular automaton.
 *
 * @param x
 *      The x coordinate of the centre of the neighbourhood.
 *
 * @param y
 *      The y coordinate of the centre of the neighbourhood.
 *
 * @param toroidal
 *      If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom.
 *
 * @return
 *      Returns the number of alive neighbours.
 */

int World::count_neighbours(const int x, const int y, bool toroidal){
    int count_neighbours = 0;
    if(!toroidal){
        //for toroidal = false
        //nested for loop for cells surrounding the current cell
        for(int j = y - 1; j <= y+1; j++){
            for(int i = x-1; i <= x+1; i++) {
                //Skips the centre cell
                if(i == x && j == y){
                    continue;
                }
                //Checks the surrounding cell of the current cell is not against the grid wall.
                if(i >= 0 && (unsigned int)i < get_width() && j >= 0 && (unsigned int)j < get_height()){
                    //Increments count_neighbours if the surrounding cell is alive.
                    if(get_state().get(i,j) == ALIVE){
                        count_neighbours += 1;
                    }
                }
            }
        }
    }else {
        //For torodial = true
        //Nested for loop for cells surrounding the current cell
        for(int j = y - 1; j <= y+1; j++){
            for(int i = x-1; i <= x+1; i++) {
                //skips the centre cell
                if(i == x && j == y) {
                    continue;
                }
                //Checks if the left side of surround cells are beyond the left wall
                else if (i  < 0) {
                    //Checks if the top left surrounding cell is beyond the grid
                    if (j < 0) {
                        //Increments the counter if the bottom right cell of the grid is alive
                        if (get_state().get(get_width() - 1, get_height() - 1) == ALIVE) {
                            count_neighbours += 1;
                        }
                    //Checks if the bottom left surrounding cell is beyond the grid.
                    } else if ((unsigned int)j >= get_height()) {
                        //Increments the counter if the top left cell of the grid is alive.
                        if (get_state().get(get_width() - 1, 0) == ALIVE) {
                            count_neighbours += 1;
                        }
                    //Checks if j is within the range of the height
                    } else {
                        //Increments the counter if the opposite right end of the current grid row is alive
                        if (get_state().get(get_width() - 1, j) == ALIVE) {
                            count_neighbours += 1;
                        }
                    }
                //Checks if the right side of surround cells are beyond the right wall
                } else if ((unsigned int)i >= get_width()) {
                    //Checks if the top right surrounding cell is beyond the grid
                    if (j < 0) {
                        //Increments the counter if the bottom left cell of the grid is alive
                        if (get_state().get(0, get_height() - 1) == ALIVE) {
                            count_neighbours += 1;
                        }
                    //Checks if the bottom right surrounding cell is beyond the grid.
                    } else if ((unsigned int)j >= get_height()) {
                        //Increments the counter if the top left cell of the grid is alive
                        if (get_state().get(0, 0) == ALIVE) {
                            count_neighbours += 1;
                        }
                    //Checks if j is within the range of the height
                    } else {
                        //Increments the counter if the opposite left end of the current grid row is alive
                        if (get_state().get(0, j) == ALIVE) {
                            count_neighbours += 1;
                        }
                    }
                //Checks if the top side of surround cells are beyond the top wall
                }else if (j < 0) {
                    //Increments the counter if the opposite bottom end of the current grid column is alive
                    if (get_state().get(i, get_height() - 1) == ALIVE) {
                        count_neighbours += 1;
                    }
                //Checks if the bottom side of surround cells are beyond the bottom wall
                }else if ((unsigned int)j >= get_height()) {
                    //Increments the counter if the opposite top end of the current grid column is alive
                    if (get_state().get(i, 0) == ALIVE) {
                        count_neighbours += 1;
                    }
                //Increments the counter if the surrounding cell is within the dimensions of the grid.
                }else if (i >= 0 && (unsigned int)i < get_width() && j >= 0 && (unsigned int)j < get_height()) {
                    if (get_state().get(i,j) == ALIVE) {
                        count_neighbours += 1;
                    }
                }
            }
        }
    }
    return count_neighbours;
}
/**
 * World::step(toroidal)
 *
 * Take one step in Conway's Game of Life.
 *
 * Reads from the current state grid and writes to the next state grid. Then swaps the grids.
 * Should be implemented by invoking World::count_neighbours(x, y, toroidal).
 * Swapping the grids should be done in O(1) constant time, and should not invoke a copy.
 * Try and boil the logic down to the fewest and most simple conditional statements.
 *
 * Rules: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *      - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *      - Any live cell with two or three live neighbours lives on to the next generation.
 *      - Any live cell with more than three live neighbours dies, as if by overpopulation.
 *      - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */

void World::step(bool toroidal){
    for(unsigned int y = 0; y < get_height(); y++){
        for(unsigned int x = 0; x < get_width(); x++){
            //find the number of neighbours of the current cell
            unsigned int num = count_neighbours(x,y,toroidal);
            //If current cell is alive and has neighbours of less than 2 or more than 3, it becomes dead.
            //If current cell is alive and has neighbours of 2 or 3, it stays alive.
            if(get_state().get(x,y) == ALIVE){
                if(num < 2 || num > 3){
                    nextGrid.set(x,y,DEAD);
                }else{
                    nextGrid.set(x,y,ALIVE);
                }
            //If current cell is dead and has neighbours of 3, it becomes alive.
            //If current cell is dead and doesnt have neighbours of 3, it stays dead.
            }else{
                if(num == 3){
                    nextGrid.set(x,y,ALIVE);
                }else{
                    nextGrid.set(x,y,DEAD);
                }
            }
        }
    }
    std::swap(currentGrid,nextGrid);
}

/**
 * World::advance(steps, toroidal)
 *
 * Advance multiple steps in the Game of Life.
 * Should be implemented by invoking World::step(toroidal).
 *
 * @param steps
 *      The number of steps to advance the world forward.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */

void World::advance(unsigned int steps, bool toroidal){
    for(unsigned int i = 0; i < steps; i++){
        step(toroidal);
    }
}