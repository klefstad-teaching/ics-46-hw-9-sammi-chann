#include "ladder.h"

int main()
{
    // verify_word_ladder();
    set<string> word_list;
    vector<string> word_ladder_test;
    load_words(word_list, "../src/test.txt");
    word_ladder_test = generate_word_ladder("hit", "cog", word_list);
    print_word_ladder(word_ladder_test);
    return 0;
}