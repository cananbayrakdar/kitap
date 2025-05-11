#ifndef HASH_HPP
#define HASH_HPP

#include "Kitap.hpp"
#include <string>
using namespace std;

// Book struct for hash tablosu
struct Book {
    int id;
    string name;
    string yayinevi;
    string dil;
    int sayfaSayisi;
    int basimYili;
    string kategori;
    int puanToplam;
    int puanSayisi;
    float puanOrtalamasi() const;
};

class KitapHashTablosu {
private:
    static const int HASH_BOYUTU = 101;
    Book* tablo[HASH_BOYUTU];
    int hashFonksiyonu(int id) const { return id % HASH_BOYUTU; }
public:
    KitapHashTablosu();
    void kitapEkle(const Book& b);
    void kitapPuanVer(int id, int puan);
    void puaniYuksekOlanlariListele() const;
    void kategoriyeGoreOneri(const string& kategori) const;
    void puanliKitaplariListele() const;
    void yazdirKitap(const Book& b) const;
};

void personelMenusuHash(KitapHashTablosu& tablo);
void kullaniciMenusuHash(KitapHashTablosu& tablo);

#endif // HASH_HPP