#include "fenetreprojetedition.h"
#include "fenetregraphique.h"
#include "Manager.h"

FenetreProjetEdition::FenetreProjetEdition(QWidget* parent): QDialog(parent)
{

    this->setWindowTitle("Edition du projet"+FenetreGraphique::projetActif->getId());
    setFixedSize(500, 200);

    titreLabel = new QLabel("Nom : ");
    titre = new QLineEdit(FenetreGraphique::projetActif->getId(), this);
    disponibiliteLabel = new QLabel("Disponibilité : ");
    disponibilite = new QDateEdit(FenetreGraphique::projetActif->getDispo());
    disponibilite->setDisabled(true);
    echeanceLabel = new QLabel("Echeance : ");
    echeance = new QDateEdit(FenetreGraphique::projetActif->getEcheance());
    echeance->setDisabled(true);

    sauver = new QPushButton("Sauver");
    annuler = new QPushButton("Annuler");

    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(titreLabel);
    coucheH1->addWidget(titre);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(disponibiliteLabel);
    coucheH2->addWidget(disponibilite);
    coucheH2->addWidget(echeanceLabel);
    coucheH2->addWidget(echeance);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(sauver);
    coucheH3->addWidget(annuler);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    this->setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverProjet()));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(close()));
}
void FenetreProjetEdition::sauverProjet()
{ 
    if(FenetreGraphique::projetActif->getId() ==  titre->text())
    {
        QMessageBox::warning(this, "Modification projet", "Aucune modification effectuée.");
        return;
    }
    else {
        if (Manager<Projet>::getInstance().isExisting(titre->text()))
            QMessageBox::warning(this, "Modification projet", "Identificateur déjà existant");
        else {
            FenetreGraphique::projetActif->setId(titre->text());
            QMessageBox::information(this, "Modification projet", "Le projet a bien été modifié.");
            this->close();
        }
    }

}

