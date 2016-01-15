#include "fenetreexportsemaine.h"

FenetreExportSemaine::FenetreExportSemaine(QWidget* parent) : QDialog(parent)
{
    setFixedSize(500, 200);
    setWindowTitle("Choix de la semaine");

    //contenu
    layoutExportSemaine = new QVBoxLayout;
    layoutChoixSemaine = new QHBoxLayout;

    labelExportSemaine = new QLabel("Selection de la semaine a exporter:");
    dateReferenceExport = new QDate(QDate::currentDate());

    bSemainePrecedente = new QPushButton("Precedente");
    bSemaineExport = new QPushButton(constructionMessageSemaineExport(dateReferenceExport));
    bSemaineExport->setEnabled(false);
    bSemaineSuivante = new QPushButton("Suivante");

    bValiderExportSemaine = new QPushButton("Exporter");
    bAnnulerExportSemaine = new QPushButton("Annuler");

    //disposition
    layoutChoixSemaine->addWidget(bSemainePrecedente);
    layoutChoixSemaine->addWidget(bSemaineExport);
    layoutChoixSemaine->addWidget(bSemaineSuivante);

    layoutExportSemaine->addWidget(labelExportSemaine);
    layoutExportSemaine->addLayout(layoutChoixSemaine);
    layoutExportSemaine->addWidget(bValiderExportSemaine);
    layoutExportSemaine->addWidget(bAnnulerExportSemaine);
    setLayout(layoutExportSemaine);

    //connections
    QObject::connect(bSemainePrecedente, SIGNAL(clicked()), this, SLOT(semainePrecedente()));
    QObject::connect(bSemaineSuivante, SIGNAL(clicked()), this, SLOT(semaineSuivante()));
    QObject::connect(bValiderExportSemaine, SIGNAL(clicked()), this, SLOT(validerExportSemaine()));
    QObject::connect(bAnnulerExportSemaine, SIGNAL(clicked()), this, SLOT(close()));
}
QString FenetreExportSemaine::constructionMessageSemaineExport(QDate* d)
{
    QString boutonSemaineExport("Semaine : ");
    boutonSemaineExport+=QString::number(d->weekNumber());
    boutonSemaineExport+=" (";
    boutonSemaineExport+=d->toString();
    boutonSemaineExport+=")";
    return boutonSemaineExport;
}
void FenetreExportSemaine::semainePrecedente()
{
    QDate *dateTemp = new QDate;
    *dateTemp = dateReferenceExport->addDays(-7);
    *dateReferenceExport=*dateTemp;
    bSemaineExport->setText(constructionMessageSemaineExport(dateReferenceExport));
    delete dateTemp;
}
void FenetreExportSemaine::semaineSuivante()
{
    QDate *dateTemp = new QDate;
    *dateTemp = dateReferenceExport->addDays(7);
    *dateReferenceExport=*dateTemp;
    bSemaineExport->setText(constructionMessageSemaineExport(dateReferenceExport));
    delete dateTemp;
}
void FenetreExportSemaine::validerExportSemaine()
{
    //appel de la methode de sauvegarde
}
