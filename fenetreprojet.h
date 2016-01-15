#ifndef FENETREPROJET
#define FENETREPROJET

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QMessageBox>

/**
 \class FenetreProjet
 \brief Fentre graphique pour la création de Projet.
 
Permet la création de projet à partir d'un identifiant, d'une date de disponibilité et un échéance
**/
class FenetreProjet : public QDialog
{
    Q_OBJECT

    //onglets creation projet
    QVBoxLayout *layoutCreationProjet;
    QHBoxLayout* layoutCreationProjet1;
    QHBoxLayout* layoutCreationProjet2;
    QHBoxLayout* layoutCreationProjet3;
    QHBoxLayout* layoutCreationProjet4;
    QLabel *labelNomProjet;
    QLineEdit *nomProjet;
    QLabel *labelProjetDateDispo;
    QDateEdit *projetDateDispo;
    QLabel *labelProjetEcheance;
    QDateEdit *projetEcheance;
    QPushButton *bCreerProjet;
    QPushButton *bAnnulerCreationProjet;

    public:
    //! \brief Unique constructeur de la classe
    FenetreProjet(QWidget *parent=0);

    public slots:
    //! \brief Creer le projet\n
    //! Ajoute le nouveau projet au manager
    void creerProjet();
};

#endif // FENETREPROJET

