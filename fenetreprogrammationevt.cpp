#include "fenetreprogrammationevt.h"

FenetreProgrammationEvt::FenetreProgrammationEvt(QWidget* parent) : QDialog(parent)
{
    setFixedSize(550, 450);
    setWindowTitle("Programmer");


    layoutCreationEvent1 = new QHBoxLayout;
    layoutCreationEvent2 = new QHBoxLayout;
    layoutCreationEvent3 = new QHBoxLayout;
    layoutCreationEvent4 = new QHBoxLayout;
    layoutCreationEvent = new QVBoxLayout;

    labelIdentificateurEvent = new QLabel("Identificateur de l'evenement");
    identificateurEvent = new QLineEdit;
    titreEventLabel = new QLabel("Titre de l'evenement");
    titreEvent = new QTextEdit;
    labelDateEvent = new QLabel("Date de l'evenement :");
    dateEvent = new QDateTimeEdit(QDateTime::currentDateTime());
    labelEventDuree = new QLabel("Durée :");
    eventHDuree = new QSpinBox;
    eventHDuree->setRange(0, 12);
    eventHDuree->setSuffix(" heure(s)");
    eventMDuree = new QSpinBox;
    eventMDuree->setRange(0,59);
    eventMDuree->setSuffix(" minute(s)");
    bCreerEvent = new QPushButton("Programmer evenement");
    bAnnulerEvent = new QPushButton("Annuler");


    //imbrication creation Event
    layoutCreationEvent1->addWidget(labelIdentificateurEvent);
    layoutCreationEvent1->addWidget(identificateurEvent);
    layoutCreationEvent2->addWidget(titreEventLabel);
    layoutCreationEvent2->addWidget(titreEvent);
    layoutCreationEvent3->addWidget(labelDateEvent);
    layoutCreationEvent3->addWidget(dateEvent);
    layoutCreationEvent3->addWidget(labelEventDuree);
    layoutCreationEvent3->addWidget(eventHDuree);
    layoutCreationEvent3->addWidget(eventMDuree);
    layoutCreationEvent4->addWidget(bCreerEvent);
    layoutCreationEvent4->addWidget(bAnnulerEvent);

    layoutCreationEvent->addLayout(layoutCreationEvent1);
    layoutCreationEvent->addLayout(layoutCreationEvent2);
    layoutCreationEvent->addLayout(layoutCreationEvent3);
    layoutCreationEvent->addLayout(layoutCreationEvent4);
    setLayout(layoutCreationEvent);

    //connections
    QObject::connect(bCreerEvent, SIGNAL(clicked()), this, SLOT(creerEvent()));
    QObject::connect(bAnnulerEvent, SIGNAL(clicked()), this, SLOT(close()));
}
void FenetreProgrammationEvt::creerEvent()
{
    //appel constructeur creation evt
}
