#include <iostream>
#include "../include/geometry.hpp"
#include "../include/canvas.hpp"
#include <exception>

int main(){
    auto canvas_sz = 200;
    auto wall_sz = 7.0;
    auto wall_z = 10;
    auto ray_orig = Tuple::point(0,0,-5);
    auto pixel_sz = wall_sz / canvas_sz;
    auto CANVAS = Canvas(canvas_sz,canvas_sz);
    auto color = Tuple::color(1,0,0);
    auto shape = Sphere();
    auto half = wall_sz / 2;
    
    std::cout<< "Set up is complete\n";
    for(int y=0; y<canvas_sz;y++){
        auto world_y = half - pixel_sz*y;
        for(int x=0;x<canvas_sz;x++){
            auto world_x = -half + pixel_sz*x;
            auto pos = Tuple::point(world_x,world_y,wall_z);
            auto r = Ray(ray_orig,pos.normalize());
            auto xs = shape.intersect(r);
            if(xs.count != 0){
                CANVAS[x][y] = color;
            }  
        }
    }
    CANVAS.to_ppm("trial1.ppm");
    std::cout<< "All done!\n";
    std::cout<< "Yahoo\n"; 
    std::cin.get(); 

    return 0;
}