#include "Projet.h"
#include "Manager.h"
#include "Tache.h"

//*********************************************************************************************************
// METHODE DE PROJET

void Projet::setDispo(QDate& _disponibilite) const
{
    //Vérifier qu'aucune sous-tache n'est disponible avant
    //Vérifier que la disponibilité est antérieur à la date d'echeance avec un écart au moins égal à Projet::getDuree
}

void Projet::setEcheance(QDate& _echeance) const{ //V�rifications � faire
//Vérifier qu'aucune sous-tache n'a une echeance après cette date
//Vérifier que l'échéance est après à la date de dispo/ou date actuelle si dispo<actuelle avec un écart au moins égal à Projet::getDuree
}


void Projet::viderProjet(void){
    for (int i = 0; i < soustaches.size(); ++i) {
        soustaches[i]->supprimer();
    }
}

int  Projet::supprimerTache(Tache* t) {

    //suppression de la tache dans Manager <Tache>
    int res = Manager<Tache>::getInstance().deleteItem(t);
    //suppresion de la tache dans la liste des sous taches du conteneur
    deleteSousTache(t);
    //suppression mémoire ou suppression des sous taches si tache composite
    t->supprimer();
    return res;
}

int Projet::detruireProjet(void){ //Supprimer intégralement un projet ainsi que toutes ses taches associées
    //suppresion du projet dans Manager<Projet>
    int res = Manager<Projet>::getInstance().deleteItem(this);
    this->viderProjet();
    return res;
}

void Projet::deleteSousTache(Tache* t){
    //Parcours récursif
    for (int i =0; i<soustaches.size(); ++i)
        if (soustaches[i]==t)
        {
            soustaches.remove(i);
            break;
        }
        else if (typeid(TacheComposite)==(typeid(*(soustaches[i]))))
        {
            TacheComposite* tmp = dynamic_cast<TacheComposite*>(soustaches[i]);
            tmp->deleteSousTache(t);
        }
}
