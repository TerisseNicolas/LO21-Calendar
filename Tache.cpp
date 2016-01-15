#include "Tache.h"
#include "Manager.h"

QString Tache::getEtat() const
{
    switch(etat)
    {
    case NON_PROGRAMMEE : return "Tâche non programmée";
        break;
    case NON_COMMENCEE : "Tâche programmée mais non démarée";
         break;
    case COMMENCEE : return "Tâche démarée non terminée";
         break;
    case TERMINEE: return "Tâche terminée";
         break;
    default: return "Erreur état";
         break;
    }
}

void TacheComposite::supprimer() //sans les précédences
{
    for (int i = 0; i < soustaches.size(); ++i) {
        Manager<Tache>::getInstance().deleteItem(soustaches[i]);
        soustaches[i]->supprimer();
        }
    delete this;
}
void TacheUnitaire::supprimer(){ delete this; }
void TacheUnitairePreemptive::supprimer(){ delete this; }

void TacheComposite::deleteSousTache(Tache* t){
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

//*******************************************************************************************************************
//********     SURCHARGE COUT
//Tache
QTextStream& operator<<(QTextStream& fout, const Tache& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    return fout;
}

//TacheUnitaire
QTextStream& operator<<(QTextStream& fout, const TacheUnitaire& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    fout<<t.getDuree().toString()<<"\n";
    return fout;
}

//TacheUnitairePreemptive
QTextStream& operator<<(QTextStream& fout, const TacheUnitairePreemptive& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    fout<<t.getDuree().toString()<<"\n";
    fout<<t.getDureeRestante().toString()<<"\n";
    return fout;
}

//TacheComposite
QTextStream& operator<<(QTextStream& fout, const TacheComposite& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    return fout;
}

