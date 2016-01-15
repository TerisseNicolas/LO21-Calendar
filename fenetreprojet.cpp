#include "fenetreprojet.h"
#include "fenetregraphique.h"

#include "Manager.h"

FenetreProjet::FenetreProjet(QWidget* parent) : QDialog(parent)
{
    setFixedSize(550, 450);
    setWindowTitle("Nouveau projet");

    //creation projets
    layoutCreationProjet1 = new QHBoxLayout;
    layoutCreationProjet2 = new QHBoxLayout;
    layoutCreationProjet3 = new QHBoxLayout;
    layoutCreationProjet4 = new QHBoxLayout;
    layoutCreationProjet = new QVBoxLayout;

    labelNomProjet = new QLabel("Nom du projet :");
    nomProjet = new QLineEdit;
    labelProjetDateDispo = new QLabel("Date de disponibilité : ");
    projetDateDispo = new QDateEdit(QDate::currentDate());
    projetDateDispo->setMinimumDate(QDate::currentDate());
    projetDateDispo->setMaximumDate(QDate::currentDate().addYears(20));
    projetDateDispo->setDisplayFormat("dd.MM.yyyy");
    labelProjetEcheance = new QLabel("Echéance du projet :");
    projetEcheance = new QDateEdit(QDate::currentDate().addYears(1));
     projetEcheance->setMinimumDate(QDate::currentDate());
    projetEcheance->setMaximumDate(QDate::currentDate().addYears(20)); //good luck !!!
    projetEcheance->setDisplayFormat("dd.MM.yyyy");
    bCreerProjet = new QPushButton("Creer projet");
    bAnnulerCreationProjet = new QPushButton("Annuler");

    //imbrication onglet creation projet
    layoutCreationProjet1->addWidget(labelNomProjet);
    layoutCreationProjet1->addWidget(nomProjet);
    layoutCreationProjet2->addWidget(labelProjetDateDispo);
    layoutCreationProjet2->addWidget(projetDateDispo);
    layoutCreationProjet3->addWidget(labelProjetEcheance);
    layoutCreationProjet3->addWidget(projetEcheance);
    layoutCreationProjet4->addWidget(bCreerProjet);
    layoutCreationProjet4->addWidget(bAnnulerCreationProjet);

    layoutCreationProjet->addLayout(layoutCreationProjet1);
    layoutCreationProjet->addLayout(layoutCreationProjet2);
    layoutCreationProjet->addLayout(layoutCreationProjet3);
    layoutCreationProjet->addLayout(layoutCreationProjet4);
    setLayout(layoutCreationProjet);

    //connections
    QObject::connect(bCreerProjet, SIGNAL(clicked()), this, SLOT(creerProjet()));
    QObject::connect(bAnnulerCreationProjet, SIGNAL(clicked()), this, SLOT(close()));
}
void FenetreProjet::creerProjet()
{
    //Condition de création
    if ((nomProjet->text())=="")
        QMessageBox::information(this, "Erreur",  "Entrez un nom valide.");

    else if (Manager<Projet>::getInstance().isExisting(nomProjet->text()))
        QMessageBox::information(this, "Erreur",  "Ce nom est déja utilisé.");

    else if ((projetDateDispo->date()) > (projetEcheance->date()))
        QMessageBox::information(this, "Erreur",  "La disponibilité doit être antérieur à l'échéance.");

    else if ((projetEcheance->date()) < (QDate::currentDate()) )
        QMessageBox::information(this, "Erreur",  "L'échéance est déja dépassée.");

    else {
    //appel constructeur creation projet
    Projet& tmp = Manager<Projet>::getInstance().ajouterProjet(nomProjet->text(),projetDateDispo->date(), projetEcheance->date());
    QMessageBox::information(this, "Création de projet", "Le projet " + tmp.getId() + " a été crée avec succès.");
    FenetreGraphique::setProjetActif(tmp);
    this->close();
    }

}


