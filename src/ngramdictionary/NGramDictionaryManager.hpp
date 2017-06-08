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
        dictionary.clear();
        stop_words.clear();
    }

    void create_dictionary(std::string const &input_file, int ngram_length);
    void print_dictionary(int limit = 20);
    void save_dictionary_to_file(std::string const &output_file);

private:
    std::map<std::wstring, int> dictionary;
    std::vector<std::wstring> stop_words;

    std::vector<std::wstring> get_ngrams(std::wstring const &word, int ng_len);
    std::vector<std::wstring> split_line(std::wstring &line);
    std::vector<std::wstring> create_stop_words_dict();
    void remove_stop_words(std::vector<std::wstring> &tokens);

    std::vector<std::pair<std::wstring, int>> convert_dict_to_vector_of_pairs();
};


#endif //NGRAMDICTIONARY_NGRAMDICTIONARYMANAGER_H
