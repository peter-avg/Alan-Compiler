#include <cstdio>
#include <iostream>
#include "../src/colors/colors.hpp"
#include <string.h>
#include <filesystem>

std::string version = "0.0.1";
std::string outputname = "a.out";
bool output_asm = false;
bool clean_up = false;
int count = 0;
colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
colors::Font red_bold = {colors::Color::RED,colors::Style::BOLD};
colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};
colors::Font green_normal = {colors::Color::GREEN,colors::Style::NORMAL};

void NoFileSpecified() {
    std::cout << red_bold << "FileError: " << white_normal << "No File specified" << std::endl;
    exit(0);
}

void Version() {
    std::cout << green_bold << "Alan Compiler" << red_normal << " " << version << "\n";
    std::cout << white_normal << "A compiler for the Alan programming language\n";
    exit(0);
}

void Source() {

    std::cout << green_bold << "Alan Compiler" << red_normal << " " << version << "\n";
    std::cout << white_normal << "You should source your bashrc or zshrc file\n";
    exit(0);
}

void Help() {
    std::cout << green_bold << "Alan Compiler" << " " << version << "\n";
    std::cout << white_normal << "A compiler for the Alan programming language\n";
    std::cout << green_normal << "Usage: alan [options] [file]\n";
    std::cout << "Options:\n";
    std::cout << green_normal << "  -h, --help" << white_normal << "    Display this information\n";
    std::cout << green_normal << "  -v, --version" << white_normal << " Display the version of the compiler\n";
    std::cout << green_normal << "  -o" << white_normal << "            Optimize the code\n";
    std::cout << green_normal << "  -i" << white_normal << "            Output Intermediate Representation\n";
    std::cout << green_normal << "  -f" << white_normal << "            Output Assembly\n";
    std::cout << green_normal << "  -p" << white_normal << "            Output the AST tree\n";
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        NoFileSpecified();
    }

    std::string command = "comp";
    std::string filename = "";

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            count++;
            Help();
        }

        if (arg == "-v" || arg == "--version") {
            count++;
            Version();
        }

        if (arg == "-o") {
            count++;
            command += " -O ";
        }

        if (arg == "-i") {
            count++;
            command += " -L ";
        }

        if (arg == "-f") {
            count++;
            output_asm = true;
        }

        if (arg == "-p") {
            count++;
            command += " -P ";
        }

        size_t pos = arg.find_last_of('.');
        if (pos != std::string::npos && arg.substr(pos + 1) == "alan") {
            filename = argv[i];
        }
    }

    if (!strcmp(filename.c_str(), "") && clean_up) {
        NoFileSpecified();
        exit(1);
    }

    if (command == "comp") {
        command += " ";
    }

    command += filename;

    int res = system(command.c_str());
    if (res != 0) {
        exit(1);
    }

    filename = filename.substr(0, filename.find_last_of('.'));
    std::string command2 = "llc -o " + filename + ".asm " + filename + ".imm";

    if (system(command2.c_str()) != 0) {
        exit(1);
    }

    if (output_asm) {
        command2 = "cat " + filename + ".asm";
        system(command2.c_str());
    }

    std::string alan_lib_path = std::getenv("ALAN_LIB_VARIABLE_PATH");
    if (alan_lib_path.empty()) {
        Source();
    }


    std::string last_command = "gcc -no-pie -o " + outputname + " " + filename + ".asm " + alan_lib_path + "/lib.a";

    if (system(last_command.c_str()) != 0) {
        exit(1);
    }
}
