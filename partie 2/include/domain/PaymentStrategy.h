#pragma once

#include <memory>
#include <string>

class IModePaiement {
public:
    virtual ~IModePaiement() = default;

    virtual double calculerTotal(double sousTotal) const = 0;
    virtual std::string getNom() const = 0;
    virtual std::string getLibelleTotal() const = 0;

    virtual bool estAucun() const { return false; }
};

class ModeAucun : public IModePaiement {
public:
    double calculerTotal(double sousTotal) const override;
    std::string getNom() const override;

    std::string getLibelleTotal() const override;
    bool estAucun() const override { return true; }
};

class ModePrevente : public IModePaiement {
public:
    double calculerTotal(double sousTotal) const override;
    std::string getNom() const override;

    std::string getLibelleTotal() const override;
};

class ModeEclair : public IModePaiement {
public:
    double calculerTotal(double sousTotal) const override;

    std::string getNom() const override;

    std::string getLibelleTotal() const override;
};

class ModePoly : public IModePaiement {
public:
    double calculerTotal(double sousTotal) const override;

    std::string getNom() const override;
    std::string getLibelleTotal() const override;
};

std::unique_ptr<IModePaiement> creerModePaiement(const std::string& code);