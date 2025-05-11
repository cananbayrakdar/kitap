#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Kitap.hpp"
#include <string>
using namespace std;

// Talep kuyruğu yapısı
struct Talep {
    int talepId;
    string kitapIsim;
    string yazar;
    int oncelik;
    Talep* next;
};

// Modül 3: Queue (Talep) Fonksiyon Prototipleri
void kitapTalepEt(Talep*& talepBas, Talep*& talepSon);
void talepleriYazdir(Talep* talepBas);
void akademikTalepEt(int id, Talep*& talepBas, Talep*& talepSon);
void kitapTedarikEt(Talep*& talepBas, Talep*& talepSon, Kitap*& bas);

#endif // QUEUE_HPP