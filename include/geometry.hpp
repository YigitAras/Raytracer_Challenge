#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <math.h>
#include <algorithm>
#include <array>
#include <iostream>
#define EPSILON 1.0e-5


//USAGE:
// std::array<int, 5> arr5 = SubArray<decltype(arr5)>(arr10, 5);
template<typename X, typename Y>
X SubArray(Y& src, const size_t size)
{
    // Probably should throw an error if the size param is bigger than the initial array
    X dst;
    for(int i=0;i<size;i++){
    std::copy(src[i].begin(), src[i].begin() + size, dst[i].begin());
    }

    return dst;
}



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

class Matrixf{
    private:
    std::array<std::array<double, 4>,4> arr;

    public:
    static Matrixf ident(int);
    Matrixf(double [4][4]);
    Matrixf(double [3][3]);
    Matrixf(double [2][2]);
    std::array<std::array<double, 4>,4> getData();
    std::array<double,4>& operator[](int ind);
    bool operator==(Matrixf& rhs) const;
    void print() const;
    Matrixf trans() const;
    Matrixf operator*(Matrixf& rhs) const;
    double det() const;
    double cofac_3x3_00() const;
    double cofac_3x3_01() const;
    double cofac_3x3_02() const;
    double cofac_3x3_03() const;
    double det2x2(int ind1,int ind2) const;
};

#endif