#include "geometry.hpp"


// TUPLE METHODS

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


// MATRIX METHODS BELOW


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

// Slower loop based
/*
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
*/

// Faster unrolled, since size is fixed
Matrixf Matrixf::operator*(Matrixf& rhs) const {
    double dest[4][4] = {0};
    dest[0][0] = this->arr[0][0] * rhs[0][0] + this->arr[0][1] * rhs[1][0] + this->arr[0][2] * rhs[2][0] + this->arr[0][3] * rhs[3][0]; 
    dest[0][1] = this->arr[0][0] * rhs[0][1] + this->arr[0][1] * rhs[1][1] + this->arr[0][2] * rhs[2][1] + this->arr[0][3] * rhs[3][1]; 
    dest[0][2] = this->arr[0][0] * rhs[0][2] + this->arr[0][1] * rhs[1][2] + this->arr[0][2] * rhs[2][2] + this->arr[0][3] * rhs[3][2]; 
    dest[0][3] = this->arr[0][0] * rhs[0][3] + this->arr[0][1] * rhs[1][3] + this->arr[0][2] * rhs[2][3] + this->arr[0][3] * rhs[3][3]; 
    dest[1][0] = this->arr[1][0] * rhs[0][0] + this->arr[1][1] * rhs[1][0] + this->arr[1][2] * rhs[2][0] + this->arr[1][3] * rhs[3][0]; 
    dest[1][1] = this->arr[1][0] * rhs[0][1] + this->arr[1][1] * rhs[1][1] + this->arr[1][2] * rhs[2][1] + this->arr[1][3] * rhs[3][1]; 
    dest[1][2] = this->arr[1][0] * rhs[0][2] + this->arr[1][1] * rhs[1][2] + this->arr[1][2] * rhs[2][2] + this->arr[1][3] * rhs[3][2]; 
    dest[1][3] = this->arr[1][0] * rhs[0][3] + this->arr[1][1] * rhs[1][3] + this->arr[1][2] * rhs[2][3] + this->arr[1][3] * rhs[3][3]; 
    dest[2][0] = this->arr[2][0] * rhs[0][0] + this->arr[2][1] * rhs[1][0] + this->arr[2][2] * rhs[2][0] + this->arr[2][3] * rhs[3][0]; 
    dest[2][1] = this->arr[2][0] * rhs[0][1] + this->arr[2][1] * rhs[1][1] + this->arr[2][2] * rhs[2][1] + this->arr[2][3] * rhs[3][1]; 
    dest[2][2] = this->arr[2][0] * rhs[0][2] + this->arr[2][1] * rhs[1][2] + this->arr[2][2] * rhs[2][2] + this->arr[2][3] * rhs[3][2]; 
    dest[2][3] = this->arr[2][0] * rhs[0][3] + this->arr[2][1] * rhs[1][3] + this->arr[2][2] * rhs[2][3] + this->arr[2][3] * rhs[3][3]; 
    dest[3][0] = this->arr[3][0] * rhs[0][0] + this->arr[3][1] * rhs[1][0] + this->arr[3][2] * rhs[2][0] + this->arr[3][3] * rhs[3][0]; 
    dest[3][1] = this->arr[3][0] * rhs[0][1] + this->arr[3][1] * rhs[1][1] + this->arr[3][2] * rhs[2][1] + this->arr[3][3] * rhs[3][1]; 
    dest[3][2] = this->arr[3][0] * rhs[0][2] + this->arr[3][1] * rhs[1][2] + this->arr[3][2] * rhs[2][2] + this->arr[3][3] * rhs[3][2]; 
    dest[3][3] = this->arr[3][0] * rhs[0][3] + this->arr[3][1] * rhs[1][3] + this->arr[3][2] * rhs[2][3] + this->arr[3][3] * rhs[3][3];
    return Matrixf(dest);
}

Tuple Matrixf::operator*(Tuple& rhs) const {
    Tuple res = Tuple(0,0,0,0);

    res.x = rhs.x * this->arr[0][0]+ rhs.y *this->arr[0][1] + rhs.z * this->arr[0][2] + rhs.w * this->arr[0][3];
    res.y = rhs.x * this->arr[1][0]+ rhs.y *this->arr[1][1] + rhs.z * this->arr[1][2] + rhs.w * this->arr[1][3];
    res.z = rhs.x * this->arr[2][0]+ rhs.y *this->arr[2][1] + rhs.z * this->arr[2][2] + rhs.w * this->arr[2][3];
    res.w = rhs.x * this->arr[3][0]+ rhs.y *this->arr[3][1] + rhs.z * this->arr[3][2] + rhs.w * this->arr[3][3];   

    return res;
}


Matrixf Matrixf::ident(int size){
    double res[4][4] = {0.0};
    for(int i=0; i<size; i++) res[i][i] = 1.0;
    return Matrixf(res);
}

Matrixf Matrixf::transpose() const {
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

// Whole formula for the 4x4 case, inspired from MESA implementation of OpenGL function 
Matrixf Matrixf::inv() const {

    double res[4][4] = {0};
    double det = 1/(this->det());
    double A2323 = this->arr[2][2] * this->arr[3][3] - this->arr[2][3] * this->arr[3][2];
    double A1323 = this->arr[2][1] * this->arr[3][3] - this->arr[2][3] * this->arr[3][1];
    double A1223 = this->arr[2][1] * this->arr[3][2] - this->arr[2][2] * this->arr[3][1];
    double A0323 = this->arr[2][0] * this->arr[3][3] - this->arr[2][3] * this->arr[3][0];
    double A0223 = this->arr[2][0] * this->arr[3][2] - this->arr[2][2] * this->arr[3][0];
    double A0123 = this->arr[2][0] * this->arr[3][1] - this->arr[2][1] * this->arr[3][0];
    double A2313 = this->arr[1][2] * this->arr[3][3] - this->arr[1][3] * this->arr[3][2];
    double A1313 = this->arr[1][1] * this->arr[3][3] - this->arr[1][3] * this->arr[3][1];
    double A1213 = this->arr[1][1] * this->arr[3][2] - this->arr[1][2] * this->arr[3][1];
    double A2312 = this->arr[1][2] * this->arr[2][3] - this->arr[1][3] * this->arr[2][2];
    double A1312 = this->arr[1][1] * this->arr[2][3] - this->arr[1][3] * this->arr[2][1];
    double A1212 = this->arr[1][1] * this->arr[2][2] - this->arr[1][2] * this->arr[2][1];
    double A0313 = this->arr[1][0] * this->arr[3][3] - this->arr[1][3] * this->arr[3][0];
    double A0213 = this->arr[1][0] * this->arr[3][2] - this->arr[1][2] * this->arr[3][0];
    double A0312 = this->arr[1][0] * this->arr[2][3] - this->arr[1][3] * this->arr[2][0];
    double A0212 = this->arr[1][0] * this->arr[2][2] - this->arr[1][2] * this->arr[2][0];
    double A0113 = this->arr[1][0] * this->arr[3][1] - this->arr[1][1] * this->arr[3][0];
    double A0112 = this->arr[1][0] * this->arr[2][1] - this->arr[1][1] * this->arr[2][0];

    res[0][ 0] = det *   ( this->arr[1][ 1] * A2323 - this->arr[1][ 2] * A1323 + this->arr[1][ 3] * A1223 );
    res[0][ 1] = det * - ( this->arr[0][ 1] * A2323 - this->arr[0][ 2] * A1323 + this->arr[0][ 3] * A1223 );
    res[0][ 2] = det *   ( this->arr[0][ 1] * A2313 - this->arr[0][ 2] * A1313 + this->arr[0][ 3] * A1213 );
    res[0][ 3] = det * - ( this->arr[0][ 1] * A2312 - this->arr[0][ 2] * A1312 + this->arr[0][ 3] * A1212 );
    res[1][ 0] = det * - ( this->arr[1][ 0] * A2323 - this->arr[1][ 2] * A0323 + this->arr[1][ 3] * A0223 );
    res[1][ 1] = det *   ( this->arr[0][ 0] * A2323 - this->arr[0][ 2] * A0323 + this->arr[0][ 3] * A0223 );
    res[1][ 2] = det * - ( this->arr[0][ 0] * A2313 - this->arr[0][ 2] * A0313 + this->arr[0][ 3] * A0213 );
    res[1][ 3] = det *   ( this->arr[0][ 0] * A2312 - this->arr[0][ 2] * A0312 + this->arr[0][ 3] * A0212 );
    res[2][ 0] = det *   ( this->arr[1][ 0] * A1323 - this->arr[1][ 1] * A0323 + this->arr[1][ 3] * A0123 );
    res[2][ 1] = det * - ( this->arr[0][ 0] * A1323 - this->arr[0][ 1] * A0323 + this->arr[0][ 3] * A0123 );
    res[2][ 2] = det *   ( this->arr[0][ 0] * A1313 - this->arr[0][ 1] * A0313 + this->arr[0][ 3] * A0113 );
    res[2][ 3] = det * - ( this->arr[0][ 0] * A1312 - this->arr[0][ 1] * A0312 + this->arr[0][ 3] * A0112 );
    res[3][ 0] = det * - ( this->arr[1][ 0] * A1223 - this->arr[1][ 1] * A0223 + this->arr[1][ 2] * A0123 );
    res[3][ 1] = det *   ( this->arr[0][ 0] * A1223 - this->arr[0][ 1] * A0223 + this->arr[0][ 2] * A0123 );
    res[3][ 2] = det * - ( this->arr[0][ 0] * A1213 - this->arr[0][ 1] * A0213 + this->arr[0][ 2] * A0113 );
    res[3][ 3] = det *   ( this->arr[0][ 0] * A1212 - this->arr[0][ 1] * A0212 + this->arr[0][ 2] * A0112 );

    return Matrixf(res);
    
}

// Transformation related stuff
Matrixf Matrixf::translation(double x,double y, double z){

    double res[4][4] = {0};
    res[0][0] = 1.0;
    res[0][3] = x;
    res[1][1] = 1.0;
    res[1][3] = y;
    res[2][2] = 1.0;
    res[2][3] = z;
    res[3][3] = 1.0;
    return Matrixf(res);
}

Matrixf Matrixf::scaling(double x,double y,double z){
    double res[4][4] = {0};
    res[0][0] = x;
    res[1][1] = y;
    res[2][2] = z;
    res[3][3] = 1;

    return Matrixf(res);
}

Matrixf Matrixf::rotation_x(double deg){
    double res[4][4] = {0};
    res[0][0] = 1;
    res[1][1] =  cos(deg);
    res[1][2] = -sin(deg);
    res[2][1] =  sin(deg);
    res[2][2] =  cos(deg);
    res[3][3] = 1;
    return Matrixf(res);
}

Matrixf Matrixf::rotation_z(double deg){
    double res[4][4] = {0};
    res[0][0] = cos(deg);
    res[0][1] = -sin(deg);
    res[1][0] = sin(deg);
    res[1][1] = cos(deg);
    res[2][2] = 1;
    res[3][3] = 1;
    return Matrixf(res);
}

Matrixf Matrixf::rotation_y(double deg){
    double res[4][4] = {0};
    res[0][0] = cos(deg);
    res[0][2] = sin(deg);
    res[1][1] = 1;
    res[3][3] = 1;
    res[2][0] = -sin(deg);
    res[2][2] = cos(deg);
    return Matrixf(res);
}

Matrixf Matrixf::shearing(double xy,double xz,double yx,double yz,double zx,double zy){
    double res[4][4] = {0};
    res[0][0] = 1;
    res[0][1] = xy;
    res[0][2] = xz;
    res[1][1] = 1;
    res[1][0] = yx;
    res[1][2] = yz;
    res[2][2] = 1;
    res[2][0] = zx;
    res[2][1] = zy;
    res[3][3] = 1;
    return Matrixf(res);
}


Matrixf Matrixf::translate(double x,double y,double z){
    *this =  translation(x,y,z) * (*this);
    return *this;
}

Matrixf Matrixf::scale(double x,double y,double z){
    *this =  scaling(x,y,z) * (*this);
    return *this;
}

Matrixf Matrixf::rotate_x(double deg){
    *this =  rotation_x(deg) * (*this);
    return *this;
}

Matrixf Matrixf::rotate_y(double deg){
    *this =  rotation_y(deg) * (*this);
    return *this;
}

Matrixf Matrixf::rotate_z(double deg){
    *this =  rotation_z(deg) * (*this);
    return *this;
}

Matrixf Matrixf::shear(double xy,double xz,double yx,double yz,double zx,double zy){
    *this =  shearing(xy, xz, yx, yz, zx, zy) * (*this);
    return *this;
}


// RAY METHODS BELOW

Ray::Ray(Tuple ori, Tuple dir) : origin(ori),direction(dir){}

Tuple Ray::get_direction(){
    return this->direction;
}

Tuple Ray::get_origin(){

    return this->origin;
}

Tuple Ray::pos(double t){
    return this->origin + t * this->direction;
}

Intersections Obj3D::intersect(Ray ray){
    std::vector<Intersection> a;
    auto res = Intersections(a);  // weird init for std::array
    // for now nothing, will implement later a generalized way
    return res;
}

Intersections Sphere::intersect(Ray ray){
    std::vector<Intersection> res;

    Tuple sphere_to_ray =  ray.get_origin() - Tuple::point(0,0,0);
    double a = ray.get_direction().dot(ray.get_direction());
    double b = 2 * ray.get_direction().dot(sphere_to_ray);
    double c = sphere_to_ray.dot(sphere_to_ray) - 1;
    double discrim = b*b - 4 * a * c;
    
    // if discrim smaller than 0 no intersection hence two infinities are returned
    if ( discrim < 0 ) return res;

    res.push_back(Intersection((-b - sqrt(discrim)) / (2*a),this));
    res.push_back(Intersection((-b + sqrt(discrim)) / (2*a),this));

    return res;
}

Tuple Sphere::get_origin(){
    return this->origin;
}
Tuple Obj3D::get_origin(){
    return this->origin;
}
Intersection::Intersection(double t,Obj3D* obj){
    this->t=t;
    this->object = obj;
}

Intersection& Intersections::operator[](int ind){
    return this->arr[ind];
}

Intersections::Intersections(std::vector<Intersection> l){
        this->arr = l;
        this->count = l.size();
    }


