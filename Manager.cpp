#include "Manager.h"
#include "Tache.h"
#include "Projet.h"
#include "Programmation.h"

#include <QVector>
#include <QString>
#include "typeinfo"

//SINGLETON TEMPLATE METHODE
template<>
Manager<Tache>::Handler Manager<Tache>::handler=Manager<Tache>::Handler();
template<>
Manager<Projet>::Handler Manager<Projet>::handler=Manager<Projet>::Handler();
template<>
Manager<Programmation>::Handler Manager<Programmation>::handler=Manager<Programmation>::Handler();

