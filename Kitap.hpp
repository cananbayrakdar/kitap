#ifndef KITAP_HPP
#define KITAP_HPP

#include <string>
#include <ctime>
#include <cstring>

using namespace std;

// Zaman damgası oluşturur
string zamanDamgasi();

struct Kitap {
    // Temel bilgiler
    int id;
    string isim;
    string yazar;
    string yayinevi;
    string dil;
    int sayfaSayisi;
    int basimYili;
    string hasarNotu;
    string zamanDamgasi;

    // Bağlı liste işaretçileri
    Kitap* sonraki = nullptr;  // Tek yönlü liste için
    Kitap* onceki  = nullptr;  // Çift yönlü dairesel liste için
    Kitap* ileri   = nullptr;  // Çift yönlü dairesel liste için

    // Kullanıcı yorumları ve okuma durumu
    string yorumlar[10];
    int yorumSayisi = 0;
    bool okundu     = false;
};

// ——————————————————————
// MODÜL 1: Personel İşlevleri
// ——————————————————————
void kitapEkle(Kitap*& bas);
void kitapDuzenle(Kitap*& bas);
void kitapSil(Kitap*& bas);
void kitapListele(Kitap* bas);
void kitapAra(Kitap* bas);
void kitapSayisi(Kitap* bas);
void siralaSayfa(Kitap*& bas);
void enEski5(Kitap* bas);
void hasarEkle(Kitap* bas);
void hasarlilariListele(Kitap* bas);

// ——————————————————————
// MODÜL 1 (Kullanıcı): Dairesel Çift Yönlü Liste İşlevleri
// ——————————————————————
void kitaplariAktar(Kitap* bas, Kitap*& basK);
void yorumYap(Kitap* basK);
void yorumlariListele(Kitap* basK);
void koleksiyonOlustur(Kitap*& koleksiyon);
void koleksiyonaEkle(Kitap* basK, Kitap*& koleksiyon);
void okunduDuzenle(Kitap* koleksiyon);
void koleksiyondanSil(Kitap*& koleksiyon);
void koleksiyonuListele(Kitap* koleksiyon);

// ——————————————————————
// Dosyadan kitap yükleme
// ——————————————————————
void kitapEkleDosyadan(const string& dosyaAdi, Kitap*& bas);

#endif // KITAP_HPP
