#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define CHILDREN 26

class AC_Trie {

    struct Node {

        char data;
        bool end_of_word = false;
        Node* longest_suffix;
        Node* children[CHILDREN] = { NULL };
        
        vector<Node*> dict_suffixes;

        Node(char data) {
            this->data = data;
        }
        
    };

    Node* root = new Node('\0');

    void add_word(Node* n, string word);
    vector<string> in_order(Node* n, string word);

public:

    void add_word(string word);
    vector<string> in_order();


};

void AC_Trie::add_word(Node* n, string word) {

    char letter = word[0];
    int index = letter - 'a';

    if (n->children[index] == NULL) {

        n->children[index] = new Node(letter);

    }

    if (word.length() == 1) {
        n->children[index]->end_of_word = true;
    } else {
        add_word(n->children[index], word.substr(1));
    }

}

void AC_Trie::add_word(string word) {

    this->add_word(this->root, word);

}

vector<string> AC_Trie::in_order(Node* n, string word_start) {

    vector<string> dictionary;

    string word;

    for (int i = 0; i < CHILDREN; i++) {
        if(n->children[i] != NULL) {
            word = word_start + n->children[i]->data;
            if (n->children[i]->end_of_word) {
                word += '\0';
                cout << word << endl;
                dictionary.push_back(word);
            }
            in_order(n->children[i], word);
        } 
    }

    return dictionary;

}

vector<string> AC_Trie::in_order() {
    
    return this->in_order(this->root, "");

}


int main() {

    AC_Trie act;

    act.add_word("foo");
    act.add_word("football");
    act.in_order();


}