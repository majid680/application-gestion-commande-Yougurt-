#include <iostream>
#include "domain/Stock.h"

Stock::Stock()
    : nature_(3), grec_(1), fruits_(5), granola_(4), miel_(4), chocolat_(1) {
}

void Stock::afficherChargementInitial() const {
    std::cout << "[Stock] nature : 0 -> " << nature_ << "\n";
    std::cout << "[Stock] grec : 0 -> " << grec_ << "\n";
    std::cout << "[Stock] fruits : 0 -> " << fruits_ << "\n";
    std::cout << "[Stock] granola : 0 -> " << granola_ << "\n";
    std::cout << "[Stock] miel : 0 -> " << miel_ << "\n";
    std::cout << "[Stock] chocolat : 0 -> " << chocolat_ << "\n";
}


void Stock::afficherStocks() const {
    std::cout << "Stocks:\n";
    std::cout << "  nature: " << nature_ << "\n";
    std::cout << "  grec: " << grec_ << "\n";
    std::cout << "  fruits: " << fruits_ << "\n";
    std::cout << "  granola: " << granola_ << "\n";
    std::cout << "  miel: " << miel_ << "\n";
    std::cout << "  chocolat: " << chocolat_ << "\n";
}



bool Stock::retirerYogourt(TypeYogourt type) {
    int* q = (type == TypeYogourt::Nature) ? &nature_ : &grec_;
    if (*q <= 0) {
        return false;
    }

    int avant = *q;
    --(*q);

    std::cout << "[Stock] " << toString(type) << " : " << avant << " -> " << *q << "\n";

    return true;
}

bool Stock::retirerGarniture(TypeGarniture type) {
    int& q = ref(type);
    if (q <= 0) {
        return false;
    }

    int avant = q;
    --q;

    std::cout << "[Stock] " << toString(type) << " : " << avant << " -> " << q << "\n";
    return true;
}

void Stock::remettreGarniture(TypeGarniture type) {
    int& q = ref(type);
    int avant = q;
    ++q;

    std::cout << "[Stock] " << toString(type) << " : " << avant << " -> " << q << "\n";
}

int Stock::quantite(TypeYogourt type) const {
    return (type == TypeYogourt::Nature) ? nature_ : grec_;
}




int Stock::quantite(TypeGarniture type) const {
    return ref(type);
}

int& Stock::ref(TypeGarniture type) {


    switch (type) {
    case TypeGarniture::Fruits: return fruits_;
    case TypeGarniture::Granola: return granola_;
    case TypeGarniture::Miel: return miel_;
    case TypeGarniture::Chocolat: return chocolat_;
    }
    return fruits_;
}

const int& Stock::ref(TypeGarniture type) const {

    switch (type) {
    case TypeGarniture::Fruits: return fruits_;
    case TypeGarniture::Granola: return granola_;
    case TypeGarniture::Miel: return miel_;
    case TypeGarniture::Chocolat: return chocolat_;
    }
    return fruits_;
}