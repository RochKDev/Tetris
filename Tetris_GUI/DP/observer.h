/*!
 * \file observer.h
 * \brief Définition de la classe he2b::esi::dev4::Observer.
 */

#ifndef __OBSERVER__H__
#define __OBSERVER__H__
#include "../model/headers/Board.h"
/*!
 * \brief Espace de nom de he2b::esi::dev4.
 */
namespace he2b::esi::dev4
{



/*!
 * \brief Classe abstraite de base de tout observateur.
 *
 * Classe dont dérive tout écouteur (ou "observateur") du modèle de
 * conception "Observer / Observable".
 *
 * \sa Observable.
 * \see https://en.wikipedia.org/wiki/Observer_pattern
 */

class Observer
{
  public:

    /*!
     * \brief Méthode virtuelle pure que chaque observateur concret doit
     * implémenter : c'est cette méthode qu'appelle le sujet observé lors
     * d'une notification.
     *
     * \param observable le sujet d'observation qui notifie un changement.
     * \see Observable::notifyObservers().
     */
      virtual void update(const Tetris::Board * observable, int score, Tetris::Level level, int lines) = 0;

    /*!
     * \brief Destructeur virtuel par défaut car utilisation polymorphique.
     */
    virtual ~Observer() = default;

    /*!
     * \brief Constructeur par recopie par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observer(const Observer &) = default;

    /*!
     * \brief Constructeur par déplacement par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observer(Observer &&) = default;

    /*!
     * \brief Opérateur d'assignation par recopie par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observer & operator=(const Observer &) = default;

    /*!
     * \brief Opérateur d'assignation par déplacement par défaut.
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observer & operator=(Observer &&) = default;

  protected:

    /*!
     * \brief Constructeur protégé pour éviter l'instanciation
     *        hors héritage.
	 *
	 * Comme la classe Observer est abstraite, l'instanciation ne peut
	 * se faire que dans le cadre d'un héritage...
     *
     * Le destructeur virtuel par défaut a des effets en cascade.
     *
     * \see http://stackoverflow.com/q/33957037
     * \see http://scottmeyers.blogspot.de/2014/03/a-concern-about-rule-of-zero.html
     */
    Observer() = default;
};

} // namespace he2b::esi::dev4

#endif
