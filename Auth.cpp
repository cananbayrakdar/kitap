#include "Auth.hpp"
#include <iostream>

static Kullanici* kullaniciList = nullptr;

void kullaniciEkle(const std::string& user,
                   const std::string& pass,
                   bool personel)
{
    Kullanici* k = new Kullanici{user, pass, personel, kullaniciList};
    kullaniciList = k;
    std::cout << "Kullanıcı eklendi: " << user
              << (personel ? " (Personel)\n" : " (Kullanıcı)\n");
}

void personelEkle(const std::string& user,
                  const std::string& pass)
{
    // personel bayrağını true olarak geçiriyoruz
    kullaniciEkle(user, pass, true);
}

Kullanici* girisYap() {
    std::string user, pass;
    std::cout << "Kullanıcı Adı: ";
    std::cin  >> user;
    std::cout << "Şifre: ";
    std::cin  >> pass;
    for (Kullanici* p = kullaniciList; p; p = p->next) {
        if (p->username == user && p->password == pass) {
            std::cout << "Giriş başarılı! Hoşgeldiniz, " << user << "\n";
            return p;
        }
    }
    std::cout << "Giriş başarısız!\n";
    return nullptr;
}
