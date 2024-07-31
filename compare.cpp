#include <bits/stdc++.h>
using namespace std;
string getString(string fileName)
{
    char id;
    fstream f;
    f.open(fileName, ios::in);
    f.get(id);
    string s = "";
    s += id;
    while (!f.eof())
    {
        f.get(id);
        s += id;
    }
    f.close();
    return s;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Failed to detect Files";
        exit(1);
    }
    string input = getString(argv[1]);
    string output = getString(argv[2]);
    if (input == output)
        cout << "Strings Matched" << endl;
    else
        cout << "Strings did not match" << endl;
}