#ifndef PROJET_h
#define PROJET_h

#include "Tache.h"
#include <QString>
#include <QVector>
#include <typeinfo>



//*******************************************************************************************************************
//********     CLASS
/**
\class ProjetException
\brief Gere les exceptions de la classe Projet
**/
class ProjetException
{
    QString info;
public:
    //! \brief  Unique constructeur de la classe
    //! \param message const QString& récupérant un message d'erreur pour l'exception levée
    ProjetException(const QString& message) :info(message){}
    //! \brief  Accesseur const pour l'attribut info
    //! \return const QStrin& le message d'erreur correspondant à l'exception levée
    QString& get_info() { return info; }
};

/**
\class Projet
\brief Classe permettant de strocker les informations relatives à un Projet

Un projet est caractérisé par un id, une date de disponibilité, une écheance et un ensemble de taches (unitaires ou composites)
**/
class Projet
{
    QString id;
    QDate disponibilite;
    QDate echeance;
    QVector<Tache*> soustaches;

    //! \brief Constrcuteur de recopie privé\n
    Projet(const Projet&) {}
    //! \brief Destructeur de la classe projet\n
    //! Ce destructeur appel la destruction de toutes les tache du projet avant de le détruire
    ~Projet();

public:
    //! \brief Unique constructeur de la classe projet\n
    //! Il est possible de construire un projet a partir d'un id, d'une date de disponibilité, d'une écheance
    //! \param _id QString contenant l'id du projet
    //! \param _disponibilite contenant la QDate de disponibilite
    //! \param _echeance contenant la QDate d'echeance
    Projet(const QString& _id, const QDate& _disponibilite, const QDate& _echeance) :id(_id), disponibilite(_disponibilite), echeance(_echeance){}

    //QVector Sous Taches
    //! \brief Ajoute une tache au projet\n
    //! \param item Tache* qui est ajouté au QVector contenant les taches du projet
    void addSoustache(Tache* item) {soustaches.push_back(item);}
    //! \brief Operateur << \n
    //! Ajoute une tache au projet
    //! \param item Tache* qui est ajouté QVector contenant les projets
    //! \return Parojet& le projet auquel la tache a été ajoutée
    Projet& operator<<(Tache* item){soustaches.push_back(item); return *this;}

    //ACCESSEURS
    //! \brief Accesseur de l'id du projet
    //! \return QString avec l'identificateur du projet
    QString getId() const { return id; }
    //! \brief Accesseur date disponibilité
    //! \return Qdate de la disponibilité du projet
    QDate getDispo() const {return disponibilite;}
    //! \brief Accesseur de l'echeance
    //! \return QDate de l'écheance du projet
    QDate getEcheance() const {return echeance;}
    //! \brief Mutateur de l'identificateur du projet
    //! \param _id const QString& avec le nouvel identificateur du projet
    void setId(const QString& _id){ id = _id; }
    //! \brief Mutateur disponibilité du projet
    //! \param _disponibilite QDate& de la nouvelle disponibilité
    void setDispo(QDate& _disponibilite) const;
    //! \brief Muatateur echeance du projet
    //! \param _echeance QDate& de la nouvelle echeance
    void setEcheance(QDate& _echeance) const;
    //! \brief Vide le projet\n
    //! Appel la destruction de toutes les taches du projet
    void viderProjet();

    //! \brief Supprime une tache du projet
    //! \param t Tache* de la tache a supprimer du projet
    void deleteSousTache(Tache* t);
    //! \brief Suppression du projet\n
    //! Supprime le projet du manager\n
    //! Vide le projet de toutes ses taches
    //! \return int la position du porjte dans le manager, -1 si echec de la suppression
    int detruireProjet(void);
    //! \brief Supprime une tache\n
    //! Supprime la tache du manager de tache
    //! Apppel de deleteSousTache pour cette tache\n
    //! Suppression de toutes ses sous taches
    //! \param t Tache* de la tache a supprimer
    //! \return int le resultat de la suppression dans le manager de tache, -1 si echec
    int  supprimerTache(Tache* t);
    //! \brief Test si le projet ne contient pas de taches
    //! \return vrai si la liste de tache est vide, faux sinon
    bool isEmpty()const{return soustaches.empty();}

    //Iterator QVector
    //! \brief debut de l'Iterator des taches du projet
    //! \return iterateur sur la premiere tache du projet 
    QVector<Tache*>::iterator IteratorSousTachesBegin(){return soustaches.begin();}
    //! \brief fin de l'iterateur des taches du projet
    //! \return iterateur sur la dernière tache du projet
    QVector<Tache*>::iterator IteratorSousTachesEnd(){return soustaches.end();}

    //Const Iterator QVector
    //! \brief debut de l'iterateur constant des taches du projet
    //! \return iterateur constant sur la premiere tache du projet
    QVector<Tache*>::const_iterator ConstIteratorSousTachesBegin(){return soustaches.cbegin();}
    //! \brief fin de l'iterateur constant des taches du projet
    //! \return iterateur constant sur la dernière tache du projet
    QVector<Tache*>::const_iterator ConstIteratorSousTachesEnd(){return soustaches.cend();}
};

#endif //PROJET.h
