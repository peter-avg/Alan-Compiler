#include <cstdio>
#include <iostream>
#include "../src/colors/colors.hpp"

std::string version = "0.0.1";

void Help() {
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font green_normal = {colors::Color::GREEN,colors::Style::NORMAL};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};

    std::cout << green_bold << "Alan Compiler" << red_normal << " " << version << "\n";
    std::cout << white_normal << "A compiler for the Alan programming language\n";
    std::cout << "Usage: alan [options] [file]\n";
    std::cout << "Options:\n";
    std::cout << green_normal << "  -h, --help" << white_normal << "    Display this information\n";
    std::cout << green_normal << "  -v, --version" << white_normal << " Display the version of the compiler\n";
    std::cout << green_normal << "  -O" << white_normal << "            Optimize the code\n";
    std::cout << green_normal << "  -L" << white_normal << "            Output Intermediate Representation\n";
    std::cout << green_normal <<"  -S" << white_normal << "            Output Assembly\n";
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Help();
    }

    std::string command = "./cmd/comp";
    std::string filename = "";

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            Help();
        }

        if (arg == "-O") {
            command += " -O ";
        }

        if (arg == "-L") {
            command += " -L ";
        }

        size_t pos = arg.find_last_of('.');
        if (pos != std::string::npos && arg.substr(pos + 1) == "alan") {
            filename = argv[i];
        }


    }

    if (filename == "") {
        std::cout << "No file specified\n";
        exit(1);
    }

    if (command == "./cmd/comp") {
        command += " ";
    }

    command += filename;


    int res = system(command.c_str());
    if (res != 0) {
    }

}
