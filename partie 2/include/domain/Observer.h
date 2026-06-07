#pragma once

#include <set>
#include <string>
#include <vector>

class IStockObservateur {
public:
    virtual ~IStockObservateur() = default;
    virtual void notifierRupture(const std::string& article) = 0;
    virtual void notifierRetour(const std::string& article) = 0;
};

class ISujet {
public:
    virtual ~ISujet() = default;
    virtual bool ajouterAbonne(const std::string& article, IStockObservateur* observateur) = 0;
    virtual bool retirerAbonne(const std::string& article, IStockObservateur* observateur) = 0;
};

class AbonneConsole : public IStockObservateur {
public:
    bool ajouterArticle(const std::string& article);
    bool retirerArticle(const std::string& article);
    bool estAbonne(const std::string& article) const;

    void afficherAbonnements() const;

    void notifierRupture(const std::string& article) override;
    void notifierRetour(const std::string& article) override;

private:
    std::set<std::string> abonnements_;
};

bool articleValide(const std::string& article);
std::vector<std::string> listeArticlesValides();