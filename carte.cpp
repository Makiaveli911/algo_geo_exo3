#include <vector>
using namespace std;

#include "carte.h"
#include "point.h"


// Destructeur
Carte::~Carte()
{
	// Supprimer tous les sommets du tableau
	for (Sommet* sommet : tableauSommets) {
		delete sommet;
	}
	// Vide le tableau des sommets pour éviter les pointeurs invalides
	tableauSommets.clear();

	// Supprimer tous les demi-côtés du tableau
	for (DemiCote* demiCote : tableauDemiCote) {
		delete demiCote;
	}
	tableauDemiCote.clear();  // Vide le tableau des demi-côtés pour éviter les pointeurs invalides

	// Supprimer le demi-côté particulier s'il est non nul
	// (Seulement si `demiCoteParticulier` ne fait pas partie de `tableauDemiCote`)
	if (demiCoteParticulier != nullptr) {
		delete demiCoteParticulier;
		demiCoteParticulier = nullptr;
	}
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
// dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
// On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, DemiCote* precedent2)
{
	// Créer les deux demi-côtés
	DemiCote* dc1 = new DemiCote(nullptr, precedent1, nullptr, precedent1->demiCoteSommet, tailleTableauDemiCotes());
	// Ajout du nouveau demi-côtés dans le tableau
	tableauDemiCote.push_back(dc1);
	DemiCote* dc2 = new DemiCote(nullptr, precedent2, dc1, precedent2->demiCoteSommet, tailleTableauDemiCotes());
	// Ajout du nouveau demi-côtés dans le tableau
	tableauDemiCote.push_back(dc2);

	// Relier dc1 et dc2 comme opposés
	dc1->demiCoteOppose = dc2;
	dc2->demiCoteOppose = dc1;

	// Mis a jour des precedents
	precedent1->demiCoteSuivant = dc1;
	precedent2->demiCoteSuivant = dc2;

	// Ajout des nouveaux demi-côtés dans le tableau
	tableauDemiCote.push_back(dc1);
	tableauDemiCote.push_back(dc2);

	// Retourner l'adresse de dc1
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
// On suppose precedent1 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, const Point& p2)
{
	// Créer les deux demi-côtés
	DemiCote* dc1 = new DemiCote(nullptr, precedent1, nullptr, precedent1->demiCoteSommet, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc1);
	DemiCote* dc2 = new DemiCote(nullptr, nullptr, dc1, nullptr, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc2);
	Sommet* NouveauSommet = new Sommet(p2,dc2,tailleTableauSommets());
	dc2->demiCoteSommet=NouveauSommet;

	// Relier dc1 et dc2 comme opposés
	dc1->demiCoteOppose = dc2;
	dc2->demiCoteOppose = dc1;

	//ajout du nouveau sommet au tableau
	tableauSommets.push_back(NouveauSommet);

	//mis a jour du coté suivant pour precedent1
	precedent1->demiCoteSuivant = dc1;


	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
// On suppose precedent2 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, DemiCote* precedent2)
{
	// Créer le demi-côté dc2 lié à precedent2
	DemiCote* dc2 = new DemiCote(nullptr, precedent2, nullptr, precedent2->demiCoteSommet, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc2);

	// Créer le demi-côté dc1 opposé à dc2
	DemiCote* dc1 = new DemiCote(nullptr, nullptr, dc2, nullptr, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc1);

	// Créer un nouveau sommet pour dc1 avec les coordonnées de p1
	Sommet* NouveauSommet = new Sommet(p1,dc1,tailleTableauSommets());
	dc1->demiCoteSommet=NouveauSommet;

	//ajout du nouveau sommet au tableau
	tableauSommets.push_back(NouveauSommet);

	// Relier dc1 et dc2 comme opposés
	dc1->demiCoteOppose = dc2;
	dc2->demiCoteOppose = dc1;

	//mis a jour du coté suivant pour precedent1
	precedent2->demiCoteSuivant = dc2;

	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
// coordonn�es sont celles des points p1 et p2 respectivement.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, const Point& p2)
{
	// Créer le demi-côté dc1
	DemiCote* dc1 = new DemiCote(nullptr, nullptr, nullptr, nullptr, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc1);
	dc1->demiCoteSuivant = dc1;
	dc1->demiCotePrecedent = dc1;
	// Créer un nouveau sommet pour dc1 avec les coordonnées de p1
	Sommet* NouveauSommetDc1 = new Sommet(p1,dc1,tailleTableauSommets());
	dc1->demiCoteSommet=NouveauSommetDc1;
	//ajout du nouveau sommet au tableau
	tableauSommets.push_back(NouveauSommetDc1);


	// Créer le demi-côté dc2 lié à precedent2
	DemiCote* dc2 = new DemiCote(nullptr, nullptr, dc1, nullptr, tailleTableauDemiCotes());
	tableauDemiCote.push_back(dc2);
	dc2->demiCoteSuivant = dc2;
	dc2->demiCotePrecedent = dc2;
	// Créer un nouveau sommet pour dc1 avec les coordonnées de p1
	Sommet* NouveauSommetDc2 = new Sommet(p2,dc2,tailleTableauSommets());
	dc2->demiCoteSommet=NouveauSommetDc2;
	//ajout du nouveau sommet au tableau
	tableauSommets.push_back(NouveauSommetDc2);

	// Relier dc1 et dc2 comme opposés
	dc1->demiCoteOppose = dc2;
	dc2->demiCoteOppose = dc1;

	return dc1;
}

// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
// par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(DemiCote* precedent, DemiCote* oppose)
{
  DemiCote* demi_cote = new DemiCote(precedent->demiCoteSuivant,precedent, oppose,precedent->demiCoteSommet,tableauDemiCote.size());
  tableauDemiCote.push_back(demi_cote); // push le demi coté
  precedent->demiCoteSuivant = demi_cote;
  demi_cote->demiCotePrecedent->demiCotePrecedent = demi_cote;
  if(oppose != nullptr){
    oppose->demiCotePrecedent = demi_cote;
  }
  return demi_cote;
}

// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
// sommet (� cr�er) dont les coordonn�es sont celles du point p.
// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(const Point &p, DemiCote* oppose)
{

  Sommet* sommet = new Sommet(p,oppose,tableauSommets.size());
  tableauSommets.push_back(sommet);

  //créer un nouveau demi coté lié au sommet
  DemiCote* demiCote = new DemiCote(nullptr,nullptr,oppose,sommet,tableauDemiCote.size());
  tableauDemiCote.push_back(demiCote); // j'ajoute le demi-côté au tableau

	return demiCote;
}
