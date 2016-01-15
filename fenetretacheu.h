#ifndef FENETRETACHEU
#define FENETRETACHEU

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QDateTimeEdit>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QListView>
#include <QCheckBox>
#include <QDateEdit>

#include "Projet.h"
#include "Tache.h"
#include "Manager.h"

/**
\class FenetreTacheU
\brief Fenetre pour la créatioon de TacheUnitaire

On crée une tache unitaire grace a un identificateur, un titre, un attribut de preemptivité, une disponibilité et une durée
**/
class FenetreTacheU : public QDialog
{
    Q_OBJECT

    Tache* tacheMere;
    QVBoxLayout* layoutCreationTache;
    QHBoxLayout* layoutCreationTache1;
    QHBoxLayout* layoutCreationTache2;
    QHBoxLayout* layoutCreationTache3;
    QHBoxLayout *layoutCreationTache4;
    QHBoxLayout* layoutCreationTache5;
    QHBoxLayout* layoutCreationTache6;

    QLineEdit* identificateurTache;
    QLabel *labelIdentificateurTache;
    QLineEdit* titreTache;
    QLabel* titreTacheLabel;
    QCheckBox* preemptiveTache;
    QLabel* labelPrecedence;
    QStringList listeTachePrecedentes;
    QStringListModel *modelePrecedence;
    QListView *vuePrecedence;
    QDateEdit* disponibiliteTache;
    QLabel* labelDisponibiliteTache;
    QDateEdit* tacheEcheance;
    QLabel* labelTacheEcheance;
    QLabel* labelTacheDuree;
    QSpinBox* tacheHDuree;
    QSpinBox* tacheMDuree;

    QPushButton* bCreerTache;
    QPushButton* bAnnulerCreationTache;

    public:
    //! \brief Unique constructeur de la fenetre\n
    //! \param tM tache mère
    FenetreTacheU(Tache&, QWidget *parent=0);

    public slots:
    //! \brief Creation de la tache unitaire\n
    //! Détection pour savoir si création à partir d'un projet ou d'une tache composite\n
    //! Verification avec les contraintes sur la tache mère/projet
    void creerTacheU();
    //! \brief Restriction sur la durée\n
    //! Le nombre de minutes doit être un multiple de 15
    //! \param n les minutes a formater
    void formatageDuree(int);
    //! \brief Liste des précédences\n
    //! \return liste de chaines des taches pouvant restreindre la réalisation de la tache
    QStringList remplissageTachePrecedence();
    //! \brief Vérification des précédences\n
    //! Test de compatibilité des écheances
    //! \param ref Tache* referente
    bool verifPrecedence(Tache* ref);
    //! \brief Mise a jour des précédences\n
    //! Lorsque que la durée est modifiée, on recharge toutes les précédences possibles
    //! \param dump QDate pour la disponibilité ou la tache modifiée
    void razPrecedence(QDate);
    //! \brief Surcharge Mise a jour des précéences\n
    //! Lorsque que la durée est modifiée, on recharge toutes les précédences possibles
    //! \param dump int pour les heures de la durée modifiée
    void razPrecedence(int);
};

#endif // FENETRETACHEU

