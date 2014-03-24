/**
 * Image Processing
 * Brian Wu
 * Convolve
 * Usage: convolve in kernel out
 */
#include "IP.h"
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

std::string readKernel(char*);

int main(int argc, char** argv) {
    std::string kernel;
    std::string str;

    kernel = readKernel(argv[1]);

    for (int i = 0; i<kernel.length(); i++) {
        cout << kernel[i];
    }
    return 0;
}

std:: string readKernel(char *file) {
    std::string filename = file;
    std::string str;
    std::ifstream t(filename);

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

    return str;


}
