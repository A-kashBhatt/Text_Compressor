# Huffman Coding Project

## Overview
This project implements Huffman Coding for file compression and decompression. It includes a Huffman tree builder and functions to encode and decode files efficiently.

## Prerequisites
- C++ compiler (e.g., g++)
- Standard Template Library (STL)

## Files
- `huffmanModule.hpp`: Header file containing the class definition and function prototypes.
- `huffman.cpp`: Implementation file containing the functions to build the Huffman tree, encode, and decode files.
- `compress.cpp`: Main program to compress a file.
- `decompress.cpp`: Main program to decompress a file.
- `compare.cpp`: Utility program to compare two files.


## Compilation
To compile the programs, use the following commands:

```
g++ compress.cpp huffman.cpp -o compress
g++ decompress.cpp huffman.cpp -o decompress
```

<br><br>

# Usage

## Compression

To compress a file, run the following command:

```
./compress <inputFile> <compressedFile>
```

<br>

## Decompression

To decompress a file, run the following command:

```
./decompress <compressedFile> <outputFile>
```


