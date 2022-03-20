#include <iostream>
#include "../include/geometry.hpp"
#include "../include/canvas.hpp"
#include <exception>

int main(){
    auto canvas_sz = 500;
    auto wall_sz = 7.0;
    auto wall_z = 10;
    auto ray_orig = Tuple::point(0,0,-5);
    auto pixel_sz = wall_sz / canvas_sz;
    auto CANVAS = Canvas(canvas_sz,canvas_sz);
    auto color = Tuple::color(1,0,0);
    auto shape = Sphere();

    shape.m = Material();
    shape.m.color = Tuple::color(1,0.2,1);
    auto half = wall_sz / 2;

    // light stuff
    auto light_pos = Tuple::point(-10,10,-10);
    auto light_col = Tuple::color(1,1,1);
    auto light = PointLight(light_pos,light_col);
    
    std::cout<< "Set up is complete\n";
    for(int y=0; y<canvas_sz;y++){
        auto world_y = half - pixel_sz*y;
        for(int x=0;x<canvas_sz;x++){
            auto world_x = -half + pixel_sz*x;
            auto pos = Tuple::point(world_x,world_y,wall_z);
            auto r = Ray(ray_orig,(pos-ray_orig).normalize());
            auto xs = shape.intersect(r);
            if(xs.count != 0){
                auto hit_int = xs.hit().first;
                auto hit_pt = r.pos(hit_int.t);
                auto hit_obj = static_cast<Sphere *>(hit_int.object);
                auto hit_norm = hit_obj->normal_at(hit_pt);
                auto eye = -r.get_direction();
                color = lighting(hit_obj->m, light, hit_pt, eye, hit_norm);
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