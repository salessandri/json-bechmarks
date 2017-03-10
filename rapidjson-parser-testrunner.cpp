#include <chrono>
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>

using namespace std;

static const uint32_t ntimes = 1000;

int main(int argc, char** argv) { 
    if (argc < 2)
        return -1;
    
    ifstream inputfile(argv[1]);
    std::string to_parse;

    inputfile.seekg(0, std::ios::end);   
    to_parse.reserve(inputfile.tellg());
    inputfile.seekg(0, std::ios::beg);

    to_parse.assign((std::istreambuf_iterator<char>(inputfile)),
                     std::istreambuf_iterator<char>());
    
    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
    for (unsigned int i = 0; i < ntimes; ++i) {
        rapidjson::Document doc;
        rapidjson::ParseResult result = doc.Parse(to_parse.c_str());
    }
    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
    chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "[+] Finished successfully with an average of: " << (us.count() / ntimes) << " us\n";
}
