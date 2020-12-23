
#include <string>
#include "trie.h"

using namespace std;

Trie::Trie(){
	root = new Node;
}

void destructorHelper(Node* node) {
	if(node == nullptr) return;
	destructorHelper(node->zero);
	destructorHelper(node->one);
	delete node;
}

Trie::~Trie() {
	destructorHelper(root);
}

void Trie::insert(string sequence) {
	
	//TODO
	
}

bool existsHelper(int index, string& sequence, Node * curr) {
	if(curr == nullptr) return false;
	if(index == (int)sequence.size()) return curr->inTrie;

	if(sequence[index] == '0') {
		return existsHelper(index + 1, sequence, curr->zero);
	}else if (sequence[index] == '1') {
		return existsHelper(index + 1, sequence, curr->one);
	}
	return false;
}

bool Trie::exists(string sequence) {
	return existsHelper(0, sequence, root);
}