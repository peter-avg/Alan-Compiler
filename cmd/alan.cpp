#include <cstdio>
#include <iostream>
#include "../src/colors/colors.hpp"

std::string version = "0.0.1";
std::string outputname = "a.out";
bool output_asm = false;

void Version() {
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font red_normal = {colors::Color::RED,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};

    std::cout << green_bold << "Alan Compiler" << red_normal << " " << version << "\n";
    std::cout << white_normal << "A compiler for the Alan programming language\n";
    exit(0);
}

void Help() {
    colors::Font green_bold = {colors::Color::GREEN,colors::Style::BOLD};
    colors::Font green_normal = {colors::Color::GREEN,colors::Style::NORMAL};
    colors::Font white_normal = {colors::Color::WHITE,colors::Style::NORMAL};

    std::cout << green_bold << "Alan Compiler" << " " << version << "\n";
    std::cout << white_normal << "A compiler for the Alan programming language\n";
    std::cout << green_normal << "Usage: alan [options] [file]\n";
    std::cout << "Options:\n";
    std::cout << green_normal << "  -h, --help" << white_normal << "    Display this information\n";
    std::cout << green_normal << "  -v, --version" << white_normal << " Display the version of the compiler\n";
    std::cout << green_normal << "  -o" << white_normal << "            Optimize the code\n";
    std::cout << green_normal << "  -f" << white_normal << "            Output Intermediate Representation\n";
    std::cout << green_normal <<"  -s" << white_normal << "            Output Assembly\n";
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Help();
    }

    std::string command = "comp";
    std::string filename = "";

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            Help();
        }

        if (arg == "-v" || arg == "--version") {
            Version();
        }

        if (arg == "-o") {
            command += " -O ";
        }

        if (arg == "-f") {
            command += " -L ";
        }

        if (arg == "-s") {
            output_asm = true;
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

    if (command == "comp") {
        command += " ";
    }

    command += filename;


    if (system("pwd > tmp") != 0) {
        exit(1);
    }

    FILE *f = fopen("tmp", "r");
    char cwd[1024];
    fgets(cwd, 1024, f);
    fclose(f);

    std::string cwd_str = cwd;

    cwd_str.pop_back();

    std::string bin_path = cwd_str + "/bin";

    if (system("rm tmp") != 0) {
        exit(1);
    }

    std::string export_path = "export PATH=" + bin_path + ":$PATH";

    if (system(export_path.c_str()) != 0) {
        exit(1);
    }

    int res = system(command.c_str());
    if (res != 0) {
        exit(1);
    }

    if (system("llc -o out.s out.ll") != 0) {
        exit(1);
    }

    if (output_asm) {
        system("cat out.s");
    }

    std::string last_command = "gcc -no-pie -o a.out out.s " + bin_path +"/lib.a";

    if (system(last_command.c_str()) != 0) {
        exit(1);
    }
}
