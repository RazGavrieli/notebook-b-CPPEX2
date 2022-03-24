#include <string>
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include "Notebook.hpp"

const int INIT_SIZE = 5;


//class Page {
    //std::vector<std::string> rows;
    const std::string emptyLine = "____________________________________________________________________________________________________";  
    const int lineSize = 100;
    void Page::allocateRows(unsigned int r) {
        /**
         * @brief private function that allocates new rows for the page
         * 
         */
        for (int i = rows.size(); i<=r; i++) {
            rows.push_back(emptyLine);
        }
    }
    
        Page::Page() {
            /**
            * @brief 
            * vector of strings has already been declared in the fields of the class. (objects initialization)
            * In this constructor we will declare defined amount of rows. Each row is a string with 100 empty characters.
            */ 

            for (int i = 0; i<INIT_SIZE; i++) {
                rows.push_back(emptyLine);
            }
        }
        int Page::getsize() {
            /**
             * @brief getter for the amount of rows in the page 
             */

            return rows.size();
        }
        std::string Page::getrow(unsigned int r) {
            /**
             * @brief getter for a specific row in the page (string type, length 100)
             * if the row is bigger than the amount of rows in the page, allocate new rows for it.
             */
            if (r>=rows.size()) {
                allocateRows(r);
                return rows.at(r);
            }
            return rows.at(r);
        }
        std::string Page::getcol(unsigned int c) {
            if (c<0 || c>lineSize) {
                throw std::runtime_error("collums must be an int between 0-100!");
            }
            std::string col;
            for (unsigned int i = 0; i < rows.size(); i++)
            {
                col += getrow(i)[c];
            }
            return col;
            
        }
        void Page::replaceline(unsigned int r, const std::string &newline) {
            if (newline.size()!=lineSize) {
                throw std::runtime_error("new line size has to be exactly 100!");
            }
            if (r>rows.size()) {
                allocateRows(r);
                rows[r] = newline;
            } else {
                rows[r] = newline;
            }
        }
//};

namespace ariel {
    //class Notebook {
            //Notebook::std::vector<Page> pages;
            const std::string emptyLine = "____________________________________________________________________________________________________";  
            const int lineSize = 100;
            const char emptyChar = '_';
            const char erasedChar = '~';
            void Notebook::allocatePages(unsigned int page) {
            /**
             * @brief private function that allocates new pages
             * 
             */
            for (int i = pages.size(); i<=page; i++) {
                    Page newPage;
                    pages.push_back(newPage);
                }
            }
            
                Notebook::Notebook()
                {
                    for (int i = 0; i<INIT_SIZE; i++) {
                        Page newPage;
                        pages.push_back(newPage);
                    }
                }
        
                void Notebook::write(unsigned int page, unsigned int row, unsigned int col, Direction dir, std::string text) {
                    if (page<0||row<0||col<0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                        throw std::runtime_error("bad input!");
                    }
                    if (page>pages.size()) {
                        allocatePages(page);
                    } 

                    if (dir==Direction::Horizontal) {
                        if (lineSize<col+text.size()) {
                            throw std::runtime_error("text is out of bounds!");
                        }
                        std::string oldLine = pages.at(page).getrow(row);
                        std::string newLine = emptyLine;
                        unsigned int j = 0;
                        for (unsigned int i = 0; i<lineSize; i++) {
                            if (i>=col&&i<col+text.size()) {
                                if (oldLine[i]==emptyChar) {
                                    newLine[i]=text[j];
                                    j++;
                                } else {
                                    throw std::runtime_error("text is overlapping!");
                                }
                            } else {
                                newLine[i]=oldLine[i];
                            }
                        }
                        pages.at(page).replaceline(row, newLine);
                    } else { // Vertical writing
                        for (unsigned int i = 0; i<text.size(); i++) {
                            std::string oldLine = pages.at(page).getrow(row+i);
                            if (oldLine[col]==emptyChar) {
                                oldLine[col]=text[i];
                            } else {
                                throw std::runtime_error("text is overlapping!");
                            }
                            pages.at(page).replaceline(row+i, oldLine);              
                        }

                    }
                    
                }
                std::string Notebook::read(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int len) {
                    if (page<0||row<0||col<0||len<=0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                        throw std::runtime_error("bad input!");
                    }
                    if (col+len>lineSize) {
                        throw std::runtime_error("out of bounds!");
                    }
                    std::string text;
                    std::string line = pages.at(page).getrow(row);
                    if (dir==Direction::Horizontal) {
                        for (unsigned int i = col; i < col+len; i++)
                        {
                            text += line[i];
                        }  
                    } else { // Vertical reading
                        for (unsigned int i = 0; i < len; i++)
                        {
                            text += line[col];
                        }
                        
                    }
                    return text;
                }
                void Notebook::erase(unsigned int page, unsigned int row, unsigned int col, Direction dir, unsigned int len) {
                    if (page<0||row<0||col<0||len<=0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                        throw std::runtime_error("bad input!");
                    }
                    if (page>pages.size()) {
                        allocatePages(page);
                    } 
                    if (dir==Direction::Horizontal) {
                        if (lineSize-col<len) {
                            throw std::runtime_error("out of bounds!");
                        }
                        std::string oldLine = pages.at(page).getrow(row);
                        for (unsigned int i = col; i < col+len; i++)
                        {
                            oldLine[i] = erasedChar;
                        }
                        pages.at(page).replaceline(row, oldLine);  
                        
                    } else { // Vertical writing
                        for (unsigned int i = 0; i < len; i++)
                        {
                            std::string oldLine = pages.at(page).getrow(row+i);
                            oldLine[col] = erasedChar;
                            pages.at(page).replaceline(row+i, oldLine);
                        }
                        
                    }
                }
                void Notebook::show(unsigned int page) {
                    std::cout << "page " << page << ":\n";
                    for (unsigned int i = 0; i<pages.at(page).getsize(); i++) {
                        std::cout << i << ".\t" << pages.at(page).getrow(i) << "\n";
                    }
                }
    //};
}

// int main() {
//     ariel::Notebook note;
//     note.write(3, 1, 50, ariel::Direction::Horizontal, "this is the text");
//     note.write(3, 0, 10, ariel::Direction::Vertical, "this is the text");
//     std::cout << note.read(3, 1, 8, ariel::Direction::Horizontal, 70) << "\n";
//     std::cout << note.read(3, 0, 51, ariel::Direction::Vertical, 30) << "\n";

//     note.show(3);
    
// }
