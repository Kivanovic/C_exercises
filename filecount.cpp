#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string_view>
#include <algorithm>
using namespace std;


/*--------------------------------------------------------*/
namespace globals {
    static map<string, int> cnt_words;
}


/*--------------------------------------------------------*/
static bool is_word(const string& word) {
    if (word.size() < 2) return false;
    for (char c : word)
        if (!isalpha(c))
            return false;
    return true;
}


/*--------------------------------------------------------*/
static auto& format_word(string& word) {
    if (word.empty()) return word;
    word[0] = static_cast<char>(toupper(word[0]));
    for_each(word.begin()+1, word.end(), [](char c) {
        return static_cast<char>(toupper(c));});
    return word;
}


/*--------------------------------------------------------*/
static auto split_line(const string& str) {
    vector<string> words;
    stringstream ss(str);
    string word;
    while (getline(ss, word, ' '))
        words.emplace_back(format_word(word));
    return words;
}


/*--------------------------------------------------------*/
static void parse_file(string_view path) {
    ifstream in(path.data());
    if (!in.is_open()) {
        printf("Failed to open file \'%s\'\n", path.data());
        return;}

    string line;
    while (in) {
        getline(in, line);
        auto words = split_line(line);
        for (string& w : words)
            if (is_word(w))
                globals::cnt_words[w]++;
    }
}


/*--------------------------------------------------------*/
int main(int argc, char** argv) {
    parse_file("C:\\Users\\User\\Desktop\\Programmig\\C_Cpp_Lessons\\main.cpp");
    return 0;
}
