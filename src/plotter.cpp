#include "plotter.hpp"

#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <numeric>

Plotter::Plotter(unsigned int maxNumberOfValues, bool rangeToZero)
: maxNumberOfValues(maxNumberOfValues), rangeToZero(rangeToZero) {

}

void Plotter::plot_values(void) {

    auto terminal_size = get_terminal_size();
    auto rows_of_values = get_value_rows();
    auto cols_of_values = get_value_cols();
    vector<pair<unsigned int, unsigned int>> rows_and_cols;
    Plot plot(terminal_size.first, terminal_size.second);

    zip(rows_of_values, cols_of_values, rows_and_cols);
    for (const auto &row_and_col : rows_and_cols) {
        cout << row_and_col.first << " " << row_and_col.second << endl;
        plot.insertMarker(row_and_col.first, row_and_col.second);
    }
    plot.insertVerticalLine(0);
    plot.insertHorizontalLine(plot.getRows()-1);

    clear_terminal();
    // Plot
    for (const auto &row : plot) {
        for (const auto &elem : row) {
            cout << elem;
        }
        cout << endl;
    }
    exit(0);
}

void Plotter::clear_values(void) {
    values.clear();
}

void Plotter::add_value(double value) {
    if (values.size() == maxNumberOfValues) {
        values.pop_front();
    }
    values.push_back(value);
}

double Plotter::get_max_value(void) {
    double maximum_element = *max_element(values.begin(), values.end());
    return rangeToZero ? max(maximum_element, 0.0) : maximum_element;
}

double Plotter::get_min_value(void) {
    double minimum_element = *min_element(values.begin(), values.end());
    return rangeToZero ? min(minimum_element, 0.0) : minimum_element;
}

vector<unsigned int> Plotter::get_value_rows() {
    auto size = get_terminal_size();
    auto minval = get_min_value();
    auto maxval = get_max_value();
    
    vector<unsigned int> row_numbers;

    cout << "Max: " << maxval << endl;
    cout << "Min: " << minval << endl;
    cout << "Rows: " << size.first << endl;
    cout << "Cols: " << size.second << endl;

    for (auto value : values) {
        // Linear min-max interpolation
        double part = (value - minval) / (maxval - minval);
        // Switch direction and scale
        row_numbers.push_back(round((1-part) * static_cast<double>(size.first)));
    }

    return row_numbers;
}

vector<unsigned int> Plotter::get_value_cols() {

    auto size = get_terminal_size();
    if (values.size() > size.second) {
        cout << "Number of values exceeds terminal size";
        return vector<unsigned int>();
    }

    vector<unsigned int> col_numbers(values.size());
    iota(col_numbers.begin(), col_numbers.end(), size.second - values.size());

    return col_numbers;
}


pair<unsigned int, unsigned int> Plotter::get_terminal_size() {
    struct winsize size;
    pair<unsigned int, unsigned int> retval;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    retval.first = size.ws_row;
    retval.second = size.ws_col;

    return retval;
}

void Plotter::clear_terminal(void) {
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}




void Plot::insertHorizontalLine(const unsigned int row) {
    for (auto &elem : this->at(row)) {
        elem = '-';
    }
}

void Plot::insertVerticalLine(const unsigned int col) {
    for (auto &row : *this) {
        row.at(col) = '|';
    }
}