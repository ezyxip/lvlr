#include <iostream>
#include <CLI/CLI.hpp>
#include <app.h>
#include <sndfile.h>

void addOptions(std::map<std::string, std::string> &keys, CLI::App &app){
    app.add_option("--file-input", [&](std::vector<std::string> strs) -> bool {
        bool res = true;
        keys["finput"] = strs[0];
        return check_input_file(strs[0]);
    }, "Input audiofile path")->required();

    app.add_option("--file-output", [&](std::vector<std::string> strs) -> bool {
        bool res = true;
        keys["foutput"] = strs[0];
        return check_output_file(strs[0]);
    }, "Output audiofile path");

    app.add_option("--filter", [&](std::vector<std::string> strs) -> bool {
        bool res = true;
        keys["ffilter"] = strs[0];
        return check_filter_file(strs[0]);
    }, "Filter .yaml file path");
}

int main(int argc, char** argv){
    CLI::App app("CLI stream equalizer", "lvlr");

    //finput - файл с входной информацией
    //foutput - выходной файл
    //ffilter - .yaml файл с фильтром
    std::map<std::string, std::string> keys;

    addOptions(keys, app);

    CLI11_PARSE(app, argc, argv);
    
    std::vector<short> audio = read_audio_file(keys["finput"]);
}