#pragma once

#include <map>
#include <string>
#include <vector>

#include "common/Types.h"

#include "domain/Observer.h"

class Stock : public ISujet {
public:
    Stock();

    void afficherChargementInitial() const;
    void afficherStocks() const;

    bool retirerYogourt(TypeYogourt type);
    bool retirerGarniture(TypeGarniture type);
    void remettreGarniture(TypeGarniture type);


    int quantite(TypeYogourt type) const;
    int quantite(TypeGarniture type) const;
    int quantiteArticle(const std::string& article) const;



    bool ajouterAbonne(const std::string& article, IStockObservateur* observateur) override;
    bool retirerAbonne(const std::string& article, IStockObservateur* observateur) override;

private:
    std::map<std::string, int> inventaire_;
    std::map<std::string, std::vector<IStockObservateur*>> listesAbonnes_;

    bool retirerArticle(const std::string& article);

    void remettreArticle(const std::string& article);


    void notifierRuptureStock(const std::string& article);
    void notifierRetourStock(const std::string& article);


    void notifierTransition(const std::string& article, int avant, int apres);
};