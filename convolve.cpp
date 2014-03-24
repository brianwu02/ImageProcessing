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

std::string readKernelFile(char*);
unsigned char initKernel(std::string);

int main(int argc, char** argv) {
    std::string kernelString;
    std::string str;

    kernelString = readKernelFile(argv[1]);

    for (int i = 0; i<kernelString.length(); i++) {
        cout << kernelString[i];
    }
    return 0;


}

unsigned char initKernel(std::string str) {

    return 0;
}

typedef struct {
    int width;
    int height;
    float *kernel;
}kernelS, *kernelP;

std:: string readKernelFile(char *file) {
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

