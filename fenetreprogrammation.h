#ifndef FENETREPROGRAMMATION
#define FENETREPROGRAMMATION

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

#include "Tache.h"
#include "Projet.h"

/**
\class FenetreProgrammation
\brief Fenetre qui permet la programmation d'une TacheUnitaire ou TacheComposite

Permet la programmation d'une tache grace à une date de début. Pour les tache unitaires preemptive, on sélectionne la durée à programmer
**/
class FenetreProgrammation : public QDialog
{
    Q_OBJECT

    Tache* tacheSelectionee = 0;
    Projet* projetSelectionne = 0;

    QVBoxLayout *layoutProgrammation;
    QHBoxLayout *layoutProgrammation0;
    QHBoxLayout *layoutProgrammation1;
    QHBoxLayout *layoutProgrammation2;
    QHBoxLayout *layoutProgrammation3;
    QHBoxLayout *layoutProgrammation4;
    QHBoxLayout *layoutProgrammation5;
    QHBoxLayout *layoutProgrammation6;

    //Liste des projets /taches
    QLabel* labelmenuDeroulantProjets;
    QComboBox *menuDeroulantProjets;
    QLabel* labelmenuDeroulantTacheEvent;
    QComboBox *menuDeroulantTacheEvent;

    QDateTimeEdit* debutProgrammation;
    QLabel* labelDebutProgrammation;
    QDateTimeEdit* finProgrammation;
    QLabel* labelFinProgrammation;
    QLabel* labelDureeProgrammation;
    QSpinBox* programmationHDuree;
    QSpinBox* programmationMDuree;
    QLabel* labelDureeRestante;
    QTimeEdit *dureeRestante;

    QPushButton *validerProgrammation;
    QPushButton *annulerProgrammation;

    public:
    //! \brief Unique constructeur de la fenetre
    FenetreProgrammation(QWidget *parent=0);

    public slots:
    //! \brief Chargement de toutes les taches non programmées d'un projet\n
    //! Il ne s'agit que de tache unitaires
    void chargementMenuTache(void);
    //! \brief Fonction récursive pour le parcourt des taches d'un projet
    //! Si unitaire, on ajoute au menu déroulant, sinon on rappel pour les sous taches de la tache composite
    void chargementRecursifMenuTache(TacheComposite&);
    //! \brief Programmation de la tache selectionnee\n
    //! Verification des contraintes par rapport à la classe mère/projet
    void programmer();
    //! \brief Selection d'une tache\n
    //! S'il s'agit d'une tache unitaire préemptive, alors on affiche une durée de programmation
    void changementTacheSelectionnee(int);
    //! \brief Selection d'un projet\n
    //! Récupère le projet selectionné dans le menu déroulant dans le manager
    void changementProjetSelectionne(int);

    //! \brief Charge toues les projets dans le menu déroulant\n
    //! Grace au manager de projets, on rempli le menu déroulant
    void initialisationMenuDeroulantProjet();
    //! \brief Arrondi un datetime au quart d'heure supérieur\n
    //! Formatage en multiple de 15\n
    //! \param tmp QDateTime a formater
    //! \return QDateTime arrondie
    QDateTime getArrondi (QDateTime tmp);
    //! \brief Restriction sur la fin de la programmation\n
    //! S'il s'agit d'une tache préemptive, on restreint la range du selecteur de minutes en fonction de la durée qui reste a programmer
    void actualiserFinProgrammation(int dump);
    //! \brief  Modification de la fin de la programmation\n
    //! Appellée lorsque l'on modifie le début de la programmation
    //! \param dump QDateTime correspondant à la nouvelle date du début de la programmation
    void actualiserFinProgrammation(QDateTime dump);
};

#endif // FENETREPROGRAMMATION*/

