#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct WordsCounter {
    string word;
    int count = 0;
};

const int COUNT_OF_WORDS_TO_OUTPUT = 25;

int main() {
    ifstream input("D:\\Subjects\\MP\\Labs\\Lab1\\Task1\\input.txt");
    string word;
    string stopWords[] = {
            "the", "for", "in"
    };
    int numberOfStopWords = sizeof(stopWords) / sizeof(string);
    int moveToLover = 'a' - 'A';
    int i, j;
    bool wordExists;
    int number;
    int tail = 0;
    WordsCounter *wordsCounter = new WordsCounter[1000];
    read:
    if (input >> word) {
        j = 0;
        toLover:
        if (word[j] != '\0') {
            if (word[j] >= 'A' && word[j] <= 'Z') {
                word[j] += moveToLover;
            }
            j++;
            goto toLover;
        }
        wordExists = false;
        i = 0;
        findWord:
        if (i < tail) {
            if (wordsCounter[i].word == word) {
                wordsCounter[i].count++;
                wordExists = true;
            }
            i++;
            goto findWord;
        }
        if (!wordExists) {
            wordsCounter[tail].word = word;
            wordsCounter[tail].count = 1;
            tail++;
        }
        goto read;
    }
    i = 0;
    sortStart:
    if (i < tail) {
        j = i;
        sortLoop:
        if (j < tail) {
            if (wordsCounter[i].count < wordsCounter[j].count) {
                WordsCounter temp = wordsCounter[i];
                wordsCounter[i] = wordsCounter[j];
                wordsCounter[j] = temp;
            }
            j++;
            goto sortLoop;
        }
        i++;
        goto sortStart;
    }
    number = 0;
    i =  0;
    print:
    if (i < tail) {
        wordExists = false;
        j = 0;
        printLoop:
        if (j < numberOfStopWords) {
            if (wordsCounter[i].word == stopWords[j]) {
                wordExists = true;
            }
            j++;
            goto printLoop;
        }
        if (!wordExists) {
            number++;
            cout << wordsCounter[i].word << " - " << wordsCounter[i].count << endl;
        }
        if (number > COUNT_OF_WORDS_TO_OUTPUT) {
            goto printEnd;
        }
        i++;
        goto print;
    }
    printEnd:
    return 0;
}
