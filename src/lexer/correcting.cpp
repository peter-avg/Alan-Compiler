#include <iostream>
#include <string>
#include <string.h>
char correctHexadecimals(char *h) {
    char symbol = 0;
    for (int i=0; i<2; i++){
        if (h[i] >= '0' && h[i] <= '9')
            *h -= '0';
        else if (h[i] >= 'A' && h[i] <= 'F')
            h[i] += (10-'A');
        else 
            h[i] += (10-'a');
     }
    symbol = 16*h[0]+h[1];
    return symbol;
}

char correctChars(char *c, int& next) {
    if(*c != '\\') {
        if (*c == '\"') std::cout << "Shit" << std::endl;
        next = 1;
        return *c;
    }
    else {
        if (*(c+1) != 'x') {
            next = 2;
            switch (*(c+1)) {
                case 'n': return '\n';
                case 't': return '\t';
                case 'r': return '\r';
                case '0': return '\0';
                case '\\': return '\\';
                case '\'': return '\'';
                case '\"': return '\"';
            }
            return '\0';
        }
        else {
            next = 4;
            return correctHexadecimals(c+2);
        }
    }
}

/*char * correctString(char *s) {
    int next;
    int i = 0;
    int size = strlen(s);
    char * result = new char[size+1];
    char * current = result;
    while (*s != '\"'){
        current += correctChars(s, next);
        std::cout << *s << "-->" << *current << std::endl; 
        std::cout << "next:" << next << std::endl;
        s += next;
        i++;
    }
    *current = '\0';
    return result;
}
*/   

std::string correctString(char *s) {
    int next;
    int i = 0;
    int size = strlen(s);
    std::string result;
    while (*s != '\"'){
        result += correctChars(s, next);
        std::cout << *s << "-->" << result << std::endl; 
        std::cout << "next:" << next << std::endl;
        s += next;
        i++;
    }
    result[i] = '\0';
    return result;

}

