#ifndef APP_H
#define APP_H

#include <string>
#include <sndfile.h>
#include <iostream>
#include <vector>


bool check_input_file(std::string filepath);
bool check_output_file(std::string filepath);
bool check_filter_file(std::string filepath);

std::vector<short> read_audio_file(std::string input_file);

#endif