#include "Hash.hpp"
#include <iostream>
using namespace std;

// Book metodu
float Book::puanOrtalamasi() const {
    return puanSayisi == 0 ? 0.0f : (float)puanToplam / puanSayisi;
}

// KitapHashTablosu ctor
KitapHashTablosu::KitapHashTablosu() {
    for (int i = 0; i < HASH_BOYUTU; ++i) tablo[i] = nullptr;
}

void KitapHashTablosu::kitapEkle(const Book& b) {
    int idx = hashFonksiyonu(b.id);
    tablo[idx] = new Book(b);
}

void KitapHashTablosu::kitapPuanVer(int id, int puan) {
    int idx = hashFonksiyonu(id);
    if (tablo[idx] && tablo[idx]->id == id) {
        tablo[idx]->puanToplam += puan;
        tablo[idx]->puanSayisi += 1;
    } else {
        cout << "Kitap bulunamadı." << endl;
    }
}

void KitapHashTablosu::puaniYuksekOlanlariListele() const {
    cout << "--- Ortalama Puanı 4 ve Üzeri Kitaplar ---" << endl;
    for (int i = 0; i < HASH_BOYUTU; ++i) {
        if (tablo[i] && tablo[i]->puanOrtalamasi() >= 4.0f) {
            yazdirKitap(*tablo[i]);
        }
    }
}

void KitapHashTablosu::kategoriyeGoreOneri(const string& kategori) const {
    cout << "--- Kategoride Öneriler: " << kategori << " ---" << endl;
    for (int i = 0; i < HASH_BOYUTU; ++i) {
        if (tablo[i] && tablo[i]->kategori == kategori) {
            yazdirKitap(*tablo[i]);
        }
    }
}

void KitapHashTablosu::puanliKitaplariListele() const {
    cout << "--- Puanlanan Kitaplar ---" << endl;
    for (int i = 0; i < HASH_BOYUTU; ++i) {
        if (tablo[i] && tablo[i]->puanSayisi > 0) {
            yazdirKitap(*tablo[i]);
            cout << "Ortalama Puan: " << tablo[i]->puanOrtalamasi() << endl;
        }
    }
}

void KitapHashTablosu::yazdirKitap(const Book& b) const {
    cout << "ID: " << b.id << ", Ad: " << b.name
         << ", Kategori: " << b.kategori
         << ", Ortalama Puan: " << b.puanOrtalamasi() << endl;
}

void personelMenusuHash(KitapHashTablosu& tablo) {
    int secim;
    do {
        cout << "--- [MODÜL 5] Personel Menüsü ---" << endl;
        cout << "1. 4 ve üzeri puanlıları listele" << endl;
        cout << "2. Çıkış" << endl;
        cout << "Seçim: "; cin >> secim;
        if (secim == 1) tablo.puaniYuksekOlanlariListele();
    } while (secim != 2);
}

void kullaniciMenusuHash(KitapHashTablosu& tablo) {
    int secim;
    do {
        cout << "--- [MODÜL 5] Kullanıcı Menüsü ---" << endl;
        cout << "1. Kategoriye göre öneri" << endl;
        cout << "2. Puan ver ve listele" << endl;
        cout << "3. Çıkış" << endl;
        cout << "Seçim: "; cin >> secim;
        if (secim == 1) {
            string kategori; cout << "Kategori: "; cin.ignore(); getline(cin, kategori);
            tablo.kategoriyeGoreOneri(kategori);
        } else if (secim == 2) {
            int id, puan; cout << "ID: "; cin >> id; cout << "Puan: "; cin >> puan;
            tablo.kitapPuanVer(id, puan);
            tablo.puanliKitaplariListele();
        }
    } while (secim != 3);
}