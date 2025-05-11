#include "Tree.hpp"
#include <iostream>
using namespace std;

// TreeNode constructor
TreeNode::TreeNode(const Kitap& k) : data(k), left(nullptr), right(nullptr) {}

// BookTree methods
BookTree::BookTree() : root(nullptr) {}

TreeNode* BookTree::insertNode(TreeNode* node, const Kitap& k) {
    if (!node) return new TreeNode(k);
    if (k.id < node->data.id)
        node->left = insertNode(node->left, k);
    else
        node->right = insertNode(node->right, k);
    return node;
}

void BookTree::ekle(const Kitap& k) {
    root = insertNode(root, k);
}

void BookTree::traverseIf(TreeNode* node, bool (*condition)(const Kitap&)) {
    if (!node) return;
    traverseIf(node->left, condition);
    if (condition(node->data))
        cout << node->data.id << " - " << node->data.isim << endl;
    traverseIf(node->right, condition);
}

void BookTree::filtreleBasimYiliOnce1950() { traverseIf(root, basim1950Once); }
void BookTree::filtreleBasimYiliSonra1950() { traverseIf(root, basim1950Sonra); }
void BookTree::filtreleSayfaSayisi1000Alti() { traverseIf(root, sayfa1000Alti); }
void BookTree::filtreleSayfaSayisi1000Ustu() { traverseIf(root, sayfa1000Ustu); }
void BookTree::filtreleDilTurkce() { traverseIf(root, dilTurkce); }
void BookTree::filtreleDilIngilizce() { traverseIf(root, dilIngilizce); }
void BookTree::filtreleYayineviYerli() { traverseIf(root, yayineviYerli); }
void BookTree::filtreleYayineviYabanci() { traverseIf(root, yayineviYabanci); }

// Condition implementations
bool basim1950Once(const Kitap& k) { return k.basimYili < 1950; }
bool basim1950Sonra(const Kitap& k) { return k.basimYili >= 1950; }
bool sayfa1000Alti(const Kitap& k) { return k.sayfaSayisi < 1000; }
bool sayfa1000Ustu(const Kitap& k) { return k.sayfaSayisi >= 1000; }
bool dilTurkce(const Kitap& k) { return k.dil == "Türkçe"; }
bool dilIngilizce(const Kitap& k) { return k.dil == "İngilizce"; }
bool yayineviYerli(const Kitap& k) { return k.yayinevi == "Yerli"; }
bool yayineviYabanci(const Kitap& k) { return k.yayinevi == "Yabancı"; }