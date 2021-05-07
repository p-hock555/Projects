#ifndef TRIE_H
#define TRIE_H

#include <string>

struct Node {
	bool inTrie = false;
	Node* zero = nullptr;
	Node* one = nullptr;
};

class Trie {
public:
	Trie();
	~Trie();

	void insert(std::string sequence);
	bool exists(std::string sequence);
private:
	Node* root;
};

#endif