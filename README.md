# application-gestion-commande-Yougurt
Markdown
# TonYogourt - Système de Gestion de Commandes

Une application en ligne de commande (CLI) robuste développée en C++ pour gérer les opérations d'une yogourterie. Ce projet met de l'avant des principes de programmation orientée objet et des patrons de conception.

## Fonctionnalités Principales

* **Prise de commande interactive :** Sélection du type de yogourt (Nature, Grec) et ajout de garnitures (fruits, granola, miel, chocolat).
* **Historique des actions :** Implémentation de commandes `Undo` et `Redo` pour annuler ou refaire l'ajout de garnitures sans erreur.
* **Gestion des stocks et notifications :** Suivi de l'inventaire en temps réel avec un système d'abonnement (Publish-Subscribe) pour alerter lors de la rupture ou du réapprovisionnement d'un article.
* **Système de facturation :** Prise en charge de différents modes de paiement, calcul du sous-total et du total projeté.

## Technologies Utilisées

* **Langage :** C++
* **Interface :** Ligne de commande (CLI)
* **Concepts mis en valeur :** Programmation Orientée Objet (POO), Patrons de conception (
