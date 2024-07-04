/*!
 * \file keyboard.hpp
 *
 * \brief Contient les modèles de fonctions pour lire des données
 *        au clavier.
 *
 * \author nvs
 */

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "stringConvert.hpp"

#include <string>
#include <iostream>

/*!
 * \brief Espace de nom de he2b::esi::dev4.
 *
 */
namespace he2b::esi::dev4
{

/*!
 * \brief Lit toute une ligne au clavier et en extrait une seule donnée.
 *
 * La ligne lue est terminée par un
 * <tt>\\</tt><tt>n</tt>
 * qui est consommé
 * mais pas pris en compte lors de la conversion vers la donnée
 * binaire retournée.
 *
 * Le modèle de fonction utilise he2b::esi::dev4::fromString(), donc l'opérateur
 * d'extraction d'un flux vers le <i>template</i>. Celui-ci
 * doit donc fournir un <tt>operator>></tt> adéquat.
 *
 * Lors de la lecture d'un booléen, seules les valeurs 0,
 * pour <tt>false</tt>, et 1, pour <tt>true</tt>, sont acceptées.
 *
 * \param t Référence d'une variable qui accueille le résultat converti
 *          de la lecture. En cas de problème lors de la lecture
 *          le contenu de cette variable est indéterminé.
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La donnée lue au clavier. En cas de problème lors de la lecture
 *          la valeur retournée est indéterminée.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions qui pourraient
 *                  être lancées par l'opérateur d'extraction du flux,
 *                  une he2b::esi::dev4::bad_string_convert est levée si
 *                  l'extraction du flux échoue ou si le flux n'est pas
 *                  épuisé en fin d'extraction, c'est-à-dire si la
 *                  donnée à extraire n'est pas seule sur la ligne lue,
 *                  car he2b::esi::dev4::fromString() est utilisée.
 */
template<typename T>
T lineFromKbd(T & t, bool iw = false)
{
    std::string s;
    std::getline(std::cin, s);
    return t = fromString(t, s, iw);
}

/*!
 * \brief Lit toute une ligne au clavier et en extrait une seule donnée.
 *
 * La ligne lue est terminée par un
 * <tt>\\</tt><tt>n</tt>
 * qui est consommé
 * mais pas pris en compte lors de la conversion vers la donnée
 * binaire retournée.
 *
 * Le modèle de fonction utilise he2b::esi::dev4::fromString(), donc l'opérateur
 * d'extraction d'un flux vers le <i>template</i>. Celui-ci
 * doit donc fournir un <tt>operator>></tt> adéquat.
 *
 * Lors de la lecture d'un booléen, seules les valeurs 0,
 * pour <tt>false</tt>, et 1, pour <tt>true</tt>, sont acceptées.
 *
 * Notez que ce modèle de fonction permet de construire des surcharges
 * de fonctions ne différant entre elles que par leur type de retour !
 *
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La donnée lue au clavier. En cas de problème lors de la lecture
 *          la valeur retournée est indéterminée.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions qui pourraient
 *                  être lancées par l'opérateur d'extraction du flux,
 *                  une he2b::esi::dev4::bad_string_convert est levée si
 *                  l'extraction du flux échoue ou si le flux n'est pas
 *                  épuisé en fin d'extraction, c'est-à-dire si la
 *                  donnée à extraire n'est pas seule sur la ligne lue,
 *                  car he2b::esi::dev4::fromString() est utilisée.
 */
template<typename T>
T lineFromKbd(bool iw = false)
{
    std::string s;
    std::getline(std::cin, s);
    return fromString<T>(s, iw);
}

} // namespace he2b::esi::dev4

#endif /* KEYBOARD_HPP_ */
