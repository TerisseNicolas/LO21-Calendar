#ifndef FENETRETACHEEDITION
#define FENETRETACHEEDITION

#include <QApplication>
#include <QCheckBox>
#include <QTextEdit>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QDateEdit>
#include <QSpinBox>
#include <QMessageBox>

//#include "calendar.h"
#include <typeinfo>
#include "Manager.h"
#include "Tache.h"

/**
\class FenetreTacheEdition
\brief Fenetre permettant d'éditer un Tache existante

Pour la tache active de la fenetre principale, on modifie ses attributs\n
La fenetre s'adapte au type réel de la tache.
**/
class FenetreTacheEdition : public QDialog {
    Q_OBJECT

    QLineEdit* identificateur;
    QLabel *identificateurLabel;
    QLineEdit* titre;
    QLabel* titreLabel;
    QCheckBox* preemptive;
    QDateEdit* disponibilite;
    QLabel* disponibiliteLabel;
    QDateEdit* echeance;
    QLabel* echeanceLabel;
    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;
    QPushButton* sauver;
    QPushButton* annuler;

    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;

public:
    //! \brief Unique constructeur\n
    //! Le cosntructeur ne prend pas d'argument car on accède à l'attribut statique tacheActive de la classe FenetreGragique
    FenetreTacheEdition(QWidget* parent =0);

public slots:
    //! \brief Initialisation de la fenetre\
    //! Si la tache est unitaire ou unitaire préemptive, on affiche la durée\n
    void initialisation();
    //! \brief Sauvegarde de la modification\n
    //! On verifie que le nom a bien été modifié et que l'identificateur n'existe pas déjà pour une autre tache
    void sauverTache();
};

#endif // FENETRETACHEEDITION

