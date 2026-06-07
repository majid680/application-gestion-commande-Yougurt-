#pragma once

#include <memory>
#include <vector>

#include "domain/Observer.h"
#include "domain/PaymentStrategy.h"
#include "domain/Stock.h"
#include "pattern2/Pattern2.h"
#include "pattern3/Pattern3.h"

class Commande {
public:
    Commande();

    void afficherResume() const;
    void afficherTotal() const;

    bool ajouterYogourt(TypeYogourt type);
    bool selectionner(std::size_t indexHumain);
    bool ajouterGarniture(TypeGarniture type);

    bool undo();
    bool redo();

    bool preparer();
    bool terminer();

    bool changerMode(const std::string& code);
    bool payer();
    bool payerAvecMode(const std::string& code);

    bool abonnerArticle(const std::string& article);
    bool desabonnerArticle(const std::string& article);
    void afficherAbonnements() const;

    Stock& getStock();
    const Stock& getStock() const;

    bool aYogourtActif() const;
    std::size_t indexActifHumain() const;

private:
    std::vector<std::unique_ptr<YogourtCourant>> yogourts_;
    std::size_t actif_;
    std::unique_ptr<EtatCommande> etat_;
    std::unique_ptr<IModePaiement> modePaiement_;
    Stock stock_;
    AbonneConsole abonneConsole_;

    YogourtCourant* yogourtActif();
    const YogourtCourant* yogourtActif() const;

    double sousTotal() const;
    double totalProjete() const;
};