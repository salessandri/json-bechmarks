#include <chrono>
#include <iostream>
#include <fstream>
#include <json_spirit.h>

using namespace std;

static uint32_t ntimes = 1000;

int main(int argc, char** argv) {
    
    if (argc < 2)
        return -1;
    
    ifstream inputfile(argv[1]);
    std::string to_parse;
    ntimes = stoi(string(argv[2]));

    inputfile.seekg(0, std::ios::end);   
    to_parse.reserve(inputfile.tellg());
    inputfile.seekg(0, std::ios::beg);

    to_parse.assign((std::istreambuf_iterator<char>(inputfile)),
                     std::istreambuf_iterator<char>());
    
    json_spirit::mValue parsed_object;
    bool result = json_spirit::read(to_parse, parsed_object);

    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
    for (int i = 0; i < ntimes; ++i) {
        std::string output = json_spirit::write(parsed_object);
    }
    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
    chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(
                               end_time - start_time);
    cout << "[+] Finished successfully with an average of: " << (us.count() / ntimes) << " us\n";
}
