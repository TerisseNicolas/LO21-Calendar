#include <iomanip>
#include "Duree.h"
#include <ctime>

using namespace TIME;

QString TIME::Duree::toString() {
    QString qstr = QString::number(this->getHeure()) + ":" + QString::number(this->getMinute());
    return qstr;
}
