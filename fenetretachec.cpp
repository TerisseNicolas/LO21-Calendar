#include "fenetretachec.h"
#include "fenetregraphique.h"

FenetreTacheC::FenetreTacheC(Tache& tM, QWidget* parent) : tacheMere(&tM), QDialog(parent)
{
    //tM informe si la tache est une sous tache d'un projet (tM==0) ou d'une tacheComposite tM

    setFixedSize(550, 450);
    setWindowTitle("Nouvelle tâche composite");

    //creation tache
    layoutCreationTache1 = new QHBoxLayout;
    layoutCreationTache2 = new QHBoxLayout;
    layoutCreationTache3 = new QHBoxLayout;
    layoutCreationTache4 = new QHBoxLayout;
    layoutCreationTache6 = new QHBoxLayout;
    layoutCreationTache = new QVBoxLayout;

    labelIdentificateurTache = new QLabel("Identificateur de la tache");
    identificateurTache = new QLineEdit;
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
    labelTacheEcheance = new QLabel("Echéance :");
    tacheEcheance = new QDateEdit(QDate::currentDate());
    bCreerTache = new QPushButton("Créer  la tâche");
    bAnnulerCreationTache = new QPushButton("Annuler");

    //imbrication creation tache
    layoutCreationTache1->addWidget(labelIdentificateurTache);
    layoutCreationTache1->addWidget(identificateurTache);
    layoutCreationTache2->addWidget(titreTacheLabel);
    layoutCreationTache2->addWidget(titreTache);
    layoutCreationTache3->addWidget(labelPrecedence);
    layoutCreationTache3->addWidget(vuePrecedence);
    layoutCreationTache4->addWidget(labelDisponibiliteTache);
    layoutCreationTache4->addWidget(disponibiliteTache);
    layoutCreationTache4->addWidget(labelTacheEcheance);
    layoutCreationTache4->addWidget(tacheEcheance);
    layoutCreationTache6->addWidget(bCreerTache);
    layoutCreationTache6->addWidget(bAnnulerCreationTache);
    layoutCreationTache->addLayout(layoutCreationTache1);
    layoutCreationTache->addLayout(layoutCreationTache2);
    layoutCreationTache->addLayout(layoutCreationTache3);
    layoutCreationTache->addLayout(layoutCreationTache4);
    layoutCreationTache->addLayout(layoutCreationTache6);

    setLayout(layoutCreationTache);

    //connections
    QObject::connect(bCreerTache, SIGNAL(clicked()), this, SLOT(creerTacheC()));
    QObject::connect(bAnnulerCreationTache, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(disponibiliteTache, SIGNAL(dateChanged(QDate)), this, SLOT(razPrecedence(QDate)));
    QObject::connect(tacheEcheance, SIGNAL(dateChanged(QDate)), this, SLOT(razPrecedence(QDate)));


}
void FenetreTacheC::creerTacheC()
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

    //********************************************************************************************************
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
                Tache& tachetmp = Manager<Tache>::getInstance().ajouterTacheComposite(*(FenetreGraphique::projetActif),
                                                                                               identificateurTache->text(),
                                                                                               titreTache->text(),
                                                                                               disponibiliteTache->date(),
                                                                                               tacheEcheance->date());
                tachetmp.setPrecedences(newListePrecedences);
                QMessageBox::information(this, "Création de tâche composite", "La tâche composite " + tachetmp.getId() + " a été créée avec succès.");
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
                Tache& tachetmp = Manager<Tache>::getInstance().ajouterTacheComposite(*(dynamic_cast<TacheComposite*>(FenetreGraphique::tacheActive)),
                                                                                               identificateurTache->text(),
                                                                                               titreTache->text(),
                                                                                               disponibiliteTache->date(),
                                                                                               tacheEcheance->date());
                tachetmp.setPrecedences(newListePrecedences);
                QMessageBox::information(this, "Création de tâche composite", "La tâche composite " + tachetmp.getId() + " a été créée avec succès.");
                this->close();
                }
        }
    }
    else
        QMessageBox::information(this, "Erreur", "Aucun projet actif séléctionné");
}

QStringList FenetreTacheC::remplissageTachePrecedence()
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
bool FenetreTacheC::verifPrecedence(Tache* ref){ //On vérifie les champs de la nouvelle tache avec la tache reference possiblement précédente
    //qDebug() << QDateTime((ref->getDateDisponibilite())).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60)); //to hours
    //Dispo+Duree de référence > echeance Tache
    if (((QDateTime(ref->getDateDisponibilite())).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60))) > (QDateTime(tacheEcheance->date(), QTime(23,45))))
        return false;

   //Date d'échéance - Durée de la tache est inférieur à Dispo + Duree ref
     if (    QDateTime(tacheEcheance->date(), QTime(23,45))
          <  QDateTime(ref->getDateDisponibilite()).addSecs(((ref->getDuree().getHeure())*3600)+((ref->getDuree().getMinute())*60))   )
        return false;

   return true; }
void FenetreTacheC::razPrecedence(QDate dump){
    modelePrecedence->setStringList(remplissageTachePrecedence());
}
