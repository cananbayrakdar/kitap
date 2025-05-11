#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include "Kitap.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Tree.hpp"
#include "Hash.hpp"

using namespace std;

int main() {
#ifdef _WIN32
    // Konsolu UTF-8 moduna geçir
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    setlocale(LC_ALL, "Turkish_Turkey.1254");

    // Global yapılar
    Kitap* bas = nullptr;
    Kitap* basK = nullptr;
    Kitap* koleksiyon = nullptr;
    StackNode* oduncStack = nullptr;
    StackNode* iadeStack = nullptr;
    DaireselNode* oduncDaire = nullptr;
    DaireselNode* iadeDaire = nullptr;
    DaireselNode* erisebilirDaire = nullptr;
    Talep* talepBas = nullptr;
    Talep* talepSon = nullptr;
    KitapHashTablosu kitapHash;

    // Başlangıç: dosyadan kitap yükle
    kitapEkleDosyadan("kitaplar.txt", bas);

    int secim;
    do {
        cout << "=== ANA MENÜ ===" << endl;
        cout << "1. Personel Girişi" << endl;
        cout << "2. Kullanıcı Girişi" << endl;
        cout << "3. Çıkış" << endl;
        cout << "Seçim: "; cin >> secim;
        switch (secim) {
            case 1: {
                int psecim;
                do {
                    cout << "--- PERSONEL MENÜSÜ ---" << endl;
                    cout << "[MODÜL 1] Kitap Yönetimi" << endl;
                    cout << "1. Kitap Ekle" << endl;
                    cout << "2. Kitap Düzenle (İsim ile)" << endl;
                    cout << "3. Kitap Sil (ID ile)" << endl;
                    cout << "4. Kitap Listele" << endl;
                    cout << "5. Kitap Ara" << endl;
                    cout << "6. Kitap Sayısı" << endl;
                    cout << "7. Sayfa Sayısına Göre Sırala" << endl;
                    cout << "8. En Eski 5 Kitap" << endl;
                    cout << "9. Hasar Notu Ekle" << endl;
                    cout << "10. Hasarlı Kitapları Listele" << endl;
                    cout << "[MODÜL 2] Raporlama" << endl;
                    cout << "11. Ödünç Raporu" << endl;
                    cout << "12. İade Raporu" << endl;
                    cout << "13. Erişilebilir Kitaplar" << endl;
                    cout << "[MODÜL 3] Tedarik" << endl;
                    cout << "14. Kitap Tedarik Et" << endl;
                    cout << "[MODÜL 4] Ağaç İşlemleri" << endl;
                    cout << "15. Filtre Basım Yılı" << endl;
                    cout << "16. Filtre Sayfa Sayısı" << endl;
                    cout << "17. Filtre Dil" << endl;
                    cout << "18. Filtre Yayınevi" << endl;
                    cout << "[MODÜL 5] Hash Sistemi" << endl;
                    cout << "19. Hash Personel Menüsü" << endl;
                    cout << "20. Ana Menüye Dön" << endl;
                    cout << "Seçim: "; cin >> psecim;
                    switch (psecim) {
                        case 1: kitapEkle(bas); break;
                        case 2: kitapDuzenle(bas); break;
                        case 3: kitapSil(bas); break;
                        case 4: kitapListele(bas); break;
                        case 5: kitapAra(bas); break;
                        case 6: kitapSayisi(bas); break;
                        case 7: siralaSayfa(bas); break;
                        case 8: enEski5(bas); break;
                        case 9: hasarEkle(bas); break;
                        case 10: hasarlilariListele(bas); break;
                        case 11: oduncRaporu(oduncDaire, oduncStack); break;
                        case 12: iadeRaporu(iadeDaire, iadeStack); break;
                        case 13: erisebilirKitaplar(erisebilirDaire, bas, oduncStack); break;
                        case 14: kitapTedarikEt(talepBas, talepSon, bas); break;
                        case 15: { BookTree tree; tree.filtreleBasimYiliOnce1950(); tree.filtreleBasimYiliSonra1950(); } break;
                        case 16: { BookTree tree; tree.filtreleSayfaSayisi1000Alti(); tree.filtreleSayfaSayisi1000Ustu(); } break;
                        case 17: { BookTree tree; tree.filtreleDilTurkce(); tree.filtreleDilIngilizce(); } break;
                        case 18: { BookTree tree; tree.filtreleYayineviYerli(); tree.filtreleYayineviYabanci(); } break;
                        case 19: personelMenusuHash(kitapHash); break;
                    }
                } while (psecim != 20);
                break;
            }

            case 2: {
                if (bas) kitaplariAktar(bas, basK);
                int ksecim;
                do {
                    cout << "--- KULLANICI MENÜSÜ ---" << endl;
                    cout << "[MODÜL 1] Koleksiyon" << endl;
                    cout << "1. Yorum Yap" << endl;
                    cout << "2. Yorumları Listele" << endl;
                    cout << "3. Koleksiyon Oluştur" << endl;
                    cout << "4. Koleksiyona Kitap Ekle" << endl;
                    cout << "5. Okundu Bilgisi Değiştir" << endl;
                    cout << "6. Koleksiyondan Sil" << endl;
                    cout << "7. Koleksiyonu Listele" << endl;
                    cout << "[MODÜL 2] Stack" << endl;
                    cout << "8. Kitap Ödünç Al" << endl;
                    cout << "9. Ödünç Listele" << endl;
                    cout << "10. Kitap İade Et" << endl;
                    cout << "11. İade Listele" << endl;
                    cout << "[MODÜL 3] Queue" << endl;
                    cout << "12. Kitap Talep Et" << endl;
                    cout << "13. Talepleri Listele" << endl;
                    cout << "14. Akademik Talep Et" << endl;
                    cout << "[MODÜL 4] Ağaç İşlemleri" << endl;
                    cout << "15. Filtre Basım Yılı" << endl;
                    cout << "16. Filtre Sayfa Sayısı" << endl;
                    cout << "17. Filtre Dil" << endl;
                    cout << "18. Filtre Yayınevi" << endl;
                    cout << "[MODÜL 5] Hash Sistemi" << endl;
                    cout << "19. Hash Kullanıcı Menüsü" << endl;
                    cout << "20. Ana Menüye Dön" << endl;
                    cout << "Seçim: "; cin >> ksecim;
                    switch (ksecim) {
                        case 1: yorumYap(basK); break;
                        case 2: yorumlariListele(basK); break;
                        case 3: koleksiyonOlustur(koleksiyon); break;
                        case 4: koleksiyonaEkle(basK, koleksiyon); break;
                        case 5: okunduDuzenle(koleksiyon); break;
                        case 6: koleksiyondanSil(koleksiyon); break;
                        case 7: koleksiyonuListele(koleksiyon); break;
                        case 8: oduncAl(oduncStack, bas); break;
                        case 9: oduncListele(oduncStack); break;
                        case 10: kitapIadeEt(oduncStack, iadeStack); break;
                        case 11: iadeListele(iadeStack); break;
                        case 12: kitapTalepEt(talepBas, talepSon); break;
                        case 13: talepleriYazdir(talepBas); break;
                        case 14: { int id; cout << "ID: "; cin >> id; akademikTalepEt(id, talepBas, talepSon); } break;
                        case 15: { BookTree tree; tree.filtreleBasimYiliOnce1950(); tree.filtreleBasimYiliSonra1950(); } break;
                        case 16: { BookTree tree; tree.filtreleSayfaSayisi1000Alti(); tree.filtreleSayfaSayisi1000Ustu(); } break;
                        case 17: { BookTree tree; tree.filtreleDilTurkce(); tree.filtreleDilIngilizce(); } break;
                        case 18: { BookTree tree; tree.filtreleYayineviYerli(); tree.filtreleYayineviYabanci(); } break;
                        case 19: kullaniciMenusuHash(kitapHash); break;
                    }
                } while (ksecim != 20);
                break;
            }

            case 3:
                cout << "Çıkış yapılıyor..." << endl;
                break;
            default:
                cout << "Geçersiz seçim!" << endl;
        }
    } while (secim != 3);

    return 0;
}
