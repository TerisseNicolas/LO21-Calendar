#include <QApplication>
#include <qDebug>

#include "fenetregraphique.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    //try{
        FenetreGraphique fenetre;
        fenetre.show();

    //} catch(...){
    //    qDebug()<<"Erreur inconnue";
    //}
    return app.exec();
}
