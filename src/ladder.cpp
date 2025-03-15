#include "ladder.h"
#include <cstdlib>

void error(string word1, string word2, string msg)
{
    cerr << "ERROR: " << msg << endl;
    // throw runtime_error("Error encountered");
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int str1_len = str1.length();
    int str2_len = str2.length();
    
    vector<vector<int>> dp(str1_len + 1, vector<int> (str2_len + 1, 0));

    for (int i = 0; i <= str1_len; ++i)
        dp[i][0] = i;

    for (int j = 0; j <= str2_len; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= str1_len; ++i)
    {
        for (int j = 1; j <= str2_len; ++j)
        {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
             {
                int insert = dp[i][j-1];
                int remove = dp[i-1][j];
                int replace = dp[i-1][j-1];

                dp[i][j] = min(insert, remove);
                dp[i][j] = 1 + min(dp[i][j], replace);
             }
        }
    }
    
    return dp[str1_len][str2_len] <= d;
}
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (begin_word == end_word)
        error("BEGIN AND END WORDS ARE EQUAL", begin_word, end_word);

    queue<string> ladder_queue;
    vector<string> visited_words;
    vector<string> ladder;

    ladder_queue.push(begin_word);
    visited_words.push_back(begin_word);

    while (!ladder_queue.empty())
    {
        string current = ladder_queue.front();
        ladder_queue.pop();
        visited_words.push_back(current);
        for (string word : word_list)
        {
            if (is_adjacent(current, word))
            {
                if (find(visited_words.begin(), visited_words.end(), word) == visited_words.end())
                {
                    vector<string> new_ladder = visited_words; 
                    new_ladder.push_back(word);
                    visited_words.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                }
            }
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if (!in)
        throw runtime_error("Can't open input file");
    for (string word; in >> word;)
        word_list.insert(word);
}
void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty())
    {
        cout << "No word ladder found. \n";
        return;
    }
    cout << "Word ladder found: ";
    for (string word: ladder)
        cout << word << " ";
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}