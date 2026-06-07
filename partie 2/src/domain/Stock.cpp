#include "domain/Stock.h"

#include <algorithm>
#include <iostream>

Stock::Stock() {
    inventaire_["nature"] = 3;
    inventaire_["grec"] = 1;
    inventaire_["fruits"] = 5;
    inventaire_["granola"] = 4;
    inventaire_["miel"] = 4;
    inventaire_["chocolat"] = 1;
}



void Stock::afficherChargementInitial() const {
    std::cout << "[Stock] nature : 0 -> " << inventaire_.at("nature") << "\n";
    std::cout << "[Stock] grec : 0 -> " << inventaire_.at("grec") << "\n";
    std::cout << "[Stock] fruits : 0 -> " << inventaire_.at("fruits") << "\n";
    std::cout << "[Stock] granola : 0 -> " << inventaire_.at("granola") << "\n";
    std::cout << "[Stock] miel : 0 -> " << inventaire_.at("miel") << "\n";
    std::cout << "[Stock] chocolat : 0 -> " << inventaire_.at("chocolat") << "\n";

}

void Stock::afficherStocks() const {
    std::cout << "Stocks:\n";
    std::cout << "  nature: " << inventaire_.at("nature") << "\n";
    std::cout << "  grec: " << inventaire_.at("grec") << "\n";
    std::cout << "  fruits: " << inventaire_.at("fruits") << "\n";
    std::cout << "  granola: " << inventaire_.at("granola") << "\n";
    std::cout << "  miel: " << inventaire_.at("miel") << "\n";
    std::cout << "  chocolat: " << inventaire_.at("chocolat") << "\n";

}


bool Stock::retirerYogourt(TypeYogourt type) {
    return retirerArticle(toString(type));
}



bool Stock::retirerGarniture(TypeGarniture type) {
    return retirerArticle(toString(type));
}

void Stock::remettreGarniture(TypeGarniture type) {
    remettreArticle(toString(type));
}


int Stock::quantite(TypeYogourt type) const {
    return quantiteArticle(toString(type));
}

int Stock::quantite(TypeGarniture type) const {
    return quantiteArticle(toString(type));
}

int Stock::quantiteArticle(const std::string& article) const {
    auto it = inventaire_.find(article);
    if (it == inventaire_.end()) {
        return 0;

    }

    return it->second;
}

bool Stock::ajouterAbonne(const std::string& article, IStockObservateur* observateur) {
    if (!observateur || !articleValide(article)) {
        return false;
    }

    auto& liste = listesAbonnes_[article];
    if (std::find(liste.begin(), liste.end(), observateur) != liste.end()) {
        return false;

    }


    liste.push_back(observateur);
    return true;
}

bool Stock::retirerAbonne(const std::string& article, IStockObservateur* observateur) {
    auto it = listesAbonnes_.find(article);
    if (it == listesAbonnes_.end()) {
        return false;

    }

    auto& liste = it->second;
    auto avant = liste.size();


    liste.erase(
        std::remove(liste.begin(), liste.end(), observateur),
        liste.end()
    );


    return avant != liste.size();
}

bool Stock::retirerArticle(const std::string& article) {
    auto it = inventaire_.find(article);
    if (it == inventaire_.end() || it->second <= 0) {
        return false;
    }

    const int avant = it->second;
    --(it->second);
    const int apres = it->second;


    std::cout << "[Stock] " << article << " : " << avant << " -> " << apres << "\n";
    notifierTransition(article, avant, apres);
    return true;

}

void Stock::remettreArticle(const std::string& article) {
    auto it = inventaire_.find(article);
    if (it == inventaire_.end()) {
        return;
    }

    const int avant = it->second;
    ++(it->second);
    const int apres = it->second;

    std::cout << "[Stock] " << article << " : " << avant << " -> " << apres << "\n";
    notifierTransition(article, avant, apres);

}

void Stock::notifierRuptureStock(const std::string& article) {
    auto it = listesAbonnes_.find(article);
    if (it == listesAbonnes_.end()) {
        return;
    }



    for (auto* obs : it->second) {
        if (obs) {
            obs->notifierRupture(article);
        }

    }
}

void Stock::notifierRetourStock(const std::string& article) {
    auto it = listesAbonnes_.find(article);
    if (it == listesAbonnes_.end()) {
        return;
    }

    for (auto* obs : it->second) {
        if (obs) {
            obs->notifierRetour(article);
        }
    }
}

void Stock::notifierTransition(const std::string& article, int avant, int apres) {
    if (avant > 0 && apres == 0) {
        notifierRuptureStock(article);

    }
    else if (avant == 0 && apres > 0) {
        notifierRetourStock(article);
    }
}