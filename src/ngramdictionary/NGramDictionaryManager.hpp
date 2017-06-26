//
// Created by user on 03.06.2017.
//

#ifndef NGRAMDICTIONARY_NGRAMDICTIONARYMANAGER_H
#define NGRAMDICTIONARY_NGRAMDICTIONARYMANAGER_H

#include <map>
#include <string>
#include <vector>

class NGramDictionaryManager
{
public:
    NGramDictionaryManager() {
        stop_words = create_stop_words_dict();
    }

    ~NGramDictionaryManager() {
        ngram_dictionary.clear();
        positions.clear();
        stop_words.clear();
    }

    void create_dictionary(std::string const &input_file, int ngram_length);


private:
    std::map<std::string, std::set<std::string>> ngram_dictionary;
    std::map<std::string, std::vector<std::pair<int, int>>> positions;
    std::vector<std::string> stop_words;

    std::vector<std::string> get_ngrams(std::string const &word, int ng_len);
    std::vector<std::string> split_text(std::string &line, bool collapse = true);
    std::vector<std::string> create_stop_words_dict();
    void save_dictionary_to_file();
    void remove_stop_words(std::vector<std::string> &tokens);

    bool endsWith(const std::string &s, const std::string &suffix);

    bool startsWith(const std::string &s, const std::string &prefix);
};


#endif //NGRAMDICTIONARY_NGRAMDICTIONARYMANAGER_H
