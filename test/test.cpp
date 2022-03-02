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