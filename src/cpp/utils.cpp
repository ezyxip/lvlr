#include <app.h>
#include <fstream>

bool checkfile(std::string filepath){
    std::ifstream file(filepath);
    return file.good();
}

bool check_input_file(std::string filepath){
    return checkfile(filepath);
}

bool check_output_file(std::string filepath){
    return checkfile(filepath);
}

bool check_filter_file(std::string filepath){
    return checkfile(filepath);
}

std::vector<short> read_audio_file(std::string input_file){
    SF_INFO info;
    info.format = 0;
    SNDFILE* file = sf_open(input_file.c_str(), SFM_READ, &info);

    if(!file){
        std::cerr << "error";
        std::cerr << "Error: " << sf_strerror(file) << std::endl;
        throw std::runtime_error("Something went wrong");
    }

    int num_samples = info.frames * info.channels;

    std::vector<short> buffer(num_samples);

    sf_count_t read_count = sf_read_short(file, buffer.data(), num_samples);

    if (read_count != num_samples) {
        std::cerr << "Warning: read " << read_count << " samples, expected " << num_samples << std::endl;
    }
    return buffer;
}