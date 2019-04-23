#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


//===========================================================
static void ShowStats(long lines, long letters, long words)
{
    printf("---------------------------------------\n");
    printf("| Words: %ld\n", words);
    printf("| Letters: %ld\n", letters);
    printf("| Lines: %ld\n", lines);
    printf("---------------------------------------\n");
    fflush(stdin);
    getchar();
}


//===========================================================
static long Words(std::string& line)
{
    long count = 0;
    auto* ch = strtok(const_cast<char*>(line.c_str()), " ");
    while (ch != nullptr) {
        ch = strtok(nullptr, " ");
        ++count; }
    return count;
}


//===========================================================
static void Parse(const char* filepath)
{
    long words = 0;
    long letters = 0;
    long lines = 0;

    std::string buffer;
    buffer.reserve(0xfff);

    std::ifstream file(filepath);
    if (!file.is_open()) {
        printf("Failed to open '%s'", filepath);
        return;
    }

    while (std::getline(file, buffer))
    {
        lines += 1;

        letters += std::count_if(buffer.begin(),
            buffer.end(), [](char c) {
            return !isspace(c);
        });

        words += Words(buffer);
    }

    ShowStats(lines, letters, words);
}


//===========================================================
int main(int argc, char** argv)
{
    if (argc != 2) {
        puts("Invalid arguments!");
        getchar();
        return -1;
    }

    Parse(argv[1]);

    return 0;
}
