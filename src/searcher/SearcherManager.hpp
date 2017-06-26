//
// Created by user on 26.06.2017.
//

#ifndef NGRAMDICTIONARY_SEARCHERMANAGER_H
#define NGRAMDICTIONARY_SEARCHERMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <set>

class SearcherManager
{
    typedef std::pair<int, int> position;
public:
    SearcherManager() {};
    ~SearcherManager() {};
    std::map<std::string, std::set<position>> search_word(const std::string &query);


private:
    std::vector<std::string> get_candidates_list(std::vector &ngrams_list);
    int levenshtein(const std::string &query, const std::string &candidate);
};

#endif //NGRAMDICTIONARY_SEARCHERMANAGER_H
