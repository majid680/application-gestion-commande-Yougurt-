#include "domain/Commande.h"

#include <iostream>

Commande::Commande()
    : actif_(0),
    etat_(std::make_unique<EtatInitiale>()),
    modePaiement_(std::make_unique<ModeAucun>()),
    stock_(),
    abonneConsole_() {
}

Stock& Commande::getStock() {
    return stock_;
}

const Stock& Commande::getStock() const {
    return stock_;
}


bool Commande::aYogourtActif() const {
    return !yogourts_.empty();
}


std::size_t Commande::indexActifHumain() const {
    return yogourts_.empty() ? 0 : actif_ + 1;
}


YogourtCourant* Commande::yogourtActif() {
    if (yogourts_.empty()) {

        return nullptr;
    }
    return yogourts_[actif_].get();
}


const YogourtCourant* Commande::yogourtActif() const {
    if (yogourts_.empty()) {

        return nullptr;
    }
    return yogourts_[actif_].get();
}


double Commande::sousTotal() const {
    double total = 0.0;
    for (const auto& y : yogourts_) {

        total += y->prix();
    }

    return total;
}



double Commande::totalProjete() const {
    return modePaiement_->calculerTotal(sousTotal());
}



void Commande::afficherResume() const {
    std::cout << "\nPhase: " << etat_->nom() << "\n";

    if (yogourts_.empty()) {
        std::cout << "Yogourts: aucun\n";
    }

    else {
        for (std::size_t i = 0; i < yogourts_.size(); ++i) {

            std::cout << "Yogourt #" << (i + 1);
            if (i == actif_) {

                std::cout << " (actif)";
            }
            std::cout << ": " << yogourts_[i]->description()

                << " | Prix: " << formatPrix(yogourts_[i]->prix()) << " CAD\n";
        }
    }


    std::cout << "Sous-total commande: " << formatPrix(sousTotal()) << " CAD\n";

    std::cout << "Paiement: ";
    if (modePaiement_->estAucun()) {

        std::cout << "Aucune | choisir un mode de paiement | "

            << (etat_->peutPayer() ? "payable" : "non payable") << "\n";
    }
    else {
        std::cout << modePaiement_->getNom()
            << " | Total projete: " << formatPrix(totalProjete()) << " CAD | "

            << (etat_->peutPayer() ? "payable" : "non payable") << "\n";

    }
}

void Commande::afficherTotal() const {
    std::cout << "Sous-total: " << formatPrix(sousTotal()) << " CAD\n";


    if (modePaiement_->estAucun()) {
        std::cout << "Aucun mode de paiement actif.\n";
        return;
    }


    std::cout << modePaiement_->getLibelleTotal() << ": "

        << formatPrix(totalProjete()) << " CAD\n";
}

bool Commande::ajouterYogourt(TypeYogourt type) {
    if (!etat_->peutModifier()) {
        std::cout << etat_->messageRefusModification() << "\n";

        return false;
    }

    if (yogourts_.size() >= 2) {
        std::cout << "Maximum de 2 yogourts par commande.\n";

        return false;
    }

    if (!stock_.retirerYogourt(type)) {
        std::cout << "Stock insuffisant pour " << toString(type) << ".\n";


        return false;
    }

    yogourts_.push_back(std::make_unique<YogourtCourant>(type));
    actif_ = yogourts_.size() - 1;

    std::cout << "Yogourt " << toString(type) << " selectionne.\n";

    return true;
}

bool Commande::selectionner(std::size_t indexHumain) {
    if (indexHumain == 0 || indexHumain > yogourts_.size()) {


        std::cout << "Selection invalide.\n";
        return false;
    }

    actif_ = indexHumain - 1;
    return true;
}

bool Commande::ajouterGarniture(TypeGarniture type) {
    if (!etat_->peutModifier()) {


        std::cout << etat_->messageRefusModification() << "\n";
        return false;
    }

    auto* y = yogourtActif();
    if (!y) {


        std::cout << "Aucun yogourt actif.\n";
        return false;
    }

    std::unique_ptr<ICommandeYogourt> cmd;

    switch (type) {


    case TypeGarniture::Fruits:
        cmd = std::make_unique<AjoutFruitsCmd>(*y, stock_);
        break;

    case TypeGarniture::Granola:
        cmd = std::make_unique<AjoutGranolaCmd>(*y, stock_);
        break;


    case TypeGarniture::Miel:
        cmd = std::make_unique<AjoutMielCmd>(*y, stock_);
        break;

    case TypeGarniture::Chocolat:
        cmd = std::make_unique<AjoutChocolatCmd>(*y, stock_);
        break;

    }

    if (!y->executerCommande(std::move(cmd))) {
        std::cout << "Stock insuffisant pour la garniture '" << toString(type) << "'.\n";
        return false;
    }

    std::cout << "Garniture '" << toString(type) << "' ajoutee.\n";
    return true;
}

bool Commande::undo() {
    if (!etat_->peutUndoRedo()) {
        std::cout << etat_->messageRefusAnnulation() << "\n";
        return false;
    }

    auto* y = yogourtActif();
    if (!y || !y->undo()) {


        std::cout << "Aucune garniture a annuler.\n";
        return false;
    }


    std::cout << "Derniere garniture annulee.\n";
    return true;

}

bool Commande::redo() {
    if (!etat_->peutUndoRedo()) {
        std::cout << etat_->messageRefusAnnulation() << "\n";
        return false;

    }

    auto* y = yogourtActif();
    if (!y || !y->redo()) {
        std::cout << "Aucune garniture a refaire.\n";
        return false;
    }

    std::cout << "Garniture retablie.\n";

    return true;
}

bool Commande::preparer() {
    if (etat_->nom() == "Terminee") {
        std::cout << "Commande deja terminee.\n";

        return false;
    }

    if (etat_->nom() == "En preparation") {
        std::cout << "Preparation deja en cours.\n";

        return false;

    }

    if (yogourts_.empty()) {
        std::cout << "Impossible de preparer sans yogourt.\n";

        return false;
    }

    etat_ = std::make_unique<EtatPreparation>();
    std::cout << "Preparation en cours...\n";

    return true;
}

bool Commande::terminer() {
    if (etat_->nom() == "Terminee") {
        std::cout << "Commande deja terminee.\n";

        return false;

    }

    if (etat_->nom() != "En preparation") {
        std::cout << "La commande doit etre preparee avant d'etre terminee.\n";

        return false;

    }

    etat_ = std::make_unique<EtatTerminee>();
    std::cout << "Commande terminee.\n";

    return true;
}

bool Commande::changerMode(const std::string& code) {
    auto nouveauMode = creerModePaiement(code);
    if (!nouveauMode) {
        std::cout << "Mode de paiement invalide.\n";


        return false;
    }

    modePaiement_ = std::move(nouveauMode);
    std::cout << "Mode de paiement actif: " << modePaiement_->getNom() << ".\n";

    return true;
}

bool Commande::payer() {
    if (!etat_->peutPayer()) {
        std::cout << "Paiement refuse: etat Terminee requis (etat actuel: "

            << etat_->nom() << ").\n";
        return false;
    }

    if (modePaiement_->estAucun()) {
        std::cout << "Paiement refuse: choisissez d'abord un mode (mode prev|eclair|poly).\n";

        return false;
    }

    std::cout << "Paiement accepte (" << modePaiement_->getNom()
        << ") | Montant: " << formatPrix(totalProjete()) << " CAD\n";
    std::cout << "Merci pour votre achat. A bientot!\n";

    return true;
}

bool Commande::payerAvecMode(const std::string& code) {
    if (!changerMode(code)) {
        return false;

    }
    return payer();
}

bool Commande::abonnerArticle(const std::string& article) {
    if (!articleValide(article)) {

        std::cout << "Article invalide.\n";
        return false;
    }

    abonneConsole_.ajouterArticle(article);
    stock_.ajouterAbonne(article, &abonneConsole_);

    std::cout << "[Abonnement] Notifications actives pour '" << article << "'.\n";

    return true;
}

bool Commande::desabonnerArticle(const std::string& article) {
    if (!articleValide(article)) {
        std::cout << "Article invalide.\n";

        return false;
    }

    abonneConsole_.retirerArticle(article);
    stock_.retirerAbonne(article, &abonneConsole_);

    std::cout << "[Abonnement] Desabonne de '" << article << "'.\n";

    return true;
}

void Commande::afficherAbonnements() const {

    abonneConsole_.afficherAbonnements();
}