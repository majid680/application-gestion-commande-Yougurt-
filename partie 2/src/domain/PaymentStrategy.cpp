#include "domain/PaymentStrategy.h"

#include <algorithm>

double ModeAucun::calculerTotal(double sousTotal) const {
    return sousTotal;
}

std::string ModeAucun::getNom() const {
    return "Aucune";
}

std::string ModeAucun::getLibelleTotal() const {
    return "Aucun mode";
}

double ModePrevente::calculerTotal(double sousTotal) const {
    return sousTotal * 0.90;
}

std::string ModePrevente::getNom() const {
    return "Prevente (-10%)";
}

std::string ModePrevente::getLibelleTotal() const {
    return "Total avec Prevente (-10%)";
}

double ModeEclair::calculerTotal(double sousTotal) const {
    return sousTotal + 1.50;
}

std::string ModeEclair::getNom() const {
    return "Vente eclair (+1.50)";
}

std::string ModeEclair::getLibelleTotal() const {
    return "Total avec Vente eclair (+1.50)";
}

double ModePoly::calculerTotal(double sousTotal) const {
    return std::max(0.0, sousTotal - 2.00);
}

std::string ModePoly::getNom() const {
    return "Coupon Poly (-2.00)";
}

std::string ModePoly::getLibelleTotal() const {
    return "Total avec Coupon Poly (-2.00)";
}

std::unique_ptr<IModePaiement> creerModePaiement(const std::string& code) {
    if (code == "prev") {
        return std::make_unique<ModePrevente>();
    }
    if (code == "eclair") {
        return std::make_unique<ModeEclair>();
    }
    if (code == "poly") {
        return std::make_unique<ModePoly>();
    }
    if (code == "aucun") {
        return std::make_unique<ModeAucun>();
    }
    return nullptr;
}