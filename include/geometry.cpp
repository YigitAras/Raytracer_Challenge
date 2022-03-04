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
Tuple::Tuple():x(0.0),y(0.0),z(0.0),w(0.0){}

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


std::array<double,4>& Matrixf::operator[](int ind){
    return this->arr[ind];
}

Matrixf::Matrixf(double x[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->arr[i][j] = x[i][j];
        }
    }
}

Matrixf::Matrixf(double x[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            this->arr[i][j] = x[i][j];
        }
    }
}

Matrixf::Matrixf(double x[2][2]){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            this->arr[i][j] = x[i][j];
        }
    }
}
bool Matrixf::operator==(Matrixf& rhs) const {
    bool res = true;
    for (int i=0;i<4; i++){
        for(int j=0; j<4; j++){
            res &= double_cmp(this->arr[i][j], rhs[i][j]);
        }
    }
    return res;
}

Matrixf Matrixf::operator*(Matrixf& rhs) const {
    double res[4][4] = {0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
            res[i][j] += this->arr[i][k] * rhs[k][j];
            }
        }
    }
    return Matrixf(res);
}

Matrixf Matrixf::ident(int size){
    double res[4][4] = {0.0};
    for(int i=0; i<size; i++) res[i][i] = 1.0;
    return Matrixf(res);
}

Matrixf Matrixf::trans() const {
    double res[4][4] = {0.0};
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            res[j][i] = this->arr[i][j];
        }
    }
    return Matrixf(res);
}

void Matrixf::print() const{
    std::cout<< "Here is the matrix: " << "\n";

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout << this->arr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::array<std::array<double, 4>,4> Matrixf::getData(){
    return this->arr;
}

double Matrixf::det2x2(int ind1, int ind2) const{

    if(ind1 == 3 || ind2 == 3 || ind1<0 || ind2<0 ) {
        std::cout << "Errenous indices provided to det2x2\n";
        return -1; // just for now, will handle errors later maybe
    }
    return this->arr[ind1][ind2]*this->arr[ind1+1][ind2+1] -
           this->arr[ind1][ind2+1]*this->arr[ind1+1][ind2];
}

double Matrixf::det() const{
    // Simply take DET assuming it is a 4x4
    // + cofac3x3(0,0)
    // - cofac3x3(0,1)
    // + cofac3x3(0,2)
    // - cofac3x3(0,3)
    
    return this->arr[0][0] * cofac_3x3_00() -
           this->arr[0][1] * cofac_3x3_01() +
           this->arr[0][2] * cofac_3x3_02() -
           this->arr[0][3] * cofac_3x3_03();    
}

inline double Matrixf::cofac_3x3_00() const {
    return this->arr[1][1] * (this->arr[2][2]*this->arr[3][3] - this->arr[2][3]*this->arr[3][2]) -
           this->arr[1][2] * (this->arr[2][1]*this->arr[3][3] - this->arr[3][1]*this->arr[2][3]) +
           this->arr[1][3] * (this->arr[2][1]*this->arr[3][2] - this->arr[3][1]*this->arr[2][2]);
}
inline double Matrixf::cofac_3x3_01() const {
    return this->arr[1][0] * (this->arr[2][2]*this->arr[3][3] - this->arr[2][3]*this->arr[3][2]) -
           this->arr[1][2] * (this->arr[2][0]*this->arr[3][3] - this->arr[3][0]*this->arr[2][3]) +
           this->arr[1][3] * (this->arr[2][0]*this->arr[3][2] - this->arr[3][0]*this->arr[2][2]);
}
inline double Matrixf::cofac_3x3_02() const {
    return this->arr[1][0] * (this->arr[2][1]*this->arr[3][3] - this->arr[3][1]*this->arr[2][3]) -
           this->arr[1][1] * (this->arr[2][0]*this->arr[3][3] - this->arr[3][0]*this->arr[2][3]) +
           this->arr[1][3] * (this->arr[2][0]*this->arr[3][1] - this->arr[3][0]*this->arr[2][1]);
}

inline double Matrixf::cofac_3x3_03() const { 
    return this->arr[1][0] * (this->arr[2][1]*this->arr[3][2] - this->arr[3][1]*this->arr[2][2]) -
           this->arr[1][1] * (this->arr[2][0]*this->arr[3][2] - this->arr[3][0]*this->arr[2][2]) +
           this->arr[1][2] * (this->arr[2][0]*this->arr[3][1] - this->arr[3][0]*this->arr[2][1]);
}

