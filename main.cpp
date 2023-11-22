#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string_view>

class WC {
    private:
        std::ifstream file;
        std::string filename;
    public:
        WC() {
        }
        WC(std::string filename) {
            this->file.open(filename);
            this->filename = filename;
        }
        int get_no_of_lines() {
            char ch;
            int no_of_lines = 0;
            if (file.get() == EOF) {
                file.close();
                file.open(filename);
            }
            while (file) {
                ch = file.get();

                if (ch == '\n') {
                    no_of_lines++;
                }
            }
            return no_of_lines;
        }

        int get_char_length() {
            char ch;
            int no_of_chars = 0;

            if (file.get() == EOF) {
                file.close();
                file.open(filename);
            }
            while (file) {

                ch = file.get();
                if (ch == EOF)
                    break;

                no_of_chars++;
            }
            return no_of_chars;
        }

        int get_byte_length() {
            return get_char_length();
        }

        int get_no_of_words() {
            char ch, prevCh;
            int no_of_words = 0;
            if (file.get() == EOF) {
                file.close();
                file.open(filename);
            }

            while (file) {
                ch = file.get();
                if (isspace(ch) && !isspace(prevCh)) {
                    no_of_words++;
                }

                prevCh = ch;
            }
            return no_of_words;
        }
};

int main (int argc, char *argv[]) {
    using namespace std::literals;
    std::string command = argv[1];

    std::string filename = argv[argc - 1];
    if (command == "-h"sv || command == "--help"sv) {
        std::cout << "help text here" << std::endl;
        return 0;
    }
    WC wc = WC(filename);
    if (command == "-c"sv) {
        std::cout << wc.get_byte_length();
        return 0;
    }
    if (command == "-l"sv) {
        std::cout << wc.get_no_of_lines();
        return 0;
    }
    if (command == "-w"sv) {
        std::cout << wc.get_no_of_words();
        return 0;
    }
    if (command == "-m"sv) {
        std::cout << wc.get_char_length();
        return 0;
    }

    if (argc == 2) {
        std::cout << "  " << wc.get_no_of_lines() <<
            "  " <<  wc.get_no_of_words() <<
            " " <<  wc.get_char_length() <<
            " " <<  filename;
    }
    return 0;
}

