#include "pattern1/Pattern1.h"

double YogourtNature::getPrix() const {
    return 2.00;
}



std::string YogourtNature::getDescription() const {
    return "Yogourt nature";
}

double YogourtGrec::getPrix() const {
    return 2.50;
}



std::string YogourtGrec::getDescription() const {
    return "Yogourt grec";
}

GarnitureDecorator::GarnitureDecorator(std::unique_ptr<IYogourt> composant)
    : composant_(std::move(composant)) {
}


double FruitsDecorator::getPrix() const {
    return composant_->getPrix() + 1.00;
}

std::string FruitsDecorator::getDescription() const {
    return composant_->getDescription() + " + fruits";
}

double GranolaDecorator::getPrix() const {
    return composant_->getPrix() + 0.80;
}

std::string GranolaDecorator::getDescription() const {
    return composant_->getDescription() + " + granola";
}



double MielDecorator::getPrix() const {
    return composant_->getPrix() + 0.60;
}

std::string MielDecorator::getDescription() const {
    return composant_->getDescription() + " + miel";
}

double ChocolatDecorator::getPrix() const {
    return composant_->getPrix() + 0.90;
}



std::string ChocolatDecorator::getDescription() const {
    return composant_->getDescription() + " + chocolat";
}

std::unique_ptr<IYogourt> construireYogourt(
    TypeYogourt base,
    const std::vector<TypeGarniture>& garnitures
) {


    std::unique_ptr<IYogourt> resultat;

    if (base == TypeYogourt::Nature) {
        resultat = std::make_unique<YogourtNature>();
    }
    else {
        resultat = std::make_unique<YogourtGrec>();
    }

    for (TypeGarniture g : garnitures) {
        switch (g) {
        case TypeGarniture::Fruits:
            resultat = std::make_unique<FruitsDecorator>(std::move(resultat));
            break;
        case TypeGarniture::Granola:
            resultat = std::make_unique<GranolaDecorator>(std::move(resultat));
            break;
        case TypeGarniture::Miel:
            resultat = std::make_unique<MielDecorator>(std::move(resultat));
            break;
        case TypeGarniture::Chocolat:
            resultat = std::make_unique<ChocolatDecorator>(std::move(resultat));
            break;
        }
    }



    return resultat;
}