#include "Queue.hpp"
#include <iostream>
#include "Kitap.hpp"
using namespace std;

// Yeni talep ekleme
void kitapTalepEt(Talep*& talepBas, Talep*& talepSon) {
    Talep* t = new Talep();
    cout << "Talep edilecek kitap ismi: "; cin.ignore(); getline(cin, t->kitapIsim);
    cout << "Yazar adı: "; getline(cin, t->yazar);
    cout << "Talep ID: "; cin >> t->talepId;
    t->oncelik = 0;
    t->next = nullptr;
    if (!talepBas) talepBas = talepSon = t;
    else { talepSon->next = t; talepSon = t; }
    cout << "Kitap talebi alındı." << endl;
}

// Tüm talepleri listeleme
void talepleriYazdir(Talep* talepBas) {
    cout << "--- Talep Listesi ---" << endl;
    for (Talep* p = talepBas; p; p = p->next) {
        cout << "ID: " << p->talepId << " | Kitap: " << p->kitapIsim << " | Yazar: " << p->yazar;
        if (p->oncelik > 0) cout << " [Akademik]";
        cout << endl;
    }
}

// Akademik talep önceliklendirme
void akademikTalepEt(int id, Talep*& talepBas, Talep*& talepSon) {
    Talep* prev = nullptr;
    for (Talep* p = talepBas; p; prev = p, p = p->next) {
        if (p->talepId == id) {
            p->oncelik++;
            if (prev) {
                prev->next = p->next;
                p->next = talepBas;
                talepBas = p;
                if (p == talepSon) talepSon = prev;
            }
            cout << "Akademik talep kaydedildi ve önceliklendirildi." << endl;
            talepleriYazdir(talepBas);
            return;
        }
    }
    cout << "Talep bulunamadı." << endl;
}

// Talepten kitap tedarik etme
void kitapTedarikEt(Talep*& talepBas, Talep*& talepSon, Kitap*& bas) {
    if (!talepBas) { cout << "Bekleyen talep yok." << endl; return; }
    Talep* ilk = talepBas;
    talepBas = talepBas->next;
    if (!talepBas) talepSon = nullptr;
    Kitap* yeni = new Kitap();
    yeni->id = rand() % 10000 + 1000;
    yeni->isim = ilk->kitapIsim;
    yeni->yazar = ilk->yazar;
    yeni->sayfaSayisi = 0;
    yeni->basimYili = 2024;
    yeni->hasarNotu = "-";
    yeni->zamanDamgasi = zamanDamgasi();
    yeni->sonraki = bas;
    bas = yeni;
    cout << "Kitap tedarik edildi ve kütüphaneye eklendi: " << yeni->isim << endl;
    delete ilk;
}