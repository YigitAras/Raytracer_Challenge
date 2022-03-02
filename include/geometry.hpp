#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <math.h>
#include <iostream>
#define EPSILON 1.0e-5

inline bool double_cmp(double a, double b){
    return fabs(a-b) < EPSILON;
}



class Tuple{
public:
    double x;
    double y;
    double z;
    double w;

    Tuple(double x, double y, double z, double w);
    Tuple();

    static Tuple point(double x, double y, double z);
    static Tuple vector(double x, double y, double z);
    static Tuple color(double r, double g, double b);

    // Opeartor overloads for convenience
    bool operator==(const Tuple& rhs) const;
    Tuple operator+(const Tuple &rhs) const;
    Tuple operator-(const Tuple &rhs) const;
    Tuple operator-() const;
    Tuple operator*(const double &rhs) const;
    // This one is strictly for color blending
    Tuple operator*(const Tuple &rhs) const;
    Tuple operator/(const double &rhs) const;

    // Mathematical functions
    double norm(){
        // Basic euclidian 2-norm
        return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w* this->w);
    }

    Tuple normalize(){
        Tuple res = Tuple(this->x,this->y,this->z,this->w);
        return res/res.norm();
    }

    double dot(const Tuple& rhs) const;
    Tuple cross(const Tuple& rhs) const;
    
    // friend functions
    friend std::ostream& operator<<(std::ostream& os, const Tuple& tp);
    friend Tuple operator*(const double &lhs ,const Tuple &rhs);
};

#endif