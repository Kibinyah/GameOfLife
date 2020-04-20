/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 969449
 * @date March, 2020
 */
#include "zoo.h"
#include <fstream>
#include <sstream>
#include <array>
#include <bitset>

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider(){
    Grid g(3,3);
    g.set(1,0,ALIVE);
    g.set(2,1,ALIVE);
    g.set(0,2,ALIVE);
    g.set(1,2,ALIVE);
    g.set(2,2,ALIVE);
    return g;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
 Grid Zoo::r_pentomino(){
     Grid g(3,3);
     g.set(1,0,ALIVE);
     g.set(2,0,ALIVE);
     g.set(0,1,ALIVE);
     g.set(1,1,ALIVE);
     g.set(1,2,ALIVE);
     return g;
 }

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship(){
    Grid g(5,4);
    g.set(1,0,ALIVE);
    g.set(4,0,ALIVE);
    g.set(0,1,ALIVE);
    g.set(0,2,ALIVE);
    g.set(4,2,ALIVE);
    g.set(0,3,ALIVE);
    g.set(1,3,ALIVE);
    g.set(2,3,ALIVE);
    g.set(3,3,ALIVE);
    return g;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(const std::string& path){
    std::string line;
    std::ifstream file(path);
    int width = 0;
    int height = 0;

    //Throws runtime error if file cannot be opened
    if(!file.is_open()){
        throw std::runtime_error("No file found");
    }
    //Reads the 1st and 2nd elements of the file as width and height.
    file >> width >> height;
    //Throws runtime error if the width or height is less than 0
    if(width < 0 || height < 0){
        throw (std::runtime_error("Width and height need to be positive"));
    }
    //Turn width and height to unsigned ints to remove warnings.
    unsigned int unsignedWidth = width;
    unsigned int unsignedHeight = height;
    Grid g(unsignedWidth, unsignedHeight);
    unsigned int y = 0;
    //Reads each line of the file.
    while(getline(file, line) && y < unsignedHeight){
        unsigned int lineSize = line.size();
        //Throws runtime error if it expects characters in the new line
        if (lineSize != unsignedWidth && y > 0){
            throw std::runtime_error("No characters in new line");
        }
        //Reads each character of the line
        for(unsigned int x = 0; x < lineSize; x++){
            char c = line.at(x);
            //Sets cell to be alive if it reads '#'
            if (c == '#') {
                g.set(x, y, Cell::ALIVE);
            //Sets cell to be dead if it reads ' '
            } else if (c == ' ') {
                g.set(x, y, Cell::DEAD);
            //throws runtime error if neither characters are read.
            } else {
                throw std::runtime_error("Wrong character");
            }
        }
        //increments y if the line size is the same as width.
        if (lineSize == unsignedWidth) {
            y++;
        }
    }
    file.close();
    return g;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(const std::string& path, const Grid& g){
    std::ofstream file;
    file.open(path,std::ios::out);
    //throws runtime error if file cannot be opened
    if(!file.is_open()){
        throw std::runtime_error("Unable to open file");
    }
    //Initially writes the width and height into file
    file << g.get_width() << " " << g.get_height() << "\n";
    //Stringstream recieves the characters that represent the grid and is converted to string value.
    std::stringstream ss;
    ss << g;
    std::string s = ss.str();
    //for loop that traverse through the grid excluding the top symbol row and the bottom symbol row
    for(unsigned int i = g.get_width() + 3; i < s.size() - g.get_width() - 3; i++) {
        //If string value has ' ', write ' ' to file.
        if (s.at(i) == ' ') {
            file << ' ';
        //If string value has '#', write '#' to file.
        } else if (s.at(i) == '#') {
            file << '#';
        //If string value has '\n', writhe '\n' to file.
        } else if (s.at(i) == '\n') {
            file << '\n';
        }
    }
    file.close();
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    unsigned int width = 0;
    unsigned int height = 0;
    //throws runtime error when the file cannot be opened.
    if (!file.is_open()) {
        throw std::runtime_error("No file found");
    }

    //Sets binary reader pointer to the end of the file to set the file size.
    file.seekg(0, std::ios::end);
    unsigned int size = file.tellg();
    //Sets the binary reader pointer back to the beginning of the file.
    file.seekg(0, std::ios::beg);
    //Reads in the first 4 byte to find the width
    file.read((char *) &width, sizeof(int));
    //Reads the next 4 bytes to find the height
    file.read((char *) &height, sizeof(int));
    //Create a bitset with width and height and assign all values to false.
    std::bitset<500> bitset(width * height);
    for (unsigned int i = 0; i < width * height; i++) {
        bitset[i] = false;
    }
    unsigned int index = 0;
    for (unsigned int j = 8; j < size; j++) {
        //Reads a byte from the file
        unsigned int byte;
        file.read((char *) &byte, 1);
        //For loop to read each bit of the byte
        for (unsigned int i = 0; i < 8; i++) {
            //Calculates if the bit is either 1 or 0
            unsigned int bit = (byte >> i) & 0x1u;
            //if bit is 1, then assign the current index of the bitset to true.
            if (bit == 1) {
                bitset[index] = true;
            }
            index++;
        }
    }
    //throws runtime error when the temp counter is smaller than the grid size.
    if(index < width*height){
        file.close();
        throw std::runtime_error("File ended unexpectedly");
    }
    Grid g(width, height);
    //Nested for loop to set cell values to from bitset
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            unsigned int point = (width * y) + x;
            //If bitset value is true, set the current cell to be alive
            if (bitset[point] == true) {
                g.set(x, y, Cell::ALIVE);}
            }
        }
    file.close();
    return g;
}



/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_binary(const std::string& path, const Grid& g){
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    //Throws runtime error if the file is unable to open.
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    //Writes into the file the width and height with 4 bytes each
    unsigned int width = g.get_width();
    unsigned int height = g.get_height();
    file.write((char *) &width, sizeof(int));
    file.write((char *) &height, sizeof(int));
    //Create a bitset with width and height and assign all values to false.
    std::bitset<500> bitset(width * height);
    for (unsigned int i = 0; i < width * height; i++) {
        bitset[i] = false;
    }
    //Nested for loop through the grid
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            //If the cell is alive, set the bitset to be true
            if (g.get(x, y) == Cell::ALIVE) {
                bitset[g.get_index(x, y)] = true;
            }
        }
    }
    unsigned int byte = 0;
    unsigned int i = 0;
    //Loop through bitset
    while(i < width*height){
        //Calculate a single byte by adding the next 8 bits together
        byte = (bitset[i]*1) + (bitset[i+1]*2) + (bitset[i+2]*4) + (bitset[i+3]*8) + (bitset[i+4]*16) +
               (bitset[i+5]*32) + (bitset[i+6]*64) + (bitset[i+7]*128);
        //Write the byte to the file.
        file.write((char*)&byte,1);
        i += 8;
    }
    file.close();
}
