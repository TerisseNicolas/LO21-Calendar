#include "fenetreprogrammationsuppr.h"
#include "Manager.h"
#include "Programmation.h"

FenetreProgrammationSuppr::FenetreProgrammationSuppr(QWidget* parent) : QDialog(parent)
{
    setFixedSize(550, 450);
    setWindowTitle("Supprimer une programmation");

    labelProgrammation = new QLabel("Programmations");
    modelProgrammation = new QStringListModel;
    miseAJourProgrammation(*modelProgrammation);
    vueProgrammation = new QListView;
    vueProgrammation->setModel(modelProgrammation);
    vueProgrammation->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bSupprimerProgrammation = new QPushButton("Supprimer la programmation");
    bFermer = new QPushButton("Fermer");

    //imbrication
    layoutSuppressionProgrammation1 = new QHBoxLayout;
    layoutSuppressionProgrammation = new QVBoxLayout;
    layoutSuppressionProgrammation1->addWidget(bSupprimerProgrammation);
    layoutSuppressionProgrammation1->addWidget(bFermer);
    layoutSuppressionProgrammation->addWidget(labelProgrammation);
    layoutSuppressionProgrammation->addWidget(vueProgrammation);
    layoutSuppressionProgrammation->addLayout(layoutSuppressionProgrammation1);
    setLayout(layoutSuppressionProgrammation);

    //connections
    QObject::connect(bSupprimerProgrammation, SIGNAL(clicked()), this, SLOT(supprimerProgrammation()));
    QObject::connect(bFermer, SIGNAL(clicked()), this, SLOT(close()));
}
void FenetreProgrammationSuppr::supprimerProgrammation()
{
    //on recupere l element
    QItemSelectionModel *selection = vueProgrammation->selectionModel();
    QModelIndex indexElementSelectionne = selection->currentIndex();
    QVariant elementSelectionne = modelProgrammation->data(indexElementSelectionne, Qt::DisplayRole);

    //on le supprime
    // verification a faire sur ce qu'on recupere
    //Programmation* prog = Manager<Programmation>::getInstance().findItem(elementSelectionne.toString());
    //Manager<Programmation>::getInstance().deleteItem(prog);

    //on recharge la liste des programmations
    miseAJourProgrammation(*modelProgrammation);
}
void FenetreProgrammationSuppr::miseAJourProgrammation(QStringListModel& model)
{
    model.setStringList(QStringList());
    model.setStringList(remplissageProgrammation());
}

QStringList FenetreProgrammationSuppr::remplissageProgrammation()
{
    QStringList listeProgrammation;
    for (QVector<Programmation*>::const_iterator it = Manager<Programmation>::getInstance().ConstIteratorManagerBegin() ; it != Manager<Programmation>::getInstance().ConstIteratorManagerEnd() ; ++it ){
              listeProgrammation << (*it)->getDate().toString();
    }
    return listeProgrammation;
}
