#include <iostream>
#include <string>
#include "plotter.hpp"

using namespace std;
static int parse_line(string line);


int main(int argc, char **argv) {
    
    Plotter p(20,true);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(11.0);
    p.add_value(11.0);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(9.0);
    p.add_value(8.0);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(10.0);
    p.add_value(10.0);

    p.plot_values();

    for (string line; getline(cin, line);) {
        parse_line(line);
    }
    exit(0);
}

int parse_line(string line) {
    return 0;
}
