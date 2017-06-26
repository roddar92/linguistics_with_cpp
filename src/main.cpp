#include <iostream>
#include <cstdlib>
#include "ngramdictionary/NGramDictionaryManager.hpp"

using namespace std;
int main(int argc, char **argv) {
    NGramDictionaryManager manager;
    if (argc == 3)
    {
        if (argv[1] == NULL || argv[1] == "")
        {
            cerr << "Wrong path to input file! Expected string." << endl;
            return 2;
        }
        try
        {
            int ng_len = atoi(argv[2]);
            manager.create_dictionary(argv[1], ng_len);
            manager.print_dictionary();
        }
        catch (const exception& e)
        {
            cout << e.what();
        }
    }
    else if (argc == 4)
    {
        if (argv[1] == NULL || argv[1] == "")
        {
            cerr << "Wrong path to input file! Expected string." << endl;
            return 3;
        }
        if (argv[3] == NULL || argv[3] == "")
        {
            cerr << "Wrong path to output file! Expected string." << endl;
            return 3;
        }
        try
        {
            int ng_len = atoi(argv[2]);
            manager.create_dictionary(argv[1], ng_len);
            manager.save_dictionary_to_file(argv[3]);
        }
        catch (const exception &e)
        {
            cout << e.what();
        }
    }
    else
    {
        cerr << "Wrong number of arguments! Expected 2 or 3." << endl;
        return 1;
    }
    return 0;
}