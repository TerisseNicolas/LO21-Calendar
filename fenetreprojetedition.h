#ifndef FENETREPROJETEDITION
#define FENETREPROJETEDITION

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QMessageBox>
#include <QTextEdit>

#include "Projet.h"

/**
\class FenetreProjetEdition
\brief Fenetre pour editer des Projet

Cette classe permet la modification de projet a aprtir d'une interface graphique.\n
Il est possible de modifier le nom du projet
**/
class FenetreProjetEdition : public QDialog {
    Q_OBJECT

    QLineEdit* titre;
    QLabel* titreLabel;
    QDateEdit* disponibilite;
    QLabel* disponibiliteLabel;
    QDateEdit* echeance;
    QLabel* echeanceLabel;
    QPushButton* sauver;
    QPushButton* annuler;

    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;

public:
    //! \brief Unique constructeur de la classe
    FenetreProjetEdition(QWidget* parent =0);

public slots:
    //! \brief modifie le projet actif\n
    //! Verifie si le nom est changé ou s'il n'existe pas déja un projet portant ce nom
    void sauverProjet();

};


#endif // FENETREPROJETEDITION

