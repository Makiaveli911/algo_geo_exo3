//
// Created by chaid on 13/12/2024.
//
#include "carte.h"
#include "triangulation.h"
#include <algorithm> // POUR LE SORT
#include <stdexcept>

#include "triangulation.h"
#include <algorithm> // pour std::sort
#include <stdexcept>

// Implémentation de la fonction triangulation
void triangulation(std::vector<Point>& T, Carte& C) {
    // Étape 1 : Trier les points par abscisses croissantes
    std::sort(T.begin(), T.end(), [](const Point& a, const Point& b) {
        return (a.x() < b.x() || (a.x() == b.x() && a.y() < b.y()));
    });

    // Vérification
    if (T.size() < 2) {
        throw std::invalid_argument("L'ensemble de points doit contenir au moins deux points !");
    }

    // Étape 2 : Construire un premier segment de base entre les deux premiers points
    DemiCote* premierDemiCote = C.ajouteCote(T[0], T[1]);
    C.changeDemiCoteParticulier(premierDemiCote);

    // Étape 3 : Ajouter les points restants à l'enveloppe convexe
    for (size_t i = 2; i < T.size(); ++i) {
        Point pointAAjouter = T[i];

        // Sens trigonométrique : trouver les côtés à droite du point
        DemiCote* courantTrigo = premierDemiCote;
        while (pointAAjouter.aGauche(courantTrigo->point(), courantTrigo->oppose()->point()) < 0) {
          DemiCote* nouveauDemiCoteTrigo = C.ajouteCote(courantTrigo->oppose(), pointAAjouter);
          courantTrigo = courantTrigo->suivant();
        }

        // Sens anti-trigonométrique : trouver les côtés à gauche du point
        DemiCote* courantAntiTrigo = premierDemiCote;
        while (pointAAjouter.aGauche(courantAntiTrigo->precedent()->point(), courantAntiTrigo->point()) > 0) {
            // Relier le pointAAjouter aux deux sommets valides
            DemiCote* nouveauDemiCote = C.ajouteCote(courantAntiTrigo, pointAAjouter);
            courantAntiTrigo = courantAntiTrigo->precedent();
        }

    }
}