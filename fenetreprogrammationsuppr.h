#ifndef FENETREPROGRAMMATIONSUPPR
#define FENETREPROGRAMMATIONSUPPR

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QMessageBox>

/**
\class FenetreProgrammationSuppr
\brief Fenetre permettant de supprimer des Programmation

L'utilisateur sélectionne une programmation afin de la supprimer
**/
class FenetreProgrammationSuppr : public QDialog
{
    Q_OBJECT

    QVBoxLayout *layoutSuppressionProgrammation;
    QHBoxLayout* layoutSuppressionProgrammation1;

    QLabel* labelProgrammation;
    QStringListModel *modelProgrammation;
    QListView *vueProgrammation;

    QPushButton *bSupprimerProgrammation;
    QPushButton *bFermer;

    public:
    //! \brief Unique constructeur de la classe
    FenetreProgrammationSuppr(QWidget *parent=0);

    public slots:
    //! \brief Suppression d'une programmation\n
    //! Récupération d'une programmation sélectionnée et suppression
    void supprimerProgrammation();
    //! \brief Mise a jour de la liste des programmations\n
    //! Recharge la liste des programmations
    void miseAJourProgrammation(QStringListModel&);
    //! \brief liste des programmations\n
    //! Parcourt toutes les programmations dans le manager
    //! \return liste des programmations sous forme de liste de chaines de caractères
    QStringList remplissageProgrammation();
};

#endif // FENETREPROGRAMMATIONSUPPR
