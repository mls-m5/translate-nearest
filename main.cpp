

#include "levenshtein_distance.h"
#include <iostream>
#include <fstream>


using namespace std;


vector<string> loadWordlist() {
    vector<string> wordlist;
    ifstream file("wordlist.txt");
    string word;
    while (file) {
        file >> word;
        // cout << "loading word " << word << endl;
        wordlist.push_back(word);
    }
    return wordlist;
}


string toLower(string data) {
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}


class Wordlist {
public:
    vector<string> wl;

    Wordlist() {
        wl = loadWordlist();
    }

    string translateWord(string word) {
        auto min = 10000;
        string nearestWord;
        for (auto w: wl) {
            auto dist = edit_distance(w, toLower(word));
            if (dist < min) {
                min = dist;
                nearestWord = w;
            }
        }

        return nearestWord;
    }

    vector <string> translateSentense(vector<string> input) {
        vector <string> output;
        for (auto w: input) {
            output.push_back(translateWord(w));
        }
        return output;
    }
};


int main(int argc, char *argv[]) {
    vector <string> inputWords;

    // auto wordlist = loadWordlist();
    Wordlist wordlist;
    if (argc < 2) {
        cout << "please input a word" << endl;
        while (cin && !cin.eof()) {
            string word;
            cin >> word;
            if (word.empty()) {
                continue;
            }
            inputWords.push_back(word);
        }
    }
    else {
        for (int i = 1; i < argc; ++i) {
            string word = argv[i];
            inputWords.push_back(word);
        }
    }

    cout << "input: ";
    for (auto w: inputWords) {
        cout << w << " ";
    }
    cout << endl;

    auto outputWords = wordlist.translateSentense(inputWords);


    cout << "output: ";
    for (auto w: outputWords) {
        cout << w << " ";
    }
    cout << endl;
}