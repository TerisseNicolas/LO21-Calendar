#ifndef FENETRETACHEC
#define FENETRETACHEC

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QListView>

#include "Projet.h"
#include "Tache.h"
#include "Manager.h"

/**
\class FenetreTacheC
\brief Fenetre permettant la création de TacheComposite

Création de tache composite à partir d'un id, d'un titre, d'une date de disponibilité, d'une écheance, et d'un ensemble de précédences.
**/
class FenetreTacheC : public QDialog
{
    Q_OBJECT

    Tache* tacheMere;
    QVBoxLayout* layoutCreationTache;
    QHBoxLayout* layoutCreationTache1;
    QHBoxLayout* layoutCreationTache2;
    QHBoxLayout* layoutCreationTache3;
    QHBoxLayout *layoutCreationTache4;
    QHBoxLayout* layoutCreationTache6;

    QLineEdit* identificateurTache;
    QLabel *labelIdentificateurTache;
    QLineEdit* titreTache;
    QLabel* titreTacheLabel;
    QLabel* labelPrecedence;
    QStringList listeTachePrecedentes;
    QStringListModel *modelePrecedence;
    QListView *vuePrecedence;
    QDateTimeEdit* disponibiliteTache;
    QLabel* labelDisponibiliteTache;
    QDateTimeEdit* tacheEcheance;
    QLabel* labelTacheEcheance;
    QLabel* labelTacheDuree;
    QSpinBox* tacheHDuree;
    QSpinBox* tacheMDuree;

    QPushButton* bCreerTache;
    QPushButton* bAnnulerCreationTache;

    public:
    //! \brief Unique constructeur\n
    //! \param tM Tache& mère est passée en argument.
    FenetreTacheC(Tache&, QWidget *parent=0);

    public slots:
    //! \brief Création d'une tache composite\n
    //! Determine si création à partir d'un projet ou d'une autre tache composite\n
    //! Verifie si une telle tache n'existe pas déjà dans le manager\n
    //! Verifie la compatibilite avec la tache mère/projet
    void creerTacheC();
    //! \brief Liste des taches précédentes\n
    //! \return  Liste de chaines de caractères avec toutes les précédences possibles pour cette tache.
    QStringList remplissageTachePrecedence();
    //! \brief Test la compatibilité des précédences\n
    //! Verifie que la date de dispo et la duree de la tache argument soient compatibles avec la tache composite que l'on veut creer
    //! \param ref Tache* dont on veux vérifier les références
    //! \return vrai si succes, faux sinon
    bool verifPrecedence(Tache* ref);
    //! \brief slot appellant le remplissage des taches precedentes
    //! \param dump QDate inutilisée
    void razPrecedence(QDate);
};

#endif // FENETRETACHEC
