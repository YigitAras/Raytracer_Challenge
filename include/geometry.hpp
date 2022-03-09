#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <math.h>
#include <algorithm>
#include <array>
#include <iostream>
#define EPSILON 1.0e-5
#define M_PI 3.14159265358979323846
#include <limits>
#include <vector>
#include <initializer_list>



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
    Matrixf transpose() const;
    Matrixf operator*(Matrixf& rhs) const;
    Tuple operator*(Tuple& rhs) const;
    double det() const;

    double cofac_3x3(double data[3][3], int ind1, int ind2) const;
    // Inline to speed things up
    // Since Matrixf is just 4x4, can use these for inv
    inline double cofac_3x3_00() const;
    inline double cofac_3x3_01() const;
    inline double cofac_3x3_02() const;
    inline double cofac_3x3_03() const;

    // MESA OpenGL implementation of 4x4 Matrix inversion
    Matrixf inv() const;

    // Transformation functions
    static Matrixf translation(double,double,double);
    static Matrixf scaling(double,double,double);
    static Matrixf rotation_x(double);
    static Matrixf rotation_y(double);
    static Matrixf rotation_z(double);
    static Matrixf shearing(double,double,double,double,double,double);


    // Easier to use API calls for modifying a Matrixf object
    Matrixf translate(double,double,double);
    Matrixf scale(double,double,double);
    Matrixf rotate_x(double);
    Matrixf rotate_y(double);
    Matrixf rotate_z(double);
    Matrixf shear(double,double,double,double,double,double);
};

class Ray{
    private:
    Tuple origin;
    Tuple direction;
    
    public:
    Ray(Tuple ori, Tuple dir);
    Tuple get_origin();
    Tuple get_direction();
    Tuple pos(double);
};

class Obj3D {
    protected:
    Tuple origin = Tuple::vector(0,0,0);
    public:
    virtual std::array<double,2> intersect(Ray ray);
    virtual Tuple get_origin();
};

class Sphere : protected Obj3D {
    private:
    double r=1; // for now initialize it as unit sphere

    public:
    std::array<double,2> intersect(Ray ray);
    Tuple get_origin();

};

class Intersection {
    public:
    Obj3D object;
    double t;
};

class Intersections {
    public:
    std::vector<Intersection> arr;
    size_t count;
    Intersection& operator[](int ind);
    Intersections(std::initializer_list<Intersection> l) : arr(l),count(l.size()) {}
};

#endif