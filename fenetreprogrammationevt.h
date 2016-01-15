#ifndef FENETREPROGRAMMATIONEVT
#define FENETREPROGRAMMATIONEVT

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
\class FenetreProgrammationEvt
\brief Fenetre permettant la création et la programmation d'un Evenement classique

La fenetre gère à la fois la création d'évènement traditionnels ratachés à aucun projet et leur programmation.
**/
class FenetreProgrammationEvt : public QDialog
{
    Q_OBJECT

    QVBoxLayout* layoutCreationEvent;
    QHBoxLayout* layoutCreationEvent1;
    QHBoxLayout* layoutCreationEvent2;
    QHBoxLayout* layoutCreationEvent3;
    QHBoxLayout* layoutCreationEvent4;

    QLineEdit* identificateurEvent;
    QLabel *labelIdentificateurEvent;
    QTextEdit* titreEvent;
    QLabel* titreEventLabel;

    QDateTimeEdit* dateEvent;
    QLabel* labelDateEvent;
    QLabel* labelEventDuree;
    QSpinBox* eventHDuree;
    QSpinBox* eventMDuree;

    QPushButton* bCreerEvent;
    QPushButton* bAnnulerEvent;

    public:
    //! \brief Unique consctructeur de la fenetre
    FenetreProgrammationEvt(QWidget *parent=0);

    public slots:
    //! \brief Création de l'évènement\n
    //! Verification si un autre evenement n'a pas le meme identificateur\n
    //! L'evenement est ajouté au manager de programmations
    void creerEvent();
};

#endif // FENETREPROGRAMMATIONEVT

