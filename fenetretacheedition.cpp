#include "fenetretacheedition.h"
#include "fenetregraphique.h"

FenetreTacheEdition::FenetreTacheEdition(QWidget* parent): QDialog(parent)
{
    this->setWindowTitle(QString("Edition de la tache "+FenetreGraphique::tacheActive->getId()));

    identificateurLabel = new QLabel("Identificateur", this);
    identificateur = new QLineEdit((FenetreGraphique::tacheActive)->getId(), this);
    titreLabel = new QLabel("Titre            ", this);
    titre = new QLineEdit((FenetreGraphique::tacheActive)->getTitre(), this);
    preemptive = new QCheckBox("Preemptive", this);
    disponibiliteLabel = new QLabel("Disponibilité", this);
    disponibilite = new QDateEdit((FenetreGraphique::tacheActive)->getDateDisponibilite(), this);
    echeanceLabel = new QLabel("Echéance :");
    echeance = new QDateEdit((FenetreGraphique::tacheActive)->getDateEcheance(), this);
    dureeLabel = new QLabel("Durée :");
    hDuree = new QSpinBox(this);
    mDuree = new QSpinBox(this);
    sauver = new QPushButton("Modifier la tâche", this);
    annuler = new QPushButton("Annuler", this);

    preemptive->setEnabled(false);
    disponibilite->setEnabled(false);
    echeance->setEnabled(false);
    hDuree->setEnabled(false);
    mDuree->setEnabled(false);

    coucheH1 = new QHBoxLayout;
    coucheH2 = new QHBoxLayout;
    coucheH3 = new QHBoxLayout;
    coucheH4 = new QHBoxLayout;
    coucheH5 = new QHBoxLayout;
    couche = new QVBoxLayout;
    coucheH1->addWidget(identificateurLabel);
    coucheH1->addWidget(identificateur);
    coucheH1->addWidget(preemptive);
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3->addWidget(disponibiliteLabel);
    coucheH3->addWidget(disponibilite);
    coucheH3->addWidget(echeanceLabel);
    coucheH3->addWidget(echeance);
    coucheH4->addWidget(dureeLabel);
    coucheH4->addWidget(hDuree);
    coucheH4->addWidget(mDuree);
    coucheH5->addWidget(sauver);
    coucheH5->addWidget(annuler);
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);

    initialisation();
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), SLOT(sauverTache()));
    QObject::connect(annuler, SIGNAL(clicked()), SLOT(close()));
}

void FenetreTacheEdition::initialisation()
{
    if (typeid(*(FenetreGraphique::tacheActive))==typeid(TacheComposite))
    {
        preemptive->setVisible(false);
        dureeLabel->setVisible(false);
        hDuree->setVisible(false);
        mDuree->setVisible(false);
    }
    else if((typeid(*(FenetreGraphique::tacheActive))==typeid(TacheUnitaire))||(typeid(*(FenetreGraphique::tacheActive))==typeid(TacheUnitairePreemptive)))
    {
        hDuree->setRange(0, 59);
        hDuree->setSuffix(" heure(s)");
        hDuree->setValue((FenetreGraphique::tacheActive)->getDuree().getHeure());
        mDuree->setRange(0,59);
        mDuree->setSuffix(" minute(s)");
        mDuree->setValue((FenetreGraphique::tacheActive)->getDuree().getMinute());
        preemptive->setChecked((dynamic_cast<TacheUnitaire*>(FenetreGraphique::tacheActive))->isPreemptive());
    }
    else
    {
        QMessageBox::warning(this, "Message", "Type de tâche inconnu");
    }
}

void FenetreTacheEdition::sauverTache()
{
    if((FenetreGraphique::tacheActive->getId() ==  identificateur->text())&&(FenetreGraphique::tacheActive->getTitre() ==  titre->text()))
    {
        QMessageBox::warning(this, "Modification tache", "Aucune modification effectuée.");
        return;
    }
    else {
        if ((FenetreGraphique::tacheActive->getId() !=  identificateur->text())&&(Manager<Tache>::getInstance().isExisting(identificateur->text())))
            QMessageBox::warning(this, "Modification tache", "Identificateur déjà existant");
        else {
            FenetreGraphique::tacheActive->setId(identificateur->text());
            FenetreGraphique::tacheActive->setTitre(titre->text());
            QMessageBox::information(this, "Modification tache", "La tache a bien été modifié.");
            this->close();
        }
    }

}
