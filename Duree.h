#if !defined(CTIME)
#define CTIME

#include<iostream>
#include<iomanip>
#include "QString"
#include "QTextStream"

/**
\namespace TIME
\brief namespace regroupant les classes TimeException et Duree
**/
namespace TIME {
   /**
   \class TimeException
   \brief Classe permettant de lever des exceptions les Duree
   **/
	class TimeException{
        public:
            //! \brief  Unique constructeur de la classe
            //! \param m const QString& récupérant un message d'erreur pour l'exception levée
            TimeException(const QString& m):info(m){}
            //! \brief  Accesseur const pour l'attribut info
            //! \return const QStrin& le message d'erreur correspondant à l'exception levée
            const QString& GetInfo() const { return info; } //<! Retourne l'information stockée dans la classe
        private:
            QString info;
    };
    /**
    \class Duree
    \brief  Classe permettant de gerer des durée ( un nombre de minutes)
    
    Cette classe permet notamment de créer des durées a partir de d'un nombre de minutes, ou d'une heure et de minutes
    **/
    class Duree{
    public:
        //! Constructeur à partir de heure et minute
        /*! \param h heure avec h>=0
            \param m minute avec 0<=m<=59
            */
        Duree(int h,int m):nb_minutes(h*60+m) {if (m>59) throw TimeException("erreur: initialisation duree invalide");}
        //! Constructeur à partir de minute
        /*! \param m minute avec m>=0
            */
        Duree(int m=0):nb_minutes(m) {}
        //! \brief  Mutateur du nombre de minutes
        //! \param minutes Le nombre de minutes
        void setDuree(int minutes) { nb_minutes=minutes; }
        //! \brief  Mutateur des minutes à partir d'heures et de minutes
        //! \param heures Le nombre d'heures
        //! \param minutes Le nombre de minutes
        void setDuree(int heures,  int minutes) { if (heures==0 && minutes>59) throw TimeException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
        //! \brief  Accesseur pour les minutes totales
        //! \return int le nombre de minutes totales de la durée
         int getDureeEnMinutes() const { return nb_minutes; }
        //! \brief  Accède aux heures totales
        //! \return double le nombre d'heures totales de la durée
        double getDureeEnHeures() const { return double(nb_minutes)/60; }
        //! \brief  Accède à la partie minutes de la durée, tronque les heures
        //! \return unsigned int la partie minute de la durée uniquement
        unsigned int getMinute() const { return nb_minutes%60; }
        //! \brief  Accède aux heures, tronque les minutes
        //! \return unsigned int la partie heure de la durée uniquement
        unsigned int getHeure() const { return nb_minutes/60; }
        //! \brief  Affichage de la durée au format hhHmm
        //! \param f QSTextSteam& sur lequel on affiche place l'affichage
        void afficher(QTextStream& f) const;
        //! \brief  Convertit la durée en chaine de caracteres
        //! \return QString la chaine contenant la durée au format hh:mm
        QString toString();
        //! \brief  Test l'égalité de durées
        //! \return Vrai si oui, faux sinon
        bool operator==(Duree d) const{
            return (nb_minutes == d.getDureeEnMinutes());
        }
        //! \brief  Test l'inégalité de durées
        //! \return Vrai si oui, faux sinon
        bool operator!=(Duree d) const{
           return (nb_minutes != d.getDureeEnMinutes());
        }
    private:
        int nb_minutes;
    };
}
//! \brief Surcharge cout\n
//! Surcharge pour une const durée
QTextStream& operator<<(QTextStream& f, const TIME::Duree & d);
//! \brief Surcharge cout\n
//! Surcharge pour une durée
QTextStream& operator>>(QTextStream&, TIME::Duree&);
#endif
