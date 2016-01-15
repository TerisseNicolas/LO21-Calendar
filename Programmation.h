#ifndef PROGRAMMATION
#define PROGRAMMATION

#include <time.h>
#include <QString>
#include <Duree.h>
#include <QDate>

class Tache;

//*******************************************************************************************************************
//********     CLASS

/**
\class ProgrammationException
\brief Gere les exceptions de la classe Programmation
**/
class ProgrammationException
{
    QString info;
public:
    //! \brief  Unique constructeur de la classe
    //! \param message const QString& récupérant un message d'erreur pour l'exception levée
    ProgrammationException(const QString& message) :info(message){}
    //! \brief  Accesseur const pour l'attribut info
    //! \return const QStrin& le message d'erreur correspondant à l'exception levée
    QString& get_info() { return info; }
};

/**
\class Evenement
\brief Structure des objets contenus dans une Programmation, classe abstaite

Cette classe existe uniquement pour généraliser les Taches et les Activite afin de pouvoir les programmer
**/ 
class Evenement{ //Abstraite
public:
    //! \brief Constructeur d'Evenement\n
    //! ne fait absolument rien
    Evenement(){}
    //! \brief Destructeur de l'Evenement
    virtual ~Evenement(){}
};

/*
class Activite : public Evenement{

public:
    QString getId() const {return id;}
};
*/
/**
\class Programmation
\brief Classe permettant de programmer un Tache ou une Activite dans l'agenda

Une Programmation est caractérisée par un Evenement à programmer, une date de programmation et une Duree\n
Une programmation a une Duree, par defaut à la Duree de la Tache lorsqu'il s'agit d'une TacheUnitaire, mais qui est inférieure ou égale à la Duree d'une TacheUnitairePreemptive, qui programmée partiellement ou en totalité
**/
class Programmation {

    Evenement* evenement;
    QDateTime date;
    TIME::Duree duree;

public:

    //! \brief Accesseur de l'evenement\n
    //! \return const Evenement& qui est programmé
    const Evenement& getEvenement() const { return *evenement; }
    //Programmation( const QDate& _date, const TIME::Duree& _horaire, const TIME::Duree& _duree = TIME::Duree(0,0)): date(_date), horaire(_horaire), duree(_duree){}
    //! \brief Constructeur de Programmation\n
    //! Une Programmation se construit à partir d'un Evenement a programmer, une date et une Duree
    //! \param _evt Evenement& a programmer
    //! \param _date const QDateTime& de la Programmation
    //! \param _duree const Duree& de la Programmation, nulle par défaut
    Programmation(Evenement& _evt, const QDateTime& _date, const TIME::Duree& _duree = TIME::Duree(0,0)): evenement(&_evt), date(_date), duree(_duree){}QDate
    //! \brief Accesseur de la date
    //! \return QdateTime de la Programmation
    QDateTime getDate() const { return date; }
    //! \brief Accesseur de la Duree
    //! \return Duree de la Programmation
    TIME::Duree getDuree() const { return duree;}

};

#endif // PROGRAMMATION

