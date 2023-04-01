#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>

using namespace std;

vector<int> tokenization (string text)
{
    char *ptr;
    vector<int> tokens;
    char *dup = strdup(text.c_str());
    ptr = strtok(dup, " ");

    do
    {
        tokens.push_back(atoi(ptr));
        ptr = strtok(NULL, " ");
    }
    while(ptr != NULL);

    return tokens;
}
