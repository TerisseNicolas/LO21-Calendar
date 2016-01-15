#ifndef SEMAINEEXPORTSEMAINE
#define FENETREEXPORTSEMAINE

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QDate>
#include <QLabel>
#include <QMessageBox>

/**
\class FenetreExportSemaine
\brief Selectionne une semaine à exporter

L'utilisateur choisit la semaine qu'il veut exporter au format brut ou en xml
**/
class FenetreExportSemaine : public QDialog
{
    Q_OBJECT

    QVBoxLayout *layoutExportSemaine;
    QHBoxLayout *layoutChoixSemaine;

    //Liste des projets
    QLabel *labelExportSemaine;
    QDate *dateReferenceExport;
    QPushButton *bSemainePrecedente;
    QPushButton *bSemaineExport;
    QPushButton *bSemaineSuivante;
    QPushButton *bValiderExportSemaine;
    QPushButton *bAnnulerExportSemaine;

    public:
    //! \brief Unique constructeur de la fenetre
    FenetreExportSemaine(QWidget *parent=0);
    //! \brief Message de la semaine\n
    //! Construction de la chaine à partir d'une date
    //! \param d date de réference pour construire une semaine entière
    //! \return chaine avec la semaine
    QString constructionMessageSemaineExport(QDate*);

    public slots:
    //! \brief Change de semaine pour la précédente\n
    //! Retire une semaine à la date de référence\n
    //! Construction d'un nouveau texte pour la semaine
    void semainePrecedente();
    //! \brief Change de semaine pour la suivante\n
    //! Ajoute une semaine à la date de référence\n
    //! Construction d'un nouveau texte pour la semaine
    void semaineSuivante();
    //! \brief Export de la programmation pour la semaine choisie\n
    //! Appel de la méthode de sauvegarde de la classe Programmation
    void validerExportSemaine();

};
#endif // FENETREEXPORTSEMAINE

