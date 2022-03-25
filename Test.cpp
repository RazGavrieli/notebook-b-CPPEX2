// CREATE TEST CLASS
#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>

std::string nospaces(std::string input) {
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

TEST_CASE("Bad input") {
    ariel::Notebook notebook;
    const std::string length20string = "123456789123456789";
        SUBCASE("Out of bounds") {
            //notebook.read(page, row, col, direction, length)
            CHECK_THROWS(notebook.read(1, 1, 1, Direction::Horizontal, 101));
            CHECK_THROWS(notebook.read(1, 1, 60, Direction::Horizontal, 41));
            CHECK_THROWS(notebook.read(1, 1, 98, Direction::Horizontal, 3));
            CHECK_THROWS(notebook.read(1, 1, 110, Direction::Horizontal, 1));

            CHECK_THROWS(notebook.erase(1, 3, 1, Direction::Horizontal, 101));
            CHECK_THROWS(notebook.erase(1, 3, 80, Direction::Horizontal, 50));
            CHECK_THROWS(notebook.erase(1, 3, 20, Direction::Horizontal, 90));

            CHECK_THROWS(notebook.write(1, 1, 90, Direction::Horizontal, length20string));
            CHECK_THROWS(notebook.write(1, 2, 103, Direction::Horizontal, length20string));
            CHECK_NOTHROW(notebook.write(1, 3, 80, Direction::Horizontal, length20string));
        }
        SUBCASE("Overlapping") {
            notebook.write(1, 3, 80, Direction::Horizontal, length20string);
            notebook.show(1);
            CHECK_THROWS(notebook.write(1, 3, 83, Direction::Horizontal, "overlap test"));
            CHECK_THROWS(notebook.write(1, 3, 73, Direction::Horizontal, "overlap test"));
            notebook.erase(1, 3, 80, Direction::Horizontal, 10);
            CHECK_THROWS(notebook.write(1, 3, 93, Direction::Horizontal, "overlap test"));
        }
        SUBCASE("Unprintable characters") {
            CHECK_THROWS(notebook.write(3, 3, 73, Direction::Horizontal, "bad \n character"));
            CHECK_THROWS(notebook.write(2, 3, 73, Direction::Horizontal, "bad \t character"));
            CHECK_THROWS(notebook.write(7, 3, 73, Direction::Horizontal, "bad \f character"));
            notebook.show(7);
            CHECK_THROWS(notebook.write(1, 3, 73, Direction::Horizontal, "bad \b character"));
        }
        SUBCASE("Negative indexs") {
            CHECK_THROWS(notebook.read(1, -1, 1, Direction::Horizontal, 101));
            CHECK_THROWS(notebook.read(1, 1, -60, Direction::Horizontal, 41));
            CHECK_THROWS(notebook.read(-1, 1, 20, Direction::Horizontal, 3));
            CHECK_THROWS(notebook.read(-1, 0, -40, Direction::Horizontal, 0));
            CHECK_THROWS(notebook.erase(1, 3, 1, Direction::Horizontal, -30));
            CHECK_THROWS(notebook.erase(1, 3, 80, Direction::Horizontal, 0));
        }
}

TEST_CASE("Good input") {
    ariel::Notebook notebook;
    SUBCASE("Horizontal") {
        
        const std::string writeTestString = "this is the test";
        const std::string erased3tildes = "~~~";
        notebook.write(1, 1, 1, Direction::Horizontal, writeTestString);
        CHECK(notebook.read(1, 1, 1, Direction::Horizontal, writeTestString.length()) == writeTestString);
        notebook.erase(1, 1, 1, Direction::Horizontal, 3);
        CHECK(notebook.read(1, 1, 1, Direction::Horizontal, 3) == erased3tildes);
        CHECK(notebook.read(1, 1, 1, Direction::Horizontal, writeTestString.length()) == erased3tildes+writeTestString.substr(3));
    }
    ariel::Notebook notebook2;
    SUBCASE("Vertical") {
        const std::string writeTestString = "t\nh\ni\ns\n \ni\ns\n \nt\nh\ne\n \nt\ne\ns\nt";
        const std::string erased3tildes = "~\n~\n~";
        notebook2.write(2, 1, 1, Direction::Vertical, nospaces(writeTestString));
        const std::string tilde = "~";
        const std::string t = "t";
        const std::string h = "h";
        const std::string i = "i";
        std::string outputString = notebook2.read(2,1,1,Direction::Vertical, 1);
        CHECK(outputString == t);
        CHECK(notebook2.read(2,2,1,Direction::Vertical, 1) == h);
        CHECK_NOTHROW(notebook2.erase(2, 1, 1, Direction::Vertical, 2));
        CHECK(notebook2.read(2,1,1,Direction::Vertical, 1) == tilde);
        CHECK(notebook2.read(2,2,1,Direction::Vertical, 1) == tilde);
        CHECK(notebook2.read(2,3,1,Direction::Vertical, 1) == i);
    }

}