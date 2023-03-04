#include <algorithm>
#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
namespace fs = std::filesystem;
void readingBMP(string filename);
int main(int argc, char* argv[]) {
    string file;
    for (auto path : fs::directory_iterator(".")) {
        readingBMP(path.path().c_str());
    }
    // ifstream bmpfile(file, ios_base::binary);
    // if (bmpfile) {
    //     vector<uint8_t> bmpdata{istreambuf_iterator<char>(bmpfile),std::istreambuf_iterator<char>()};
    //     int pos=53;
    //     for (int height = 0; height < 16; height++) {
    //         uint16_t tmp = 0;
    //         for (int x = 0; x < 16; x++) {
    //             uint8_t raw;
    //             int sum = 0;
    //             for (int rgb = 0; rgb < 3; rgb++) {
    //                 raw = bmpdata.at(54+(height*48 + 3*x));
    //                 sum += raw;
    //             }
    //             sum ? tmp : tmp += 0b1000000000000000 >> x;
    //         }
    //         pattern[15 - height] = tmp;
    //     }
    //     for (auto a : pattern) {
    //         bitset<16> b(a);
    //         cout << b << endl;
    //     }
    // } else
    //     cout << "couldn't open file \n";
}
void readingBMP(string filename) {
    cout << filename << endl;
    uint16_t pattern[16] = {
        0,
    };
    ifstream bmpfile(filename, ios_base::binary);
    if (bmpfile) {
        vector<uint8_t> bmpdata{istreambuf_iterator<char>(bmpfile), std::istreambuf_iterator<char>()};
        int pos = 53;
        for (int height = 0; height < 16; height++) {
            uint16_t tmp = 0;
            for (int x = 0; x < 16; x++) {
                uint8_t raw;
                int sum = 0;
                for (int rgb = 0; rgb < 3; rgb++) {
                    raw = bmpdata.at(54 + (height * 48 + 3 * x));
                    sum += raw;
                }
                sum ? tmp : tmp += 0b1000000000000000 >> x;
            }
            pattern[15 - height] = tmp;
        }
        for (auto a : pattern) {
            bitset<16> b(a);
            cout << b << endl;
        }
    } else
        cout << "couldn't open file \n";
}