#include "geometry.hpp"


// ostream overload for printing
std::ostream& operator<<(std::ostream& os, const Tuple& tp){
    os << "Tuple: " << tp.x << " " << tp.y << " " << tp.z << " " << tp.w;
    return os;
}

// for commutativity
Tuple operator*(const double &lhs ,const Tuple &rhs) {
    return rhs * lhs;
}

// Tuple class related functions
Tuple::Tuple(double x,double y,double z,double w):x(x),y(y),z(z),w(w){}

Tuple Tuple::point(double x,double y,double z){
    return Tuple(x,y,z,1.0);
}

Tuple Tuple::vector(double x,double y,double z){
    return Tuple(x,y,z,0.0);
}

Tuple Tuple::color(double r, double g, double b){
    // w can be used as opacity later on
    return Tuple(r,g,b,0.0);
}

// Mathematical operations
double Tuple::dot(const Tuple &rhs) const {
    return this->x * rhs.x +
           this->y * rhs.y +
           this->z * rhs.z +
           this->w * rhs.w;
}

Tuple Tuple::cross(const Tuple &rhs) const {
    return Tuple::vector(this->y*rhs.z - this->z*rhs.y,
                         this->z*rhs.x - this->x*rhs.z,
                         this->x*rhs.y - this->y*rhs.x);
}

// Operator overloads

bool Tuple::operator==(const Tuple& rhs) const {
    return  double_cmp(this->x, rhs.x) &&
            double_cmp(this->y, rhs.y) &&
            double_cmp(this->z, rhs.z) &&
            double_cmp(this->w, rhs.w);
}

Tuple Tuple::operator+(const Tuple& rhs) const {
    Tuple res = Tuple(0,0,0,0);
    res.x = this-> x + rhs.x;
    res.y = this-> y + rhs.y;
    res.z = this-> z + rhs.z;
    res.w = this-> w + rhs.w;
    return res;
}

Tuple Tuple::operator-(const Tuple &rhs) const {
    Tuple res = Tuple(0,0,0,0);
    res.x = this-> x - rhs.x;
    res.y = this-> y - rhs.y;
    res.z = this-> z - rhs.z;
    res.w = this-> w - rhs.w;
    return res;
}

Tuple Tuple::operator-() const{
    Tuple res = Tuple(0,0,0,0);
    res.x = -this-> x;
    res.y = -this-> y;
    res.z = -this-> z;
    res.w = -this-> w;
    return res;
}

Tuple Tuple::operator*(const double &rhs) const{
    Tuple res = Tuple(0,0,0,0);
    res.x = this-> x * rhs;
    res.y = this-> y * rhs;
    res.z = this-> z * rhs;
    res.w = this-> w * rhs;
    return res;
}

Tuple Tuple::operator*(const Tuple &rhs) const {
    Tuple res = Tuple(0,0,0,0);
    res.x = this-> x * rhs.x;
    res.y = this-> y * rhs.y;
    res.z = this-> z * rhs.z;
    res.w = this-> w * rhs.w;
    return res;
}

Tuple Tuple::operator/(const double &rhs) const{
    Tuple res = Tuple(0,0,0,0);
    res.x = this-> x / rhs;
    res.y = this-> y / rhs;
    res.z = this-> z / rhs;
    res.w = this-> w / rhs;
    return res;
}
