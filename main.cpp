#include "point.h"
#include "carte.h"
#include "affichage.h"
#include "triangulation.h"
#include <iostream>

int main() {
    try{
    // Initialiser une carte
    Carte carte;

    // Ajouter des points pour les sommets
        Point p1(100, 100);
        Point p2(300, 100);
        Point p3(200, 300);


    // Ajouter ces points dans un vecteur
    std::vector<Point> points = {p1, p2, p3};
    triangulation(points, carte);

    // Afficher un message de succès
    std::cout << "Triangulation réalisée avec succès !" << std::endl;

    trace(carte);


} catch (const std::exception& e) {
    // Gérer les exceptions
    std::cerr << "Erreur : " << e.what() << std::endl;
}

    return 0;

    }