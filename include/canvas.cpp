#include "canvas.hpp"
#define PPM_LINE 70

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

    // to count the number of chars written already
    int ctr = 0;
    for(int i=0; i<this->get_height();i++){
        for(int j=0; j<this->get_width(); j++){
            std::stringstream ss;
            Tuple tmp = IMG[i][j];
            std::string r = std::to_string((int)std::round(this->clamp(tmp.x*255.0,0.0,255.0)));
            std::string g = std::to_string((int)std::round(this->clamp(tmp.y*255.0,0.0,255.0)));
            std::string b = std::to_string((int)std::round(this->clamp(tmp.z*255.0,0.0,255.0)));
            ss << r << " " << g << " " << b;
            
            
            // now handle the ending
            if(ctr + ss.str().length() + 1 >= PPM_LINE){ 
                ppm_file << "\n" << ss.str() << " ";
                ctr = ss.str().length() + 1 ;
            }else if(j == this->get_width()-1){
                ppm_file << ss.str() << "\n";
                ctr = 0;
            } 
            // Can just write it
            else {
                ppm_file << ss.str() << " ";
                ctr += ss.str().length() + 1;
            }
        }
    }

    ppm_file.close();
}