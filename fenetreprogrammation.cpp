#include "fenetreprogrammation.h"
#include "Manager.h"
#include "Tache.h"
#include "QDebug"

FenetreProgrammation::FenetreProgrammation(QWidget* parent) : QDialog(parent)
{
    setFixedSize(550, 450);
    setWindowTitle("Programmer");

    //Liste des projets
    labelmenuDeroulantProjets = new QLabel("Projets :");
    menuDeroulantProjets = new QComboBox;
    labelmenuDeroulantTacheEvent = new QLabel("Taches programmables :");
    menuDeroulantTacheEvent = new QComboBox;

    labelDureeRestante = new QLabel("Durée restante à programmer :");
    dureeRestante = new QTimeEdit;
    dureeRestante->setEnabled(false);
    labelDebutProgrammation = new QLabel("Début :");
    debutProgrammation = new QDateTimeEdit(getArrondi(QDateTime::currentDateTime()));
    debutProgrammation->setEnabled(false);
    labelFinProgrammation = new QLabel("Fin :");
    finProgrammation = new QDateTimeEdit(getArrondi(QDateTime::currentDateTime()));
    finProgrammation->setEnabled(false);
    labelDureeProgrammation = new QLabel("Durée :");
    programmationHDuree = new QSpinBox;
    programmationHDuree->setRange(0, 200);
    programmationHDuree->setSuffix(" heure(s)");
    programmationHDuree->setEnabled(false);
    programmationMDuree = new QSpinBox;
    programmationMDuree->setRange(0,45);
    programmationMDuree->setSingleStep(15);
    programmationMDuree->setSuffix(" minute(s)");
    programmationMDuree->setEnabled(false);
    validerProgrammation = new QPushButton("Programmer");
    validerProgrammation->setEnabled(false);
    annulerProgrammation = new QPushButton("Annuler");

    //disposition
    layoutProgrammation0 = new QHBoxLayout;
    layoutProgrammation0->addWidget(labelmenuDeroulantProjets);
    layoutProgrammation0->addWidget(menuDeroulantProjets);
    layoutProgrammation1 = new QHBoxLayout;
    layoutProgrammation1->addWidget(labelmenuDeroulantTacheEvent);
    layoutProgrammation1->addWidget(menuDeroulantTacheEvent);
    layoutProgrammation2 = new QHBoxLayout;
    layoutProgrammation2->addWidget(labelDureeRestante);
    layoutProgrammation2->addWidget(dureeRestante);
    layoutProgrammation3 = new QHBoxLayout;
    layoutProgrammation3->addWidget(labelDebutProgrammation);
    layoutProgrammation3->addWidget(debutProgrammation);
    layoutProgrammation4 = new QHBoxLayout;
    layoutProgrammation4->addWidget(labelFinProgrammation);
    layoutProgrammation4->addWidget(finProgrammation);
    layoutProgrammation5 = new QHBoxLayout;
    layoutProgrammation5->addWidget(labelDureeProgrammation);
    layoutProgrammation5->addWidget(programmationHDuree);
    layoutProgrammation5->addWidget(programmationMDuree);
    layoutProgrammation6 = new QHBoxLayout;
    layoutProgrammation6->addWidget(validerProgrammation);
    layoutProgrammation6->addWidget(annulerProgrammation);
    layoutProgrammation = new QVBoxLayout;
    layoutProgrammation->addLayout(layoutProgrammation0);
    layoutProgrammation->addLayout(layoutProgrammation1);
    layoutProgrammation->addLayout(layoutProgrammation2);
    layoutProgrammation->addLayout(layoutProgrammation3);
    layoutProgrammation->addLayout(layoutProgrammation4);
    layoutProgrammation->addLayout(layoutProgrammation5);
    layoutProgrammation->addLayout(layoutProgrammation6);
    setLayout(layoutProgrammation);

    initialisationMenuDeroulantProjet();
    chargementMenuTache();

    //connections
    QObject::connect(validerProgrammation, SIGNAL(clicked()), this, SLOT(programmer()));
    QObject::connect(annulerProgrammation, SIGNAL(clicked()), this, SLOT(close()));

    QObject::connect(menuDeroulantProjets, SIGNAL(currentIndexChanged(int)), this, SLOT(changementProjetSelectionne(int)));
    QObject::connect(menuDeroulantTacheEvent, SIGNAL(currentIndexChanged(int)), this, SLOT(changementTacheSelectionnee(int)));

    QObject::connect(debutProgrammation, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(actualiserFinProgrammation(QDateTime)));
    QObject::connect(programmationHDuree, SIGNAL(valueChanged(int)), this, SLOT(actualiserFinProgrammation(int)));
    QObject::connect(programmationMDuree, SIGNAL(valueChanged(int)), this, SLOT(actualiserFinProgrammation(int)));
}


QDateTime FenetreProgrammation::getArrondi (QDateTime tmp)
{
    int minutes = tmp.time().minute();
    QDateTime res = tmp;
    if((minutes>0)&&(minutes<15))
        res = tmp.addSecs((15-minutes)*60);
    else if((minutes>15)&&(minutes<30))
        res = tmp.addSecs((30-minutes)*60);
    else if((minutes>30)&&(minutes<45))
        res = tmp.addSecs((45-minutes)*60);
    else if((minutes>45)&&(minutes<60))
        res = tmp.addSecs((60-minutes)*60);

    return res;
}

//Liste de projet
void FenetreProgrammation::initialisationMenuDeroulantProjet()
{
    menuDeroulantProjets->clear();
    for(int i =0; i< Manager<Projet>::getInstance().getSize(); ++i)
    {
        menuDeroulantProjets->addItem(Manager<Projet>::getInstance().getItem(i)->getId());
    }
    if(menuDeroulantProjets->currentIndex()!=-1) //Si au moins un projet dans la liste
    {
        projetSelectionne = Manager<Projet>::getInstance().findItem(menuDeroulantProjets->currentText());
    }
}
void FenetreProgrammation::changementProjetSelectionne(int i)
{
   if (i!=-1) //appel via Clear()
   {
    projetSelectionne = Manager<Projet>::getInstance().findItem(menuDeroulantProjets->itemText(i));
    chargementMenuTache();
   }
   else projetSelectionne = 0;
}
//Liste de taches
void FenetreProgrammation::chargementMenuTache(void)
{
    if ((menuDeroulantTacheEvent->count())!=0) menuDeroulantTacheEvent->clear();
    if (projetSelectionne != 0)
    {
       // Les taches programmables sont les taches Unitaires simple non programmées ou
       // les taches unitaires preemptives ayant une durée restante non programmée
       for ( QVector<Tache*>::iterator it = projetSelectionne->IteratorSousTachesBegin(); it != projetSelectionne->IteratorSousTachesEnd(); ++it)
        {
            if((typeid(**it)==typeid(TacheUnitaire)))
            {
                if ( (!(*it)->isProgrammed())) menuDeroulantTacheEvent->addItem((*it)->getId());
            }
            else if (typeid(**it)==typeid(TacheUnitairePreemptive))
            {
                if ((dynamic_cast<TacheUnitairePreemptive*>(*it))->getDureeRestante() != TIME::Duree(0,0)) menuDeroulantTacheEvent->addItem((*it)->getId());
            }
            else if(typeid(**it)==typeid(TacheComposite))
            {
                chargementRecursifMenuTache(dynamic_cast<TacheComposite&>(**it));
            }
            else
            {
                QMessageBox::warning(this, "erreur", "Erreur du type de tâche");
            }
        }

       //Premiere Tache de la liste séléctionnée par défaut
       if (menuDeroulantTacheEvent->count() != 0) {
           menuDeroulantTacheEvent->setCurrentIndex(0);
           changementTacheSelectionnee(0);
       }
    }
    else validerProgrammation->setEnabled(false);
}
void FenetreProgrammation::chargementRecursifMenuTache(TacheComposite& t)
{
    for ( QVector<Tache*>::iterator it = t.IteratorSousTachesBegin(); it != t.IteratorSousTachesEnd(); ++it)
    {
        if((typeid(**it)==typeid(TacheUnitaire)))
        {
            if ( (!(*it)->isProgrammed())) menuDeroulantTacheEvent->addItem((*it)->getId());
        }
        else if (typeid(**it)==typeid(TacheUnitairePreemptive))
        {
            if ((dynamic_cast<TacheUnitairePreemptive*>(*it))->getDureeRestante() != TIME::Duree(0,0)) menuDeroulantTacheEvent->addItem((*it)->getId());
        }
        else if(typeid(**it)==typeid(TacheComposite))
        {
            chargementRecursifMenuTache(dynamic_cast<TacheComposite&>(**it));
        }
        else
        {
            QMessageBox::warning(this, "erreur", "Erreur du type de la tâche");
        }
    }
}
void FenetreProgrammation::changementTacheSelectionnee(int i)
{
   if (i!=-1) //un QComboBox->Clear() appel currentIndexChanged avec -1
   {
       tacheSelectionee = Manager<Tache>::getInstance().findItem(menuDeroulantTacheEvent->itemText(i));
       validerProgrammation->setEnabled(true);
        if (typeid(*tacheSelectionee)==typeid(TacheUnitairePreemptive))
        {
            labelDureeRestante->setVisible(true);
            dureeRestante->setVisible(true);

            labelDureeProgrammation->setEnabled(true);
            programmationHDuree->setEnabled(true);
            programmationMDuree->setEnabled(true);
            programmationHDuree->setRange(0,(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getHeure());
            programmationMDuree->setRange(0,(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getMinute());

            programmationHDuree->setValue(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee)->getDuree().getHeure());
            programmationMDuree->setValue(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee)->getDuree().getMinute());
            dureeRestante->setTime(QTime((dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getHeure(),(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getMinute()));
        }
        else //tacheUnitaire
        {
            labelDureeRestante->setVisible(false);
            dureeRestante->setVisible(false);

            labelDureeProgrammation->setEnabled(false);
            programmationHDuree->setEnabled(false);
            programmationMDuree->setEnabled(false);

            programmationHDuree->setValue(dynamic_cast<TacheUnitaire*>(tacheSelectionee)->getDuree().getHeure());
            programmationMDuree->setValue(dynamic_cast<TacheUnitaire*>(tacheSelectionee)->getDuree().getMinute());

        }
       debutProgrammation->setEnabled(true);
       debutProgrammation->setDateTime(QDateTime(tacheSelectionee->getDateDisponibilite(),QTime(7,0)));

   }
   else { //index = -1
        tacheSelectionee = 0;
        debutProgrammation->setEnabled(false);
   }
}


void FenetreProgrammation::actualiserFinProgrammation(int dump){
    //La durée de programmation a été changé veut dire qu'il s'agit d'une tache Unitaire Preemptive
    // Par défaut la durée programmée est la durée restante
    if (((dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getHeure()) != programmationHDuree->value())
        programmationMDuree->setRange(0,45);
    else
        programmationMDuree->setRange(0,(dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionee))->getDureeRestante().getMinute());

    finProgrammation->setDateTime(debutProgrammation->dateTime().addSecs(programmationHDuree->value()*3600+programmationMDuree->value()*60));
    //verification();
}
void FenetreProgrammation::actualiserFinProgrammation(QDateTime dump){
    int minutes = dump.time().minute();
    QDateTime temp = dump;
        if((minutes>0)&&(minutes<15))
            temp = dump.addSecs((15-minutes)*60);
        else if((minutes>15)&&(minutes<30))
            temp = dump.addSecs((30-minutes)*60);
        else if((minutes>30)&&(minutes<45))
            temp = dump.addSecs((45-minutes)*60);
        else if((minutes>45)&&(minutes<60))
            temp = dump.addSecs((60-minutes)*60);
        debutProgrammation->setDateTime(temp);

        finProgrammation->setDateTime(debutProgrammation->dateTime().addSecs(programmationHDuree->value()*3600+programmationMDuree->value()*60));
    //verification();
}

void FenetreProgrammation::programmer()
{
    if(debutProgrammation->time().hour()<7)
        QMessageBox::information(this, "Erreur", "Il est impossible de programmer une tache avant 7h.");

    else if(finProgrammation->time()>QTime(22, 1))
        QMessageBox::information(this, "Erreur", "Il est impossible de programmer une tache après 22h.");

    else if((programmationHDuree->value() >= 12) && (programmationMDuree->value() > 0) )
        QMessageBox::information(this, "Erreur", "Il est impossible de programmer une tache plus de 12h.");

    else {
        TacheUnitaire* newE = dynamic_cast<TacheUnitaire*>(tacheSelectionee);
        QDateTime horaire = debutProgrammation->dateTime();
        TIME::Duree duree = TIME::Duree(programmationHDuree->value(),programmationMDuree->value());
        Manager<Programmation>::getInstance().ajouterProgrammation(*(dynamic_cast<Evenement*>(newE)),horaire,duree);
        tacheSelectionee->setProgrammed();
        // on met à jour le calendrier
        this->close();
    }
}


