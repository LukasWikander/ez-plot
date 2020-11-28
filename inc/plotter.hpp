
#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <iostream>
#include <deque>
#include <tuple>
#include <vector>

using namespace std;

class Plotter {
public:
    Plotter(unsigned int maxNumberOfValues=20, bool rangeToZero=true);
    void add_value(double value);
    void clear_values(void);
    void plot_values(void);
private:
    deque<double> values;
    unsigned int maxNumberOfValues;
    bool rangeToZero;
    
    double get_max_value(void);
    double get_min_value(void);
    vector<unsigned int> get_value_rows();
    vector<unsigned int> get_value_cols();
    pair<unsigned int,unsigned int> get_terminal_size();
    void clear_terminal(void);


    template <typename A, typename B>
    void zip(
        const vector<A> &a, 
        const vector<B> &b, 
        vector<pair<A,B>> &zipped) {
        for (size_t i = 0; i<a.size(); ++i) {
            zipped.push_back(std::make_pair(a[i], b[i]));
        }
    }
    
    template <typename A, typename B>
    void unzip(
        const std::vector<std::pair<A, B>> &zipped, 
        std::vector<A> &a, 
        std::vector<B> &b) {
        for (size_t i = 0; i < a.size(); i++) {
            a[i] = zipped[i].first;
            b[i] = zipped[i].second;
        }
    }
};

class Plot : public vector<vector<char>> {
    public:
    Plot(const unsigned int rows, const unsigned int cols) {
        for (unsigned int i = 0; i < rows; ++i) {
            this->push_back(vector<char>(cols, ' '));
        }
    }
    void insertHorizontalLine(const unsigned int row);
    void insertVerticalLine(const unsigned int col);
    void insertMarker(const unsigned int row, const unsigned int col,
            const char marker = '#') { this->at(row).at(col) = marker; }

    unsigned int getRows() const { return this->size(); }
    unsigned int getCols() const { return this->at(0).size(); }
};


#endif