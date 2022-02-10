#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Dictionary {
    string word;
    int pages[100];
    int count = 0;
    int totalCount = 0;
};

const string PAGE_SEPARATOR = "----------------------------------------------";

int main() {
    ifstream input("D:\\Subjects\\MP\\Labs\\Lab1\\Task2\\input.txt");
    string word, tempWord;
    int currentPage = 1;
    int dictionarySize = 8;
    int lastElem = 0;
    int moveToLover = 'a' - 'A';
    int count, i, j;
    Dictionary *dictionary = new Dictionary[dictionarySize];
    read:
    if (input >> word) {
        if (PAGE_SEPARATOR + to_string(currentPage) + PAGE_SEPARATOR == word) {
            currentPage++;
        } else {
            i = 0;
            tempWord = "";
            validateWord:
            if (word[i] != '\0') {
                if (word[i] >= 'A' && word[i] <= 'Z') {
                    word[i] += moveToLover;
                }
                if (word[i] >= 'a' && word[i] <= 'z' || word[i] == '-') {
                    tempWord += word[i];
                }
                i++;
                goto validateWord;
            }
            if (tempWord == "") {
                goto read;
            }
            word = tempWord;
            bool foundWord = false;
            i = 0;
            lookForWord:
            if (i < lastElem) {
                if (dictionary[i].word == word) {
                    foundWord = true;
                    count = dictionary[i].count;
                    if (dictionary[i].totalCount < 100 && dictionary[i].pages[count - 1] != currentPage) {
                        dictionary[i].pages[count] = currentPage;
                        dictionary[i].count++;
                        dictionary[i].totalCount++;
                    } else {
                        dictionary[i].totalCount++;
                    }
                    goto lookForWordEnd;
                }
                i++;
                goto lookForWord;
            }
            lookForWordEnd:
            if (!foundWord) {
                if (lastElem == dictionarySize) {
                    dictionarySize *= 2;
                    Dictionary* temp = new Dictionary[dictionarySize];
                    i = 0;
                    extendCapacity:
                    if (i < lastElem) {
                        temp[i] = dictionary[i];
                        i++;
                        goto extendCapacity;
                    }
                    dictionary = temp;
                }
                dictionary[lastElem].word = word;
                count = dictionary[lastElem].count++;
                dictionary[lastElem].totalCount++;
                dictionary[lastElem].pages[count] = currentPage;
                lastElem++;
            }
        }
        goto read;
    }
    i = 0;
    sortDictionary:
    if (i < lastElem) {
        j = i;
        sortInnerLoop:
        if (j < lastElem) {
            if (dictionary[i].word > dictionary[j].word) {
                Dictionary temp = dictionary[i];
                dictionary[i] = dictionary[j];
                dictionary[j] = temp;
            }
            j++;
            goto sortInnerLoop;
        }
        i++;
        goto sortDictionary;
    }
    i = 0;
    print:
    if (i < lastElem) {
        if (dictionary[i].totalCount <= 100) {
            cout << dictionary[i].word << " - ";
            j = 0;
            printInnerLoop:
            if (j < dictionary[i].count - 1) {
                cout << dictionary[i].pages[j] << ", ";
                j++;
                goto printInnerLoop;
            }
            cout << dictionary[i].pages[dictionary[i].count - 1] << endl;
        }
        i++;
        goto print;
    }
    return 0;
}
