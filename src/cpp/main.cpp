#include <iostream>
#include <memory>
#include <chrono>
#include <app.h>
#include <thread>
#include <ConToDefProcess.h>
#include <DSPFilter.h>

using namespace std::chrono_literals;


class FakeFilter: public lvlr::Filter{
public: 
    float process(float sample) override{
        return sample;
    }
};

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
    
    std::shared_ptr<FakeFilter> filter {new FakeFilter()};

    lvlr::ConToDefProcess process(std::static_pointer_cast<lvlr::Filter>(filter), audio);

    process.run();
    std::cout << "1235";
    Pa_Sleep(3000);

    std::cout << "!!!";
    // process.wait();
    // std::this_thread::sleep_for(2000ms);
    

    return 0;
}