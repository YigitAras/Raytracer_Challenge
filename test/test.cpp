#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/geometry.hpp"
#include "../include/canvas.hpp"



TEST_CASE( "Tuple elements can be accessed", "[Tuple]" ) {
    Tuple ex_tuple = Tuple(4.3,-4.2,3.1,1.0);
    REQUIRE(double_cmp(ex_tuple.x,4.3) == true);
    REQUIRE(double_cmp(ex_tuple.y,-4.2) == true);
    REQUIRE(double_cmp(ex_tuple.z,3.1) == true);
    REQUIRE(double_cmp(ex_tuple.w,1.0) == true);
}
TEST_CASE( "Point has w=1, Vector has w=0", "[Vector and Point]" ) {
    Tuple ex_point1 = Tuple::point(4,-4,3);
    Tuple ex_tuple1 = Tuple(4,-4,3,1);
    Tuple ex_point2 = Tuple::vector(4,-4,3);
    Tuple ex_tuple2 = Tuple(4,-4,3,0);
    
    REQUIRE(ex_point1 == ex_tuple1);
    REQUIRE(ex_point2 == ex_tuple2);
}


TEST_CASE( "Adding two tuples results in another tuple", "[TUPLE+TUPLE=TUPLE]" ) {
    Tuple t1 = Tuple(3,-2,5,1);
    Tuple t2 = Tuple(-2,3,1,0);
    Tuple res_sum = Tuple(1,1,6,1);
    REQUIRE(res_sum == t1+t2);
}

TEST_CASE("Subtracting a point from another point yields a vector", "[Point-Point = Vec]"){
    Tuple p1 = Tuple::point(3,2,1);
    Tuple p2 = Tuple::point(5,6,7);
    Tuple res_sub = Tuple::vector(-2,-4,-6);
    REQUIRE(res_sub == p1-p2);
}


TEST_CASE("Subtracting a vector from a point yields another point", "[Point-VEC=Point]") {
    Tuple p1 = Tuple::point(3,2,1);
    Tuple p2 = Tuple::vector(5,6,7);
    Tuple res_sub = Tuple::point(-2,-4,-6);
    REQUIRE(res_sub == p1-p2);
}
TEST_CASE("Subtracting a vector from another vector yields another vector", "[VEC-VEC=VEC]") {
    Tuple p1 = Tuple::vector(3,2,1);
    Tuple p2 = Tuple::vector(5,6,7);
    Tuple res_sub = Tuple::vector(-2,-4,-6);
    REQUIRE(res_sub == p1-p2);
}

TEST_CASE("Negating a vector is just its negative", "[minus VEC = VEC * -1]") {
    Tuple p1 = Tuple(1,-2,3,-4);
    Tuple res_neg = Tuple(-1,2,-3,4);
    REQUIRE(res_neg == -p1);
}

TEST_CASE("Scalar multiplication of a tuple", "[Tuple*scalar]"){
    Tuple p1 = Tuple(1,-2,3,-4);
    Tuple res = Tuple(3.5,-7,10.5,-14);    
    Tuple res2 = Tuple(0.5,-1,1.5,-2);
    REQUIRE(res ==  p1 * 3.5);
    REQUIRE(res2 == p1 *0.5);
}

TEST_CASE("Scalar divison of a tuple", "[Tuple/scalar]"){
    Tuple p1 = Tuple(1,-2,3,-4);
       
    Tuple res = Tuple(0.5,-1,1.5,-2);
    REQUIRE(res ==  p1 / 2);
    
}

TEST_CASE("Norm of one vector is it's magnitude", "[Norm of a vector]"){
    Tuple v1 = Tuple::vector(1,0,0);
    Tuple v2 = Tuple::vector(0,1,0);
    Tuple v3 = Tuple::vector(0,0,1);

    REQUIRE( 1 == v1.norm());
    REQUIRE( 1 == v2.norm());
    REQUIRE( 1 == v3.norm());

    Tuple v4 = Tuple::vector(1,2,3);
    REQUIRE(sqrt(14) == v4.norm());
    Tuple v5 = Tuple::vector(-1,-2,-3);
    REQUIRE(sqrt(14) == v5.norm());
}

TEST_CASE("A normalized vector should have magnitude 1", "[Norm(vec) == 1 if normalized]"){
    Tuple v1 = Tuple::vector(4,0,0);
    Tuple v2 = Tuple::vector(1,2,3);
    
    Tuple res1 = Tuple::vector(1,0,0);
    Tuple res2 = Tuple::vector(0.26726, 0.53452, 0.80178);
    REQUIRE(v1.normalize() == res1);
    REQUIRE(v2.normalize() == res2);
}

TEST_CASE("Dot product between two vectors/tuples", "[Vec1 dot Vec2]"){
    Tuple v1 = Tuple::vector(1,2,3);
    Tuple v2 = Tuple::vector(2,3,4);

    REQUIRE(v1.dot(v2) == 20);
}

TEST_CASE("Cross product of two vectors is another that is orthogonal to both", "[Vec1 cross Vec2]"){
    Tuple v1 = Tuple::vector(1,2,3);
    Tuple v2 = Tuple::vector(2,3,4);

    Tuple res1 = Tuple::vector(-1,2,-1);
    Tuple res2 = Tuple::vector(1,-2,1);

    REQUIRE(res1 == v1.cross(v2));
    REQUIRE(res2 == v2.cross(v1));
}

TEST_CASE("Can use Tuple for color operations", "[Color operations]"){
    Tuple c1 = Tuple::color(0.9, 0.6, 0.75);
    Tuple c2 = Tuple::color(0.7, 0.1, 0.25);
    Tuple res1 = Tuple::color(1.6,0.7,1.0);
    Tuple res2 = Tuple::color(0.2,0.5,0.5);

    REQUIRE(res1 == c1+c2);
    REQUIRE(res2 == c1-c2);

    Tuple c3 = Tuple::color(0.2,0.3,0.4);
    Tuple res3 = Tuple::color(0.4,0.6,0.8);
    REQUIRE(res3 == c3*2);

    Tuple c4 = Tuple::color(1,0.2,0.4);
    Tuple c5 = Tuple::color(0.9,1,0.1);
    Tuple res4 = Tuple::color(0.9,0.2,0.04);
    REQUIRE(res4 == c4*c5);

}

TEST_CASE("Canvas is initialized with color(0,0,0) for all elements", "[Canvas init]"){
    Canvas img = Canvas(10,20);

    for(int i=0; i<20;i++){
        for(int j=0; j<10; j++){
            REQUIRE(img[i][j] == Tuple::color(0,0,0));
        }
    }
}

TEST_CASE("Can update a value in IMG with indexing", "[IMG indexing]"){
    Canvas img = Canvas(10,20);
    Tuple c1 = Tuple::color(1,0,0);

    img[2][3] = c1;
    REQUIRE(img[2][3] == Tuple(1,0,0,0));
}

TEST_CASE("Writing to PPM file works for header part", "[PPM format write]"){
    Canvas img = Canvas(5,3);
    img.dummy_to_ppm("out1.txt");

    std::ifstream test1("test1.txt");
    std::ifstream out1("../out1.txt");

    std::stringstream b1;
    std::stringstream b2;

    b1 << test1.rdbuf();
    b2 << out1.rdbuf();

    REQUIRE(b1.str() == b2.str());
}

TEST_CASE("Full write test for PPM files work", "[PPM write full]"){
    Canvas img = Canvas(5,3);
    Tuple c1 = Tuple::color(1.5,0,0);
    Tuple c2 = Tuple::color(0,0.5,0);
    Tuple c3 = Tuple::color(-0.5,0,1);
    img[0][0] = c1;
    img[1][2] = c2;
    img[2][4] = c3;

    img.to_ppm("out2.txt");

    std::ifstream test2("test2.txt");
    std::ifstream out2("../out2.txt");

    std::stringstream b1;
    std::stringstream b2;

    b1 << test2.rdbuf();
    b2 << out2.rdbuf();

    std::cout << b1.str() << std::endl;
    std::cout << b2.str() << std::endl;
    REQUIRE(b1.str() == b2.str());
    
}

TEST_CASE("Full write test for PPM files work, also with line endings", "[PPM write full with line end]"){
    Canvas img = Canvas(10,2);
    for(int i = 0; i< img.get_height(); i++){
        for(int j = 0; j< img.get_width(); j++){
            img[i][j] = Tuple::color(1,0.8,0.6);
        }
    }
    img.to_ppm("out3.txt");
    std::ifstream test3("test3.txt");
    std::ifstream out3("../out3.txt");

    std::stringstream b1;
    std::stringstream b2;

    b1 << test3.rdbuf();
    b2 << out3.rdbuf();

    std::cout << b1.str() << std::endl;
    std::cout << b2.str() << std::endl;
    REQUIRE(b1.str() == b2.str());
}

TEST_CASE("Matrix can be initialized properly", "[Matrix initialization]"){
    double mat[4][4] = {{1.0,2.0,3.0,4.0},{5.5,6.5,7.5,8.5},{9.0,10.0,11.0,12.0},{13.5,14.5,15.5,16.5}};
    Matrixf m1 = Matrixf(mat);

    REQUIRE(m1[0][0] ==1.0); 
    REQUIRE(m1[0][3] == 4.0);
    REQUIRE(m1[1][0]== 5.5);
    REQUIRE(m1[1][2] == 7.5);
    REQUIRE(m1[2][2] == 11.0);
    REQUIRE(m1[3][0] == 13.5);
    REQUIRE(m1[3][2] == 15.5);
}

TEST_CASE("Can check equality of two matrices", "[Matrix equality]"){
    double m4[4][4] = {{-3,5,0,1},{1,-2,-7,2},{0,1,1,3},{1,2,3,4}};
    double m5[4][4] = {{-3,5,0,1},{1,-2,-3,3},{0,2,2,3},{1,2,3,4}};
    Matrixf mat1 = Matrixf(m4);
    Matrixf mat2 = Matrixf(m4);
    Matrixf mat3 = Matrixf(m5);
    REQUIRE((mat1 == mat2));
    REQUIRE(!(mat3 == mat2));
}

TEST_CASE("Matrix multiplication works", "[Matrix multiplication]"){
    double m4[4][4] = {{1,2,3,4},{5,6,7,8},{9,8,7,6},{5,4,3,2}};
    double m5[4][4] = {{-2,1,2,3},{3,2,1,-1},{4,3,6,5},{1,2,7,8}};
    double res[4][4] = {{20,22,50,48},{44,54,114,108},{40,58,110,102},{16,26,46,42}};

    Matrixf mat4(m4);
    Matrixf mat5(m5);
    Matrixf matres(res);
    Matrixf matmul = mat4*mat5;
    REQUIRE((matmul==matres)); 
}

TEST_CASE("Matrix-Tuple multiplication works", "[Matrix*Tuple]"){
    double m1[4][4] = {{1,2,3,4},{2,4,4,2},{8,6,4,1},{0,0,0,1}};
    Matrixf mat1(m1);
    Tuple b = Tuple(1,2,3,1);
    Tuple res = Tuple(18,24,33,1);
    Tuple resmul = mat1*b;
    REQUIRE((res == resmul));
}

TEST_CASE("Identity matrix can be initialized", "[Identity matrix]"){
    Matrixf identity = Matrixf::ident(4);
    double res[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    Matrixf matres = Matrixf(res);

    double m4[4][4] = {{1,2,3,4},{5,6,7,8},{9,8,7,6},{5,4,3,2}};
    Matrixf mat4(m4);
    Matrixf resmul = mat4*identity;
    Matrixf resmul2 = identity*mat4;
    REQUIRE((identity == matres));
    REQUIRE((mat4 == resmul));
    REQUIRE((resmul2 == mat4));
}

TEST_CASE("Matrix transpose works", "[Matrix transpose]"){
    double m1[4][4] = {{0,9,3,0},{9,8,0,8},{1,8,5,3},{0,0,5,8}};
    Matrixf mat1(m1);
    double mt[4][4] = {{0,9,1,0},{9,8,8,0},{3,0,5,5},{0,8,3,8}};
    Matrixf matt(mt);
    Matrixf res = mat1.transpose();

    Matrixf id = Matrixf::ident(4);
    Matrixf id_t = id.transpose();
    REQUIRE((res==matt));
    REQUIRE((id_t == id));
}

TEST_CASE("4x4 Determinant works", "[Determinat 4x4]"){
    double m1[4][4] ={{-2,-8,3,5},{-3,1,7,3},{1,2,-9,6},{-6,7,7,-9}};
    Matrixf mat1(m1);
    double m2[4][4] ={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    Matrixf mat2(m2);

    double res = mat1.det();
    double res2 = mat2.det();
    REQUIRE(res==-4071);
    REQUIRE(res2==1);
}

TEST_CASE("Can tell if matrix is invertible", "[Invertibility of Matrix]"){
    double m1[4][4] ={{6,4,4,4},{5,5,7,6},{4,-9,3,-7},{9,1,7,-6}};
    double m2[4][4] ={{-4,2,-2,-3},{9,6,2,6},{0,-5,1,-5},{0,0,0,0}};
    Matrixf mat1 = Matrixf(m1);
    Matrixf mat2 = Matrixf(m2);
    double det1 = mat1.det();
    double det2 = mat2.det();
    REQUIRE(det1 != 0.0);
    REQUIRE(det2 == 0.0);
}
TEST_CASE("Can invert a 4x4 matrix correctly", "[4x4 Matrix Inversion]"){
    double m1[4][4] ={{-5,2,6,-8},{1,-5,1,8},{7,7,-6,-7},{1,-3,7,4}};
    double mres[4][4] = {{0.21805 , 0.45113 , 0.24060 , -0.04511},{-0.80827 , -1.45677 , -0.44361 , 0.52068},{-0.07895 , -0.22368 , -0.05263 , 0.19737},{-0.52256 , -0.81391 , -0.30075 , 0.30639}};
    Matrixf mat1(m1);
    Matrixf matres(mres);
    Matrixf matinv = mat1.inv();
    REQUIRE((matinv == matres));

    double m2[4][4] ={{8,-5,9,2},{7,5,6,1},{-6,0,9,6},{-3,0,-9,-4}};
    double mres2[4][4] = {{-0.15385 , -0.15385 , -0.28205 , -0.53846},{-0.07692 , 0.12308 , 0.02564 , 0.03077},{0.35897 , 0.35897 , 0.43590 , 0.92308},{-0.69231 , -0.69231 , -0.76923 , -1.92308}};
    Matrixf mat2(m2);
    Matrixf matres2(mres2);
    Matrixf matinv2 = mat2.inv();
    REQUIRE((matinv2 == matres2));

    double m3[4][4] ={{9 , 3 , 0 , 9},{-5 , -2 , -6 , -3},{-4 , 9 , 6 , 4},{-7 , 6 , 6 , 2}};
    double mres3[4][4] = {{-0.04074 , -0.07778 , 0.14444 , -0.22222},{-0.07778 , 0.03333 , 0.36667 , -0.33333},{-0.02901 , -0.14630 , -0.10926 , 0.12963},{0.17778 , 0.06667 , -0.26667 , 0.33333}};
    Matrixf mat3(m3);
    Matrixf matres3(mres3);
    Matrixf matinv3 = mat3.inv();
    REQUIRE((matinv3 == matres3));
}

TEST_CASE("A*B=C ==> A = C*B_inv","[Multiply by inverse]"){
    double a[4][4] = {{3 , -9 , 7 , 3},{3 , -8 , 2 , -9},{-4 , 4 , 4 , 1},{-6 , 5 , -1 , 1}};
    double b[4][4] = {{8 , 2 , 2 , 2},{3 , -1 , 7 , 0},{7 , 0 , 5 , 4},{6 , -2 , 0 , 5}};

    Matrixf A(a);
    Matrixf B(b);
    Matrixf C = A*B;
    Matrixf B_inv = B.inv();
    Matrixf res = C*B_inv;

    REQUIRE((A==res));
}

TEST_CASE("Translation matrix works as intended", "[Translation matrix]"){
    Matrixf transform = Matrixf::translation(5,-3,2);
    Tuple ptr = Tuple::point(-3,4,5);
    Tuple res = Tuple::point(2,1,7);
    Tuple resmul = transform * ptr;
    REQUIRE((resmul == res));

    Tuple res2 = Tuple::point(-8,7,3);
    Tuple resmul2 = transform.inv() * ptr;
    REQUIRE((resmul2 == res2));

    Tuple vec = Tuple::vector(-3,4,5);
    Tuple vecres = transform * vec;
    REQUIRE((vec == vecres));
}

TEST_CASE("Scaling matrix works as intended", "[Scaling matrix]"){
    Matrixf transform = Matrixf::scaling(2,3,4);
    Tuple ptr = Tuple::point(-4,6,8);
    Tuple res1 = Tuple::point(-8,18,32);
    Tuple ressca = transform * ptr;
    
    Tuple vec = Tuple::vector(-4,6,8);
    Tuple res2 = Tuple::vector(-8,18,32);
    Tuple ressca2 = transform * vec;
    
    Tuple res3 = Tuple::vector(-2,2,2);
    Tuple ressca3 =  transform.inv() * vec;

    // reflection
    Matrixf transform2 = Matrixf::scaling(-1,1,1);
    Tuple pt2 = Tuple::point(2,3,4);
    Tuple res4 = Tuple::point(-2,3,4);
    Tuple ressca4 = transform2 * pt2;
    
    REQUIRE((ressca == res1));
    REQUIRE((ressca2 == res2));
    REQUIRE((ressca3 == res3));
    REQUIRE((ressca4 == res4));
}

TEST_CASE("Rotation around X works (Left Handed)", "[Rotate X]"){
    Tuple pt = Tuple::point(0,1,0);
    Matrixf half_q = Matrixf::rotation_x(M_PI/4);
    Matrixf inv_half_q = half_q.inv();
    Tuple res = Tuple::point(0, sqrt(2)/2, -sqrt(2)/2);
    Tuple matres = inv_half_q * pt;
    REQUIRE((matres==res)); 
}

TEST_CASE("Rotation around Y works (Left Handed)", "[Rotate Y]"){
    Tuple pt = Tuple::point(0,0,1);
    Matrixf half_q = Matrixf::rotation_y(M_PI/4);
    Matrixf full_q = Matrixf::rotation_y(M_PI/2);
    Tuple res = Tuple::point(sqrt(2)/2, 0, sqrt(2)/2);
    Tuple matres = half_q * pt;
    Tuple matres2 = full_q * pt;
    Tuple pt2 = Tuple::point(1,0,0);
    REQUIRE((res==matres));
    REQUIRE((matres2==pt2));
    
}


TEST_CASE("Rotation around Z works (Left Handed)", "[Rotate Z]"){
    Tuple pt = Tuple::point(0,1,0);
    Matrixf half_q = Matrixf::rotation_z(M_PI/4);
    Matrixf full_q = Matrixf::rotation_z(M_PI/2);
    Tuple res = Tuple::point(-sqrt(2)/2, sqrt(2)/2, 0);
    Tuple matres = half_q * pt;
    Tuple matres2 = full_q * pt;
    Tuple pt2 = Tuple::point(-1,0,0);
    REQUIRE((res==matres));
    REQUIRE((matres2==pt2));
    
}

TEST_CASE("Shear matrix works as intended", "[Shear matrix]") {
    Matrixf sh1 = Matrixf::shearing(0,1,0,0,0,0);
    Tuple pt1 = Tuple::point(2,3,4);
    Tuple res1 = Tuple::point(6,3,4);
    Tuple matres1 = sh1 * pt1;


    Matrixf sh2 = Matrixf::shearing(0,0,1,0,0,0);
    Tuple pt2 = Tuple::point(2,3,4);
    Tuple res2 = Tuple::point(2,5,4);
    Tuple matres2 = sh2 * pt2;

    Matrixf sh3 = Matrixf::shearing(0,0,0,1,0,0);
    Tuple pt3 = Tuple::point(2,3,4);
    Tuple res3 = Tuple::point(2,7,4);
    Tuple matres3 = sh3 * pt3;

    Matrixf sh4 = Matrixf::shearing(0,0,0,0,1,0);
    Tuple pt4 = Tuple::point(2,3,4);
    Tuple res4 = Tuple::point(2,3,6);
    Tuple matres4 = sh4 * pt4;

    Matrixf sh5 = Matrixf::shearing(0,0,0,0,0,1);
    Tuple pt5 = Tuple::point(2,3,4);
    Tuple res5 = Tuple::point(2,3,7);
    Tuple matres = sh5 * pt5;

    REQUIRE((res1 == matres1));
    REQUIRE((res2 == matres2));
    REQUIRE((res3 == matres3));
    REQUIRE((res4 == matres4));
    REQUIRE((res5 == matres));
}

TEST_CASE("Transformation API calls working as intended", "[Fleunt API]"){
    Matrixf transform = Matrixf::ident(4).
                        rotate_x(M_PI/2).
                        scale(5,5,5).
                        translate(10,5,7);

    Tuple point = Tuple::point(1,0,1);
    Tuple res = Tuple::point(15,0,7);
    Tuple mulres = transform*point;
    REQUIRE((mulres == res));
}

TEST_CASE("Can instantiate a Ray and its values are correct","[Ray Initialization]"){
    Tuple origin = Tuple::point(1,2,3);
    Tuple direction = Tuple::vector(4,5,6);

    Ray r1 = Ray(origin,direction);
    REQUIRE((r1.get_direction() == direction));
    REQUIRE((r1.get_origin() == origin));
}

TEST_CASE("Can query a position at time T from a Ray","[Ray Pos at T]"){
    Tuple origin = Tuple::point(2,3,4);
    Tuple direction = Tuple::vector(1,0,0);
    Ray  r1 = Ray(origin,direction);
    Tuple p1 = Tuple::point(2,3,4);
    Tuple p2 = Tuple::point(3,3,4);
    Tuple p3 = Tuple::point(1,3,4);
    Tuple p4 = Tuple::point(4.5,3,4);

    REQUIRE((p1 == r1.pos(0)));
    REQUIRE((p2 == r1.pos(1)));
    REQUIRE((p3 == r1.pos(-1)));
    REQUIRE((p4 == r1.pos(2.5)));

}

TEST_CASE("Intersection between a ray and a sphere works", "[Ray | Sphere]"){
    Ray r1 = Ray(Tuple::point(0,0,-5),Tuple::vector(0,0,1));
    Ray r2 = Ray(Tuple::point(0,1,-5),Tuple::vector(0,0,1));
    Ray r3 = Ray(Tuple::point(0,2,-5),Tuple::vector(0,0,1));
    Ray r4 = Ray(Tuple::point(0,0,0),Tuple::vector(0,0,1));
    Ray r5 = Ray(Tuple::point(0,0,5),Tuple::vector(0,0,1));
    // No idea why it does not work
    Sphere s = Sphere();
    
    
    auto res1 = s.intersect(r1);
    auto res2 = s.intersect(r2);
    auto res3 = s.intersect(r3);
    auto res4 = s.intersect(r4);
    auto res5 = s.intersect(r5);

    REQUIRE(4.0==res1[0].t);
    REQUIRE(6.0==res1[1].t);
    REQUIRE(5.0==res2[0].t);
    REQUIRE(5.0==res2[1].t);
    REQUIRE(0==res3.count);
    REQUIRE(0==res3.count);
    REQUIRE(-1.0==res4[0].t);
    REQUIRE(1.0==res4[1].t);
    REQUIRE(-6.0==res5[0].t);
    REQUIRE(-4.0==res5[1].t);
}

TEST_CASE("Variadic length Intersections class can be initialized and accessed","[Variadic Intersections class]"){
    Sphere* s = new Sphere();
    auto i1 = Intersection(1,s);
    auto i2 = Intersection(2,s);
    std::vector<Intersection> arr;
    arr.push_back(i1);
    arr.push_back(i2);
    auto xs = Intersections(arr);
    REQUIRE(xs.count == 2);
    REQUIRE(xs[0].t == 1);
    REQUIRE(xs[1].t == 2);
}

TEST_CASE("Hits can be returned from Intersections","[Hits from intersections]"){
    Sphere* s = new Sphere();
    auto i1 = Intersection(1,s);
    auto i2 = Intersection(2,s);
    std::vector<Intersection> arr;
    arr.push_back(i1);
    arr.push_back(i2);
    auto xs = Intersections(arr);
    auto [i_res, c1] = xs.hit();
    // This should work
    REQUIRE((i_res==i1));

    auto i3 = Intersection(-1,s);
    auto i4 = Intersection(1,s);
    std::vector<Intersection> arr2;
    arr2.push_back(i3);
    arr2.push_back(i4);
    auto xs2 = Intersections(arr2);
    auto [i_res2, c2] = xs2.hit();
    REQUIRE((i_res2==i4));

    auto i5 = Intersection(-1,s);
    auto i6 = Intersection(-2,s);
    std::vector<Intersection> arr3;
    arr3.push_back(i5);
    arr3.push_back(i6);
    auto xs3 = Intersections(arr3);
    auto [i_res3, c3] = xs3.hit();
 
    REQUIRE(c3==false);

}

TEST_CASE("Hits return correct even with unordered inputs","[Hits unordered correct]"){
    Sphere* s = new Sphere();
    auto i1 = Intersection(5,s);
    auto i2 = Intersection(7,s);
    auto i3 = Intersection(-3,s);
    auto i4 = Intersection(2,s);
    std::vector<Intersection> arr;
    arr.push_back(i1);
    arr.push_back(i2);
    arr.push_back(i3);
    arr.push_back(i4);
    auto xs = Intersections(arr);
    auto [i_res,c] = xs.hit();
    REQUIRE(c==true);
    REQUIRE((i_res==i4));

}

TEST_CASE("Transforms can be applied to rays","[Rays Transformations]"){
    auto r1 = Ray(Tuple::point(1,2,3),Tuple::vector(0,1,0));
    auto m1  = Matrixf::translation(3,4,5);
    auto res1 = r1.transformed(m1);
    auto res_ori1 = Tuple::point(4,6,8);
    auto res_dir1 = Tuple::vector(0,1,0);
    // no idea why not

    REQUIRE((res1.get_direction() == res_dir1));
    REQUIRE((res1.get_origin() == res_ori1));

    auto r2 = Ray(Tuple::point(1,2,3),Tuple::vector(0,1,0));
    auto m2 = Matrixf::scaling(2,3,4);
    auto res2 = r2.transformed(m2);
    auto res_ori2 = Tuple::point(2,6,12);
    auto res_dir2 =  Tuple::vector(0,3,0);

    REQUIRE((res2.get_direction() == res_dir2));
    REQUIRE((res2.get_origin() == res_ori2));
}

TEST_CASE("Ray intersection works with transformed objects","[Ray Transformed Intersection]"){
    auto r1 = Ray(Tuple::point(0,0,-5),Tuple::vector(0,0,1));
    auto s = new Sphere();
    auto m = Matrixf::translation(5,0,0);
    s->set_transform(m);
    auto xs = s->intersect(r1);
    REQUIRE(xs.count == 0);
}

TEST_CASE("Normal on a point of a sphere can be constructred","[Normal on Sphere]"){
    auto s = Sphere();
    auto n1 = s.normal_at(Tuple::point(1,0,0));
    auto na1 = Tuple::vector(1,0,0);
    REQUIRE((n1==na1));

    auto n2 = s.normal_at(Tuple::point(0,1,0));
    auto na2 = Tuple::vector(0,1,0);
    REQUIRE((n2==na2));

    auto n3 = s.normal_at(Tuple::point(0,0,1));
    auto na3 = Tuple::vector(0,0,1);
    REQUIRE((n3==na3));

    auto n4 =  s.normal_at(Tuple::point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    auto na4 = Tuple::vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    REQUIRE((na4==n4));
    REQUIRE((na4==n4.normalize()));

    auto s2 = Sphere();
    s2.set_transform(Matrixf::translation(0,1,0));
    auto n5 = s2.normal_at(Tuple::point(0, 1.70711, -0.70711));
    auto na5 = Tuple::vector(0, 0.70711, -0.70711);

    REQUIRE((na5==n5));

    auto s3 = Sphere();
    auto m = Matrixf::ident(4).rotate_z(M_PI/5).scale(1,0.5,1); 
    s3.set_transform(m);
    auto n6 = s3.normal_at(Tuple::point(0,sqrt(2)/2,-sqrt(2)/2));
    auto na6 = Tuple::vector(0,0.97014,-0.24254);

    REQUIRE((n6==na6));
}


/*

SCENARIO( "vectors can be sized and resized", "[vector]" ) {

    GIVEN( "A vector with some items" ) {
        std::vector<int> v( 5 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );

        WHEN( "the size is increased" ) {
            v.resize( 10 );

            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "the size is reduced" ) {
            v.resize( 0 );

            THEN( "the size changes but not capacity" ) {
                REQUIRE( v.size() == 0 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
        WHEN( "more capacity is reserved" ) {
            v.reserve( 10 );

            THEN( "the capacity changes but not the size" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "less capacity is reserved" ) {
            v.reserve( 0 );

            THEN( "neither size nor capacity are changed" ) {
                REQUIRE( v.size() == 5 );
                REQUIRE( v.capacity() >= 5 );
            }
        }
    }
}
*/