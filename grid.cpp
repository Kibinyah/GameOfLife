/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 969449
 * @date March, 2020
 */
#include "grid.h"
#include <cstdlib>
#include <stdexcept>

// Include the minimal number of headers needed to support your implementation.
// #include ...
/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */

Grid::Grid() {
    height = 0;
    width = 0;
    grid.assign(0, Cell::DEAD);
}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(unsigned int square_size) {
    width = square_size;
    height = square_size;
    grid.assign(get_total_cells(), Cell::DEAD);
}


/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */

Grid::Grid(const unsigned int w, const unsigned int h) {
    this->width = w;
    this->height = h;
    grid.assign(get_total_cells(), Cell::DEAD);
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */

unsigned int Grid::get_width() const {
    return width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */

unsigned int Grid::get_height() const {
    return height;
}


/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int Grid::get_total_cells() const {
    return width * height;
}


/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int Grid::get_alive_cells() const {
    int count = 0;
    for (unsigned int i = 0; i < get_total_cells(); i++) {
        if (grid[i] == ALIVE) {
            count++;
        }
    }
    return count;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int Grid::get_dead_cells() const {
    int count = 0;
    for (unsigned int i = 0; i < get_total_cells(); i++) {
        if (grid[i] == DEAD) {
            count++;
        }
    }
    return count;
}


/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(const unsigned int &square_size) {
    //Finds the minimum between the square size and length for width and height
    unsigned int minWidth = std::min(square_size, width);
    unsigned int minHeight = std::min(square_size, height);

    //Created a new vector that contains the values of the original vector
    std::vector<Cell> oldGrid(grid);
    //Converts the original vector with the new sizes and fills it all with dead cells.
    grid.assign(square_size * square_size, Cell::DEAD);

    for (unsigned int y = 0; y < minWidth; y++) {
        for (unsigned int x = 0; x < minHeight; x++) {
            unsigned int coordinate = (square_size * y) + x;
            //if the a Cell exists in the old grid, store cell in the new grid of the same position
            //else, store the cell as DEAD in new grid.
            if (oldGrid[(width * y) + x]) {
                grid[coordinate] = oldGrid[(width * y) + x];
            } else {
                grid[coordinate] = DEAD;
            }
        }
    }
    //Assign the width and height to the square size
    this->width = square_size;
    this->height = square_size;
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(const unsigned int &w, const unsigned int &h) {
    //Finds the minimum between the new width and new height with the current width and height
    unsigned int minWidth = std::min(w, width);
    unsigned int minHeight = std::min(h, height);

    //Created a new vector that contains the values of the original vector
    std::vector<Cell> oldGrid(grid);
    //Converts the original vector with the new width and height and fills it all with dead cells.
    grid.assign(w * h, Cell::DEAD);
    //nested for loop up to the mininum height and mininum width
    for (unsigned int y = 0; y < minHeight; y++) {
        for (unsigned int x = 0; x < minWidth; x++) {
            //if the a Cell exists in the old grid, store cell in the new grid of the same position
            //else, store the cell as DEAD in new grid.
            if (oldGrid[(width * y) + x]) {
                grid[(w * y) + x] = oldGrid[(width * y) + x];
            } else {
                grid[(w * y) + x] = DEAD;
            }
        }
    }
    //Assign current width and height to new width and height.
    this->width = w;
    this->height = h;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */

unsigned int Grid::get_index(unsigned int x, unsigned int y) const {
    return (width * y) + x;
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell Grid::get(unsigned int x, unsigned int y) const {
    if (x >= width ||  y >= height) {
        throw (std::exception());
    } else {
        return grid[get_index(x, y)];
    }
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(const unsigned int &x, const unsigned int &y, const Cell &value) {
    if (x >= width || y >= height) {
        throw (std::exception());
    } else {
        grid[get_index(x, y)] = value;
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell &Grid::operator()(unsigned int x, unsigned int y) {
    if (x >= width || y >= height) {
        throw std::runtime_error("Not a valid coordinate");
    } else {
        return grid[get_index(x, y)];
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

const Cell &Grid::operator()(unsigned int x, unsigned int y) const {
    if (x >= width || y >= height) {
        throw std::runtime_error("Not a valid coordinate");
    } else {
        return grid[get_index(x, y)];
    }
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const{
    //Throws exception when either variables arnt a valid coordinate or if x1,y1 are smaller than x0,y0
    if (x0 < 0 || x1 < 0 || x0 > width || x1 > width || y0 < 0 || y1 < 0 || y0 > height ||
        y1 > height || x0 > x1 || y0 > y1) {
        throw (std::exception());
    }
    //Calculates the new width and height for the grid
    unsigned int newWidth = x1 - x0;
    unsigned int newHeight = y1 - y0;
    //Create a new grid with the new width and height
    Grid g(newWidth, newHeight);
    //Values to be incremented during nested for loop to find coordinate of new grid.
    unsigned int newX = 0;
    unsigned int newY = 0;
    //Nested for loop for cells between x0,y0 to x1,y1
    for (unsigned int y = y0; y < y1; y++) {
        for (unsigned int x = x0; x < x1; x++) {
            //Sets the cell from cropped grid to new grid.
            g.grid[newX + (newWidth * newY)] = grid[x + (width * y)];
            //Increment newX but if it is 1 below the newWidth, set to 0 for new row.
            if (newX == newWidth - 1) {
                newX = 0;
            } else {
                newX++;
            }
        }
        newY++;
    }
    return g;
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */

void Grid::merge(const Grid &other, int x0,  int y0, bool alive_only) {
    //Throws exception if the other grid has larger dimensions than current grid or if x0,y0 does not fit in current dimensions.
    if ((other.width * other.height) > width * height || x0 < 0 || y0 < 0 || (unsigned int)x0 > width || (unsigned int)y0 > height) {
        throw (std::exception());
    } else {
        //Turns ints to unsigned ints to avoid warnings
        unsigned int mergeX = x0;
        unsigned int mergeY = y0;
        //Nested for loop to the size of other grid from the merge points.
        for (unsigned int y = mergeY; y < (mergeY + other.height); y++) {
            for (unsigned int x = mergeX; x < (mergeX + other.width); x++) {
                unsigned int position = ((y - mergeY) * (other.width)) + (x - mergeX);
                //if alive_only is false, set the current position to the calculated position of the other grid.
                if (!alive_only) {
                    set(x, y, other.grid[position]);
                } else {
                    //if alive_only is true and other grid Cell is ALIVE, set the current cell to ALIVE
                    if (other.grid[position] == Cell::ALIVE) {
                        set(x, y, other.grid[position]);
                    }
                }
            }
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 **/

Grid Grid::rotate(int rotation) {
    unsigned int offset = 0;
    //Assigns the rotation value to be either 0,1,2 or 3 using math algorithm
    //0 is for 0 degrees
    //1 is for 90 degrees
    //2 is for 180 degrees
    //3 is for 270 degrees
    rotation = std::abs(rotation % 4 + 4) % 4;

    if (rotation == 1) {
        //New grid with swapped width and height is made to set values to from old grid
        Grid g = Grid(height, width);
        for (unsigned int y = 0; y < width; y++) {
            for (unsigned int x = 0; x < height; x++){
                //For 90 degrees, a slightly different algorithm is used depending on the size of width and height
                //All algorithms have the same premise of traversing the old grid from bottom left upwards and rightwards to top right.
                if(width > height) {
                    offset = (height * height - 1) - (x * (width)) + y;
                }else if(width == height){
                    offset = (width * (width - 1)) - (x * (width)) + y;
                }else{
                    offset = (width * width) - (x * (width)) + y;
                }
                g.set(x, y, grid[offset]);
            }
        }
        return g;

    }else if (rotation == 2) {
        Grid g = Grid(width, height);
        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                //For 180 degrees, algorithm will traverse the old grid backwards from bottom right to top left
                unsigned int offset = (height * width - 1) - get_index(x, y);
                g.set(x, y, grid[offset]);
            }
        }
        return g;

    } else if (rotation == 3) {
        Grid g = Grid(height, width);
            for (unsigned int y = 0; y < width; y++) {
                for (unsigned int x = 0; x < height; x++) {
                    //For 270 degrees, algorithm traverses the old grid from top right downwards and leftward to bottom left.
                    unsigned int offset = (width - 1 - y) + (x * (width));
                    g.set(x, y, grid[offset]);
                }
            }

        return g;
    }
    //Returns the current grid when the rotation is 0.
    return *this;
}


/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */


std::ostream &operator<<(std::ostream &out, const Grid &g) {
    //Print out the first row symbols
    out << "+";
    for (unsigned int i = 0; i < g.get_width(); i++) {
        out << "-";
    }
    out << "+" << std::endl;

    //Print out the cells with boundary lines.
    for (unsigned int j = 0; j < g.get_height(); j++) {
        out << "|";
        for (unsigned int i = 0; i < g.get_width(); i++) {
            if (g.get(i, j) == Cell::ALIVE) {
                out << "#";
            } else {
                out << " ";
            }
        }
        out << "|" << std::endl;
    }

    //Print out the bottom row symbols
    out << "+";
    for (unsigned int i = 0; i < g.get_width(); i++) {
        out << "-";
    }
    out << "+" << std::endl;
    return out;
}
