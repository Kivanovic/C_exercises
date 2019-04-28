#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <stdio.h>


//-------------------------------------------
static inline void RightTrim(std::string& line)
{
    line.erase(line.begin(),
        std::find_if(line.begin(),
        line.end(), [](char ch) {
        return !isspace(ch);
    }));
}


//-------------------------------------------
static bool SortFile(const char* filepath)
{
    std::ifstream inFile(filepath);
    if (!inFile.is_open())
        return false;

    std::multiset<std::string> lines;
    std::string line;

    while (std::getline(inFile, line)) {
        RightTrim(line);
        if (!line.empty()) {
            lines.insert(line);
        }
    }

    inFile.close();
    std::ofstream outFile(filepath);
    if (!outFile.is_open())
        return false;

    for (const std::string& l : lines)
        outFile << l << "\n\r";

    return true;
}


//-------------------------------------------
int main(int argc, char** argv)
{
    if (argc != 2) {
        puts("Invalid input!");
        return -1;
    }

    if (!SortFile(argv[1])) {
        puts("Failed to parse file!");
        return -1;
    }

    puts("File sorted successfuly!");
    getchar();
    return 0;
}
