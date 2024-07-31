#ifndef HUFFMAN_HEADER
#define HUFFMAN_HEADER

#include <bits/stdc++.h>
using namespace std;

// Definition of Huffman Tree Node
struct Node
{
    char data;
    unsigned freq;
    string code;
    Node *left, *right;

    Node() : data('\0'), freq(0), left(nullptr), right(nullptr) {}
};

class huffman
{
private:
    vector<Node *> nodeArray;
    fstream inputFile, outputFile;
    string inputFileName, outputFileName;
    Node *root;

    class CompareNodes
    {
    public:
        bool operator()(Node *l, Node *r)
        {
            return l->freq > r->freq;
        }
    };

    priority_queue<Node *, vector<Node *>, CompareNodes> minHeap;

    // Initialize a vector of tree nodes for each character ASCII value, setting frequency to 0
    void initializeArray();

    // Traverse the Huffman tree to generate codes for each character
    void encodeTraversal(Node *, const string &);

    // Convert binary string to its decimal equivalent
    int binaryToDecimal(const string &);

    // Convert a decimal number to its binary string equivalent
    string decimalToBinary(int);

    // Rebuild the Huffman tree during file decoding
    void constructTree(char, const string &);

    // Create a min heap of nodes based on character frequency in the input file
    void generateMinHeap();

    // Build the Huffman tree
    void generateTree();

    // Generate Huffman codes
    void generateCodes();

    // Save the encoded file
    void writeEncodedFile();

    // Save the decoded file to retrieve the original content
    void writeDecodedFile();

    // Read the file to reconstruct the Huffman tree
    void decodeTree();

public:
    // Constructor
    huffman(string inputFileName, string outputFileName)
        : inputFileName(inputFileName), outputFileName(outputFileName), root(nullptr)
    {
        initializeArray();
    }

    // Compress the input file
    void compress();

    // Decompress the input file
    void decompress();
};

#endif
