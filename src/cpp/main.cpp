#include <iostream>
#include <memory>
#include <chrono>
#include <app.h>
#include <thread>
#include <ConToDefProcess.h>
#include <DSPFilter.h>
#include <Biquad.h>

int main(int argc, char **argv)
{
    CLI::App app("CLI stream equalizer", "lvlr");

    // finput - файл с входной информацией
    // foutput - выходной файл
    // ffilter - .yaml файл с фильтром
    std::map<std::string, std::string> keys;

    lvlr::conf_options(keys, app);

    CLI11_PARSE(app, argc, argv);

    auto audio = std::make_shared<lvlr::AudioContainer>(lvlr::read_audio_file(keys["finput"]));
    
    std::shared_ptr<Biquad> filter {new Biquad(
        bq_type_highshelf, 1000, 1, std::stod(keys["db"])
    )};

    lvlr::ConToDefProcess process(std::static_pointer_cast<lvlr::Filter>(filter), audio);

    process.run();

    process.wait();
    

    return 0;
}