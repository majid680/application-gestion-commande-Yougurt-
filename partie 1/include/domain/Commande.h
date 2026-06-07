#pragma once
#include <memory>
#include <vector>
#include "common/Types.h"
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

    void changerMode(ModePaiement mode);
    bool payer();
    bool payerAvecMode(ModePaiement mode);

    Stock& getStock();
    const Stock& getStock() const;



    bool aYogourtActif() const;
    std::size_t indexActifHumain() const;


private:
    std::vector<std::unique_ptr<YogourtCourant>> yogourts_;
    std::size_t actif_;
    std::unique_ptr<EtatCommande> etat_;
    ModePaiement mode_;
    Stock stock_;



    YogourtCourant* yogourtActif();
    const YogourtCourant* yogourtActif() const;


    double sousTotal() const;
    double totalProjete() const;
};