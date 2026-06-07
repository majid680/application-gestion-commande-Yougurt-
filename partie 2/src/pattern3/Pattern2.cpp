#include "pattern3/Pattern3.h"

std::string EtatInitiale::nom() const {
    return "Initiale";
}



bool EtatInitiale::peutModifier() const {
    return true;
}

bool EtatInitiale::peutUndoRedo() const {
    return true;

}

bool EtatInitiale::peutPayer() const {

    return false;
}

std::string EtatInitiale::messageRefusModification() const {
    return "Modification impossible.";
}



std::string EtatInitiale::messageRefusAnnulation() const {

    return "Annulation impossible.";
}

std::string EtatPreparation::nom() const {
    return "En preparation";
}


bool EtatPreparation::peutModifier() const {
    return false;
}



bool EtatPreparation::peutUndoRedo() const {
    return false;
}


bool EtatPreparation::peutPayer() const {
    return false;
}


std::string EtatPreparation::messageRefusModification() const {
    return "Commande en preparation: modification verrouillee.";
}

std::string EtatPreparation::messageRefusAnnulation() const {


    return "Commande en preparation: annulation verrouillee.";
}

std::string EtatTerminee::nom() const {
    return "Terminee";
}


bool EtatTerminee::peutModifier() const {
    return false;
}

bool EtatTerminee::peutUndoRedo() const {
    return false;

}

bool EtatTerminee::peutPayer() const {
    return true;
}

std::string EtatTerminee::messageRefusModification() const {

    return "Commande terminee: impossible de modifier le yogourt.";
}



std::string EtatTerminee::messageRefusAnnulation() const {
    return "Commande terminee: annulation impossible.";
}
