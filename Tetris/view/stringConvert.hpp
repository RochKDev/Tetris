/*!
 * \file stringConvert.hpp
 *
 * \brief Contient les modèles de fonctions pour convertir
 *        depuis et vers une <tt>string</tt> standard.
 *
 * \author nvs
 */

#ifndef STRINGCONVERT_HPP_
#define STRINGCONVERT_HPP_

#include <string>
#include <sstream>
#include <typeinfo> // pour bad_cast

/*!
 * \brief Espace de nom de he2b::esi::dev4.
 *
 */
namespace he2b::esi::dev4
{
/*!
 * \brief Classe d'exception utilisée lors des conversions
 *        depuis une <tt>std::string</tt>.
 *
 * Levée par he2b::esi::dev4::fromString().
 */
class bad_string_convert : public std::bad_cast
{
public:

    /*!
     * \brief Destructeur par défaut.
     */
    virtual ~bad_string_convert() = default;

    /*!
     * \brief Retourne une description de l'erreur rencontrée.
     *
     * En fait, retourne toujours la chaîne de caractères :
     * <tt>%he2b::esi::dev4::bad_string_convert</tt>. Pas très utile donc...
     *
     * \return La chaîne de caractères : <tt>%he2b::esi::dev4::bad_string_convert</tt>.
     */
    virtual const char * what() const noexcept
    {
        return "he2b::esi::dev4::bad_string_convert";
    }
};

/*!
 * \brief Modèle de fonction de conversion d'un type
 * quelconque vers une <tt>string</tt>.
 *
 * Pour que la fonction soit générée, le type de l'argument
 * doit permettre son injection dans un flux en sortie à l'aide de
 * l'opérateur <tt><<</tt>.
 *
 * \deprecated Depuis C++11, la fonction standard
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/to_string" target="blank"><tt>to_string</tt></a>
 * offre la possibilité de convertir une valeur numérique
 * en <tt>std::string</tt>.
 *
 * \param in La valeur à représenter sous la forme d'une string.
 *
 * \return La <tt>string</tt> représentant la valeur, sur base de
 *         l'<tt>operator<<</tt> de celle-ci.
 *
 */
template<typename T>
std::string toString(const T & in)
{
    std::ostringstream oss;
    oss << in;
    return oss.str();
}

/*!
 * \brief Modèle de fonction de conversion d'une <tt>string</tt>
 * vers un type quelconque <i>sauf</i> <tt>char</tt>
 * et <tt>char *</tt>.
 *
 * Le modèle de fonction utilise l'opérateur
 * d'extraction d'un flux vers le type de retour. Celui-ci
 * doit donc fournir un <tt>operator>></tt> adéquat.
 *
 * Lors de la conversion vers un booléen, seules les valeurs 0,
 * pour <tt>false</tt>, et 1, pour <tt>true</tt>, sont acceptées.
 *
 * \deprecated Depuis C++11, des fonctions d'extraction d'entiers, signés
 * ou non, et de flottants depuis une chaîne sont disponibles.
 * Il s'agit des fonctions
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stoi</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stol</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stoll</tt></a>
 * et
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stoul" target="_blank"><tt>std::stoul</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stoul" target="_blank"><tt>std::stoull</tt></a>
 * et
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stof</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stod</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stold</tt></a>.
 * Notez que les fonctions d'extraction d'entiers permettent de choisir la
 * base, ce qui n'est pas de cas de he2b::esi::dev4::fromString().
 *
 * Pour une étude comparative des fonctions de conversion d'une
 * <tt>std::string</tt> en <tt>int</tt>, allez voir
 * <a href="http://www.kumobius.com/2013/08/c-string-to-int/" target="_blank">ici</a>.
 *
 * \param t Référence d'une variable qui accueille le résultat de
 *          la conversion de la string.
 * \param s La <tt>string</tt> à convertir.
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La représentation de la <tt>string</tt> dans le type
 *         demandé lors de l'appel.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions
 *            qui pourraient
 *            être lancées par l'opérateur d'extraction de flux,
 *            une he2b::esi::dev4::bad_string_convert est levée si
 *            l'extraction du flux
 *            échoue ou si le flux n'est pas épuisé en fin
 *            d'extraction.
 */
template<typename T>
T fromString(T & t, const std::string & s, bool iw = false)
{
    std::istringstream iss(s);
    if (!iw) iss >> std::noskipws;
    iss >> t; // pourrait lever exception...
    if (iss.fail()) throw bad_string_convert();
    if (iw) iss >> std::ws;
    if (!iss.eof()) throw bad_string_convert();
    // le soucis avec char vient d'ici : 1! caractère,
    //  c.-à-d. 1! byte est lu => la fin du flux n'est pas détectée,
    //  il faut une lecture de plus.
    //  avec int, par exemple, le flux est épuisé pour détecter la fin
    //  de l'int (codé en string)

    return t;
}

/*!
 * \brief Modèle de fonction de conversion d'une <tt>string</tt>
 * vers un type quelconque <i>sauf</i> <tt>char</tt>
 * et <tt>char *</tt>.
 *
 * Le modèle de fonction utilise l'opérateur
 * d'extraction d'un flux vers le type de retour. Celui-ci
 * doit donc fournir un <tt>operator>></tt> adéquat.
 *
 * Lors de la conversion vers un booléen, seules les valeurs 0,
 * pour <tt>false</tt>, et 1, pour <tt>true</tt>, sont acceptées.
 *
 * \deprecated Depuis C++11, des fonctions d'extraction d'entiers, signés
 * ou non, et de flottants depuis une chaîne sont disponibles.
 * Il s'agit des fonctions
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stoi</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stol</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank"><tt>std::stoll</tt></a>
 * et
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stoul" target="_blank"><tt>std::stoul</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stoul" target="_blank"><tt>std::stoull</tt></a>
 * et
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stof</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stod</tt></a>,
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/stof" target="_blank"><tt>std::stold</tt></a>.
 * Notez que les fonctions d'extraction d'entiers permettent de choisir la
 * base, ce qui n'est pas de cas de he2b::esi::dev4::fromString().
 *
 * Pour une étude comparative des fonctions de conversion d'une
 * <tt>std::string</tt> en <tt>int</tt>, allez voir
 * <a href="http://www.kumobius.com/2013/08/c-string-to-int/" target="_blank">ici</a>.
 *
 * Notez que ce modèle de fonction permet de construire des surcharges
 * de fonctions ne différant entre elles que par leur type de retour !
 *
 * \param s La <tt>string</tt> à convertir.
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La représentation de la <tt>string</tt> dans le type
 *         demandé lors de l'appel.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions
 *            qui pourraient
 *            être lancées par l'opérateur d'extraction de flux,
 *            une he2b::esi::dev4::bad_string_convert est levée si
 *            l'extraction du flux
 *            échoue ou si le flux n'est pas épuisé en fin
 *            d'extraction.
 */
template<typename T>
T fromString(const std::string & s, bool iw = false)
{
    T t;
    std::istringstream iss(s);
    if (!iw) iss >> std::noskipws;
    iss >> t; // pourrait lever exception...
    if (iss.fail()) throw bad_string_convert();
    if (iw) iss >> std::ws;
    if (!iss.eof()) throw bad_string_convert();
    // le soucis avec char vient d'ici : 1! caractère,
    //  c.-à-d. 1! byte est lu => la fin du flux n'est pas détectée,
    //  il faut une lecture de plus.
    //  avec int, par exemple, le flux est épuisé pour détecter la fin
    //  de l'int (codé en string)

    return t;
}

// surcharges des templates
// pas de spécialisation :
// http://www.gotw.ca/publications/mill17.htm
// http://stackoverflow.com/questions/1511935/differences-between-
//                  template-specialization-and-overloading-for-functions

/*!
 * \brief Surcharge du modèle de fonction de conversion
 * d'une <tt>string</tt>
 * vers un type quelconque pour le type <tt>char</tt>.
 *
 * On utilise une surcharge plutôt qu'une spécialisation de modèle.
 * Les raisons en sont données
 * <a href="http://www.gotw.ca/publications/mill17.htm" target="_blank">ici</a>
 * et
 * <a href="https://stackoverflow.com/q/1511935" target="_blank">ici</a>.
 *
 * \param c Référence de la variable qui accueille le résultat de
 *          la conversion de la string en caractère.
 * \param s La <tt>string</tt> à convertir.
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La représentation de la <tt>string</tt> sous la
 *         forme d'un <tt>char</tt>.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions
 *            qui pourraient
 *            être lancées par l'opérateur d'extraction de flux,
 *            une he2b::esi::dev4::bad_string_convert est levée si
 *            l'extraction du flux
 *            échoue ou si le flux n'est pas épuisé en fin
 *            d'extraction.
 */
inline char fromString(char & c, const std::string & s,
                       bool iw = false)
{
    char bidon;
    std::istringstream iss(s);
    if (!iw) iss >> std::noskipws;
    iss >> c; // pourrait lever exception...
    if (iss.fail()) throw bad_string_convert();
    if (iw) iss >> std::ws;
    // pour épuiser le flux si bel et bien 1! caractère initialement
    // ne pas le faire avant car sinon : fail du flux !
    // et car sinon string("E f"); passe car iss >> bidon met f dans
    // bidon car le blanc entre E et f est sauté
    // (lié à if (!iw) iss >> std::noskipws;)
    iss >> bidon;
    if (!iss.eof()) throw bad_string_convert();

    return c;
}

/*!
 * \brief Fonction mise en <tt>delete</tt> pour empêcher son existence.
 *
 * La conversion de <tt>std::string</tt> en <tt>char *</tt> avec
 * he2b::esi::dev4::fromString() n'est pas sûre (cf. mémoire suffisamment allouée,
 * pointeur ok) et / ou ne fonctionne pas. Comme je n'ai pas envie de
 * développer la chose, je l'empêche avec
 * <a href="https://en.wikipedia.org/wiki/C%2B%2B11#Explicitly_defaulted_and_deleted_special_member_functions" target="_blank"><tt>= delete</tt></a>.
 *
 * Pour passer d'une <tt>std::string</tt> à une chaîne <i>à la C</i>
 * <tt>char *</tt>, il suffit d'utiliser les méthodes
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/c_str" target="_blank"><tt>c_str()</tt></a>
 * ou
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/data" target="_blank"><tt>data()</tt></a> de <tt>std::string</tt>.
 */
char * fromString(char *, const std::string &, bool = false) = delete;

// ici on doit passer par la spécialisation de template car la surcharge
// de fonction sur leur type de retour uniquement mène à des
// ambiguïtés => erreurs de compilation
// attention : pas de valeurs par défaut dans une spécialisation
// de template
// http://stackoverflow.com/questions/4050202/why-default-argument-cannot-be-specified-for-an-explicit-template-specialization
// ajouter inline pour que ld soit content...
/*!
 * \brief Spécialisation du modèle de fonction de conversion
 * d'une <tt>string</tt>
 * vers un type quelconque pour le type <tt>char</tt>.
 *
 * \param s La <tt>string</tt> à convertir.
 * \param iw Mis à <tt>true</tt>, les espaces blanches en début et
 *           en fin de la <tt>string</tt> sont
 *           ignorées ; par défaut ce paramètre est mis
 *           à <tt>false</tt> : les blancs ne sont pas ignorés.
 *
 * \return La représentation de la <tt>string</tt> sous la
 *         forme d'un <tt>char</tt>.
 *
 * \exception he2b::esi::dev4::bad_string_convert Outre les exceptions
 *            qui pourraient
 *            être lancées par l'opérateur d'extraction de flux,
 *            une he2b::esi::dev4::bad_string_convert est levée si
 *            l'extraction du flux
 *            échoue ou si le flux n'est pas épuisé en fin
 *            d'extraction.
 */
template <>
inline char fromString<char>(const std::string & s, bool iw)
{
    char c;
    char bidon;
    std::istringstream iss(s);
    if (!iw) iss >> std::noskipws;
    iss >> c; // pourrait lever exception...
    if (iss.fail()) throw bad_string_convert();
    if (iw) iss >> std::ws;
    // pour épuiser le flux si bel et bien 1! caractère initialement
    // ne pas le faire avant car sinon : fail du flux !
    // et car sinon string("E f"); passe car iss >> bidon met f dans
    // bidon car le blanc entre E et f est sauté
    // (lié à if (!iw) iss >> std::noskipws;)
    iss >> bidon;
    if (!iss.eof()) throw bad_string_convert();

    return c;
}

/*!
 * \brief Spécialisation de modèle de fonction mise en <tt>delete</tt>
 *        pour empêcher son existence.
 *
 * La conversion de <tt>std::string</tt> en <tt>char *</tt> avec
 * he2b::esi::dev4::fromString() n'est pas sûre (cf. mémoire suffisamment allouée,
 * pointeur ok) et / ou ne fonctionne pas. Comme je n'ai pas envie de
 * développer la chose, je l'empêche avec
 * <a href="https://en.wikipedia.org/wiki/C%2B%2B11#Explicitly_defaulted_and_deleted_special_member_functions" target="_blank"><tt>= delete</tt></a>.
 *
 * Pour passer d'une <tt>std::string</tt> à une chaîne <i>à la C</i>
 * <tt>char *</tt>, il suffit d'utiliser les méthodes
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/c_str" target="_blank"><tt>c_str()</tt></a>
 * ou
 * <a href="http://en.cppreference.com/w/cpp/string/basic_string/data" target="_blank"><tt>data()</tt></a> de <tt>std::string</tt>.
 */
template<>
char * fromString<char *>(const std::string &, bool) = delete;

} // namespace he2b::esi::dev4

#endif /* STRINGCONVERT_HPP_ */
