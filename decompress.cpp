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
    cout << "Decompressing.............." << endl;
    huffman huffmanDecompressor(argv[1], argv[2]);
    huffmanDecompressor.decompress();
    cout << "Decompressed successfully" << endl;

    return 0;
}
