# AlanCompiler

## Dependencies
* [C++14](https://www.cplusplus.com/)
* [Bison](https://www.gnu.org/software/bison/)
* [Flex](https://en.wikipedia.org/wiki/Flex_(lexical_analyser_generator))
* [LLVM12](https://llvm.org/)
* [CLANG12](https://clang.llvm.org)

## Installation 
```bash 
git clone https://github.com/ntua-el15074/Alan-Compiler.git
make -C cmd
source $HOME/.bashrc
```

## Usage 
* ```alan [OPTIONS] source_file```

The Alan executable is located in the ```bin``` folder.
The executable requires ```lib.a``` also located in the ```bin``` folder, 
which was provided by professor [Kostis Sagonas](https://github.com/kostis).
The building process of the compiler adds the lib.a and bin paths to your 
```.bashrc``` and/or ```.zshrc```. 

The compiler can be used with any of these options
```c++
    -h, --help                Display this information
    -v, --version             Display the version of the compiler
    -o                        Optimize the code
    -i                        Output Intermediate Representation to Standard Output
    -f                        Output Assembly to Standard Output
    -p                        Output the AST tree
    --changesuffix [suffix]   Change the suffix of the assembly file
    --changellc [llc]         Change the llc command
    --changeout [file]        Change the output name
```

The compiler will provide an executable of the program named ```a.out```.

## Demo 
<div align="center">
    <img src="./assets/hello.gif" width="600" height="450" />
</div>

