#include "Kitap.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <vector>
#include <limits>
using namespace std;

// ——————————————————————
// Yardımcı Fonksiyon
// ——————————————————————
string zamanDamgasi() {
    time_t now = time(nullptr);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0';
    return string(dt);
}

// ——————————————————————
// Dosyadan Kitap Yükleme
// ——————————————————————
void kitapEkleDosyadan(const string& dosyaAdi, Kitap*& bas) {
    ifstream dosya(dosyaAdi);
    if (!dosya.is_open()) {
        cout << "Dosya açılmadı: " << dosyaAdi << endl;
        return;
    }
    while (true) {
        Kitap* k = new Kitap();
        if (!(dosya >> k->id)) { delete k; break; }
        dosya.ignore();
        getline(dosya, k->isim);
        getline(dosya, k->yazar);
        dosya >> k->sayfaSayisi >> k->basimYili;
        dosya.ignore();
        getline(dosya, k->hasarNotu);
        getline(dosya, k->yayinevi);
        getline(dosya, k->dil);
        k->zamanDamgasi = zamanDamgasi();
        k->sonraki = bas;
        bas = k;
    }
    dosya.close();
    cout << "Kitaplar dosyadan yüklendi." << endl;
}
void kitaplariDosyayaKaydet(Kitap* bas, const string& dosyaAdi) {
    ofstream out(dosyaAdi, ios::trunc);
    if (!out) {
        cerr << "Dosya açılamadı: " << dosyaAdi << endl;
        return;
    }
    for (Kitap* p = bas; p; p = p->sonraki) {
        out << p->id          << endl
            << p->isim        << endl
            << p->yazar       << endl
            << p->sayfaSayisi << endl
            << p->basimYili   << endl
            << p->hasarNotu   << endl
            << p->yayinevi    << endl
            << p->dil          << endl;
    }
    out.close();
}

// ——————————————————————
// MODÜL 1 – Personel İşlevleri
// ——————————————————————
void kitapEkle(Kitap*& bas) {
    Kitap* yeni = new Kitap();
    cout << "ID: ";        cin >> yeni->id; cin.ignore();
    cout << "İsim: ";      getline(cin, yeni->isim);
    cout << "Yazar: ";     getline(cin, yeni->yazar);
    cout << "Sayfa Sayısı: "; cin >> yeni->sayfaSayisi;
    cout << "Basım Yılı: ";  cin >> yeni->basimYili; cin.ignore();
    cout << "Hasar Notu: ";  getline(cin, yeni->hasarNotu);
    cout << "Yayınevi: ";    getline(cin, yeni->yayinevi);
    cout << "Dil: ";         getline(cin, yeni->dil);
    yeni->zamanDamgasi = zamanDamgasi();
    yeni->sonraki = bas;
    bas = yeni;
    cout << "Kitap eklendi!" << endl;
    // Dosyayı güncelle
    kitaplariDosyayaKaydet(bas, "kitaplar.txt");
}

#include <limits>  // <limits> eklendi

void kitapDuzenle(Kitap*& bas) {
    if (!bas) {
        cout << "Liste boş." << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Düzenlenecek kitabın ismini girin: ";
    string aranan; getline(cin, aranan);
    for (Kitap* p = bas; p; p = p->sonraki) {
        if (p->isim == aranan) {
            cout << "Yeni isim: ";   getline(cin, p->isim);
            cout << "Yeni yazar: ";  getline(cin, p->yazar);
            cout << "Kitap güncellendi." << endl;
            // Dosyayı güncelle
            kitaplariDosyayaKaydet(bas, "kitaplar.txt");
            return;
        }
    }
    cout << "Kitap bulunamadı." << endl;
}


void kitapSil(Kitap*& bas) {
    cout << "Silinecek kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();
    Kitap* p = bas;
    Kitap* prev = nullptr;
    while (p) {
        if (p->id == id) {
            if (prev) prev->sonraki = p->sonraki;
            else       bas = p->sonraki;
            delete p;
            cout << "Kitap silindi." << endl;
            // Dosyayı güncelle
            kitaplariDosyayaKaydet(bas, "kitaplar.txt");
            return;
        }
        prev = p;
        p = p->sonraki;
    }
    cout << "Kitap bulunamadı." << endl;
}

void kitapListele(Kitap* bas) {
    cout << "--- Kitap Listesi ---\n";
    for (Kitap* p = bas; p; p = p->sonraki)
        cout << p->id << " - " << p->isim
             << " (" << p->zamanDamgasi << ")\n";
}

void kitapAra(Kitap* bas) {
    cout << "Aranacak kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();
    for (Kitap* p = bas; p; p = p->sonraki) {
        if (p->id == id) {
            cout << "Bulundu: " << p->isim
                 << " – " << p->yazar << "\n";
            return;
        }
    }
    cout << "Kitap bulunamadı.\n";
}

void kitapSayisi(Kitap* bas) {
    int count = 0;
    for (Kitap* p = bas; p; p = p->sonraki) ++count;
    cout << "Toplam kitap sayısı: " << count << "\n";
}

void siralaSayfa(Kitap*& bas) {
    if (!bas || !bas->sonraki) return;
    vector<Kitap*> arr;
    for (Kitap* p = bas; p; p = p->sonraki) arr.push_back(p);
    sort(arr.begin(), arr.end(),
         [](Kitap* a, Kitap* b){ return a->sayfaSayisi < b->sayfaSayisi; });
    for (size_t i = 0; i + 1 < arr.size(); ++i)
        arr[i]->sonraki = arr[i+1];
    arr.back()->sonraki = nullptr;
    bas = arr[0];
    kitapListele(bas);
}

void enEski5(Kitap* bas) {
    vector<Kitap*> arr;
    for (Kitap* p = bas; p; p = p->sonraki) arr.push_back(p);
    sort(arr.begin(), arr.end(),
         [](Kitap* a, Kitap* b){ return a->basimYili < b->basimYili; });
    cout << "En eski 5 kitap:\n";
    for (int i = 0; i < min(5, (int)arr.size()); ++i)
        cout << arr[i]->isim << " - " << arr[i]->basimYili << "\n";
}

void hasarEkle(Kitap* bas) {
    cout << "Hasar notu eklenecek kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();
    for (Kitap* p = bas; p; p = p->sonraki) {
        if (p->id == id) {
            cout << "Hasar notunu girin: ";
            getline(cin, p->hasarNotu);
            cout << "Hasar kaydedildi." << endl;
            // Dosyayı güncelle
            kitaplariDosyayaKaydet(bas, "kitaplar.txt");
            return;
        }
    }
    cout << "Kitap bulunamadı." << endl;
}

void hasarlilariListele(Kitap* bas) {
    cout << "--- Hasarlı Kitaplar ---\n";
    for (Kitap* p = bas; p; p = p->sonraki) {
        if (!p->hasarNotu.empty())
            cout << p->isim << " - " << p->hasarNotu << "\n";
    }
}

// ——————————————————————
// MODÜL 1 (Kullanıcı) – Dairesel Çift Yönlü Liste İşlevleri
// ——————————————————————
void kitaplariAktar(Kitap* bas, Kitap*& basK) {
    for (Kitap* p = bas; p; p = p->sonraki) {
        Kitap* yeni = new Kitap(*p);
        if (!basK)
            basK = yeni->ileri = yeni->onceki = yeni;
        else {
            Kitap* son = basK->onceki;
            son->ileri   = yeni; yeni->onceki = son;
            yeni->ileri  = basK; basK->onceki = yeni;
        }
    }
}

void yorumYap(Kitap* basK) {
    if (!basK) {
        cout << "Henüz kitap listesi oluşturulmadı.\n";
        return;
    }
    cout << "Yorum yapmak istediğiniz kitabın ID'sini girin: ";
    int id; 
    if (!(cin >> id)) {
        cout << "Geçersiz ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Kitap* p = basK;
    do {
        if (p->id == id) {
            if (p->yorumSayisi < 10) {
                cout << "Yorumunuzu girin: ";
                getline(cin, p->yorumlar[p->yorumSayisi++]);
                cout << "Yorum kaydedildi.\n";
            } else {
                cout << "Maksimum yorum sayısına ulaşıldı.\n";
            }
            return;
        }
        p = p->ileri;
    } while (p != basK);
    cout << "Kitap bulunamadı.\n";
}

void yorumlariListele(Kitap* basK) {
    if (!basK) { cout << "Liste boş.\n"; return; }
    cout << "Yorumlarını görmek istediğiniz kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();
    Kitap* p = basK;
    do {
        if (p->id == id) {
            for (int i = 0; i < p->yorumSayisi; ++i)
                cout << "- " << p->yorumlar[i] << "\n";
            return;
        }
        p = p->ileri;
    } while (p != basK);
    cout << "Kitap bulunamadı.\n";
}

void koleksiyonOlustur(Kitap*& koleksiyon) {
    if (!koleksiyon) {
        koleksiyon = nullptr;  // ilk kez oluşturuluyor
        cout << "Koleksiyon oluşturuldu.\n";
    } else {
        cout << "Zaten bir koleksiyonunuz var.\n";
    }
}

void koleksiyonaEkle(Kitap* basK, Kitap*& koleksiyon) {
    cout << "Eklemek istediğiniz kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();
    Kitap* p = basK;
    do {
        if (p->id == id) {
            Kitap* yeni = new Kitap(*p);
            yeni->sonraki = koleksiyon;
            koleksiyon    = yeni;
            cout << "Kitap koleksiyona eklendi.\n";
            return;
        }
        p = p->ileri;
    } while (p != basK);
    cout << "Kitap bulunamadı.\n";
}

void okunduDuzenle(Kitap* koleksiyon) {
    if (!koleksiyon) {
        cout << "Koleksiyon boş.\n";
        return;
    }
    cout << "--- Koleksiyon ---\n";
    for (Kitap* p = koleksiyon; p; p = p->sonraki)
        cout << p->id << " | " << p->isim
             << " | Okundu: " << (p->okundu ? "Evet" : "Hayır") << "\n";

    cout << "Güncellenecek kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();

    Kitap* hedef = nullptr;
    for (Kitap* p = koleksiyon; p; p = p->sonraki) {
        if (p->id == id) { hedef = p; break; }
    }
    if (!hedef) { cout << "Kitap bulunamadı.\n"; return; }

    cout << "1. Okundu olarak işaretle\n"
         << "2. Okunmadı olarak işaretle\n"
         << "Seçiminiz: ";
    int sec; cin >> sec; cin.ignore();
    if (sec == 1) hedef->okundu = true;
    else if (sec == 2) hedef->okundu = false;
    else { cout << "Geçersiz seçim.\n"; return; }
    cout << "Bilgi güncellendi.\n";
}

void koleksiyondanSil(Kitap*& bas) {
    if (!bas) {
        cout << "Koleksiyon boş.\n";
        return;
    }
    cout << "Silinecek kitabın ID'sini girin: ";
    int id; cin >> id; cin.ignore();

    Kitap* p = bas;
    do {
        if (p->id == id) break;
        p = p->ileri;
    } while (p != bas);

    if (p->id != id) {
        cout << "Kitap bulunamadı.\n";
        return;
    }

    if (p->ileri == p) {
        delete p;
        bas = nullptr;
    } else {
        p->onceki->ileri = p->ileri;
        p->ileri->onceki = p->onceki;
        if (p == bas) bas = p->ileri;
        delete p;
    }
    cout << "Silme tamamlandı.\n";
}

void koleksiyonuListele(Kitap* koleksiyon) {
    cout << "--- Koleksiyon ---\n";
    for (Kitap* p = koleksiyon; p; p = p->sonraki)
        cout << p->isim
             << " | Okundu: " << (p->okundu ? "Evet" : "Hayır") << "\n";
}
