#include "fenetregraphique.h"
#include "fenetretacheu.h"
#include "QVector"
#include "Manager.h"
#include "Tache.h"



FenetreTacheU::FenetreTacheU(Tache& tM, QWidget* parent) : tacheMere(&tM), QDialog(parent)
{
    //tM informe si le tache est une sous tache d'un projet (tM==0) ou d'une tacheComposite tM

    setFixedSize(550, 450);
    setWindowTitle(FenetreGraphique::projetActif->getId() + ": Nouvelle tâche unitaire");

    //creation tache
    layoutCreationTache1 = new QHBoxLayout;
    layoutCreationTache2 = new QHBoxLayout;
    layoutCreationTache3 = new QHBoxLayout;
    layoutCreationTache4 = new QHBoxLayout;
    layoutCreationTache5 = new QHBoxLayout;
    layoutCreationTache6 = new QHBoxLayout;
    layoutCreationTache = new QVBoxLayout;

    labelIdentificateurTache = new QLabel("Identificateur de la tache");
    identificateurTache = new QLineEdit;
    preemptiveTache = new QCheckBox("Preemptive");
    titreTacheLabel = new QLabel("Titre de la tache     ");
    titreTache = new QLineEdit;

    //====
    labelPrecedence = new QLabel("Tâches précédentes");
    modelePrecedence = new QStringListModel(remplissageTachePrecedence());
    vuePrecedence = new QListView;
    vuePrecedence->setModel(modelePrecedence);
    vuePrecedence->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vuePrecedence->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //=====

    labelDisponibiliteTache = new QLabel("Disponibilité :");
    disponibiliteTache = new QDateEdit(QDate::currentDate());
    labelTacheEcheance = new QLabel("Echeance :");
    tacheEcheance = new QDateEdit(QDate::currentDate());
    labelTacheDuree = new QLabel("Durée :");
    tacheHDuree = new QSpinBox;
    tacheHDuree->setRange(0, 200);
    tacheHDuree->setSuffix(" heure(s)");
    tacheMDuree = new QSpinBox;
    tacheMDuree->setRange(0,45);
    tacheMDuree->setSingleStep(15);
    tacheMDuree->setSuffix(" minute(s)");
    bCreerTache = new QPushButton("Creer  la tâche");
    bAnnulerCreationTache = new QPushButton("Annuler");

    //imbrication creation tache
    layoutCreationTache1->addWidget(labelIdentificateurTache);
    layoutCreationTache1->addWidget(identificateurTache);
    layoutCreationTache1->addWidget(preemptiveTache);
    layoutCreationTache2->addWidget(titreTacheLabel);
    layoutCreationTache2->addWidget(titreTache);
    layoutCreationTache3->addWidget(labelPrecedence);
    layoutCreationTache3->addWidget(vuePrecedence);
    layoutCreationTache4->addWidget(labelDisponibiliteTache);
    layoutCreationTache4->addWidget(disponibiliteTache);
    layoutCreationTache4->addWidget(labelTacheEcheance);
    layoutCreationTache4->addWidget(tacheEcheance);
    layoutCreationTache5->addWidget(labelTacheDuree);
    layoutCreationTache5->addWidget(tacheHDuree);
    layoutCreationTache5->addWidget(tacheMDuree);
    layoutCreationTache6->addWidget(bCreerTache);
    layoutCreationTache6->addWidget(bAnnulerCreationTache);

    layoutCreationTache->addLayout(layoutCreationTache1);
    layoutCreationTache->addLayout(layoutCreationTache2);
    layoutCreationTache->addLayout(layoutCreationTache3);
    layoutCreationTache->addLayout(layoutCreationTache4);
    layoutCreationTache->addLayout(layoutCreationTache5);
    layoutCreationTache->addLayout(layoutCreationTache6);

    setLayout(layoutCreationTache);

    //connections
    QObject::connect(bCreerTache, SIGNAL(clicked()), this, SLOT(creerTacheU()));
    QObject::connect(tacheMDuree, SIGNAL(valueChanged(int)), this, SLOT(formatageDuree(int)));
    QObject::connect(tacheHDuree, SIGNAL(valueChanged(int)), this, SLOT(razPrecedence(int)));
    QObject::connect(disponibiliteTache, SIGNAL(dateChanged(QDate)), this, SLOT(razPrecedence(QDate)));
    QObject::connect(tacheEcheance, SIGNAL(dateChanged(QDate)), this, SLOT(razPrecedence(QDate)));
    QObject::connect(bAnnulerCreationTache, SIGNAL(clicked()), this, SLOT(close()));
}
void FenetreTacheU::creerTacheU()
{
    //Précédences
    //on recupere les elements selectionnes
    QItemSelectionModel *selection = vuePrecedence->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    QVector<Tache*> newListePrecedences;
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modelePrecedence->data(listeSelections[i], Qt::DisplayRole);
        newListePrecedences.push_back(Manager<Tache>::getInstance().findItem(elementSelectionne.toString()));

    }
    //QMessageBox::information(this, "Eléments sélectionnés",elementsSelectionnes);

//****************************************************************************************************
    if (FenetreGraphique::projetActif!=0) {

        if ((identificateurTache->text())=="")
            QMessageBox::information(this, "Erreur",  "Entrez un identificateur valide.");

        else if (Manager<Tache>::getInstance().isExisting(identificateurTache->text()))
            QMessageBox::information(this, "Erreur",  "Cet id est déja utilisé.");

       // else if ((titreTache->text())=="")
       //     QMessageBox::information(this, "Erreur",  "Entrez un titre valide.");

        else if ((disponibiliteTache->date()) > (tacheEcheance->date()))
            QMessageBox::information(this, "Erreur",  "La disponibilité doit être antérieur à l'échéance.");

        else if ((tacheEcheance->date()) < (QDate::currentDate()) )
            QMessageBox::information(this, "Erreur",  "L'échéance est déja dépassée.");


        else if (tacheMere==0){ // Création à partir d'un projet
            if (FenetreGraphique::projetActif->getDispo() > disponibiliteTache->date())
                QMessageBox::information(this, "Erreur",  "La disponibilité est antérieur à la disponibilité du projet.");

            else if (FenetreGraphique::projetActif->getDispo() > tacheEcheance->date()) //logiquement impossible
                QMessageBox::information(this, "Erreur",  "L'échéance est postérieure à la disponibilité du projet.");

            else if (FenetreGraphique::projetActif->getEcheance() < disponibiliteTache->date())
                QMessageBox::information(this, "Erreur",  "La disponibilité est postérieure à l'échéance du projet.");

            else if (FenetreGraphique::projetActif->getEcheance() < tacheEcheance->date())
                QMessageBox::information(this, "Erreur",  "L'échéance est postérieure à l'échéance du projet.");

            else //Création de la tache
            {
                Tache& tachetmp = Manager<Tache>::getInstance().ajouterTacheUnitaire(*(FenetreGraphique::projetActif),
                                                                                     identificateurTache->text(),
                                                                                     titreTache->text(),
                                                                                     disponibiliteTache->date(),
                                                                                     tacheEcheance->date(),
                                                                                     TIME::Duree(tacheHDuree->value(), tacheMDuree->value()),
                                                                                     preemptiveTache->isChecked());
                tachetmp.setPrecedences(newListePrecedences);
                QMessageBox::information(this, "Création de tâche unitaire", "La tâche unitaire " + tachetmp.getId() + " a été créée avec succès.");
                this->close();
            }
        }
        else { //Création à partir d'une tache mère
            if(tacheMere->getDateDisponibilite() > disponibiliteTache->date())
                QMessageBox::information(this, "Erreur",  "La disponibilité est antérieur à la disponibilité de la tache mère.");

            else if (tacheMere->getDateDisponibilite() > tacheEcheance->date())
                QMessageBox::information(this, "Erreur",  "L'échéance est postérieure à la disponibilité de la tache mère.");

            else if (tacheMere->getDateEcheance() < disponibiliteTache->date())
                QMessageBox::information(this, "Erreur",  "La disponibilité est postérieure à l'échéance de la tache mère.");

            else if (tacheMere->getDateEcheance() < tacheEcheance->date())
                QMessageBox::information(this, "Erreur",  "L'échéance est postérieure à l'échéance de la tache mère.");

            else  //Création de la tache
            {
                Tache& tachetmp = Manager<Tache>::getInstance().ajouterTacheUnitaire(*(dynamic_cast<TacheComposite*>(FenetreGraphique::tacheActive)),
                                                                                     identificateurTache->text(),
                                                                                     titreTache->text(),
                                                                                     disponibiliteTache->date(),
                                                                                     tacheEcheance->date(),
                                                                                     TIME::Duree(tacheHDuree->value(), tacheMDuree->value()),
                                                                                     preemptiveTache->isChecked());
                tachetmp.setPrecedences(newListePrecedences);
                QMessageBox::information(this, "Création de tâche unitaire", "La tâche unitaire " + tachetmp.getId() + " a été créée avec succès.");
                this->close();
                }
        }
    }
    else
        QMessageBox::information(this, "Erreur", "Aucun projet actif séléctionné");
}
void FenetreTacheU::formatageDuree(int n)
{
    int temp = n;
    if((n>0)&&(n<15))
        temp += 15-n;
    else if((n>15)&&(n<30))
        temp += 30-n;
    else if((n>30)&&(n<45))
        temp += 45-n;
    else if((n>45)&&(n<60))
        temp = 60-n;
    tacheMDuree->setValue(temp);
}
QStringList FenetreTacheU::remplissageTachePrecedence()
{
    QStringList listeTachePrecedentes;
    //on parcourt toutes les sous-taches du projet/ou de la tache mère
    if (tacheMere==0) // On analyse les sous-taches de projet actif
    {
        for (QVector<Tache*>::const_iterator it = FenetreGraphique::projetActif->ConstIteratorSousTachesBegin(); it != FenetreGraphique::projetActif->ConstIteratorSousTachesEnd(); ++it ){
            if (verifPrecedence(*it))
                    listeTachePrecedentes << (*it)->getId();
        }
    }
    return listeTachePrecedentes;
}
bool FenetreTacheU::verifPrecedence(Tache* ref){ //On vérifie les champs de la nouvelle tache avec la tache reference possiblement précédente
    //qDebug() << QDateTime((ref->getDateDisponibilite())).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60)); //to hours
    //Dispo+Duree de référence > echeance Tache
    if (((QDateTime(ref->getDateDisponibilite())).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60))) > (QDateTime(tacheEcheance->date(), QTime(23,45))))
        return false;

   //Date d'échéance - Durée de la tache est inférieur à Dispo + Duree ref
     if (    QDateTime(tacheEcheance->date(), QTime(23,45)).addSecs((tacheHDuree->value() * (-3600))+(tacheMDuree->value() * (-60)))
          <  QDateTime(ref->getDateDisponibilite()).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60))   )
        return false;

   return true; }
void FenetreTacheU::razPrecedence(QDate dump){
    modelePrecedence->setStringList(remplissageTachePrecedence());
}
void FenetreTacheU::razPrecedence(int dump){
    modelePrecedence->setStringList(remplissageTachePrecedence());
}
