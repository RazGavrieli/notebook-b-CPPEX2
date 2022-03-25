
#include <string>
#include "Direction.hpp"
#include <vector>

class Page {
    
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
