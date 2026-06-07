#pragma once
#include <memory>
#include <string>
#include <vector>
#include "common/Types.h"

// -- TODO : Changer le nom de la classe du fichier et puis ajouter toutes les méthodes nécessaires pour cette composante 
// Composante = Patron de conception, classe, etc etc
class Stock;

class ICommandeYogourt {

public:
    virtual ~ICommandeYogourt() = default;
    virtual bool executer() = 0;
    virtual bool annuler() = 0;
    virtual bool retablir() = 0;

};



class YogourtCourant {
public:
    explicit YogourtCourant(TypeYogourt base);

    std::string description() const;
    double prix() const;

    bool executerCommande(std::unique_ptr<ICommandeYogourt> commande);
    bool undo();
    bool redo();

    bool ajouterGarnitureBrut(TypeGarniture garniture);
    bool retirerDerniereGarnitureBrut();

private:

    TypeYogourt base_;
    std::vector<TypeGarniture> garnitures_;
    std::vector<std::unique_ptr<ICommandeYogourt>> undoStack_;
    std::vector<std::unique_ptr<ICommandeYogourt>> redoStack_;
};


class AjoutGarnitureCommande : public ICommandeYogourt {
public:

    AjoutGarnitureCommande(YogourtCourant& yogourt, Stock& stock, TypeGarniture type);

    bool executer() override;
    bool annuler() override;
    bool retablir() override;


protected:
    YogourtCourant& yogourt_;
    Stock& stock_;
    TypeGarniture type_;
};


class AjoutFruitsCmd : public AjoutGarnitureCommande {

public:
    AjoutFruitsCmd(YogourtCourant& yogourt, Stock& stock);
};

class AjoutGranolaCmd : public AjoutGarnitureCommande {
public:

    AjoutGranolaCmd(YogourtCourant& yogourt, Stock& stock);

};



class AjoutMielCmd : public AjoutGarnitureCommande {
public:
    AjoutMielCmd(YogourtCourant& yogourt, Stock& stock);

};


class AjoutChocolatCmd : public AjoutGarnitureCommande {
public:
    AjoutChocolatCmd(YogourtCourant& yogourt, Stock& stock);
};