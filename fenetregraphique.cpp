#include "fenetregraphique.h"
#include "fenetreprogrammation.h"
#include "fenetreprogrammationevt.h"
#include "fenetreexportsemaine.h"
#include "fenetreprojet.h"
#include "fenetretachec.h"
#include "fenetretacheu.h"
#include "fenetretacheedition.h"
#include "fenetreprojetedition.h"
#include "fenetreprogrammationsuppr.h"

#include <QDebug>
#include <QVector>
#include <QString>

#include "Manager.h"
#include "Projet.h"
#include "Tache.h"


Projet* FenetreGraphique::projetNull= new Projet("", QDate::currentDate(), QDate::currentDate());
Projet* FenetreGraphique::projetActif = projetNull;
Tache* FenetreGraphique::tacheActive = 0;

FenetreGraphique::FenetreGraphique(QWidget* parent): QWidget(parent){

    //Fentre principale
    this->setWindowTitle(QString("Project Calendar"));
    //setFixedSize(1200,800);
    setFixedSize(900,600);
    //qApp->setStyleSheet("QTableView{border:1px solid red;}");

    //Onglets saisie et affichage
    onglets = new QTabWidget(this);
    //onglets->setGeometry(10,10,1180,780);
    onglets->setGeometry(10,10,980,540);
    pageSaisie = new QWidget;
    pageAffichage = new QWidget;
    pageExport = new QWidget;

    //Page Saisie//////////////////////////////////////////////////////////////////////////////////////////////
    layoutPageSaisiePrincipal = new QHBoxLayout;

    //GroupBox selectionprojet + treeview
    layoutProjetTV = new QVBoxLayout;
    gBProjetTV = new QGroupBox(this);
    gBProjetTV->setTitle("Projets");
    gBProjetTV->setFixedWidth(300);

    //onglets creation projet, tache, event
    supportOngletsCreation = new QWidget;
    ongletsNiveau2 = new QTabWidget(supportOngletsCreation);
    ongletsNiveau2->setGeometry(0,10,540,420);
    //ongletsNiveau2->setGeometry(0,10,840,720);
    pageCreationprojet = new QWidget;
    pageTacheUnitaire = new QWidget;
    pageTacheComposite = new QWidget;
    initialisationTabPTUTC();

    //Liste des projets
    bNouveauProjet = new QPushButton("Nouveau projet");
    menuDeroulantProjets = new QComboBox;
    initialisationMenuProjet();

    //Treeview
    modelTreeView = new QStandardItemModel;
    vueTreeView = new QTreeView;
    vueTreeView->setModel(modelTreeView);
    vueTreeView->setHeaderHidden(true);
    vueTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //creation projets
    layoutCreationProjet1 = new QHBoxLayout;
    layoutCreationProjet2 = new QHBoxLayout;
    layoutCreationProjet3 = new QHBoxLayout;
    layoutCreationProjet4 = new QHBoxLayout;
    layoutCreationProjet5 = new QHBoxLayout;
    layoutCreationProjet = new QVBoxLayout;

    labelNomProjet = new QLabel("Nom du projet :");    
    nomProjet = new QLabel("");
    labelProjetDateDispo = new QLabel("Date de disponibilité : ");
    projetDateDispo = new QLabel("");
    labelProjetEcheance = new QLabel("Echéance du projet :");
    projetEcheance = new QLabel("");
    bCreerTacheUProjet = new QPushButton("Creer tache unitaire");
    bCreerTacheCProjet = new QPushButton("Creer tache composite");
    bModifierProjet = new QPushButton("Modifier le projet");
    bdetruireProjet = new QPushButton("Supprimer");

    //creation tache
    layoutCreationTache1 = new QHBoxLayout;
    layoutCreationTache2 = new QHBoxLayout;
    layoutCreationTache3 = new QHBoxLayout;
    layoutCreationTache4 = new QHBoxLayout;
    layoutCreationTache5 = new QHBoxLayout;
    layoutCreationTache6 = new QHBoxLayout;
    layoutCreationTache7 = new QHBoxLayout;
    layoutCreationTache8 = new QHBoxLayout;
    layoutCreationTache = new QVBoxLayout;

    //Fenetre TacheUnitaire
    labelIdentificateurTache = new QLabel("Identificateur de la tache : ");
    identificateurTache = new QLabel("");
    preemptiveTache = new QCheckBox("Preemptive");
    preemptiveTache->setDisabled(true);
    titreTacheLabel = new QLabel("Titre de la tache :");
    titreTache = new QLabel("");
    labelTacheEtat = new QLabel("Etat :");
    tacheEtat = new QLabel("");
    labelDisponibiliteTache = new QLabel("Date de disponibilité :");
    disponibiliteTache = new QLabel("");
    labelTacheEcheance = new QLabel("Date d'écheance :");
    tacheEcheance = new QLabel("");
    labelTacheDuree = new QLabel("Durée :");
    tacheDuree = new QLabel("");
    labelPrecedenceTacheU = new QLabel("Tâches précédentes");
    modelePrecedenceTacheU = new QStringListModel(QStringList(""));
    vuePrecedenceTacheU = new QListView;
    vuePrecedenceTacheU->setModel(modelePrecedenceTacheU);
    vuePrecedenceTacheU->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bModifierTacheU = new QPushButton("Modifier");
    bSupprimerTacheU = new QPushButton("Supprimer");

    //creation Event
    layoutCreationEvent1 = new QHBoxLayout;
    layoutCreationEvent2 = new QHBoxLayout;
    layoutCreationEvent3 = new QHBoxLayout;
    layoutCreationEvent4 = new QHBoxLayout;
    layoutCreationEvent5 = new QHBoxLayout;
    layoutCreationEvent6 = new QHBoxLayout;
    layoutCreationEvent7 = new QHBoxLayout;
    layoutCreationEvent8 = new QHBoxLayout;
    layoutCreationEvent9 = new QHBoxLayout;
    layoutCreationEvent = new QVBoxLayout;

    //Fenetre Tache Composite
    labelIdentificateurTacheC = new QLabel("Identificateur de la tache : ");
    identificateurTacheC = new QLabel("");
    titreTacheLabelC = new QLabel("Titre de la tache");
    titreTacheC = new QLabel("");
    labelTacheEtatC = new QLabel("Etat :");
    tacheEtatC = new QLabel("");
    labelDisponibiliteTacheC = new QLabel("Date de disponibilité :");
    disponibiliteTacheC = new QLabel("");
    labelTacheCEcheance = new QLabel("Date d'écheance :");
    tacheCEcheance = new QLabel("");
    labelTacheCDuree = new QLabel("Durée totale:");
    tacheCDuree = new QLabel("");
    labelPrecedenceTacheC = new QLabel("Tâches précédentes");
    modelePrecedenceTacheC = new QStringListModel(QStringList(""));
    vuePrecedenceTacheC = new QListView;
    vuePrecedenceTacheC->setModel(modelePrecedenceTacheC);
    vuePrecedenceTacheC->setEditTriggers(QAbstractItemView::NoEditTriggers);

    bTacheCCreerTacheU = new QPushButton("Creer sous tâche unitaire");
    bTacheCCreerTacheC = new QPushButton("Creer sous tâche composite");
    bModifierTacheC = new QPushButton("Modifier");
    bSupprimerTacheC = new QPushButton("Supprimer");

    //Imbrication projets + treeview
    layoutProjetTV->addWidget(bNouveauProjet);
    layoutProjetTV->addWidget(menuDeroulantProjets);
    layoutProjetTV->addWidget(vueTreeView);
    gBProjetTV->setLayout(layoutProjetTV);

    //imbrication onglet creation projet
    layoutCreationProjet1->addWidget(labelNomProjet);
    layoutCreationProjet1->addWidget(nomProjet);
    layoutCreationProjet2->addWidget(labelProjetDateDispo);
    layoutCreationProjet2->addWidget(projetDateDispo);
    layoutCreationProjet3->addWidget(labelProjetEcheance);
    layoutCreationProjet3->addWidget(projetEcheance);
    layoutCreationProjet4->addWidget(bCreerTacheUProjet);
    layoutCreationProjet4->addWidget(bCreerTacheCProjet);
    layoutCreationProjet5->addWidget(bModifierProjet);
    layoutCreationProjet5->addWidget(bdetruireProjet);
    layoutCreationProjet->addLayout(layoutCreationProjet1);
    layoutCreationProjet->addLayout(layoutCreationProjet2);
    layoutCreationProjet->addLayout(layoutCreationProjet3);
    layoutCreationProjet->addLayout(layoutCreationProjet4);
    layoutCreationProjet->addLayout(layoutCreationProjet5);
    pageCreationprojet->setLayout(layoutCreationProjet);

    //imbrication creation tache
    layoutCreationTache1->addWidget(labelIdentificateurTache);
    layoutCreationTache1->addWidget(identificateurTache);
    layoutCreationTache1->addWidget(preemptiveTache);
    layoutCreationTache2->addWidget(titreTacheLabel);
    layoutCreationTache2->addWidget(titreTache);
    layoutCreationTache3->addWidget(labelTacheEtat);
    layoutCreationTache3->addWidget(tacheEtat);
    layoutCreationTache4->addWidget(labelDisponibiliteTache);
    layoutCreationTache4->addWidget(disponibiliteTache);
    layoutCreationTache5->addWidget(labelTacheEcheance);
    layoutCreationTache5->addWidget(tacheEcheance);
    layoutCreationTache6->addWidget(labelTacheDuree);
    layoutCreationTache6->addWidget(tacheDuree);
    layoutCreationTache7->addWidget(labelPrecedenceTacheU);
    layoutCreationTache7->addWidget(vuePrecedenceTacheU);
    layoutCreationTache8->addWidget(bModifierTacheU);
    layoutCreationTache8->addWidget(bSupprimerTacheU);
    layoutCreationTache->addLayout(layoutCreationTache1);
    layoutCreationTache->addLayout(layoutCreationTache2);
    layoutCreationTache->addLayout(layoutCreationTache3);
    layoutCreationTache->addLayout(layoutCreationTache4);
    layoutCreationTache->addLayout(layoutCreationTache5);
    layoutCreationTache->addLayout(layoutCreationTache6);
    layoutCreationTache->addLayout(layoutCreationTache7);
    layoutCreationTache->addLayout(layoutCreationTache8);

    pageTacheUnitaire->setLayout(layoutCreationTache);

    //imbrication creation Event
    layoutCreationEvent1->addWidget(labelIdentificateurTacheC);
    layoutCreationEvent1->addWidget(identificateurTacheC);
    layoutCreationEvent2->addWidget(titreTacheLabelC);
    layoutCreationEvent2->addWidget(titreTacheC);
    layoutCreationEvent3->addWidget(labelTacheEtatC);
    layoutCreationEvent3->addWidget(tacheEtatC);
    layoutCreationEvent4->addWidget(labelDisponibiliteTacheC);
    layoutCreationEvent4->addWidget(disponibiliteTacheC);
    layoutCreationEvent5->addWidget(labelTacheCEcheance);
    layoutCreationEvent5->addWidget(tacheCEcheance);
    layoutCreationEvent6->addWidget(labelTacheCDuree);
    layoutCreationEvent6->addWidget(tacheCDuree);
    layoutCreationEvent7->addWidget(labelPrecedenceTacheC);
    layoutCreationEvent7->addWidget(vuePrecedenceTacheC);
    layoutCreationEvent8->addWidget(bTacheCCreerTacheU);
    layoutCreationEvent8->addWidget(bTacheCCreerTacheC);
    layoutCreationEvent9->addWidget(bModifierTacheC);
    layoutCreationEvent9->addWidget(bSupprimerTacheC);

    layoutCreationEvent->addLayout(layoutCreationEvent1);
    layoutCreationEvent->addLayout(layoutCreationEvent2);
    layoutCreationEvent->addLayout(layoutCreationEvent3);
    layoutCreationEvent->addLayout(layoutCreationEvent4);
    layoutCreationEvent->addLayout(layoutCreationEvent5);
    layoutCreationEvent->addLayout(layoutCreationEvent6);
    layoutCreationEvent->addLayout(layoutCreationEvent7);
    layoutCreationEvent->addLayout(layoutCreationEvent8);
    layoutCreationEvent->addLayout(layoutCreationEvent9);
    pageTacheComposite->setLayout(layoutCreationEvent);

    //imbrication onglets niveau2 + layout principal pageSaisie
    ongletsNiveau2->addTab(pageCreationprojet, "Projet");
    ongletsNiveau2->addTab(pageTacheUnitaire, "Tâche unitaire");
    ongletsNiveau2->addTab(pageTacheComposite, "Tâche composite");
    layoutPageSaisiePrincipal->addWidget(gBProjetTV);
    layoutPageSaisiePrincipal->addWidget(supportOngletsCreation);

    //page Affichage/////////////////////////////////////////////////////////////////////////////////////////////////////

    layoutPageAffichagePrincipal = new QVBoxLayout;

    //En tete (gestion semaine suivante/precedente
    layoutHautAgenda = new QHBoxLayout;
    dateReferenceAgenda = new QDate(QDate::currentDate());
    jourActuel = new QPushButton(constructionMessageSemaineAgenda(dateReferenceAgenda));
    jourActuel->setEnabled(false);
    bSemainePrecedente = new QPushButton("Semaine precedent");
    bSemaineSuivante = new QPushButton("Semaine suivant");

    layoutHautAgenda->addWidget(bSemainePrecedente);
    layoutHautAgenda->addWidget(jourActuel);
    layoutHautAgenda->addWidget(bSemaineSuivante);

    QStandardItemModel *modelAgenda = new QStandardItemModel(60, 7);
    QTableView *vueAgenda = new QTableView;
    vueAgenda->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueAgenda->setModel(modelAgenda);
    vueAgenda->setFixedWidth(1157);
    vueAgenda->setFixedHeight(625);
    vueAgenda->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    vueAgenda->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    vueAgenda->setSelectionMode(QAbstractItemView::SingleSelection);

    //===========
    vueAgenda->setGridStyle(Qt::DashDotLine);

    miseAJourTableau(*modelAgenda); //, *vueAgenda);

    itemCol0 = new QStandardItem(chaineJoursHeader(1, dateReferenceAgenda->addDays(1-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol1 = new QStandardItem(chaineJoursHeader(2, dateReferenceAgenda->addDays(2-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol2 = new QStandardItem(chaineJoursHeader(3, dateReferenceAgenda->addDays(3-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol3 = new QStandardItem(chaineJoursHeader(4, dateReferenceAgenda->addDays(4-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol4 = new QStandardItem(chaineJoursHeader(5, dateReferenceAgenda->addDays(5-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol5 = new QStandardItem(chaineJoursHeader(6, dateReferenceAgenda->addDays(6-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));
    itemCol6 = new QStandardItem(chaineJoursHeader(7, dateReferenceAgenda->addDays(7-dateReferenceAgenda->dayOfWeek()).day(), dateReferenceAgenda->month()));

    modelAgenda->setHorizontalHeaderItem(0, itemCol0);
    modelAgenda->setHorizontalHeaderItem(1, itemCol1);
    modelAgenda->setHorizontalHeaderItem(2, itemCol2);
    modelAgenda->setHorizontalHeaderItem(3, itemCol3);
    modelAgenda->setHorizontalHeaderItem(4, itemCol4);
    modelAgenda->setHorizontalHeaderItem(5, itemCol5);
    modelAgenda->setHorizontalHeaderItem(6, itemCol6);

    QStringList headerVTableau;
    for(unsigned int i=7; i<22; i++)
    {
        headerVTableau << QString::number(i)+"h00";
        for(unsigned int j=1; j<4; j++)
        {
            headerVTableau << "";
            //headerVTableau << QString::number(j*15);
        }
    }
    modelAgenda->setVerticalHeaderLabels(headerVTableau);
    miseEnFormeLigneColonnes(vueAgenda);

    //bas de page (programmation)
    layoutProgrammation = new QHBoxLayout;

    bProgrammerTache = new QPushButton("Programmer tâche");
    bProgrammerEvt = new QPushButton("Programmer Evenement");
    bSupprimerProgrammation = new QPushButton("Supprimer programmation");
    layoutProgrammation->addWidget(bProgrammerTache);
    layoutProgrammation->addWidget(bProgrammerEvt);
    layoutProgrammation->addWidget(bSupprimerProgrammation);

    //pose des layouts pageAffichage
    layoutPageAffichagePrincipal->addLayout(layoutHautAgenda);
    layoutPageAffichagePrincipal->addWidget(vueAgenda);
    layoutPageAffichagePrincipal->addLayout(layoutProgrammation);

    //pageExport/////////////////////////////////////////////////////////////////////////////////////////////////////
    layoutPageExportPrincipal = new QHBoxLayout;
    widgetSecondairePageExport = new QWidget;
    widgetSecondairePageExport->setFixedSize(400, 300);
    layoutPageExportSecondaire = new QVBoxLayout(widgetSecondairePageExport);

    labelExport = new QLabel("Chosir le type d'export:");
    nomFichierExport = new QLineEdit("NomFichier");
    bExportImport = new QPushButton("Importer");
    bExportImport->setEnabled(false);
    bExportProgrammationBrut = new QPushButton("Programmation totale (brut)");
    bExportProgrammationXml = new QPushButton("Programmation totale (Xml");
    bExportSemaineBrut = new QPushButton("Programmation semaine (brut)");
    bExportSemaineXml = new QPushButton("Programmation semaine (Xml)");

    //pose des layout page export
    layoutPageExportSecondaire->addWidget(labelExport);
    layoutPageExportSecondaire->addWidget(nomFichierExport);
    layoutPageExportSecondaire->addWidget(bExportImport);
    layoutPageExportSecondaire->addWidget(bExportProgrammationBrut);
    layoutPageExportSecondaire->addWidget(bExportProgrammationXml);
    layoutPageExportSecondaire->addWidget(bExportSemaineBrut);
    layoutPageExportSecondaire->addWidget(bExportSemaineXml);
    layoutPageExportPrincipal->addWidget(widgetSecondairePageExport);

    //pose des layouts principaux
    pageAffichage->setLayout(layoutPageAffichagePrincipal);
    pageSaisie->setLayout(layoutPageSaisiePrincipal);
    pageExport->setLayout(layoutPageExportPrincipal);

    onglets->addTab(pageAffichage, "Agenda");
    onglets->addTab(pageSaisie, "Gestionnaire de projet");
    onglets->addTab(pageExport, "Exports");

    //connections page saisie-------------
    QObject::connect(vueAgenda, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(affichageContenuCase(const QModelIndex)));
    QObject::connect(bSemainePrecedente, SIGNAL(clicked()), this, SLOT(semainePrecedente()));
    QObject::connect(bSemaineSuivante, SIGNAL(clicked()), this, SLOT(semaineSuivante()));
    QObject::connect(bProgrammerTache, SIGNAL(clicked()), this, SLOT(nouvelleProgrammationTache()));
    QObject::connect(bProgrammerEvt, SIGNAL(clicked()), this, SLOT(nouvelleProgrammationEvt()));
    QObject::connect(bSupprimerProgrammation, SIGNAL(clicked()), this, SLOT(supprimerProgrammation()));

    //connexions page affichage----------
    //tree view
    QObject::connect(menuDeroulantProjets, SIGNAL(currentIndexChanged(int)), this, SLOT(changerProjetTreeView(int)));
    QObject::connect(vueTreeView, SIGNAL(clicked(const QModelIndex)), this, SLOT(selectionTreeView(const QModelIndex)));

    //Creation projet, tache, evenement
    QObject::connect(bNouveauProjet, SIGNAL(clicked()), this, SLOT(creerProjet()));
    QObject::connect(bCreerTacheUProjet, SIGNAL(clicked()), this, SLOT(creerTacheUProjet()));
    QObject::connect(bCreerTacheCProjet, SIGNAL(clicked()), this, SLOT(creerTacheCProjet()));
    QObject::connect(bModifierProjet, SIGNAL(clicked()), this, SLOT(modifierProjet()));
    QObject::connect(bdetruireProjet, SIGNAL(clicked()), this, SLOT(detruireProjet()));
    QObject::connect(bModifierTacheU, SIGNAL(clicked()), this, SLOT(modifierTacheU()));
    QObject::connect(bSupprimerTacheU, SIGNAL(clicked()), this, SLOT(supprimerTacheU()));
    QObject::connect(bTacheCCreerTacheU, SIGNAL(clicked()), this, SLOT(creerTacheUTacheC()));
    QObject::connect(bTacheCCreerTacheC, SIGNAL(clicked()), this, SLOT(creerTacheCTacheC()));
    QObject::connect(bModifierTacheC, SIGNAL(clicked()), this, SLOT(modifierTacheC()));
    QObject::connect(bSupprimerTacheC, SIGNAL(clicked()), this, SLOT(supprimerTacheC()));

    //connexions page export--------------
    QObject::connect(nomFichierExport, SIGNAL(textEdited(QString)), this, SLOT(validationNomExport(QString)));
    QObject::connect(bExportProgrammationBrut, SIGNAL(clicked()), this, SLOT(exportProgrammationBrut()));
    QObject::connect(bExportProgrammationXml, SIGNAL(clicked()), this, SLOT(exportProgrammationXml()));
    QObject::connect(bExportSemaineBrut, SIGNAL(clicked()), this, SLOT(exportSemaineBrut()));
    QObject::connect(bExportSemaineXml, SIGNAL(clicked()), this, SLOT(exportSemaineXml()));
}

//=================
void FenetreGraphique::setProjetActif(Projet& projet)
{
    projetActif = &projet;
}
void FenetreGraphique::nouvelleProgrammationTache()
{
    FenetreProgrammation fen;
    fen.exec();

    //on recharge l'affichage de l'agenda
}
void FenetreGraphique::nouvelleProgrammationEvt()
{
    FenetreProgrammationEvt fen;
    fen.exec();
    //on recharge l'affichage de l'agenda
}
void FenetreGraphique::supprimerProgrammation()
{
    FenetreProgrammationSuppr fen;
    fen.exec();
    // on rechearge l'affichage de l'agenda
}

void FenetreGraphique::changerProjetTreeView(int i)
{
    if (i!=-1)
        projetActif = Manager<Projet>::getInstance().findItem(menuDeroulantProjets->itemText(i));

    majProjetTreeView();
}
void FenetreGraphique::majProjetTreeView (void){
    ongletsNiveau2->setCurrentWidget(pageCreationprojet);
    pageTacheComposite->setEnabled(false);
    pageTacheUnitaire->setEnabled(false);
    if(projetActif!=projetNull)
    {
        pageCreationprojet->setEnabled(true);
        remplissageOngletProjet();
    }
    else
        pageCreationprojet->setEnabled(false);

    majTachesTreeView();
}
void FenetreGraphique::majTachesTreeView(void)
{
    modelTreeView->clear();

    for ( QVector<Tache*>::iterator it = projetActif->IteratorSousTachesBegin(); it != projetActif->IteratorSousTachesEnd(); ++it)
    {
        if((typeid(**it)==typeid(TacheUnitaire))||(typeid(**it)==typeid(TacheUnitairePreemptive)))
        {
            QStandardItem* itemTmp = new QStandardItem((*it)->getId());
            modelTreeView->appendRow(itemTmp);
        }
        else if(typeid(**it)==typeid(TacheComposite))
        {
            QStandardItem* itemTmp = new QStandardItem((*it)->getId());
            modelTreeView->appendRow(itemTmp);
            recursiveTreeView(*itemTmp,dynamic_cast<TacheComposite&>(**it));
        }
        else
        {
            QMessageBox::warning(this, "erreur", "la tache est du type");
        }
    }
    vueTreeView->expandAll();
}
void FenetreGraphique::recursiveTreeView(QStandardItem& itemPere, TacheComposite& t)
{
    for ( QVector<Tache*>::iterator it = t.IteratorSousTachesBegin(); it != t.IteratorSousTachesEnd(); ++it)
    {
        if((typeid(**it)==typeid(TacheUnitaire))||(typeid(**it)==typeid(TacheUnitairePreemptive)))
        {
            QStandardItem* itemTmp = new QStandardItem((*it)->getId());
            itemPere.appendRow(itemTmp);
        }
        else if(typeid(**it)==typeid(TacheComposite))
        {
            QStandardItem* itemTmp = new QStandardItem((*it)->getId());
            itemPere.appendRow(itemTmp);
            recursiveTreeView(*itemTmp,dynamic_cast<TacheComposite&>(**it));
        }
        else
        {
        QMessageBox::warning(this, "erreur", "la tache est du type");
        }
    }
}
void FenetreGraphique::majSelectionTacheActive(void)
{
    if (tacheActive==0) {}
    else if ((typeid(*tacheActive)==typeid(TacheUnitaire)) || (typeid(*tacheActive)==typeid(TacheUnitairePreemptive)))
    {
        //si tache unitaire selectionne
        pageTacheUnitaire->setEnabled(true);
        ongletsNiveau2->setCurrentWidget(pageTacheUnitaire);
        pageTacheComposite->setEnabled(false);
        remplissageOngletTacheU();
    }
    else if (typeid(*tacheActive)==typeid(TacheComposite))
    {
        //si tache composite selectionne
        pageTacheComposite->setEnabled(true);
        ongletsNiveau2->setCurrentWidget(pageTacheComposite);
        pageTacheUnitaire->setEnabled(false);
        remplissageOngletTacheC();
    }
}
void FenetreGraphique::selectionTreeView(const QModelIndex& I)
{
    //QItemSelectionModel *selectionTreeView = vueTreeView->selectionModel();
    QVariant elementSelectionneTreeView = modelTreeView->data(I,Qt::DisplayRole);
    //QMessageBox::information(this, "Elément sélectionné",elementSelectionneTreeView.toString());

    Tache& tmp = Manager<Tache>::getInstance().getItem(elementSelectionneTreeView.toString());
    tacheActive = &tmp;
    //QMessageBox::information(this, "tache active",tacheActive->getId());
    majSelectionTacheActive();
}
void FenetreGraphique::initialisationMenuProjet()
{
    menuDeroulantProjets->clear();
    for(int i =0; i< Manager<Projet>::getInstance().getSize(); ++i)
    {
        menuDeroulantProjets->addItem(Manager<Projet>::getInstance().getItem(i)->getId());
    }
}
void FenetreGraphique::ajoutMenuProjet(Projet& projet)
{
    //initialisationMenuProjet();
    menuDeroulantProjets->addItem(projet.getId());
    menuDeroulantProjets->setCurrentText(projet.getId());
    //menuDeroulantProjets->setsupprimerPro( Manager<Projet>::getInstance().findObject(projet.getId()));
}
void FenetreGraphique::initialisationTabPTUTC()
{
    pageTacheUnitaire->setEnabled(false);
    pageTacheComposite->setEnabled(false);
    pageCreationprojet->setEnabled(false);
}
QStringList FenetreGraphique::remplissageTachePrecedence()
{
    QStringList listeTachePrecedentes;
    for (QVector<Tache*>::const_iterator it = tacheActive->ConstIteratorPrecedencesBegin(); it != tacheActive->ConstIteratorPrecedencesEnd(); ++it ){
        listeTachePrecedentes << (*it)->getId();
    }
    return listeTachePrecedentes;
}
//Gestion projets
void FenetreGraphique::creerProjet()
{
    Projet* old = projetActif;
    FenetreProjet fen;
    fen.exec();
    if (projetActif != old){ //Si abandon lors de la création d'un projet
        ajoutMenuProjet(*projetActif);
        majProjetTreeView();
    }
}
void FenetreGraphique::creerTacheUProjet()
{
    Tache* p=0; //Pas de tache mère mais un projet
    FenetreTacheU fen(*p);
    fen.exec();
    majTachesTreeView();
}
void FenetreGraphique::creerTacheCProjet()
{
    Tache* p=0; //Pas de tache mère mais un projet
    FenetreTacheC fen(*p);
    fen.exec();
    majTachesTreeView();
}
void FenetreGraphique::modifierProjet()
{
    FenetreProjetEdition fen(this);
    fen.exec();
    if (projetActif->getId() != menuDeroulantProjets->currentText()) //actualisation du nouvel id
        menuDeroulantProjets->setItemText(menuDeroulantProjets->currentIndex(),projetActif->getId());
    remplissageOngletProjet();
}
void FenetreGraphique::detruireProjet()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Supression projet", "Voulez-vous suprimer le projet " + projetActif->getId() + "\n(supression de toutes ses tâches)?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Test", "Suppression du projet");
        //int i = Manager<Projet>::getInstance().detruireProjet(projetActif);
        int i = projetActif->detruireProjet();
        projetActif= projetNull;

        menuDeroulantProjets->removeItem(i);

        if(!(Manager<Projet>::getInstance().isEmpty()))
        {
            projetActif = Manager<Projet>::getInstance().getItem(0);
        }
        else
        {
            projetActif = projetNull;
            pageCreationprojet->setEnabled(false);
            remplissageOngletProjet();
        }
        majProjetTreeView();
        //mise a jour agenda
    }
    else
    {
        //on fait rien
        QMessageBox::information(this, "Test", "non");

    }
}
void FenetreGraphique::remplissageOngletProjet(void)
{
    //QMessageBox::information(this, "test", "remplissage onglet projet avec argument");
    if (projetActif!=0)
    {
        nomProjet->setText(projetActif->getId());
        projetDateDispo->setText(projetActif->getDispo().toString("dd/MM/yyyy"));
        projetEcheance->setText(projetActif->getEcheance().toString("dd/MM/yyyy"));
    }
}
//gestion tache unitaire
void FenetreGraphique::modifierTacheU()
{
    // construction nouvelle fenetre
    FenetreTacheEdition fen(this);
    fen.exec();
    majTachesTreeView();
    remplissageOngletTacheU();
}
void FenetreGraphique::supprimerTacheU()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Supression tâche unitaire", "Voulez vous suprimer cette tâche?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Test", "suppression de la tâche U");
        projetActif->supprimerTache(tacheActive);
        tacheActive=0;
        majSelectionTacheActive();
        majTachesTreeView();
        //mise a jour agenda

        pageTacheUnitaire->setEnabled(false);
    }
    else
    {
        //on fait rien
        QMessageBox::information(this, "Test", "non");

    }
}
void FenetreGraphique::remplissageOngletTacheU()
{
    if (tacheActive != 0 ) {
        identificateurTache->setText(tacheActive->getId());
        preemptiveTache->setChecked((dynamic_cast<TacheUnitaire*>(tacheActive))->isPreemptive());
        titreTache->setText(tacheActive->getTitre());
        disponibiliteTache->setText(tacheActive->getDateDisponibilite().toString("dd/MM/yyyy"));
        tacheEcheance->setText(tacheActive->getDateEcheance().toString("dd/MM/yyyy"));
        tacheDuree->setText(tacheActive->getDuree().toString());

        modelePrecedenceTacheU->setStringList(QStringList());
        modelePrecedenceTacheU->setStringList(remplissageTachePrecedence());
    }
}
//gestion tache composite
void FenetreGraphique::creerTacheUTacheC()
{
    FenetreTacheU fen(*tacheActive);
    fen.exec();
    majTachesTreeView();
}
void FenetreGraphique::creerTacheCTacheC()
{
    FenetreTacheC fen(*tacheActive);
    fen.exec();
    majTachesTreeView();
}
void FenetreGraphique::modifierTacheC()
{
    FenetreTacheEdition fen(this);
    fen.exec();
    majTachesTreeView();
    remplissageOngletTacheC();
}
void FenetreGraphique::supprimerTacheC()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Supression tâche composite", "Voulez vous suprimer cette tâche (supression de toutes ses sous-tâches)?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "OK", "suppression de la tâche composite");
        projetActif->supprimerTache(tacheActive);
        tacheActive=0;
        majSelectionTacheActive();
        majTachesTreeView();

        //mise a jour agenda

        pageTacheComposite->setEnabled(false);
    }
    else
    {
        //on fait rien
        QMessageBox::information(this, "Test", "non");

    }
}
void FenetreGraphique::remplissageOngletTacheC()
{
    if (tacheActive != 0 )
    {
        identificateurTacheC->setText(tacheActive->getId());
        titreTacheC->setText(tacheActive->getTitre());
        disponibiliteTacheC->setText(tacheActive->getDateDisponibilite().toString("dd/MM/yyyy"));
        tacheCEcheance->setText(tacheActive->getDateEcheance().toString("dd/MM/yyyy"));
        tacheCDuree->setText(tacheActive->getDuree().toString());
        //tacheEtat->setText(tacheActive->getEtat());
        modelePrecedenceTacheC->setStringList(QStringList());
        modelePrecedenceTacheC->setStringList(remplissageTachePrecedence());
    }
}
//gestion export
void FenetreGraphique::validationNomExport(QString s)
{
    QRegExp regExpNomFichier("^[a-z|A-Z|\\d]{1,25}$");
    if(s.contains(regExpNomFichier))
    {
        bExportProgrammationBrut->setEnabled(true);
        bExportProgrammationXml->setEnabled(true);
        bExportSemaineBrut->setEnabled(true);
        bExportSemaineXml->setEnabled(true);
     }
    else
    {
        bExportProgrammationBrut->setEnabled(false);
        bExportProgrammationXml->setEnabled(false);
        bExportSemaineBrut->setEnabled(false);
        bExportSemaineXml->setEnabled(false);
    }
}
void FenetreGraphique::exportProgrammationBrut()
{
    //appel export programmation totale brut
}
void FenetreGraphique::exportProgrammationXml()
{
    //appel export programmation totale xml
}
void FenetreGraphique::exportSemaineBrut()
{
    //attention au type d export: argument constructeur fenetre
    FenetreExportSemaine fen;
    fen.exec();
}
void FenetreGraphique::exportSemaineXml()
{
    //attention au type d export: argument constructeur fenetre
    FenetreExportSemaine fen;
    fen.exec();
}
//Gestion agenda
QString FenetreGraphique::constructionMessageSemaineAgenda(QDate* d)
{
    QString boutonSemaineAgenda("Semaine : ");
    boutonSemaineAgenda+=QString::number(d->weekNumber());
    boutonSemaineAgenda+=" (";
    boutonSemaineAgenda+=d->toString();
    boutonSemaineAgenda+=")";
    return boutonSemaineAgenda;
}
void FenetreGraphique::semainePrecedente()
{
    //modification bouton jourActuel
    QDate *dateTemp = new QDate;
    *dateTemp = dateReferenceAgenda->addDays(-7);
    *dateReferenceAgenda=*dateTemp;
    jourActuel->setText(constructionMessageSemaineAgenda(dateReferenceAgenda));
    delete dateTemp;

    //modification header
    miseAJourHeader();

    //generation tableau
    miseAJourTableau(*modelAgenda);
    //miseAJourTableau(*modelAgenda, *vueAgenda);
}
void FenetreGraphique::semaineSuivante()
{
    QDate *dateTemp = new QDate;
    *dateTemp = dateReferenceAgenda->addDays(7);
    *dateReferenceAgenda=*dateTemp;
    jourActuel->setText(constructionMessageSemaineAgenda(dateReferenceAgenda));
    delete dateTemp;

    //modification header
    miseAJourHeader();

    //generation tableau
}
void FenetreGraphique::miseAJourHeader()
{
    int jourDeLaSemaine = dateReferenceAgenda->dayOfWeek();

    itemCol0->setText(chaineJoursHeader(1, dateReferenceAgenda->addDays(1-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(1-jourDeLaSemaine).month()));
    itemCol1->setText(chaineJoursHeader(2, dateReferenceAgenda->addDays(2-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(2-jourDeLaSemaine).month()));
    itemCol2->setText(chaineJoursHeader(3, dateReferenceAgenda->addDays(3-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(3-jourDeLaSemaine).month()));
    itemCol3->setText(chaineJoursHeader(4, dateReferenceAgenda->addDays(4-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(4-jourDeLaSemaine).month()));
    itemCol4->setText(chaineJoursHeader(5, dateReferenceAgenda->addDays(5-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(5-jourDeLaSemaine).month()));
    itemCol5->setText(chaineJoursHeader(6, dateReferenceAgenda->addDays(6-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(6-jourDeLaSemaine).month()));
    itemCol6->setText(chaineJoursHeader(7, dateReferenceAgenda->addDays(7-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(7-jourDeLaSemaine).month()));

    //miseAJourTableau();
}
QString FenetreGraphique::chaineDay(int i)
{
    switch (i)
    {
        case 1: return "Lundi";
        case 2: return "Mardi";
        case 3: return "Mercredi";
        case 4: return "Jeudi";
        case 5: return "Vendredi";
        case 6: return "Samedi";
        case 7: return "Dimanche";
    }
}
QString FenetreGraphique::chaineMonth(int i)
{
    switch (i)
    {
        case 1: return "Janvier";
        case 2: return "Fevrier";
        case 3: return "Mars";
        case 4: return "Avril";
        case 5: return "Mai";
        case 6: return "Juin";
        case 7: return "Juillet";
        case 8: return "Aout";
        case 9: return "Septembre";
        case 10: return "Octobre";
        case 11: return "Novembre";
        case 12: return "Decembre";
    }
}
QString FenetreGraphique::chaineJoursHeader(int jS, int jM, int m)
{
    QString chaineTemp;
    chaineTemp = chaineDay(jS);
    chaineTemp+= " ";
    chaineTemp+= QString::number(jM);
    chaineTemp+= "\n";
    chaineTemp+= chaineMonth(m);

    return chaineTemp;
}
void FenetreGraphique::miseAJourTableau(QStandardItemModel& model) //, QTableView& vue)
{
    //QMessageBox::information(this, "test", "fx de mise a jour");

    //qDebug() << model.rowCount();
    //model.clear();

    //pour tous les jours de la semaine correspondante dateReferenceAgenda    
    /*int jourDeLaSemaine = dateReferenceAgenda->dayOfWeek();
    QDate jourActu;
    for(unsigned int jour=1; jour<8; jour++)
    {
        jourActu = dateReferenceAgenda->addDays(jour-jourDeLaSemaine);
        itemCol0->setText(chaineJoursHeader(1, dateReferenceAgenda->addDays(1-jourDeLaSemaine).day(), dateReferenceAgenda->addDays(1-jourDeLaSemaine).month()));
        //Pour ttoutes les jours de cette semaine
            // On calcule la position row, column de chaque event->case correspondante
            //si la case existe deja, on ajoute (QStandardItem * QStandardItemModel::item(int row, int column = 0) const)
            //sinon nouvelle case et nouveau contenu
    }*/

    //Pour tous les projets
    /*for(int i =0; i< Manager<Projet>::getInstance().getSize(); ++i)
    {
        //for ( QVector<Tache*>::iterator it = projetActif->IteratorSousTachesBegin(); it != projetActif->IteratorSousTachesEnd(); ++it)
        //pour toutes les taches du projets
        for ( QVector<Tache*>::iterator it = Manager<Projet>::getInstance().getItem(i)->IteratorSousTachesBegin(); it != Manager<Projet>::getInstance().getItem(i)->IteratorSousTachesEnd(); ++it)
        {
            if((typeid(**it)==typeid(TacheUnitaire))||(typeid(**it)==typeid(TacheUnitairePreemptive)))
            {
                //on traite l'affichage pour cette tache
                afficherTacheDansAgenda(**it);
            }
            else if(typeid(**it)==typeid(TacheComposite))
            {
                recursiveAgenda(dynamic_cast<TacheComposite&>(**it));
            }
        }
    }*/
    //menuDeroulantProjets->addItem(Manager<Projet>::getInstance().getItem(i)->getId());

    int jourDeLaSemaine = dateReferenceAgenda->dayOfWeek();
    //Pour toutes les programmations nigaud
    for(unsigned int i=0; i<Manager<Programmation>::getInstance().getSize(); ++i)
    {
        Programmation* prog = Manager<Programmation>::getInstance().getItem(i);
        if((prog->getDate().date()>=dateReferenceAgenda->addDays(1-jourDeLaSemaine))&&(prog->getDate().date()<=dateReferenceAgenda->addDays(7-jourDeLaSemaine)))
        {
            //on est dans le cas ou la programmation se trouve dans la semaine active
            TIME::Duree heureDebut;
            TIME::Duree heureFin;
            //TIME::Duree heureTemp;
            int caseDeb=0;
            int caseFin=0;

            /*if(prog->getDate().time()<TIME::Duree(8, 0)) heureDebut=TIME::Duree(8,0);
            else heureDebut=prog->getDate().time();*/
/*
            heureFin=prog->getDate().time();
            heureFin=heureFin.addSecs(prog->getDuree().hour()*3600);
            heureFin=heureFin.addSecs(prog->getDuree().minute()*60);
*/
            /*if(heureTemp>TIME::Duree(, 0)) heureFin=TIME::Duree(19,0);
            else heureFin=heureTemp;*/
/*
            caseDeb=(heureDebut.hour()-7)*4+(heureDebut.minute()/15);
            caseFin=(heureFin.hour()-7)*4+(heureFin.minute()/15);
*/
            //model.setItem(caseDeb, jourDeLaSemaine-1, new QStandardItem(prog->getEvenement().getId()));
            vueAgenda->setSpan(caseDeb,prog->getDate().date().dayOfWeek(),caseFin-caseDeb,1);
            model.item(caseDeb, prog->getDate().date().dayOfWeek())->setBackground(QBrush(QColor(Qt::green)));
        }
    }


    /*model.setItem(0, 0, new QStandardItem("Origine"));
    model.item(0, 0)->setBackground(QBrush(QColor(Qt::green)));
    model.setItem(3, 2, new QStandardItem("Item"));
    model.setItem(3, 5, new QStandardItem("Item2"));*/
    //vue.setSpan(0,0,3,1);
   // vueAgenda->setSpan(0,0,3,3);
}
/*
void FenetreGraphique::recursiveAgenda(TacheComposite& t)
{
    for ( QVector<Tache*>::iterator it = t.IteratorSousTachesBegin(); it != t.IteratorSousTachesEnd(); ++it)
    {
        if((typeid(**it)==typeid(TacheUnitaire))||(typeid(**it)==typeid(TacheUnitairePreemptive)))
        {
            //on traite l'affichage
            afficherTacheDansAgenda(**it);

        }
        else if(typeid(**it)==typeid(TacheComposite))
        {
            recursiveAgenda(dynamic_cast<TacheComposite&>(**it));
        }
    }
}
*/
/*void FenetreGraphique::afficherTacheDansAgenda(Tache& t)
{

}*/
void FenetreGraphique::miseEnFormeLigneColonnes(QTableView* t)
{
    for(unsigned int i=0; i<7; i++)
    {
        t->setColumnWidth(i, 155);
    }
    /*for(unsigned int j=0; j<11; j++)
    {
        t->setRowHeight(j, 52);
    }*/
}
void FenetreGraphique::affichageContenuCase(const QModelIndex& I)
{
    //QVariant elementSelectionneTreeView = modelAgenda->data(I,Qt::DisplayRole);
    //QItemSelectionModel *selection = vueAgenda->selectionModel();
    //QModelIndex indexElementSelectionne = index; //selection->currentIndex();
    //QVariant elementSelectionne = modelAgenda->data(indexElementSelectionne,Qt::DisplayRole);
    //QMessageBox::information(this, "Elément sélectionné", elementSelectionne.toString());
    //QMessageBox::information(this, "test", (modelAgenda->data(index, Qt::DisplayRole)).toString());
    QMessageBox::information(this, "test", "test");

}

/*void FenetreGraphique::clearLayoutTachePrecedence(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayoutTachePrecedence(item->layout());
            delete item->layout();
        }
        delete item->widget();
        delete item;
    }
}*/
