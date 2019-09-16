#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <string_view>
#include <algorithm>
using namespace std;


/*--------------------------------------------------------*/
namespace globals {
    static map<string, int> cnt_words;
    static vector<pair<int, string>> srt_words;
    static string filepath;
}


/*--------------------------------------------------------*/
static string get_filename(string& path) {
    string fname;
    auto delim = path.end()-1;
    for (; *delim != '\\' || *delim != '/'; --delim);
    copy(delim, path.end(), fname);
    return fname;
}


/*--------------------------------------------------------*/
template <typename T, typename S>
static auto& sort_stats(T& words, S& srt_words) {
    for (auto&[k, v] : words)
        srt_words.emplace_back(v, std::move(k));
    sort(srt_words.begin(), srt_words.end(), [](auto& a, auto& b) {
        return (a.first > b.first);
    });
    return srt_words;
}

/*--------------------------------------------------------*/
template <typename T>
static void display_stats(const T& words) {
    for (auto& w : words)
        printf("%s => %d\n", w.second.c_str(), w.first);
}


/*--------------------------------------------------------*/
template <typename T>
static void save_stats(const T& words) {
    string fname = get_filename(globals::filepath) + "_stats.txt";

    ofstream out(fname);
    if (!out.is_open()) {
        puts("| Failed to write statistics!\a");
        fflush(stdin);
        getchar();}

    for (auto& w : words)
        out << w.second << " => " << w.first << "\n";
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

    sort_stats(globals::cnt_words, globals::srt_words);
}


/*--------------------------------------------------------*/
static void save_or_display_stats() {
    while (true) {
        printf("Save or display statistics?\n\n");
        printf("1 - Save\n");
        printf("2 - Display\n\n");
        printf(">> ");
        int rep;
        if (scanf(" %d", &rep) != 1) {
            printf("| Inavalid option!\a\n");
            continue;}
        if (rep == 1) save_stats(globals::srt_words);
        else if (rep == 2) display_stats(globals::srt_words);
    }
}


/*--------------------------------------------------------*/
int main(int argc, char** argv) {
    if (argc != 2) {
        puts("Invalid command!");
        puts("Usage: fc filepath");
        fflush(stdin);
        getchar();
    }

    globals::filepath = argv[1];

    parse_file(globals::filepath);
    save_or_display_stats();
    return 0;
}
