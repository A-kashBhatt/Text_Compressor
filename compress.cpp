#include <iostream>
#include "huffmanModule.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Failed to detect Files" << endl;
        return 1;
    }

    cout << "Compressing..................." << endl;
    huffman huffmanCompressor(argv[1], argv[2]);
    huffmanCompressor.compress();
    cout << "Compressed successfully" << endl;

    return 0;
}
