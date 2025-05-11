#pragma once
#include <string>

struct Kullanici {
    std::string username;
    std::string password;
    bool        isPersonel;
    Kullanici*  next;
};

// Yeni bir kullanıcı (personel veya normal) ekler
void kullaniciEkle(const std::string& user,
                   const std::string& pass,
                   bool personel);

// Sadece personel eklemek için kısayol
void personelEkle(const std::string& user,
                  const std::string& pass);

// Giriş işlemi: doğruysa ilgili Kullanici*, değilse nullptr döner
Kullanici* girisYap();