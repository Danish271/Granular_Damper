/*! \file random.hpp
 * \brief Archivo de cabecera para la clase RandomGenerator
 * \author Manuel Carlevaro <manuel@iflysib.unlp.edu.ar>
 * \version 1.0
 * \date 2018.12.14
 */


#ifndef _RANDOM_HPP
#define _RANDOM_HPP

#include <random>

/*! \class RandomGenerator random.hpp "random.hpp"
 * \brief Clase para instanciar un generador de números aleatorios
 */
class RandomGenerator {
    private:
        int semilla; /*!< Semilla del generador */
        std::mt19937 generator; /*!< Generador de números aleatorios */
    public:
        /*! Constructor por defecto
         * Utiliza 13 como semilla
         */
        RandomGenerator() : semilla(300) {}

        /*! Constructor que inicializa la semilla
         * \param int i: semilla
         */
        RandomGenerator(int i) : semilla(i) {generator.seed(semilla);}

        /*! Devuelve un double en [0,1)
         * \param void
         * \return double
         */
        double get01() {return double(generator()) / generator.max();}

        /*! Devuelve un double en [a,b)
         * \param double a
         * \param double b
         * \return double
         */
        double getAB(double a, double b) {
            double r = double(generator()) / generator.max();
            return (a + r * (b - a));
        }
};

#endif
