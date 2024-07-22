#include <app.h>
#include <fstream>

bool check_input_file(std::string filepath){
    return checkfile(filepath);
}

bool check_output_file(std::string filepath){
    return checkfile(filepath);
}

bool check_filter_file(std::string filepath){
    return checkfile(filepath);
}

bool checkfile(std::string filepath){
    std::ifstream file(filepath);
    return file.good();
}