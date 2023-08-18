#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <mtrp/base64.hpp>

using namespace std;
using namespace mtrp;

size_t g_BlobSize;
size_t g_NumRepetitions;

void display_help()
{
    cout << "Usage: benchmark [OPTION]..." << endl;
    cout << "  bs=BYTES (128, 128B, 128K, 128M, 128G)" << endl;
    cout << "  rp=REPETITIONS (Number of repetitions)" << endl;
    cout << "  --help (Display this help)" << endl;
}

void exit_and_display_help(int code) noexcept
{
    display_help();
    exit(code);
}

void parse_bs(string value)
{
    if (value.empty())
        exit_and_display_help(1);

    size_t multiplier = 0;
    switch (value.back())
    {
        case 'B': multiplier = 1; break;
        case 'K': multiplier = 1024; break;
        case 'M': multiplier = 1024*1024; break;
        case 'G': multiplier = 1024*1024*1024; break;
    }
    if (multiplier != 0)
         value.pop_back();
    else multiplier = 1;
    
    try {g_BlobSize = stoi(value) * multiplier;}
    catch(...) {exit_and_display_help(1);}
}

void parse_rp(string value)
{
    try {g_NumRepetitions = stoi(value);}
    catch(...) {exit_and_display_help(1);}
}

pair<string,string> split_by_equal_delim(string const& arg)
{
    auto delim = arg.find('=');
    if (delim == arg.npos)
        return {};
    
    return {arg.substr(0, delim), arg.substr(delim+1, arg.npos)};
}

void parse_options(int argc, char **argv)
{
    if (argc <= 1)
        exit_and_display_help(1);
    
    string args[argc - 1];
    for (int i = 1; i < argc; i++)
        args[i - 1] = argv[i];
    
    for (auto const& arg : args)
    {
        if (arg == "--help")
            exit_and_display_help(0);

        auto operand = split_by_equal_delim(arg);

        if (operand.first == "bs")
            parse_bs(operand.second);
        else if (operand.first == "rp")
            parse_rp(operand.second);
        else
            exit_and_display_help(1);
    }
}

void run_benchmark()
{
    vector<uint8_t> decoded_mem;
    vector<uint8_t> encoded_mem;

    cout << "Memory allocation... " << flush;
    try {
        decoded_mem.resize(g_BlobSize);
        encoded_mem.resize(b64::detail::calc_enc(nullptr, (void*)g_BlobSize, b64::pad::FORBIDDEN));
    } catch (bad_alloc) {
        cout << "FAIL" << endl;
        exit(2);
    }
    cout << "OK" << endl;

    void * const decoded_beg = &*decoded_mem.begin();
    void * const decoded_end = &*decoded_mem.end();
    void * const encoded_beg = &*encoded_mem.begin();
    void * const encoded_end = &*encoded_mem.end();

    cout << "Data filling (please wait)... " << flush;
    srand(0);
    generate(decoded_mem.begin(), decoded_mem.end(), rand);
    cout << "OK" << endl;

    double encoder_elapsed;
    double decoder_elapsed;

    cout << "Benchmark execution (please wait)... " << flush;

    for (size_t i = 0; i < g_NumRepetitions; i++) {
        auto t1 = chrono::high_resolution_clock::now();
        b64::detail::c_api::mtrp_b64_encode(decoded_beg, decoded_end, encoded_beg, int(b64::pad::FORBIDDEN));
        auto t2 = chrono::high_resolution_clock::now();
        encoder_elapsed += chrono::duration<double>(t2 - t1).count();
    }

    for (size_t i = 0; i < g_NumRepetitions; i++) {
        auto t1 = chrono::high_resolution_clock::now();
        b64::detail::c_api::mtrp_b64_decode(encoded_beg, encoded_end, decoded_beg, int(b64::pad::FORBIDDEN));
        auto t2 = chrono::high_resolution_clock::now();
        decoder_elapsed += chrono::duration<double>(t2 - t1).count();
    }

    cout << "OK" << endl;

    double encoder_avg_time = encoder_elapsed / double(g_NumRepetitions);
    double decoder_avg_time = decoder_elapsed / double(g_NumRepetitions);
    double encoder_avg_speed = double(decoded_mem.size()) / encoder_avg_time;
    double decoder_avg_speed = double(encoded_mem.size()) / decoder_avg_time;

    encoder_avg_speed /= (1024*1024*1024);
    decoder_avg_speed /= (1024*1024*1024);

    cout << "[Encoder] Average time is ~" << encoder_avg_time << " seconds (~" << encoder_avg_speed << " GiB per second)" << endl;
    cout << "[Decoder] Average time is ~" << decoder_avg_time << " seconds (~" << decoder_avg_speed << " GiB per second)" << endl;
}

int main(int argc, char **argv)
{
    parse_options(argc, argv);
    cout << "Selected preset: [BlobSize = " << g_BlobSize << " bytes, Repetitions = " << g_NumRepetitions << "]" << endl;
    run_benchmark();
}
