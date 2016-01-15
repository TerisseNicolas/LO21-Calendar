/**
\file fenetregraphique.h
\date 14/06/2015
\author Nicolas Terisse, Antoine Le Comte

\brief Déclaration des fonctions membres de la classe FenetreGraphique

Ce fichier contient toutes les fonctions de la classe FenetreGraphique.\n
**/

#ifndef FENETREGRAPHIQUE
#define FENETREGRAPHIQUE

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMessageBox>
#include <QModelIndex>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QTableWidgetItem>
#include <QTreeView>
#include <QTabWidget>
#include <QTextEdit>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#include <typeinfo>

#include "Projet.h"

/**
 \class FenetreGraphique
 \brief Déclaration de la fenetre principale de l'application

La fenetre principale du projet permet de gerer les Projet, de visualiser l'agenda et de faire des exportations.
**/
class FenetreGraphique : public QWidget {
    Q_OBJECT

    //onglets
    //! \brief Onglets ageanda, gestion de projets et export
    QTabWidget *onglets;
    //! \brief onnglet gestion de projet
    QWidget *pageSaisie;
    //! \brief onglet agenda
    QWidget *pageAffichage;
    //! \brief onglet export
    QWidget *pageExport;

    //============================================// structure onglet gestion de projet
    //! \brief layout principal onglet de gestion
    QHBoxLayout *layoutPageSaisiePrincipal;
    //! \brief layout pour gerer la vue a gauche
    QVBoxLayout *layoutProjetTV;
    //! \brief widget pour supporter les sous onglets
    QWidget *supportOngletsCreation;

    //selection projet + treeview
    //! \brief groupbox pour création de projet, choix de projet et treeview
    QGroupBox *gBProjetTV;
    //! \brief onglets projet, tache unitaire, tache composite
    QTabWidget *ongletsNiveau2;
    //! \brief onglet projet
    QWidget *pageCreationprojet;
    //! \brief onglet tache unitaire
    QWidget *pageTacheUnitaire;
    //! \brief onglet tache composite
    QWidget *pageTacheComposite;
    //! \brief choix du projet
    QComboBox *menuDeroulantProjets;
    //! \brief modele du treeview de taches
    QStandardItemModel *modelTreeView;
    
    /*QStandardItem *itemTest1;
    QStandardItem *itemTest2;
    QStandardItem *itemTest3;*/
    //! \brief vue treeview de taches
    QTreeView *vueTreeView;

    //onglets creation projet
    QVBoxLayout *layoutCreationProjet;
    QHBoxLayout *layoutCreationProjet1;
    QHBoxLayout *layoutCreationProjet2;
    QHBoxLayout *layoutCreationProjet3;
    QHBoxLayout *layoutCreationProjet4;
    QHBoxLayout *layoutCreationProjet5;
    QPushButton *bNouveauProjet;
    QLabel *labelNomProjet;
    QLabel *nomProjet;
    QLabel *labelProjetDateDispo;
    QLabel *projetDateDispo;
    QLabel *labelProjetEcheance;
    QLabel *projetEcheance;
    QPushButton *bCreerTacheUProjet;
    QPushButton *bCreerTacheCProjet;
    QPushButton *bModifierProjet;
    QPushButton *bdetruireProjet;

    //onglet creation tache unitaire
    QVBoxLayout* layoutCreationTache;
    QHBoxLayout* layoutCreationTache1;
    QHBoxLayout* layoutCreationTache2;
    QHBoxLayout* layoutCreationTache3;
    QHBoxLayout* layoutCreationTache4;
    QHBoxLayout* layoutCreationTache5;
    QHBoxLayout* layoutCreationTache6;
    QHBoxLayout* layoutCreationTache7;
    QHBoxLayout* layoutCreationTache8;
    QLabel* identificateurTache;
    QLabel *labelIdentificateurTache;
    QLabel* titreTache;
    QLabel* titreTacheLabel;
    QCheckBox* preemptiveTache;
    QLabel* labelTacheEtat;
    QLabel* tacheEtat;
    QLabel* disponibiliteTache;
    QLabel* labelDisponibiliteTache;
    QLabel* tacheEcheance;
    QLabel* labelTacheEcheance;
    QLabel* labelTacheDuree;
    QLabel* tacheDuree;
    QLabel *labelPrecedenceTacheU;
    QStringListModel *modelePrecedenceTacheU;
    QListView *vuePrecedenceTacheU;
    QPushButton* bModifierTacheU;
    QPushButton* bSupprimerTacheU;

    //onglet creation evenement(tache composite)
    QVBoxLayout* layoutCreationEvent;
    QHBoxLayout* layoutCreationEvent1;
    QHBoxLayout* layoutCreationEvent2;
    QHBoxLayout* layoutCreationEvent3;
    QHBoxLayout* layoutCreationEvent4;
    QHBoxLayout* layoutCreationEvent5;
    QHBoxLayout* layoutCreationEvent6;
    QHBoxLayout* layoutCreationEvent7;
    QHBoxLayout* layoutCreationEvent8;
    QHBoxLayout* layoutCreationEvent9;
    QLabel* identificateurTacheC;
    QLabel *labelIdentificateurTacheC;
    QLabel* titreTacheC;
    QLabel* titreTacheLabelC;
    QLabel* labelTacheEtatC;
    QLabel* tacheEtatC;
    QLabel* disponibiliteTacheC;
    QLabel* labelDisponibiliteTacheC;
    QLabel* tacheCEcheance;
    QLabel* labelTacheCEcheance;
    QLabel* labelTacheCDuree;
    QLabel* tacheCDuree;
    QLabel *labelPrecedenceTacheC;
    QStringListModel *modelePrecedenceTacheC;
    QListView *vuePrecedenceTacheC;
    QPushButton* bTacheCCreerTacheC;
    QPushButton* bTacheCCreerTacheU;
    QPushButton* bModifierTacheC;
    QPushButton* bSupprimerTacheC;

    //============================================// structure onglet agenda
    QVBoxLayout *layoutPageAffichagePrincipal;

    //Agenda
    QHBoxLayout *layoutAgenda;
    QWidget *widgetAgenda;
    QDate *dateReferenceAgenda;

    //Haut de page agenda
    QHBoxLayout *layoutHautAgenda;
    QPushButton *bSemainePrecedente;
    QPushButton *bSemaineSuivante;
    QPushButton *jourActuel;

    //tableau agenda
    QStandardItemModel *modelAgenda;
    QTableView *vueAgenda;
    QStringList hearderVTableau;
    QStandardItem *itemCol0;
    QStandardItem *itemCol1;
    QStandardItem *itemCol2;
    QStandardItem *itemCol3;
    QStandardItem *itemCol4;
    QStandardItem *itemCol5;
    QStandardItem *itemCol6;

    //bas de page
    QHBoxLayout *layoutProgrammation;
    QPushButton *bProgrammerTache;
    QPushButton *bProgrammerEvt;
    QPushButton *bSupprimerProgrammation;

    //===============================================// Structure onglet export
    QHBoxLayout *layoutPageExportPrincipal;
    QVBoxLayout *layoutPageExportSecondaire;

    QWidget *widgetSecondairePageExport;
    QLabel *labelExport;
    QLineEdit *nomFichierExport;
    QPushButton *bExportImport;
    QPushButton *bExportProgrammationBrut;
    QPushButton *bExportProgrammationXml;
    QPushButton *bExportSemaineBrut;
    QPushButton *bExportSemaineXml;

public:
   //! \brief définition d'un projet nul
    static Projet* projetNull;
    //! \brief définition d'un projet actif pour toute l'application
    static Projet* projetActif;
    //! \brief définition d'une tache courante pour toute l'application
    static Tache* tacheActive;
   //! \brief unique constructeur de la fenetre principale de l'application
    FenetreGraphique(QWidget* parent =0);

public slots:
   //! \brief Mutateur du projet courant
    static void setProjetActif(Projet&);

    //Agenda en tete
    //! \brief construit une chaine de caractères pour la semaine actuelle
    QString constructionMessageSemaineAgenda(QDate*);
    //! \brief chaine du jour
    //! \return une chaine avec le jour de la semaine a partir de son jour dans la semaine 
    QString chaineDay(int);
    //! \brief chaine du mois
    //! \return renvoie une chaine avec le mois
    QString chaineMonth(int);
    //! \brief chaine date
    //! \return une chaine pour un jour, mois et annee donnée
    QString chaineJoursHeader(int, int, int);
    //! \brief change la semaine de l'agenda à la suivante
    void semaineSuivante();
    //! \brief change la semaine de l'agenda à la précédente
    void semainePrecedente();
    //! \brief met a jour les jours en haut de l'agenda
    void miseAJourHeader();

    //Agenda tableau
    //! \brief met a jour l'affichage du tableau a partir de son modele
    void miseAJourTableau(QStandardItemModel&);
    //! \brief affiche le contenu d'une case
    void affichageContenuCase(const QModelIndex&);
    //! \brief formatage de du design de l'agenda
    void miseEnFormeLigneColonnes(QTableView*);
    //! \brief slot pour appeler le constructeur de la fenetre de rpogrammation de tache
    void nouvelleProgrammationTache();
    //! \brief slot pour appeler le constructeur de la fenetre de programmation d'un evenement
    void nouvelleProgrammationEvt();
    //! \brief slot pour appeler la fenetre de suppression de programmation
    void supprimerProgrammation();

    //treeview
    //! \brief ajoute tous les projets du manager dans le menu déroulant
    void initialisationMenuProjet();
    //! \brief ajoute un projet au menu déroulant de projets
    void ajoutMenuProjet(Projet&);
    //! \brief récupère la tache selectionnee dans le tree view et appel la mise de la tache active
    void selectionTreeView(const QModelIndex&);
    //! \brief slot qui gere la selection d'un nouveau projet dans le menu deroulant
    void changerProjetTreeView(int);
    //! \brief appelé lorsque le selectionné change, agit sur l accessibilité des onglets
    void majProjetTreeView (void);
    //! \brief on charge toutes les taches dans le treeview pour un projet donné
    void majTachesTreeView(void);
    //! \brief detection du type de la tache selectionnée et renvoie sur l'onglet adapté
    void majSelectionTacheActive(void);
    //! \brief permet de construire l'arborescence du treeview
    void recursiveTreeView(QStandardItem&, TacheComposite&);


    //creation projet, tache, event(tache composite)
    //! \brief initialisation des onglets projets, tache unitaire, tache composite
    void initialisationTabPTUTC();
    //! \brief liste des précédences
    //! \return la liste de toutes les précedences pour une tache donnée
    QStringList remplissageTachePrecedence();

    //! \brief Appel la fenetre de creation de projet
    void creerProjet();
    //! \brief appel la fenetre de modification de projet
    void modifierProjet();
    //! \brief appel la fenetre de creation de tache unitaire a la racine d'un projet
    void creerTacheUProjet();
    //! \brief appel la fenetre de cretaion de tache composite a la racine d'un projet
    void creerTacheCProjet();
    //! \brief destruction d'un projet
    void detruireProjet();
    //! \brief remplissage de l'onglet contenant les informations d'un projet
    void remplissageOngletProjet();
    //! \brief appel de la fenetre de modfication d'une tache unitaire
    void modifierTacheU();
    //! \brief suppression d'une tache unitaire
    void supprimerTacheU();
    //! \brief remplissage de l'onglet contenant les informations d'une tache unitaire
    void remplissageOngletTacheU();
    //! \brief creation tache unitaire a partir d'une tache composite
    void creerTacheUTacheC();
    //! \brief creation d'une tache composite a partir d'une tache composite
    void creerTacheCTacheC();
    //! \brief modification d'une tache composite
    void modifierTacheC();
    //! \brief suppression d'une tache composite
    void supprimerTacheC();
    //! \brief remplissage de l'onglet contenant les informations d'une tache composite
    void remplissageOngletTacheC();

    //export
    //! \brief verification de la validité du nom du fichier contenant l 'export
    void validationNomExport(QString s);
    //! \brief export total des programmation au format brut
    void exportProgrammationBrut();
    //! \brief export total des programmations au format xml
    void exportProgrammationXml();
    //! \brief export des programmations pour une semaine selectionnee au format brut
    void exportSemaineBrut();
    //! \brief export des programmations pour une semaine selectionnee au format xml
    void exportSemaineXml();

};
#endif // FENETREGRAPHIQUE
