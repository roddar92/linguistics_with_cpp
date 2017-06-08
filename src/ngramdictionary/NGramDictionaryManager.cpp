//
// Created by user on 03.06.2017.
//

#include <cstdio>
#include <iterator>
#include <iostream>
#include <fstream>
#include <regex>
#include "NGramDictionaryManager.hpp"

using namespace std;
void NGramDictionaryManager::create_dictionary(string const &input_file,
                                               int ngram_length)
{
    wifstream ifs(input_file, ios::binary);
    if (ifs)
    {
        wstring inputString;
        while (getline(ifs, inputString))
        {
            vector<wstring> tokens = split_line(inputString);
            remove_stop_words(tokens);
            for (auto token : tokens)
            {
                vector<wstring> ngrams = get_ngrams(token, ngram_length);
                for (auto ngram : ngrams) {
                    dictionary[ngram]++;
                }
            }
        }

        ifs.close();
    }
}

vector<wstring> NGramDictionaryManager::split_line(wstring &line) {
    vector<wstring> tokens;

    wchar_t * wcstr = new wchar_t[line.size() + 1];
    wcscpy(wcstr, line.c_str());

    wchar_t * token = wcstok(wcstr, L" \"\'.,:;!?-_+=*/\\#@№$&^()[]{}|<>");
    while (token != NULL)
    {
        tokens.push_back(wstring(token));
        token = wcstok(NULL, L" \"\'.,:;!?-_+=*/\\#@№$&^()[]{}|<>");
    }

    delete[] wcstr;
    delete[] token;

    return tokens;
}

auto cmp = [](std::pair<wstring,int> const & a, std::pair<wstring,int> const & b)
{
    return a.second != b.second ?  a.second > b.second : a.first < b.first;
};
void NGramDictionaryManager::print_dictionary(int limit) {
    int i = 0;
    vector<std::pair<wstring, int>> items = convert_dict_to_vector_of_pairs();
    std::sort(items.begin(), items.end(), cmp);
    for (auto item : items)
    {
        if (i < limit) {
            wcout << item.first << " - " << item.second << endl;
            i++;
        }
    }
}

void NGramDictionaryManager::save_dictionary_to_file(string const &output_file) {
    try {
        wofstream output(output_file);
        for (map<wstring, int>::iterator it = dictionary.begin();
             it != dictionary.end(); ++it)
        {
            output << it->first << " - " << it->second << endl;
        }
        output.flush();
        output.close();
        cout << "Writing of data to the file is over!" << endl;
    } catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

vector<wstring> NGramDictionaryManager::get_ngrams(wstring const &word, int ng_len) {
    vector<wstring> result;
    if (word.size() >= ng_len)
    {
        for (size_t i = 0; i < word.size() - ng_len + 1; ++i)
        {
            result.push_back(word.substr(i, i + ng_len));
        }
    }
    return result;
}

vector<wstring> NGramDictionaryManager::create_stop_words_dict() {
    vector<wstring> stop_words;

    try {
        wifstream dict("stopwords.txt");
        if (dict)
        {
            wstring line;
            while (getline(dict, line))
            {
                stop_words.push_back(line);
            }
        }
    } catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return stop_words;
}

void NGramDictionaryManager::remove_stop_words(vector<wstring> &tokens) {
    vector<wstring>::iterator it1, it2;
    for (it2 = tokens.begin(); it2 != tokens.end(); ++it2)
    {
        it1 = find(stop_words.begin(), stop_words.end(), *it2);
        if (it1 != stop_words.end())
        {
            tokens.erase(it2);
        }
    }
}

vector<std::pair<wstring, int>> NGramDictionaryManager::convert_dict_to_vector_of_pairs() {
    vector<pair<wstring, int>> result(dictionary.size());
    for (map<wstring, int>::iterator it = dictionary.begin();
         it != dictionary.end(); ++it)
    {
        result.push_back(pair<wstring, int>(it->first, it->second));
    }
    return result;
}
