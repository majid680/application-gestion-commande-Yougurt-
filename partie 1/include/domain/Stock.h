#pragma once
#include "common/Types.h"

class Stock {
public:
    Stock();

    void afficherChargementInitial() const;
    void afficherStocks() const;


    bool retirerYogourt(TypeYogourt type);
    bool retirerGarniture(TypeGarniture type);
    void remettreGarniture(TypeGarniture type);



    int quantite(TypeYogourt type) const;
    int quantite(TypeGarniture type) const;


private:

    int nature_;
    int grec_;
    int fruits_;
    int granola_;
    int miel_;
    int chocolat_;


    int& ref(TypeGarniture type);
    const int& ref(TypeGarniture type) const;
};