#include <iostream>
#include <CLI/CLI.hpp>

void addOptions(std::map<std::string, std::string> &keys, CLI::App &app){
    app.add_option("--file-input", [&](std::vector<std::string> strs) -> bool {
        bool res = true;
        keys["finput"] = strs[0];
        return true;
    }, "Input file path");

    app.add_option("--file-output", [&](std::vector<std::string> strs) -> bool {
        bool res = true;
        keys["foutput"] = strs[0];
        return res;
    }, "Output file path");
}

int main(int argc, char** argv){
    CLI::App app("CLI stream equalizer", "lvlr");

    //finput - файл с входной информацией
    //foutput - выходной файл
    std::map<std::string, std::string> keys;

    addOptions(keys, app);

    CLI11_PARSE(app, argc, argv);
    
    std::cout << "finput: " << keys["finput"] << "\n";
    std::cout << "foutput: " << keys["foutput"] << "\n";

    
}