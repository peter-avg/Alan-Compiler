#include <cstdio>
#include <iostream>
#include "../src/colors/colors.hpp"
#include <string.h>

std::string version = "0.0.1";
std::string outputname = "a.out";
std::string assembly_suffix = ".s"; // Works for my linux machine
std::string llc = "llc";
bool output_asm = false;
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
    std::cout << green_normal << "Usage: alan [options] [file.alan]\n";
    std::cout << "Options:\n";
    std::cout << green_normal << "  -h, --help" << white_normal << "                Display this information\n";
    std::cout << green_normal << "  -v, --version" << white_normal << "             Display the version of the compiler\n";
    std::cout << green_normal << "  -o" << white_normal << "                        Optimize the code\n";
    std::cout << green_normal << "  -i" << white_normal << "                        Output Intermediate Representation\n";
    std::cout << green_normal << "  -f" << white_normal << "                        Output Assembly\n";
    std::cout << green_normal << "  -p" << white_normal << "                        Output the AST tree\n";
    std::cout << green_normal << "  --changesuffix [suffix]" << white_normal << "   Change the suffix of the assembly file\n";
    std::cout << green_normal << "  --changellc [llc]" << white_normal << "         Change the llc command\n";
    std::cout << green_normal << "  --changeout [file]" << white_normal << "        Change the output name\n";
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

        if (arg == "--changeout") {
            if (argv[i + 1] == nullptr) {
                Help();
            }

            if (!strcmp(argv[i+1], "-h") || !strcmp(argv[i+1], "--help")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-v") || !strcmp(argv[i+1], "--version")) {
                Version();
            }

            if (!strcmp(argv[i+1], "-o")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-i")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-f")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-p")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changesuffix")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changellc")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changeout")) {
                Help();
            }

            outputname = argv[i + 1];
        }

        if (arg == "--changellc") {
            if (argv[i + 1] == nullptr) {
                Help();
            }

            if (!strcmp(argv[i+1], "-h") || !strcmp(argv[i+1], "--help")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-v") || !strcmp(argv[i+1], "--version")) {
                Version();
            }

            if (!strcmp(argv[i+1], "-o")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-i")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-f")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-p")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changesuffix")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changellc")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changeout")) {
                Help();
            }

            llc = argv[i + 1];
        }

        if (arg == "--changesuffix") {
            if (argv[i + 1] == nullptr) {
                Help();
            }

            if (!strcmp(argv[i+1], "-h") || !strcmp(argv[i+1], "--help")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-v") || !strcmp(argv[i+1], "--version")) {
                Version();
            }

            if (!strcmp(argv[i+1], "-o")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-i")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-f")) {
                Help();
            }

            if (!strcmp(argv[i+1], "-p")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changesuffix")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changellc")) {
                Help();
            }

            if (!strcmp(argv[i+1], "--changeout")) {
                Help();
            }

            std::string suffix = argv[i + 1];
            assembly_suffix = "." + suffix;
        }

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

    if (!strcmp(filename.c_str(), "")) {
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
    std::string command2 =  llc + " -o " + filename + assembly_suffix + " " + filename + ".imm";

    if (system(command2.c_str()) != 0) {
        exit(1);
    }

    if (output_asm) {
        command2 = "cat " + filename + assembly_suffix;
        system(command2.c_str());
    }

    std::string alan_lib_path = std::getenv("ALAN_LIB_VARIABLE_PATH");
    if (alan_lib_path.empty()) {
        Source();
    }


    std::string last_command = "gcc -no-pie -o " + outputname + " " + filename + assembly_suffix + " " + alan_lib_path + "/lib.a";

    if (system(last_command.c_str()) != 0) {
        exit(1);
    }
}
