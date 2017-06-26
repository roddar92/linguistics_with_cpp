#include "SearcherManager.hpp"
#include <string>
#include <vector>

using namespace std;
map<string, set<SearcherManager::position>>
SearcherManager::search_word(const std::string &query) {
    return map<string, set<SearcherManager::position>>();
}

vector<string>
SearcherManager::get_candidates_list(vector &ngrams_list)
{
    return vector<string>();
}

int SearcherManager::levenshtein(const std::string &query, const std::string &candidate) {
    return 0;
}
