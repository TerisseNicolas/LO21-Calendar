#ifndef TACHE_h
#define TACHE_h

#include <QVector>
#include <QString>
#include <QTime>
#include <QTextStream>
#include <typeinfo>

#include <Programmation.h> //Obligatoire pour l'héritage multiple

//*******************************************************************************************************************
//********     CLASS
/**
\class TacheException
\brief Classe permettant de lever des exceptions les Tache
**/
class TacheException{
public:
    //! \brief  Unique constructeur de la classe
    //! \param message const QString& récupérant un message d'erreur pour l'exception levée
    TacheException(const QString& message) :info(message){}
    //! \brief  Accesseur const pour l'attribut info
    //! \return const QStrin& le message d'erreur correspondant à l'exception levée
    QString getInfo() const { return info; }
private:
    QString info;
};

//******************
//   TACHE   *******
/**
\class Tache
\brief Classe abstraite comportant les attrbuts communs au classes TacheComposite et TacheUnitaire

Il s'agit de l'abstraction entre la feuille n'ayant pas de sous composant ( tache unitaire) et le composite ayant des sous composants (tache composite) 
**/
class Tache { //Abstraite + Design Pattern Composite

protected:
    QString identificateur;
    QString titre;
    //! \brief Differents états possibles d'une tache
    enum Etat {NON_PROGRAMMEE, NON_COMMENCEE,COMMENCEE,TERMINEE};
    Etat etat;
    QDate disponibilite;
    QDate echeance;
    TIME::Duree duree;
    QVector<Tache*> precedences;

    //! \brief Unique constructeur d'une tache\n
    //! La création de tache est gérée par le manager de tache\n
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \param _duree const Duree& de la tache, parametre optionnel
    Tache(const QString& _identificateur, const QString& _titre, const QDate& _disponibilite, const QDate& _echeance, const TIME::Duree& _duree = TIME::Duree(0,0)):
           identificateur(_identificateur),titre(_titre),etat(NON_PROGRAMMEE),disponibilite(_disponibilite),echeance(_echeance),duree(_duree){}
    //! \brief Destructeur de tache\n
    //! La destruction de tache est gérée par le tache manager
    virtual ~Tache(){}

private:
    //! \brief Constructeur de recopie\n
    //! Recopie interdite
     Tache(const Tache& t);

public:

    // ACCESSEURS LECTURE/ECRITURE
    //! \brief Accesseur de l'identificateur\n
    //! \return QString de l'identificateur
    QString getId() const { return identificateur; }
    //! \brief Accesseur du titre\n
    //! \return QString du titre
    QString getTitre() const { return titre; }
    //! \brief Accesseur de la disponibilité\n
    //! \return QDate de disponibilité
    QDate getDateDisponibilite() const {  return disponibilite; }
    //! \brief Accesseur de l'echeance
    //! \return QDate de l'écheance
    QDate getDateEcheance() const {  return echeance; }
    //! \brief Accesseur de la durée
    //! \return Duree de la tache
    TIME::Duree getDuree() const {return duree;}
    //! \brief Accesseur de l'état
    //! \return QString de l'état
    QString getEtat() const;

    //! \brief Mutateur de l'identificateur
    //! \param str const QString du nouvel identificateur
    void setId(const QString& str) { identificateur = str; }
    //! \brief Mutateur de titre
    //! \param str const QString du nouveau titre
    void setTitre(const QString& str) { titre = str; }
    //! \brief Mutateur de durée
    //! \param d Duree& de la nouvelle durée
    void setDuree(const TIME::Duree& d) { duree = d; }
    //! \brief Mutateur de précedences
    //! \param tmp const QVector<Tache*> contenant les taches précedentes
    void setPrecedences (const QVector<Tache*> tmp) {precedences = tmp; }
    //! \brief Mutateur d'état programmé\n
    //! Met l'état de la tache a programmée mais pas encore commencée
    void setProgrammed() { etat = NON_COMMENCEE ;}

    //! \brief Suppression de la tache\n
    //! Methode virtuelle pure implémentée dans les classes filles
    virtual void supprimer() = 0 ;
    //! \brief test si la tache est programmée
    //! \return vrai si la tache est programmée, faux dans le cas contraire
    bool isProgrammed() const {return (etat!=NON_PROGRAMMEE);}

    //Iterator QVector
    //! \brief debut de l'Iterator des precedences
    //! \return iterateur sur la premiere precedence
    QVector<Tache*>::iterator IteratorPrecedencesBegin(){return precedences.begin();}
    //! \brief fin de l'iterateur des precedences de la tache
    //! \return iterateur sur la dernière précedence
    QVector<Tache*>::iterator IteratorPrecedencesEnd(){return precedences.end();}

    //Const Iterator QVector
    //! \brief debut de l'iterateur constant des précedences de la tache
    //! \return iterateur constant sur la premiere précedence
    QVector<Tache*>::const_iterator ConstIteratorPrecedencesBegin(){return precedences.cbegin();}
    //! \brief fin de l'iterateur constant des précedences
    //! \return iterateur constant sur la dernière précedence
    QVector<Tache*>::const_iterator ConstIteratorPrecedencesEnd(){return precedences.cend();}

};


//***************************
//   TACHE UNITAIRE   *******
/**
\class TacheUnitaire
\brief Héritage multiple de Tache et de Evenement

La classe contient toutes les caractéristiques d'une tache, mais hérite aussi de la classe abstraite evenement, qui est le seul type accepté pour les programmations
**/
class TacheUnitaire : public Tache, public Evenement {
protected:


public:
    //! \brief Constructeur de tache unitaire\n
    //! Elle se construit en appelant le constructeur de tache, sa classe mere
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \param _duree const Duree& de la tache, ici obligatoire    
    TacheUnitaire(const QString& _identificateur, const QString& _titre, const QDate& _disponibilite, const QDate& _echeance, const TIME::Duree _duree):
            Tache(_identificateur, _titre, _disponibilite, _echeance, _duree){}
    //! \brief Destructeur de tache unitaire
    virtual ~TacheUnitaire(){}

    //! \brief Suppression de tache\n
    //! Implementation obligatoire sinon classe abstraire comme la classe Tache\n
    //! Appel le destructeur de TacheUnitaire
    virtual void supprimer();
    //! \brief Test si la tache est prémptive\n
    //! Il existe une classe héritée pour les taches unitaires preemptives
    //! \return faux dans tous les cas
    virtual bool isPreemptive() const {return false;}
};


//*************************************
//   TACHE UNITAIRE PREEMPTIVE   *******
/**
\class TacheUnitairePreemptive
\brief Classe héritée de TacheUniatire

Cette classe est semblable à sa classe mère, sauf qu'elle peut être réalisée que partiellement\n
Elle a donc un attribut décrivant la durée restante a réaliser
**/
class TacheUnitairePreemptive : public TacheUnitaire
{
    TIME::Duree dureeRestante;
public:
    //! \brief Accesseur de la durée restante
    //! \return Duree restante
    TIME::Duree getDureeRestante() const {return dureeRestante ; }

    //! \brief Constructeur de la classe\n
    //! Construction semblable à sa tache mère\n
    //! Lunique attribut dureeRestante est initialisé avec la durée de la tache
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \param _duree const Duree& de la tache
    TacheUnitairePreemptive(const QString& _identificateur, const QString& _titre, const QDate& _disponibilite, const QDate& _echeance, const TIME::Duree _duree):
            TacheUnitaire(_identificateur, _titre, _disponibilite, _echeance, _duree),dureeRestante(_duree){}

    //! \brief Suppression de la tache préemptive\n
    //! Appel son destructeur;
    void supprimer();
    //! \brief Test si la tache est préemptive\n
    //! \return vrai, toujours (la classe est preemptive par nature)
    bool isPreemptive() const {return true;}
};

//**************************
//   TACHE COMPOSITE *******
/**
\class TacheComposite
\brief Classe composante du Design Pattern Composite, héritée de Tache

Cette classe contient un ensemble de sous tache
**/
class TacheComposite : public Tache
{
    QVector<Tache*> soustaches;

public:

    //Gestion QVector soustaches
    //! \brief Ajoute une sous tache
    //! \param item Tache* de la tache a jouter
    void addSoustache(Tache* item) {soustaches.push_back(item);}
    //! \brief Ajoute une sous tache
    //! \param item tache* de la tache à ajouter
    //! \return TacheComposite& mère de cette sous tache
    TacheComposite& operator<<(Tache* item){soustaches.push_back(item); return *this;}
    //! \brief Ajoute une sous tache composite
    //! \param t TacheComposite* a ajouter
    //! \return tacheComposite& mère de la nouvelle sous tache composite
    TacheComposite& addSoustache(TacheComposite* t);

    //ACCESSEURS
    //! \brief Constructeur de la tache composite\n
    //! Un objet est construit de la même façon que Tache (non instanciable)\n
    //! La durée de la tache sera nulle à sa construction
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    TacheComposite(const QString& _identificateur, const QString& _titre, const QDate& _disponibilite, const QDate& _echeance):
            Tache(_identificateur, _titre, _disponibilite, _echeance){}
    //! \brief Destructeur de la tache composite
    virtual ~TacheComposite(){}

    //! \brief Supprime la tache composite\n
    //! Appel le destructeur de toutes ses sous taches, qu'elles soient composites ou unitaires
    void supprimer();
    //! \brief Supprime une sous tache\n
    //! Parcout recursif de ses sous tache pour trouver la tache passée en argument\n
    //! Lorsque cette tache est trouvée, la methode appel son destructeur
    //! \param t Tache* a supprimer
    void deleteSousTache(Tache* t);

    //Iterator QVector
    //! \brief debut de l'Iterator des sous taches
    //! \return iterateur sur la premiere sous tache du 
    QVector<Tache*>::iterator IteratorSousTachesBegin(){return soustaches.begin();}
    //! \brief fin de l'iterateur des sous taches
    //! \return iterateur sur la dernière sous tache
    QVector<Tache*>::iterator IteratorSousTachesEnd(){return soustaches.end();}

    //Const Iterator QVector
    //! \brief debut de l'iterateur constant des sous taches
    //! \return iterateur constant sur la premiere sous tache
    QVector<Tache*>::const_iterator ConstIteratorSousTachesBegin(){return soustaches.cbegin();}
    //! \brief fin de l'iterateur constant des sous taches
    //! \return iterateur constant sur la dernière sous tache
    QVector<Tache*>::const_iterator ConstIteratorSousTachesEnd(){return soustaches.cend();}
};

//********     FUNCTIONS
//! \brief Surcharge cout\n
//! Surcharge pour une tache
QTextStream& operator<<(QTextStream& fout, const Tache& t);
//! \brief Surcharge cout\n
//! Surcharge pour une tache unitaire
QTextStream& operator<<(QTextStream& fout, const TacheUnitaire& t);
//! \brief Surcharge cout\n
//! Surcharge pour une tache unitaire péréemptive
QTextStream& operator<<(QTextStream& fout, const TacheUnitairePreemptive& t);
//! \brief Surcharge cout\n
//! Surcharge pour une tache composite
QTextStream& operator<<(QTextStream& fout, const TacheComposite& t);

#endif // TACHE.h
