#include <string>
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include "Notebook.hpp"

const int INIT_SIZE = 5;
const std::string emptyLine = "____________________________________________________________________________________________________";  
const int lineSize = 100;
const char emptyChar = '_';
const char erasedChar = '~';

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
        std::string Page::getrow( unsigned int r) {
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
        //std::string Page::getcol( unsigned int c) {
            /**
             * @brief unused function for future use
             * 
             */
        //     if (c<0 || c>lineSize) {
        //         throw std::runtime_error("collums must be an int between 0-100!");
        //     }
            
        //     std::string col;
        //     for ( int i = 0; i < rows.size(); i++)
        //     {
        //         col += getrow(i)[c];
        //     }
        //     return col;      
        // }

        void Page::replaceline( unsigned int r, const std::string &newline) {
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

namespace ariel {
    void Notebook::allocatePages( unsigned int page) {
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
            /**
             * @brief constructor for the notebook. 
             * Initialized INIT_SIZE pages
             * 
             */
            for (int i = 0; i<INIT_SIZE; i++) {
                Page newPage;
                pages.push_back(newPage);
            }
        }

        void Notebook::write( int spage,  int srow,  int scol, Direction dir, std::string text) {
            /**
             * @brief writes text into the asked indexs
             * 
             */
            if (spage<0||srow<0||scol<0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                throw std::runtime_error("bad input!");
            }
            unsigned int page = (unsigned int)spage; unsigned int row = (unsigned int)srow; unsigned int col = (unsigned int)scol;
            
            if (page>=pages.size()) {
                allocatePages(page);
            } 

            if (dir==Direction::Horizontal) {
                if (lineSize<col+text.size()) {
                    throw std::runtime_error("text is out of bounds!");
                }
                std::string oldLine = pages.at(page).getrow(row);
                std::string newLine = emptyLine;
                size_t j = 0;
                for (size_t i = 0; i<lineSize; i++) {
                    if (i>=col&&i<col+text.size()) {
                        if (oldLine[i]==emptyChar) {
                            if (isprint(text[j])==0||text[j]=='~') {
                                throw std::runtime_error("bad character found in text");
                            }
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
                for (   size_t i = 0; i<text.size(); i++) {
                    std::string oldLine = pages.at(page).getrow(row+i);
                    if (oldLine[col]==emptyChar) {
                        if (isprint(text[i])==0||text[i]=='~') {
                            throw std::runtime_error("bad character found in text");
                        }
                        oldLine[col]=text[i];
                    } else {
                        throw std::runtime_error("text is overlapping!");
                    }
                    pages.at(page).replaceline(row+i, oldLine);              
                }

            }
            
        }
        std::string Notebook::read( int spage,  int srow,  int scol, Direction dir,  int slen) {
            /**
             * @brief returns the text at the asked indexs
             * 
             */
            if (spage<0||srow<0||scol<0||slen<=0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                throw std::runtime_error("bad input!");
            }
            unsigned int page = (unsigned int)spage; unsigned int row = (unsigned int)srow; unsigned col = (unsigned int)scol; unsigned int len = (unsigned int)slen;

            if (page>pages.size()) {
                allocatePages(page);
            }
            std::string text;
            std::string line = pages.at(page).getrow(row);
            if (dir==Direction::Horizontal) {
                if (col+len>lineSize) {
                     throw std::runtime_error("out of bounds!");
                }
                for ( size_t i = col; i < col+len; i++)
                {
                    text += line[i];
                }  
            } else { // Vertical reading
                if (col>=lineSize) {
                    throw std::runtime_error("out of bounds!");
                }
                for ( size_t i = 0; i < len; i++)
                {
                    line = pages.at(page).getrow(row+i);
                    text += line[col];
                }
                
            }
            return text;
        }
        void Notebook::erase( int spage,  int srow,  int scol, Direction dir,  int slen) {
            /**
             * @brief writes '~' ontop of the asked indexs in the notebook
             * 
             */
            if (spage<0||srow<0||scol<0||slen<=0||(dir!=Direction::Vertical&&dir!=Direction::Horizontal)) {
                throw std::runtime_error("bad input!");
            }
            unsigned int page = (unsigned int)spage; unsigned int row = (unsigned int)srow; unsigned int col = (unsigned int)scol; unsigned int len = (unsigned int)slen;
            if (page>pages.size()) {
                allocatePages(page);
            } 
            if (dir==Direction::Horizontal) {
                if (lineSize<len+col) {
                    throw std::runtime_error("out of bounds!");
                }
                std::string oldLine = pages.at(page).getrow(row);
                for ( size_t i = col; i < col+len; i++)
                {
                    oldLine[i] = erasedChar;
                }
                pages.at(page).replaceline(row, oldLine);  
                
            } else { // Vertical writing
                 if (col>=lineSize) {
                    throw std::runtime_error("out of bounds!");
                }
                for ( size_t i = 0; i < len; i++)
                {
                    std::string oldLine = pages.at(page).getrow(row+i);
                    oldLine[col] = erasedChar;
                    pages.at(page).replaceline(row+i, oldLine);
                }
                
            }
        }
        void Notebook::show( int spage) {
            /**
             * @brief prints to std::cout every allocated line of the asked page.
             * page #:
             *      0. ...
             *      1. ... 
             *      2. ..
             *      .  ..
             *      .  ..
             *      .  ..
             */
            if (spage<0) {
                throw std::runtime_error("indexs cant be negative");
            }
            unsigned int page = (unsigned int)spage;
            std::cout << "page " << page << ":\n";
            for ( size_t i = 0; i<pages.at(page).getsize(); i++) {
                std::cout << i << ".\t" << pages.at(page).getrow(i) << "\n";
            }
        }
}


