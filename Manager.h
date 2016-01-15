#ifndef MANAGER_h
#define MANAGER_h

#include <QVector>
#include <QString>
#include <QDate>

#include "Tache.h"
#include "Projet.h"
#include "Programmation.h"



//*******************************************************************************************************************
//********     CLASS
//*******************************************************************************************************
/**
\class ManagerException
\brief Gere les exceptions de la classe Manager
**/
class ManagerException
{
    QString info;
public:
    //! \brief  Unique constructeur de la classe
    //! \param message const QString& récupérant un message d'erreur pour l'exception levée
    ManagerException(const QString& message) :info(message){}
    //! \brief  Accesseur const pour l'attribut info
    //! \return const QStrin& le message d'erreur correspondant à l'exception levée
    QString& get_info() { return info; }
};

template <class T> //Template Class
/**
\class Manager
\brief Class template permettant de gerer des Projet, Tache, Programmation

Cette classe est implémentée comme singleton, il ne peut y avoir q'un seul gestionnaire de Projet Tache Programmation
**/
class Manager { //**Singleton**
private:
    QVector<T*> liste;

    //Singleton
    //! \brief Constructeur de la classe\n
    //! En privé car singleton, restiction de la constrcution
    Manager(){}
    //! \brief Destructeur de la classe
    virtual ~Manager(){}
    //! \brief Constructeur de recopie\n
    //! Recopie interdite car singleton
    Manager(const Manager& um);
    //! \brief Operateur d'affectation\n
    //! Affectation interdire, singleton
    Manager& operator=(const Manager& um);

    //Handler
    //! \brief Handler pour implementation du singleton
    //! \struct Handler
    struct Handler{
        Manager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:

    //Singleton
    //! \fn static Manager<T>& getInstance()
    //! \brief Recupère l'instance unique du Manager\n
    //! Creer l'instance si elle n'existe pas
    //! \return Manager<T>& l'instance unique
    static Manager<T>& getInstance() {
        if (handler.instance==0) handler.instance=new Manager<T>;
        return *(handler.instance);
    }
    //! \fn static void libererInstance()
    //! \brief Libere l'instance unique si elle existe
    static void libererInstance() {
        if (handler.instance!=0) delete handler.instance;
        handler.instance=0;
    }

    //QVector
    //! \brief Ajoute un item dans le Manager
    //! \param item T* de l'objet a ajouter au Manager
    void addItem(T* item) { liste.push_back(item);}
    //! \brief Ajoute un item au Manager
    //! \param item T& de l'objet a ajouter au Manager
    //! \return Manager& ou l'on a ajouté un objet
    Manager& operator<<(T& item){liste.push_back(item); return *this;}
    //! \brief Supprime un élément du Manager\n
    //! \param item T* de l'objet a enlever
    int deleteItem(T* item) ;
    //! \brief Accesseur du nombre d'item dans le Manager\n
    //! \return int la taille du QVector contenant les items
    int getSize()const{ return liste.size();}

    //Iterator
    //! \brief debut de l'Iterator des items du Manager
    //! \return iterateur sur le premier item
    typename QVector<T*>::iterator IteratorManagerBegin(){return liste.begin();}
    //! \brief fin de l'iterateur des items du Manager
    //! \return iterateur sur le dernier item
    typename QVector<T*>::iterator IteratorManagerEnd(){return liste.end();}

    //Const Iterator
    //! \brief debut de l'Iterator constant des items du Manager
    //! \return iterateur constant sur le premier item
    typename QVector<T*>::const_iterator ConstIteratorManagerBegin(){return liste.cbegin();}
    //! \brief fin de l'iterateur des constant items du Manager
    //! \return iterateur constant sur le dernier item
    typename QVector<T*>::const_iterator ConstIteratorManagerEnd(){return liste.cend();}    

    //Usually functions - CAN'T BE DEFINED IN .CPP
    //! \brief Cherche un item dans le Manager
    //! \param id const QString le nom de l'item
    //! \return T* de l'item recherché, nul si echec
    T* findItem(const QString& id) const ;
    //! \brief Recupère un item dans le Manager
    //! \param id const QString le nom de l'item
    //! \return T& de l'item recherché, levée d'exception si echec  
    T& getItem(const QString& id);
    //! \brief Recupère un item dans le Manager
    //! \param indice const int l'indice de l'item a récuperer
    //! \return T* de l'item recherché, levée d'exception si echec 
    T* getItem(const int indice);
    //! \brief Renvoie le Manager utilisé
    //! \param id const QString 
    //! \return const T& du 
    const T& getObject(const QString& id) const { return const_cast<Manager*>(this)->getObject(id);}
    //! \brief Test si l'item existe
    //! \param id const QString l'id de l'item a rechercher
    //! \return vrai si l'item existe, faux sinon
    bool isExisting(const QString& id) const { return findItem(id)!=0; }
    //! \brief Test si le Manager est vide\n
    //! Recupère la taille du QVector du Manager
    //! \return vrai si la Manager ne contient pas d'item, faux sinon
	bool isEmpty() const {return liste.empty();}


    //*******************************************************************************************************************
    //********    METHODES SPECIFIQUES D'AJOUT

    //CREER PROJET **************************************************************************
    //! \brief Creation d'un Projet\n
    //! Le manager gère la création des projets\n
    //! Verifie si un projet ayant le même identificateur n'existe pas déjà
    //! \param _id QString contenant l'id du projet
    //! \param _disponibilite contenant la QDate de disponibilite
    //! \param _echeance contenant la QDate d'echeance
    //! \return Projet& du nouveau projet
    Projet& ajouterProjet(const QString& _id,const QDate& _disponibilite, const QDate& _echeance){

        if (isExisting(_id)) throw ManagerException("erreur, Manager, Projet deja existant");
        Projet* newt = new Projet(_id, _disponibilite, _echeance);

        //Mise à jour Manager
        addItem(newt);

        return *newt;

    }

	 //Surcharge si conteneur de la tache est un projet ou une tache composite
    //! \brief Ajoute une nouvelle TacheUnitaire à un Projet\n
    //! Verifie si une telle Tache n'existe pas déjà et l'ajoute au Manager
    //! Verifie s'il ne s'agit pas d'une TacheUnitairePreemptive, sinon ajoute une nouvelle TacheUnitairePreemptive
    //! \param conteneur Projet& père de la Tache a ajouter
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \param _duree const Duree& de la tache, ici obligatoire
    //! \param checkBoxPreemptive const bool si la Tache est une TacheUnitairePreemptive
    //! \return Tache& de la Tache crée
	 Tache& ajouterTacheUnitaire(Projet& conteneur, const QString& _identificateur, const QString& _titre,
                            const QDate& _disponibilite, const QDate& _echeance,
                            const TIME::Duree& _duree, const bool checkBoxPreemptive){
    if (Manager<Tache>::getInstance().findItem(_identificateur)) throw ManagerException("erreur, Manager, Tache deja existante");

    Tache* newt = 0;
    if (!checkBoxPreemptive) //Création d'une tacheUnitaire
        newt = new TacheUnitaire(_identificateur, _titre, _disponibilite, _echeance, _duree);
    else //Création d'une tacheUnitairePreemptive
        newt = new TacheUnitairePreemptive(_identificateur, _titre, _disponibilite, _echeance, _duree);

    //Mise à jour
    Manager<Tache>::getInstance().addItem(newt);
    conteneur.addSoustache(newt);

    return *newt;
}
    //! \brief Ajoute une nouvelle TacheUnitaire à une TacheComposite\n
    //! Verifie si une telle Tache n'existe pas déjà et l'ajoute au Manager
    //! Verifie s'il ne s'agit pas d'une TacheUnitairePreemptive, sinon ajoute une nouvelle TacheUnitairePreemptive
    //! \param conteneur TacheComposite& mère de la Tache a ajouter
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \param _duree const Duree& de la tache
    //! \param checkBoxPreemptive const bool si la Tache est une TacheUnitairePreemptive
    //! \return Tache& de la Tache crée
	Tache& ajouterTacheUnitaire(TacheComposite& conteneur, const QString& _identificateur, const QString& _titre,
                            const QDate& _disponibilite, const QDate& _echeance,
                            const TIME::Duree& _duree, const bool checkBoxPreemptive){
    if (Manager<Tache>::getInstance().findItem(_identificateur)) throw ManagerException("erreur, Manager, Tache deja existante");

    TacheUnitaire* newt = 0;
    if (!checkBoxPreemptive) //Création d'une tacheUnitaire
        newt = new TacheUnitaire(_identificateur, _titre, _disponibilite, _echeance, _duree);
    else //Création d'une tacheUnitairePreemptive
        newt = new TacheUnitairePreemptive(_identificateur, _titre, _disponibilite, _echeance, _duree);

    //Mise à jour
    Manager<Tache>::getInstance().addItem(newt);
    conteneur.addSoustache(newt);

    return *newt;
    }

    //! \brief Ajoute une nouvelle TacheComposite à un Projet\n
    //! Verifie si une telle Tache n'existe pas déjà et l'ajoute au Manager
    //! \param conteneur Projet& père de la Tache a ajouter
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \return Tache& de la Tache crée
    Tache& ajouterTacheComposite(Projet& conteneur, const QString& _identificateur, const QString& _titre,
                                   const QDate& _disponibilite, const QDate& _echeance){
        if (Manager<Tache>::getInstance().findItem(_identificateur)) throw ManagerException("erreur, Manager, Tache deja existante");
        Tache* newt =0;
        newt = new TacheComposite(_identificateur, _titre, _disponibilite, _echeance);

        //Mise à jour
        Manager<Tache>::getInstance().addItem(newt);
        conteneur.addSoustache(newt);

        return *newt;
    }
    //! \brief Ajoute une nouvelle TacheComposite à une TacheComposite\n
    //! Verifie si une telle Tache n'existe pas déjà et l'ajoute au Manager
    //! Verifie s'il ne s'agit pas d'une TacheUnitairePreemptive, sinon ajoute une nouvelle TacheUnitairePreemptive
    //! \param conteneur TacheComposite& mère de la Tache a ajouter
    //! \param _identificateur const QString& avec l'identificateur de la tache
    //! \param _titre const QString& avec le titre de la tache
    //! \param _disponibilite const QDate& de la disponibiliteé de la tache
    //! \param _echeance const QDate& de l'echeance de la tache
    //! \return Tache& de la Tache crée
    Tache& ajouterTacheComposite(TacheComposite& conteneur, const QString& _identificateur, const QString& _titre,
                                   const QDate& _disponibilite, const QDate& _echeance){
        if (Manager<Tache>::getInstance().findItem(_identificateur)) throw ManagerException("erreur, Manager, Tache deja existante");
        Tache* newt =0;
        newt = new TacheComposite(_identificateur, _titre, _disponibilite, _echeance);

        //Mise à jour
        Manager<Tache>::getInstance().addItem(newt);
        conteneur.addSoustache(newt);

        return *newt;
    }
    //! \brief Ajoute une nouvelle Programmation à son Manager\n
    //! \param _evt Evenement& a programmer
    //! \param _date const QDateTime& de la Programmation
    //! \param _duree const Duree& de la Programmation
    //! \return Programmation& qui a étée ajoutée au Manager de Programmation
    Programmation& ajouterProgrammation(Evenement& _evt, QDateTime& _date, TIME::Duree& _duree)
    {
        Programmation* newp =0;
        newp = new Programmation(_evt, _date, _duree);

        //Mise à jour
        addItem(newp);
        return *newp;
    }
};
//*********************************************************************************************************
// METHODE DE MANAGER (.H CAR PATRON DE CLASSE)

template <class T>
int Manager<T>::deleteItem(T* item){
    //suppresion du projet dans Manager<Projet>
    for (int i = 0; i < liste.size(); ++i)
    {
        if (liste[i] == item)
        {
            liste.remove(i);
            return i;
        }
    }
    throw ManagerException("erreur, Manager, Element à supprimer non existant");
    return -1;
}

template <class T>
T* Manager<T>::findItem(const QString& id) const {
    for (int i = 0; i < liste.size(); ++i)   if (liste[i]->getId() == id) return liste[i];
    return 0;
}

template <class T>
T& Manager<T>::getItem(const QString& id){
    T* t = findItem(id);
    if (!t) throw ManagerException("erreur, object inexistant dans le Manager");
    return *t;
}

template <class T>
T* Manager<T>::getItem(const int indice){
    T* t = liste.value(indice);
    //if (!t) throw ManagerException("erreur, item inexistant dans le Manager");
    return t;
}

#endif // MANAGER

