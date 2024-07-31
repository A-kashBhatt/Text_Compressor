#include "huffmanModule.hpp"

void huffman::initializeArray()
{
    for (int i = 0; i < 128; ++i)
    {
        nodeArray.emplace_back(new Node());
        nodeArray[i]->data = static_cast<char>(i);
        nodeArray[i]->freq = 0;
    }
}

void huffman::encodeTraversal(Node *node, const std::string &str)
{
    if (!node->left && !node->right)
    {
        node->code = str;
        return;
    }
    encodeTraversal(node->left, str + '0');
    encodeTraversal(node->right, str + '1');
}

int huffman::binaryToDecimal(const std::string &binaryStr)
{
    int decimal = 0;
    for (char c : binaryStr)
    {
        decimal = (decimal << 1) + (c - '0');
    }
    return decimal;
}

std::string huffman::decimalToBinary(int number)
{
    std::string binaryStr, reversedStr;
    while (number > 0)
    {
        binaryStr += (number % 2) + '0';
        number /= 2;
    }
    reversedStr.append(8 - binaryStr.length(), '0');
    for (auto it = binaryStr.rbegin(); it != binaryStr.rend(); ++it)
    {
        reversedStr += *it;
    }
    return reversedStr;
}

void huffman::constructTree(char character, const std::string &path)
{
    Node *current = root;
    for (char c : path)
    {
        if (c == '0')
        {
            if (!current->left)
            {
                current->left = new Node();
            }
            current = current->left;
        }
        else
        {
            if (!current->right)
            {
                current->right = new Node();
            }
            current = current->right;
        }
    }
    current->data = character;
}

void huffman::generateMinHeap()
{
    char ch;
    inputFile.open(inputFileName, std::ios::in);
    inputFile.get(ch);
    while (inputFile)
    {
        nodeArray[static_cast<unsigned char>(ch)]->freq++;
        inputFile.get(ch);
    }
    inputFile.close();
    for (const auto &node : nodeArray)
    {
        if (node->freq > 0)
        {
            minHeap.push(node);
        }
    }
}

void huffman::generateTree()
{
    Node *left, *right;
    std::priority_queue<Node *, std::vector<Node *>, CompareNodes> tempPQ(minHeap);
    while (tempPQ.size() > 1)
    {
        left = tempPQ.top();
        tempPQ.pop();
        right = tempPQ.top();
        tempPQ.pop();
        root = new Node();
        root->freq = left->freq + right->freq;
        root->left = left;
        root->right = right;
        tempPQ.push(root);
    }
}

void huffman::generateCodes()
{
    encodeTraversal(root, "");
}

void huffman::writeEncodedFile()
{
    inputFile.open(inputFileName, std::ios::in);
    outputFile.open(outputFileName, std::ios::out | std::ios::binary);
    std::string inputStr, bitString;
    char ch;

    inputStr += static_cast<char>(minHeap.size());
    std::priority_queue<Node *, std::vector<Node *>, CompareNodes> tempPQ(minHeap);
    while (!tempPQ.empty())
    {
        Node *node = tempPQ.top();
        inputStr += node->data;
        bitString.assign(127 - node->code.length(), '0');
        bitString += '1' + node->code;
        inputStr += static_cast<char>(binaryToDecimal(bitString.substr(0, 8)));
        for (int i = 1; i < 16; ++i)
        {
            bitString = bitString.substr(8);
            inputStr += static_cast<char>(binaryToDecimal(bitString.substr(0, 8)));
        }
        tempPQ.pop();
    }
    bitString.clear();

    inputFile.get(ch);
    while (inputFile)
    {
        bitString += nodeArray[static_cast<unsigned char>(ch)]->code;
        while (bitString.length() >= 8)
        {
            inputStr += static_cast<char>(binaryToDecimal(bitString.substr(0, 8)));
            bitString = bitString.substr(8);
        }
        inputFile.get(ch);
    }

    int paddingCount = 8 - bitString.length();
    if (bitString.length() < 8)
    {
        bitString.append(paddingCount, '0');
    }
    inputStr += static_cast<char>(binaryToDecimal(bitString));
    inputStr += static_cast<char>(paddingCount);

    outputFile.write(inputStr.c_str(), inputStr.size());
    inputFile.close();
    outputFile.close();
}

void huffman::writeDecodedFile()
{
    inputFile.open(inputFileName, std::ios::in | std::ios::binary);
    outputFile.open(outputFileName, std::ios::out);
    unsigned char heapSize;
    inputFile.read(reinterpret_cast<char *>(&heapSize), 1);

    inputFile.seekg(-1, std::ios::end);
    char paddingCount;
    inputFile.read(&paddingCount, 1);
    inputFile.seekg(1 + 17 * heapSize, std::ios::beg);

    std::vector<unsigned char> encodedText;
    unsigned char byte;
    inputFile.read(reinterpret_cast<char *>(&byte), 1);
    while (inputFile)
    {
        encodedText.push_back(byte);
        inputFile.read(reinterpret_cast<char *>(&byte), 1);
    }

    Node *current = root;
    std::string bitPath;
    for (size_t i = 0; i < encodedText.size() - 1; ++i)
    {
        bitPath = decimalToBinary(encodedText[i]);
        if (i == encodedText.size() - 2)
        {
            bitPath = bitPath.substr(0, 8 - paddingCount);
        }
        for (char c : bitPath)
        {
            current = (c == '0') ? current->left : current->right;
            if (!current->left && !current->right)
            {
                outputFile.put(current->data);
                current = root;
            }
        }
    }
    inputFile.close();
    outputFile.close();
}

void huffman::decodeTree()
{
    inputFile.open(inputFileName, std::ios::in | std::ios::binary);
    unsigned char heapSize;
    inputFile.read(reinterpret_cast<char *>(&heapSize), 1);
    root = new Node();
    for (int i = 0; i < heapSize; ++i)
    {
        char character;
        unsigned char codeSegments[16];
        inputFile.read(&character, 1);
        inputFile.read(reinterpret_cast<char *>(codeSegments), 16);
        std::string codeStr;
        for (int j = 0; j < 16; ++j)
        {
            codeStr += decimalToBinary(codeSegments[j]);
        }
        int idx = 0;
        while (codeStr[idx] == '0')
        {
            ++idx;
        }
        codeStr = codeStr.substr(idx + 1);
        constructTree(character, codeStr);
    }
    inputFile.close();
}

void huffman::compress()
{
    generateMinHeap();
    generateTree();
    generateCodes();
    writeEncodedFile();
}

void huffman::decompress()
{
    decodeTree();
    writeDecodedFile();
}
