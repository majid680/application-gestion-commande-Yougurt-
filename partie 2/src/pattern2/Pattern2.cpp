#include "pattern2/Pattern2.h"
#include "pattern1/Pattern1.h"
#include "domain/Stock.h"

YogourtCourant::YogourtCourant(TypeYogourt base) : base_(base) {}

std::string YogourtCourant::description() const {
    return construireYogourt(base_, garnitures_)->getDescription();

}

double YogourtCourant::prix() const {
    return construireYogourt(base_, garnitures_)->getPrix();


}

bool YogourtCourant::ajouterGarnitureBrut(TypeGarniture garniture) {
    garnitures_.push_back(garniture);
    return true;

}

bool YogourtCourant::retirerDerniereGarnitureBrut() {
    if (garnitures_.empty()) {

        return false;
    }
    garnitures_.pop_back();
    return true;
}

bool YogourtCourant::executerCommande(std::unique_ptr<ICommandeYogourt> commande) {
    if (!commande || !commande->executer()) {
        return false;

    }

    redoStack_.clear();
    undoStack_.push_back(std::move(commande));
    return true;


}

bool YogourtCourant::undo() {
    if (undoStack_.empty()) {


        return false;
    }

    auto commande = std::move(undoStack_.back());
    undoStack_.pop_back();

    if (!commande->annuler()) {
        return false;

    }

    redoStack_.push_back(std::move(commande));
    return true;
}

bool YogourtCourant::redo() {

    if (redoStack_.empty()) {
        return false;
    }

    auto commande = std::move(redoStack_.back());
    redoStack_.pop_back();

    if (!commande->retablir()) {
        return false;
    }


    undoStack_.push_back(std::move(commande));
    return true;
}



AjoutGarnitureCommande::AjoutGarnitureCommande(
    YogourtCourant& yogourt,

    Stock& stock,
    TypeGarniture type
) : yogourt_(yogourt), stock_(stock), type_(type) {

}

bool AjoutGarnitureCommande::executer() {
    if (!stock_.retirerGarniture(type_)) {

        return false;
    }
    return yogourt_.ajouterGarnitureBrut(type_);
}

bool AjoutGarnitureCommande::annuler() {
    if (!yogourt_.retirerDerniereGarnitureBrut()) {

        return false;

    }
    stock_.remettreGarniture(type_);
    return true;

}



bool AjoutGarnitureCommande::retablir() {
    if (!stock_.retirerGarniture(type_)) {


        return false;
    }
    return yogourt_.ajouterGarnitureBrut(type_);
}



AjoutFruitsCmd::AjoutFruitsCmd(YogourtCourant& yogourt, Stock& stock)
    : AjoutGarnitureCommande(yogourt, stock, TypeGarniture::Fruits) {
}


AjoutGranolaCmd::AjoutGranolaCmd(YogourtCourant& yogourt, Stock& stock)
    : AjoutGarnitureCommande(yogourt, stock, TypeGarniture::Granola) {
}

AjoutMielCmd::AjoutMielCmd(YogourtCourant& yogourt, Stock& stock)
    : AjoutGarnitureCommande(yogourt, stock, TypeGarniture::Miel) {

}

AjoutChocolatCmd::AjoutChocolatCmd(YogourtCourant& yogourt, Stock& stock)

    : AjoutGarnitureCommande(yogourt, stock, TypeGarniture::Chocolat) {

}