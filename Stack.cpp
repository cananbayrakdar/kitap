#include "Stack.hpp"
#include <iostream>
#include "Kitap.hpp"
using namespace std;

void oduncAl(StackNode*& oduncStack, Kitap* bas) {
    int id; 
    cout << "Ödünç alınacak kitap ID: "; 
    cin >> id;
    for (Kitap* tmp = bas; tmp; tmp = tmp->sonraki) {
        if (tmp->id == id) {
            StackNode* yeni = new StackNode{tmp, zamanDamgasi(), "-", oduncStack};
            oduncStack = yeni;
            cout << "Kitap ödünç alındı." << endl;
            return;
        }
    }
    cout << "Kitap bulunamadı." << endl;
}

void kitapIadeEt(StackNode*& oduncStack, StackNode*& iadeStack) {
    if (!oduncStack) {
        cout << "Ödünç kitap yok." << endl;
        return;
    }
    int id;
    cout << "İade edilecek kitap ID: "; 
    cin >> id;
    StackNode* prev = nullptr;
    StackNode* curr = oduncStack;
    while (curr) {
        if (curr->kitapPtr->id == id) {
            if (!prev) oduncStack = curr->next;
            else prev->next = curr->next;
            curr->teslimZamani = zamanDamgasi();
            curr->next = iadeStack;
            iadeStack = curr;
            cout << "Kitap iade edildi." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Bu ID'ye sahip ödünç kitap bulunamadı." << endl;
}

void oduncListele(StackNode* oduncStack) {
    cout << "--- Ödünç Kitaplar ---" << endl;
    for (StackNode* p = oduncStack; p; p = p->next)
        cout << p->kitapPtr->id << " - " << p->kitapPtr->isim << " | Alım: " << p->almaZamani << endl;
}

void iadeListele(StackNode* iadeStack) {
    cout << "--- İade Edilen Kitaplar ---" << endl;
    for (StackNode* p = iadeStack; p; p = p->next)
        cout << p->kitapPtr->id << " - " << p->kitapPtr->isim << " | Alım: " << p->almaZamani
             << " | Iade: " << p->teslimZamani << endl;
}

void stackToDaire(StackNode* stack, DaireselNode*& daireHead) {
    for (StackNode* p = stack; p; p = p->next) {
        DaireselNode* yeni = new DaireselNode{*(p->kitapPtr), p->almaZamani, p->teslimZamani, nullptr};
        if (!daireHead) {
            daireHead = yeni;
            yeni->next = daireHead;
        } else {
            DaireselNode* it = daireHead;
            while (it->next != daireHead) it = it->next;
            it->next = yeni;
            yeni->next = daireHead;
        }
    }
}

void oduncRaporu(DaireselNode*& oduncDaire, StackNode* oduncStack) {
    if (!oduncDaire) stackToDaire(oduncStack, oduncDaire);
    cout << "--- Ödünç Raporu ---" << endl;
    if (!oduncDaire) { cout << "Rapor boş." << endl; return; }
    DaireselNode* tmp = oduncDaire;
    do {
        cout << "[ÖDÜNÇ] " << tmp->kitap.isim << " | Alım: " << tmp->almaZamani << endl;
        tmp = tmp->next;
    } while (tmp != oduncDaire);
}

void iadeRaporu(DaireselNode*& iadeDaire, StackNode* iadeStack) {
    if (!iadeDaire) stackToDaire(iadeStack, iadeDaire);
    cout << "--- İade Raporu ---" << endl;
    if (!iadeDaire) { cout << "Rapor boş." << endl; return; }
    DaireselNode* tmp = iadeDaire;
    do {
        cout << "[İADE] " << tmp->kitap.isim << " | Alım: " << tmp->almaZamani 
             << " | Iade: " << tmp->teslimZamani << endl;
        tmp = tmp->next;
    } while (tmp != iadeDaire);
}

void erisebilirKitaplar(DaireselNode*& erisebilirDaire, Kitap* bas, StackNode* oduncStack) {
    erisebilirDaire = nullptr;
    for (Kitap* tmp = bas; tmp; tmp = tmp->sonraki) {
        bool al = false;
        for (StackNode* s = oduncStack; s; s = s->next)
            if (s->kitapPtr->id == tmp->id) { al = true; break; }
        if (!al) {
            DaireselNode* yeni = new DaireselNode{*tmp, "-", "-", nullptr};
            if (!erisebilirDaire) {
                erisebilirDaire = yeni;
                yeni->next = erisebilirDaire;
            } else {
                DaireselNode* it = erisebilirDaire;
                while (it->next != erisebilirDaire) it = it->next;
                it->next = yeni;
                yeni->next = erisebilirDaire;
            }
        }
    }
    cout << "--- Erişilebilir Kitaplar ---" << endl;
    if (!erisebilirDaire) { cout << "Yok." << endl; return; }
    DaireselNode* tmp = erisebilirDaire;
    do {
        cout << tmp->kitap.id << " - " << tmp->kitap.isim << endl;
        tmp = tmp->next;
    } while (tmp != erisebilirDaire);
}
