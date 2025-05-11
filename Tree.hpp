#ifndef TREE_HPP
#define TREE_HPP

#include "Kitap.hpp"

// Ağaç düğümü yapısı
struct TreeNode {
    Kitap data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const Kitap& k);
};

class BookTree {
private:
    TreeNode* root;
    TreeNode* insertNode(TreeNode* node, const Kitap& k);
    void traverseIf(TreeNode* node, bool (*condition)(const Kitap&));
public:
    BookTree();
    void ekle(const Kitap& k);
    void filtreleBasimYiliOnce1950();
    void filtreleBasimYiliSonra1950();
    void filtreleSayfaSayisi1000Alti();
    void filtreleSayfaSayisi1000Ustu();
    void filtreleDilTurkce();
    void filtreleDilIngilizce();
    void filtreleYayineviYerli();
    void filtreleYayineviYabanci();
};

// Koşul fonksiyonları
bool basim1950Once(const Kitap& k);
bool basim1950Sonra(const Kitap& k);
bool sayfa1000Alti(const Kitap& k);
bool sayfa1000Ustu(const Kitap& k);
bool dilTurkce(const Kitap& k);
bool dilIngilizce(const Kitap& k);
bool yayineviYerli(const Kitap& k);
bool yayineviYabanci(const Kitap& k);

#endif // TREE_HPP