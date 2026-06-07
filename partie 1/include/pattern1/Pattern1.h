#pragma once
#include <memory>
#include <string>
#include <vector>
#include "common/Types.h"

// -- TODO : Changer le nom de la classe du fichier et puis ajouter toutes les méthodes nécessaires pour cette composante 
// Composante = Patron de conception, classe, etc etc
class IYogourt {
public:

    virtual ~IYogourt() = default;
    virtual double getPrix() const = 0;
    virtual std::string getDescription() const = 0;

};


class YogourtNature : public IYogourt {
public:
    double getPrix() const override;

    std::string getDescription() const override;
};


class YogourtGrec : public IYogourt {
public:

    double getPrix() const override;
    std::string getDescription() const override;
};


class GarnitureDecorator : public IYogourt {
public:
    explicit GarnitureDecorator(std::unique_ptr<IYogourt> composant);

protected:
    std::unique_ptr<IYogourt> composant_;
};



class FruitsDecorator : public GarnitureDecorator {
public:
    using GarnitureDecorator::GarnitureDecorator;
    double getPrix() const override;
    std::string getDescription() const override;
};





class GranolaDecorator : public GarnitureDecorator {

public:
    using GarnitureDecorator::GarnitureDecorator;
    double getPrix() const override;
    std::string getDescription() const override;
};


class MielDecorator : public GarnitureDecorator {
public:

    using GarnitureDecorator::GarnitureDecorator;
    double getPrix() const override;
    std::string getDescription() const override;
};

class ChocolatDecorator : public GarnitureDecorator {

public:

    using GarnitureDecorator::GarnitureDecorator;
    double getPrix() const override;
    std::string getDescription() const override;

};

std::unique_ptr<IYogourt> construireYogourt(
    TypeYogourt base,

    const std::vector<TypeGarniture>& garnitures
);