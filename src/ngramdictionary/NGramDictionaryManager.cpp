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
    ifstream ifs(input_file, ios::binary);
    if (ifs)
    {
        std::stringstream ss;
        ss << ifs.rdbuf();
        std::string content(ss.str());

        std::vector<string> tokens = NGramDictionaryManager::split_text(content);
        remove_stop_words(tokens);

        for (auto token : tokens)
        {
            vector<string> ngrams = get_ngrams(token, ngram_length);
            for (auto ngram : ngrams) {
                ngram_dictionary[ngram].insert(token);
            }
        }

        ifs.close();
    }
}

vector<string> NGramDictionaryManager::split_text(string &line, bool collapse) {
    std::vector<std::string> tokens;
    std::string delims = " \"\n\r\t.,:;!?_-~+=*/\\#№&^()[]{}|<>\u2014\u0060\u00B4\u2018\u2019\u201C\u201D";
    size_t prev = 0, found;

    do
    {
        found = line.find_first_of(delims, prev);
        if (!collapse || prev != found)
        {
            std::string word(line.substr(prev, found - prev));
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            /**
             * Process words with aphostrafs
             * */
            if (NGramDictionaryManager::endsWith(word, std::string("n\'t")) ||
                NGramDictionaryManager::endsWith(word, std::string("\'s")))
            {
                word.replace(word.end() - 2, word.end() - 1, "");
            }
            if (NGramDictionaryManager::endsWith(word, std::string("\'")))
            {
                word.replace(word.end() - 1, word.end(), "");
            }
            if (NGramDictionaryManager::startsWith(word, std::string("\'")))
            {
                word.replace(word.begin(), word.begin() + 1, "");
            }

            if (!word.empty())
            {
                tokens.push_back(word);
            }
        }
        prev = found + 1;
    } while (found != std::string::npos);

    return tokens;
}

void NGramDictionaryManager::save_dictionary_to_file() {
    try {
        ofstream indexer("indexer.txt");
        for (map<string, set<string>>::iterator it = ngram_dictionary.begin();
             it != ngram_dictionary.end(); ++it)
        {
            indexer << it->first << "\t";
            set<string> posting = it->second;
            set<string>::iterator it1 = posting.begin();
            indexer << *it1;
            while (it1 != posting.end())
            {
                indexer << string(", ") << *it1;
                ++it1;
            }
            indexer << endl;
        }

        indexer.flush();
        indexer.close();

        ofstream output("positions.txt");
        for (map<string, vector<pair<int, int>>>::iterator it = positions.begin();
             it != positions.end(); ++it)
        {
            output << it->first << "\t";
            vector<pair<int, int>> poss = it->second;
            vector<pair<int, int>>::iterator it1 = poss.begin();
            output << it1->first << ":" << it1->second;
            while (it1 != poss.end())
            {
                output << string(", ") << it1->first << ":" << it1->second;
                ++it1;
            }
            output << endl;
        }
        output.flush();
        output.close();
        cout << "Writing of data to the file is over!" << endl;
    } catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}

vector<string> NGramDictionaryManager::get_ngrams(string const &word, int ng_len) {
    vector<string> result;
    if (word.size() >= ng_len)
    {
        for (size_t i = 0; i < word.size() - ng_len + 1; ++i)
        {
            result.push_back(word.substr(i, i + ng_len));
        }
    }
    return result;
}

vector<string> NGramDictionaryManager::create_stop_words_dict() {
    vector<string> stop_words;

    try {
        ifstream dict("stopwords.txt");
        if (dict)
        {
            string line;
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

void NGramDictionaryManager::remove_stop_words(vector<string> &tokens) {
    tokens.erase(
        remove_if(tokens.begin(), tokens.end(),
                  [&](const std::string& str) {
                      return find(stop_words.begin(), stop_words.end(), str) != stop_words.end();
                  }),
        tokens.end()
    );
}

bool NGramDictionaryManager::endsWith(const std::string& s, const std::string& suffix)
{
    return s.size() >= suffix.size() &&
           s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool NGramDictionaryManager::startsWith(const std::string& s, const std::string& prefix) {
    return s.size() >= prefix.size() &&
           s.compare(0, prefix.size(), prefix) == 0;
}