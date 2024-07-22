#include <iostream>
#include <app.h>
#include <thread>

using namespace lvlr;

int main(int argc, char **argv)
{
    CLI::App app("CLI stream equalizer", "lvlr");

    // finput - файл с входной информацией
    // foutput - выходной файл
    // ffilter - .yaml файл с фильтром
    std::map<std::string, std::string> keys;

    conf_options(keys, app);

    CLI11_PARSE(app, argc, argv);

    AudioData audio = read_audio_file(keys["finput"]);

    PaError err = Pa_Initialize();
    if (err != paNoError)
        printf("PortAudio error 1: %s\n", Pa_GetErrorText(err));

    PaStream *stream;
    err = Pa_OpenDefaultStream(
        &stream,
        0,
        audio.channels,
        paFloat32,
        audio.sampleRate,
        paFramesPerBufferUnspecified,
        pa_stream_callback,
        &audio);

    if (err != paNoError)
        printf("PortAudio error 2: %s\n", Pa_GetErrorText(err));

    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    while (Pa_IsStreamActive(stream) == 1)
    {
        Pa_Sleep(100);
    }

    // Остановка и закрытие аудиопотока
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}