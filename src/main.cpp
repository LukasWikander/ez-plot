#include <iostream>
#include <string>

using namespace std;
static int parseLine(string line);


int main(int argc, char **argv) {
    
    for (string line; getline(cin, line);) {
        parseLine(line);
    }
    exit(0);
}

int parseLine(string line) {
    
}