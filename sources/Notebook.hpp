
#include <string>
#include "Direction.hpp"
#include <vector>

class Page {
        // this class will have a dynamic array of Strings.
        // The length of each string is 100.
        // Dynamic array of strings:
        // Upon declaration a page will have DEFINED amount of rows. 
        // If a row bigger then the current amount of rows is being reached, we will make the amount of rows bigger. To infinity.
        // 
        std::vector<std::string> rows;
        void allocateRows( unsigned int r);
        public:
            Page(); 
            int getsize();
            std::string getrow(unsigned int r);
            //std::string getcol(unsigned int c); - written function that is currently unused
            void replaceline( unsigned int r,  const std::string &newline);
    };
namespace ariel {
    class Notebook {
        // This class will have a dynamic array of pages. 
        // 
        // Dynamic array of pages:
        // Upon declaration a notebook will have DEFINED amount of pages. 
        // Each page is an objects of it's own, the page manage its own amount of rows. 
        // If a page higher then the current amount of pages is being reached, we will make the amount of pages bigger. To infinity.
        std::vector<Page> pages;
        void allocatePages( unsigned int page);
        public:
            Notebook();
            void write( int page, int row, int col, Direction dir, std::string text);
            std::string read( int page, int row, int col, Direction dir, int len);
            void erase( int page,  int row,  int col, Direction dir,  int len);
            void show( int page);
    };
}
/** Declration of class Page removed from .hpp to keep it away from client **/
