/*!
 * \file observable.cpp
 * \brief Implémentation de la classe he2b::esi::dev4::Observable.
 */

#include "observable.h"
#include "observer.h"

namespace he2b::esi::dev4
{

void Observable::registerObserver(Observer * observer)
{
    observers_.insert(observer);
    notifyObservers();
}

void Observable::unregisterObserver(Observer * observer)
{
    observers_.erase(observer);
}


} // namespace he2b::esi::dev4
