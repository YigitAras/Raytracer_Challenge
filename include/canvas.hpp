#ifndef CANVAS_H
#define CANVAS_H
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "geometry.hpp"


class Canvas{
    private:
    std::vector<std::vector<Tuple>> IMG;
    int width;
    int height;

    public:
    Canvas(int W,int H);
    double clamp(double num, double lo, double hi);
    int get_width(){return this->width;}
    int get_height(){return this->height;}
    std::vector<Tuple>& operator[](int ind);
    void dummy_to_ppm(std::string);
    void to_ppm(std::string);
};


#endif