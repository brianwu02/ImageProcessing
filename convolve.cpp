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

int main(int argc, char** argv) {
    
    ifstream myReadFile;

    int i, total, arg1;
    unsigned char *in;
    char *tmp;
    imageP I1, I2;
    std::string str;
    std::string filename = argv[1];

    if (filename.empty()) {
        cerr << "you need to enter a filename" << endl;
        exit(1);
    }

    cout << filename << endl;





    std::ifstream t("file1.AF");

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    
    for (int i = 0; i<str.length(); i++) {
        cout << str[i];
    }




    return 0;


}
