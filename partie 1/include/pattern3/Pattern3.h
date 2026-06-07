#pragma once
#include <string>
// -- TODO : Changer le nom de la classe du fichier et puis ajouter toutes les méthodes nécessaires pour cette composante 
// Composante = Patron de conception, classe, etc etc
class EtatCommande {
public:
    virtual ~EtatCommande() = default;

    virtual std::string nom() const = 0;
    virtual bool peutModifier() const = 0;
    virtual bool peutUndoRedo() const = 0;
    virtual bool peutPayer() const = 0;

    virtual std::string messageRefusModification() const = 0;
    virtual std::string messageRefusAnnulation() const = 0;
};

class EtatInitiale : public EtatCommande {
public:
    std::string nom() const override;
    bool peutModifier() const override;
    bool peutUndoRedo() const override;
    bool peutPayer() const override;
    std::string messageRefusModification() const override;
    std::string messageRefusAnnulation() const override;
};

class EtatPreparation : public EtatCommande {
public:
    std::string nom() const override;
    bool peutModifier() const override;
    bool peutUndoRedo() const override;
    bool peutPayer() const override;
    std::string messageRefusModification() const override;
    std::string messageRefusAnnulation() const override;
};

class EtatTerminee : public EtatCommande {
public:
    std::string nom() const override;
    bool peutModifier() const override;
    bool peutUndoRedo() const override;
    bool peutPayer() const override;
    std::string messageRefusModification() const override;
    std::string messageRefusAnnulation() const override;
};