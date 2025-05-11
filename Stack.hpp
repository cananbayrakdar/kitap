#ifndef STACK_HPP
#define STACK_HPP

#include "Kitap.hpp"
#include <string>
using namespace std;

// Stack yapısı ile ödünç alma/iade işlemleri
struct StackNode {
    Kitap* kitapPtr;
    string almaZamani;
    string teslimZamani;
    StackNode* next;
};

// Dairesel listeye dönüştürme
struct DaireselNode {
    Kitap kitap;
    string almaZamani;
    string teslimZamani;
    DaireselNode* next;
};

// Fonksiyon prototipleri
void oduncAl(StackNode*& oduncStack, Kitap* bas);
void kitapIadeEt(StackNode*& oduncStack, StackNode*& iadeStack);
void oduncListele(StackNode* oduncStack);
void iadeListele(StackNode* iadeStack);
void stackToDaire(StackNode* stack, DaireselNode*& daireHead);
void oduncRaporu(DaireselNode*& oduncDaire, StackNode* oduncStack);
void iadeRaporu(DaireselNode*& iadeDaire, StackNode* iadeStack);
void erisebilirKitaplar(DaireselNode*& erisebilirDaire, Kitap* bas, StackNode* oduncStack);

#endif // STACK_HPP
