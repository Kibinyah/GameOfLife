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
    g.set(1,0,Cell::ALIVE);
    g.set(2,1,Cell::ALIVE);
    g.set(2,0,Cell::ALIVE);
    g.set(2,1,Cell::ALIVE);
    g.set(2,2,Cell::ALIVE);
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
     g.set(1,0,Cell::ALIVE);
     g.set(2,0,Cell::ALIVE);
     g.set(0,1,Cell::ALIVE);
     g.set(1,1,Cell::ALIVE);
     g.set(1,2,Cell::ALIVE);
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
    g.set(1,0,Cell::ALIVE);
    g.set(4,0,Cell::ALIVE);
    g.set(0,1,Cell::ALIVE);
    g.set(0,2,Cell::ALIVE);
    g.set(0,3,Cell::ALIVE);
    g.set(4,3,Cell::ALIVE);
    g.set(1,3,Cell::ALIVE);
    g.set(2,3,Cell::ALIVE);
    g.set(3,3,Cell::ALIVE);
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
Grid Zoo::load_ascii(std::string path){
    std::string line;
    std::ifstream file(path);
    int width = 0;
    int height = 0;
    //int x = 0;
    int y = 0;
    Grid g;

    if (!file.is_open()) {
        throw std::runtime_error("No file found");
    }
        file >> width >> height;

        if (width < 0 || height < 0) {
            throw (std::runtime_error("Width and height need to be positive"));
        }
        g = Grid(width, height);
        while (getline(file, line) && y < height) {
            if (line.size() != width && y > 0) {
                throw std::runtime_error("No characters in new line");
            }
            for (int x = 0; x < line.size(); x++) {
                char c = line.at(x);
                if (c == '#') {
                    g.set(x, y, Cell::ALIVE);
                } else if (c == ' ') {
                    g.set(x, y, Cell::DEAD);
                } else {
                    throw std::runtime_error("Wrong character");
                }
            }
            // }
            if (line.size() == width) {
                y++;
            }
        }
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
void Zoo::save_ascii(std::string path, const Grid& g){
    std::ofstream file;
    file.open(path,std::ios::out);
    if(!file.is_open()){
        throw std::runtime_error("Unable to open file");
    }
    file << g.get_width() << " " << g.get_height() << "\n";
    std::stringstream ss;
    ss << g;
    std::string s = ss.str();
    bool temp = true;
    for(int i = 0; i < s.size() - g.get_width() - 3; i++) {
        if (s.at(i) == ' ') {
            file << ' ';
        } else if (s.at(i) == '#') {
            file << '#';
        } else if (s.at(i) == '\n' && temp == false) {
            file << '\n';
        } else if (s.at(i) == '\n' && temp == true) {
            temp = false;
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
Grid Zoo::load_binary(std::string path) {
    std::ifstream file(path, std::ios::binary);
    unsigned int width = 0;
    unsigned int height = 0;
    //Grid g(width,height);
    if (!file.is_open()) {
        throw std::runtime_error("No file found");
    }

        file.seekg(0, std::ios::end);
        unsigned int size = file.tellg();
        file.seekg(0, std::ios::beg);

        file.read((char *) &width, sizeof(int));
        //file.seekg(4);
        file.read((char *) &height, sizeof(int));
        Grid g(width, height);

        //file.seekg(8);

        std::bitset<1000> bitset(width * height);
        for (int i = 0; i < width * height; i++) {
            bitset[i] = 0;
        }

        //int counter = 8;
        unsigned int temp = 0;
        for (int j = 8; j < size; j++) {
            //file.seekg(j);
            unsigned int byte;
            file.read((char *) &byte, 1);
            for (int i = 0; i < 8; i++) {
                unsigned int bit = (byte >> i) & 0x1;
                unsigned int index = i + temp;
                if (bit == 1) {
                    bitset[index] = 1;
                }
            }
            temp += 8;
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                unsigned int point = (width * y) + x;
                if (bitset[point] == 1) {
                    g.set(x, y, Cell::ALIVE);
                }
            }
        }

    return g;
}
    /*std::ifstream file(path, std::ios::in | std::ios::binary);
    int width;
    int height;

    if (!file.is_open()) {
        throw std::runtime_error("No file found");
    }

    file.seekg(0, std::ios::end);
    int size = (int) file.tellg();
    file.seekg(0, std::ios::beg);

    file.read((char *) &width, 4);
    file.seekg(4);
    file.read((char *) &height, 4);

    Grid g(width, height);

    file.seekg(8);
    int counter = 8;

    std::stringstream ss;
    while (counter != size) {
        int byte;
        file.read((char *) &byte, 1);
        std::array<int,8> bits;
        for (int i = 0; i < 8; i++) {
            bits[i] = (byte >> i) & 0x1;
            ss << bits[i];
            std::cout << bits[i];
        }
        std::cout << std::endl;
        counter += 1;
        file.seekg(counter);
    }
    std::string s = ss.str();
    std::cout << s << std::endl;
    if(s.length() < width*height){
        throw std::runtime_error("File ended.");
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (s.at((width*y)+x) == '0') {
                g.set(x, y, Cell::DEAD);
            } else if(s.at((width*y)+x) == '1') {
                g.set(x, y, Cell::ALIVE);
            } else{
                throw std::runtime_error("Error");
            }
        }
    }

    std::cout << g.get_alive_cells() <<std::endl;

    std::cout << g.get(1,3) <<std::endl;
    std::cout << g.get(2,3) <<std::endl;
    std::cout << g.get(3,3) <<std::endl;
    std::cout << g.get(3,2) <<std::endl;
    std::cout << g.get(3,2) <<std::endl;

    std::cout << g;
    return g;
    */


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

