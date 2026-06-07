#include "domain/Observer.h"

#include <iostream>

std::vector<std::string> listeArticlesValides() {
    return { "nature", "grec", "fruits", "granola", "miel", "chocolat" };

}


bool articleValide(const std::string& article) {
    for (const auto& a : listeArticlesValides()) {
        if (a == article) {

            return true;
        }
    }
    return false;
}


bool AbonneConsole::ajouterArticle(const std::string& article) {
    if (!articleValide(article)) {

        return false;
    }
    return abonnements_.insert(article).second;
}

bool AbonneConsole::retirerArticle(const std::string& article) {
    return abonnements_.erase(article) > 0;
}

bool AbonneConsole::estAbonne(const std::string& article) const {
    return abonnements_.find(article) != abonnements_.end();
}



void AbonneConsole::afficherAbonnements() const {
    std::cout << "Abonnements actifs:\n";
    if (abonnements_.empty()) {
        std::cout << "  (aucun)\n";
        return;
    }

    for (const auto& article : abonnements_) {
        std::cout << "  - " << article << "\n";
    }
}

void AbonneConsole::notifierRupture(const std::string& article) {
    std::cout << "[Notif Abonne] Rupture de stock pour '" << article << "'.\n";
}



void AbonneConsole::notifierRetour(const std::string& article) {
    std::cout << "[Notif Abonne] '" << article << "' est de retour en stock.\n";
}