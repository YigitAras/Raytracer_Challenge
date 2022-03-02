#include "canvas.hpp"

Canvas::Canvas(int W,int H):IMG(H,std::vector<Tuple>(W)),width(W),height(H){}

std::vector<Tuple>& Canvas::operator[](int ind){
    return this->IMG[ind];
}

double Canvas::clamp(double num, double lo, double hi){
    num = (num < lo) ? lo : num;
    num = (num > hi) ? hi : num;
    return num;
}

void Canvas::dummy_to_ppm(std::string file){
    std::ofstream ppm_file(file);
    ppm_file << "P3\n";  // PPM file format
    ppm_file << this->width << " " << this->height << "\n"; // IMAGE dimensions
    ppm_file << "255\n";  // Max color value
    
    // Close the file after done
    ppm_file.close();
}

void Canvas::to_ppm(std::string file){
    std::ofstream ppm_file(file);

    ppm_file << "P3\n";  // PPM file format
    ppm_file << this->width << " " << this->height << "\n"; // IMAGE dimensions
    ppm_file << "255\n";  // Max color value


    for(int i=0; i<this->get_height();i++){
        for(int j=0; j<this->get_width(); j++){
            Tuple tmp = IMG[i][j];
            int r = std::round(this->clamp(tmp.x*255.0,0.0,255.0));
            int g = std::round(this->clamp(tmp.y*255.0,0.0,255.0));
            int b = std::round(this->clamp(tmp.z*255.0,0.0,255.0));
            if(j == this->get_width()-1){
                ppm_file << r << " " << g << " " << b << "\n";
            }else {
                ppm_file << r << " " << g << " " << b << " ";
            }
             
        }
    }

    ppm_file.close();
}