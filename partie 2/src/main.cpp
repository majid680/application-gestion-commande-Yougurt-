#include <iostream>
#include <sstream>
#include <string>

#include "domain/Commande.h"

static void afficherAide() {

    std::cout << "Commandes:\n";
    std::cout << "  c nature|grec              -> Ajouter un yogourt (max 2)\n";
    std::cout << "  sel 1|2                    -> Selectionner le yogourt actif\n";
    std::cout << "  f                          -> Ouvrir menu garnitures du yogourt actif\n";
    std::cout << "  u                          -> Annuler derniere garniture du yogourt actif\n";
    std::cout << "  r                          -> Refaire derniere garniture du yogourt actif\n";
    std::cout << "  p                          -> Preparer la commande\n";
    std::cout << "  t                          -> Terminer la commande\n";

    std::cout << "  mode prev|eclair|poly      -> Changer le mode de paiement\n";
    std::cout << "  pay                        -> Finaliser paiement (etat Terminee requis)\n";
    std::cout << "  pay prev|eclair|poly       -> Alias mode + payer\n";
    std::cout << "  total                      -> Afficher sous-total et total projete\n";

    std::cout << "  sub article                -> S'abonner aux notifications d'un article\n";
    std::cout << "  unsub article              -> Se desabonner d'un article\n";
    std::cout << "  subs                       -> Afficher abonnements actifs\n";

    std::cout << "  clear|cls                  -> Nettoyer l'ecran\n";
    std::cout << "  s                          -> Afficher les stocks\n";
    std::cout << "  h                          -> Aide\n";
    std::cout << "  q                          -> Quitter\n";
}

static void nettoyerEcran() {
    for (int i = 0; i < 40; ++i) {
        std::cout << "\n";
    }
}

static void menuGarnitures(Commande& commande) {
    if (!commande.aYogourtActif()) {
        std::cout << "Aucun yogourt actif.\n";

        return;
    }



    while (true) {
        std::cout << "\nMenu Garnitures\n";
        std::cout << "  Yogourt actif: #" << commande.indexActifHumain() << "\n";
        std::cout << "  1 -> fruits   (" << commande.getStock().quantite(TypeGarniture::Fruits) << " en stock)\n";
        std::cout << "  2 -> granola  (" << commande.getStock().quantite(TypeGarniture::Granola) << " en stock)\n";
        std::cout << "  3 -> miel     (" << commande.getStock().quantite(TypeGarniture::Miel) << " en stock)\n";
        std::cout << "  4 -> chocolat (" << commande.getStock().quantite(TypeGarniture::Chocolat) << " en stock)\n";
        std::cout << "  q -> retour menu principal\n";
        std::cout << "Choix garniture: ";

        std::string choix;
        std::getline(std::cin, choix);

        if (choix == "q") {
            std::cout << "Retour au menu principal.\n";

            return;
        }
        if (choix == "1") {
            commande.ajouterGarniture(TypeGarniture::Fruits);

            continue;
        }
        if (choix == "2") {
            commande.ajouterGarniture(TypeGarniture::Granola);

            continue;
        }
        if (choix == "3") {
            commande.ajouterGarniture(TypeGarniture::Miel);
            continue;

        }
        if (choix == "4") {

            commande.ajouterGarniture(TypeGarniture::Chocolat);
            continue;
        }

        std::cout << "Choix invalide.\n";

    }
}

int main() {
    Commande commande;
    commande.getStock().afficherChargementInitial();

    std::cout << "Bienvenue sur TonYogourt\n";

    afficherAide();

    while (true) {
        commande.afficherResume();

        std::cout << "\nCommande: ";
        std::string ligne;

        if (!std::getline(std::cin, ligne)) {
            break;
        }

        std::istringstream iss(ligne);
        std::string cmd;
        std::string arg;
        iss >> cmd >> arg;

        if (cmd.empty()) {
            continue;

        }

        if (cmd == "q") {
            break;
        }
        else if (cmd == "h") {
            afficherAide();
        }
        else if (cmd == "clear" || cmd == "cls") {
            nettoyerEcran();

        }
        else if (cmd == "s") {
            commande.getStock().afficherStocks();
        }
        else if (cmd == "c") {
            if (arg == "nature") {

                commande.ajouterYogourt(TypeYogourt::Nature);
            }
            else if (arg == "grec") {
                commande.ajouterYogourt(TypeYogourt::Grec);
            }
            else {
                std::cout << "Commande inconnue.\n";

            }
        }
        else if (cmd == "sel") {
            if (arg == "1") {
                commande.selectionner(1);

            }

            else if (arg == "2") {
                commande.selectionner(2);

            }
            else {
                std::cout << "Commande inconnue.\n";
            }
        }
        else if (cmd == "f") {
            menuGarnitures(commande);
        }
        else if (cmd == "u") {

            commande.undo();

        }
        else if (cmd == "r") {

            commande.redo();
        }
        else if (cmd == "p") {
            commande.preparer();
        }
        else if (cmd == "t") {

            commande.terminer();
        }

        else if (cmd == "mode") {
            if (!commande.changerMode(arg)) {

                std::cout << "Commande inconnue.\n";
            }
        }
        else if (cmd == "pay") {
            if (arg.empty()) {
                commande.payer();

            }
            else {
                commande.payerAvecMode(arg);
            }
        }
        else if (cmd == "total") {
            commande.afficherTotal();
        }
        else if (cmd == "sub") {
            commande.abonnerArticle(arg);

        }

        else if (cmd == "unsub") {

            commande.desabonnerArticle(arg);
        }
        else if (cmd == "subs") {

            commande.afficherAbonnements();
        }
        else {

            std::cout << "Commande inconnue.\n";

        }
    }

    return 0;
}