#include <fstream>
#include <vector>
#include <chrono>
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
    static chrono::duration<double> elapsed_time;
}


/*--------------------------------------------------------*/
static void wait_key() {
    fflush(stdin);
    getchar();
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
template <bool Format>
static auto split_line(const string& str, char delim = ' ') {
    vector<string> words;
    stringstream ss(str);
    string word;
    while (getline(ss, word, delim))
        if constexpr (Format)
            words.emplace_back(format_word(word));
        else words.emplace_back(word);
    return words;
}


/*--------------------------------------------------------*/
static string get_filename(string path) {
    string name;
    transform(path.begin(), path.end(), name.begin(), [](char c) {
        return (c == '\\') ? '/' : c; });
    return split_line<false>(path, '/').back();
}


/*--------------------------------------------------------*/
static void print_elaps() {
    printf("\n|------------------------------------------------\n");
    printf("| Filename: %s\n", get_filename(globals::filepath).c_str());
    printf("| Time elapsed: %.3f seconds\n", globals::elapsed_time.count());
    printf("|------------------------------------------------");
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
    printf("\n\n|------------------------------------------------\n");
    for (auto& w : words)
        printf("| %s => %d\n", w.second.c_str(), w.first);
    printf("|------------------------------------------------");
}


/*--------------------------------------------------------*/
template <typename T>
static void save_stats(const T& words) {
    string fname = get_filename(globals::filepath) + "_stats.txt";

    ofstream out(fname);
    if (!out.is_open()) {
        puts("| Failed to write statistics!\a");
        wait_key();
        exit(1);}

    for (auto& w : words)
        out << w.second << " => " << w.first << "\n";
}


/*--------------------------------------------------------*/
static inline bool is_word(const string& word) {
    if (word.size() < 2) return false;
    for (char c : word)
        if (!isalpha(c))
            return false;
    return true;
}


/*--------------------------------------------------------*/
static void parse_file(string_view path) {
    ifstream in(path.data());
    if (!in.is_open()) {
        printf("Failed to open file \'%s\'\n", path.data());
        exit(1);}

    string line;
    auto start = std::chrono::high_resolution_clock::now();

    while (in) {
        getline(in, line);
        auto words = split_line<true>(line);
        for (string& w : words)
            if (is_word(w))
                globals::cnt_words[w]++;
    }

    sort_stats(globals::cnt_words, globals::srt_words);

    auto end = std::chrono::high_resolution_clock::now();
    globals::elapsed_time = end- start;
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
        break;
    }
}


/*--------------------------------------------------------*/
int main(int argc, char** argv) {
    if (argc != 2) {
        puts("| Invalid command!\a");
        puts("| Usage: fc filepath");
        wait_key();
        return 1;
    }

    globals::filepath = argv[1];

    parse_file(globals::filepath);
    save_or_display_stats();
    print_elaps();
    wait_key();
    return 0;
}
