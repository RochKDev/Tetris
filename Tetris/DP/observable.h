/*!
 * \file observable.h
 * \brief Définition de la classe he2b::esi::dev4::Observable.
 */

#ifndef __OBSERVABLE__H__
#define __OBSERVABLE__H__

#include <set>

/*!
 * \mainpage Modèle de conception Observer / Observable
 *
 * L'implémentation du _desing pattern_
 * [Observer](https://en.wikipedia.org/wiki/Observer_pattern)
 * donnée ici est fidèle au modèle du
 * [Gang of Four](https://en.wikipedia.org/wiki/Design_Patterns). En
 * particulier, il n'y est pas fait usage d'une classe correspondant
 * aux _événements_, mais uniquement d'une classe
 * _source d'événements_, le sujet he2b::esi::dev4::Observable, 
 * et d'une classe _écouteur d'événements_, 
 * l'observateur he2b::esi::dev4::Observer.
 *
 * Dans ses mises en œuvre effective, ce modèle est très souvent
 * étoffé par l'ajout de classes d'événement ou par la multiplication
 * des méthodes de notification.
 * Rien, cependant, de ce que ces complexifications du modèle
 * rendent plus facile aux utilisateurs, n'est hors de portée du
 * modèle simple donné ici. Les développements du modèle de conception
 * peuvent en effet être reportées sur les classes concrètes qui
 * l'implémentent. Remarquez que si le contenu de ce paragraphe
 * vous semble abscons, oubliez-le provisoirement. On en reparle
 * lors de la
 * [gestion des événements avec Qt](https://doc.qt.io/qt-6/eventsandfilters.html).
 *
 */

/*!
 * \brief Espace de nom de he2b::esi::dev4.
 */
namespace he2b::esi::dev4
{

class Observer;

/*!
 * \brief Classe de base de tout observable (ou "sujet d'observation").
 *
 * Classe dont dérive toute source d'événement (ou "sujet d'observation")
 * du modèle de conception "Observateur / Observable".
 *
 * \sa Observer.
 */
class Observable
{
  public:

    /*!
     * \brief Destructeur virtuel par défaut car utilisation polymorphique.
     */
    virtual ~Observable() = default;

    /*!
     * \brief Constructeur par recopie par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observable(const Observable &) = default;

    /*!
     * \brief Constructeur par déplacement par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observable(Observable &&) = default;

    /*!
     * \brief Opérateur d'assignation par recopie par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observable & operator=(const Observable &) = default;

    /*!
     * \brief Opérateur d'assignation par déplacement par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observable & operator=(Observable &&) = default;

    /*!
     * \brief Méthode pour l'ajout d'un observateur au carnet d'adresse 
     * des observateurs enregistés de l'observable.
     *
     * \param observer un pointeur vers le candidat observateur.
     */
    virtual void registerObserver(Observer * observer) final;

    /*!
     * \brief Méthode pour le retrait d'un observateur au carnet d'adresse 
     * des observateurs enregistés de l'observable.
     *
     * \param observer l'adresse de l'observateur désintéressé.
     */
    virtual void unregisterObserver(Observer * observer) final;

  protected:

    /*!
     * \brief Constructeur protégé pour éviter l'instanciation
     *        hors héritage.
     */
    Observable() = default;

public:
    /*!
     * \brief Méthode qui se charge de prévenir les observateurs d'un
     * changement d'état de l'observable, en invoquant leur
     * méthode Observer::update().
     *
     * \sa Observer::update(const Observable *).
     */
    virtual void notifyObservers() const = 0;

  protected:

    /*!
     * \brief L'ensemble d'observateurs enregistrés.
     */
    std::set<Observer *> observers_ { };
};

} // namespace he2b::esi::dev4

#endif
