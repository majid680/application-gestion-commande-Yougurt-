#pragma once
#include <iomanip>
#include <sstream>
#include <string>

enum class TypeYogourt { Nature, Grec };
enum class TypeGarniture { Fruits, Granola, Miel, Chocolat };
enum class ModePaiement { Aucun, Prevente, Eclair };

inline std::string toString(TypeYogourt type) {
    switch (type) {
    case TypeYogourt::Nature: return "nature";
    case TypeYogourt::Grec: return "grec";
    }
    return "";
}

inline std::string toString(TypeGarniture type) {
    switch (type) {
    case TypeGarniture::Fruits: return "fruits";
    case TypeGarniture::Granola: return "granola";
    case TypeGarniture::Miel: return "miel";
    case TypeGarniture::Chocolat: return "chocolat";
    }
    return "";
}

inline double prixYogourt(TypeYogourt type) {
    return (type == TypeYogourt::Nature) ? 2.00 : 2.50;
}

inline double prixGarniture(TypeGarniture type) {
    switch (type) {
    case TypeGarniture::Fruits: return 1.00;
    case TypeGarniture::Granola: return 0.80;
    case TypeGarniture::Miel: return 0.60;
    case TypeGarniture::Chocolat: return 0.90;
    }
    return 0.0;
}

inline std::string formatPrix(double valeur) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << valeur;
    return oss.str();
}

inline std::string labelModePaiement(ModePaiement mode) {
    switch (mode) {

    case ModePaiement::Aucun: return "Aucune";

    case ModePaiement::Prevente: return "Prevente (-10%)";

    case ModePaiement::Eclair: return "Vente eclair (+1.50)";

    }
    return "";
}

inline std::string labelTotalPaiement(ModePaiement mode) {
    switch (mode) {
    case ModePaiement::Aucun: return "Aucun mode";
    case ModePaiement::Prevente: return "Total avec Prevente (-10%)";

    case ModePaiement::Eclair: return "Total avec Vente eclair (+1.50)";
    }
    return "";
}