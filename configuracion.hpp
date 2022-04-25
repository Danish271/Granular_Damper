

#ifndef _CONFIGURACION_H
#define _CONFIGURACION_H


// includes para THD-----------
#include <stdio.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <iostream>
#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>
#include <numeric>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])
//------------------------

#include<string>
#include "random.hpp"

#include "include/box2d/box2d.h"
#include <cstdlib>
using std::exit;
#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream;
#include <iomanip>
using std::fixed; using std::setw;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <cmath>
using std::sin; using std::cos;



struct Contenedor {

	double ancho; /*!< Ancho del contenedor */
	double altura; /*!< Altura del contenedor */
	double AltBase; /*!< Altura de la base del contenedor */
	double AnPar; /*!< Ancho de la pared del contenedor */
	double start; /*!< No sé qué es del contenedor */
	double dens; /*!< Densidad del material del contenedor */
	double roz; /*!< Coeficiente de rozamiento del contenedor */
	double rest; /*!< Coeficiente de restitución del contenedor */
	
};

struct obstaculos {
	
	//las coordenadas son respecto al centro del fondo de la caja	
	
	float obx = 0.0;
	float oby = 1.5;
	float obr = 0.75;
		
};
/** \struct tipoGrano
 * \brief Estructura que contiene información sobre un determinado tipo de granos
 * 
 * Estructura que contiene información sobre un determinado tipo de grano:
 * \li datos geométricos
 * \ñi información sobre el material que lo compone
 * */
struct tipoGrano {

	int noGranos;	/*!< Cantidad de granos de este tipo */
	double radio;	/*!< Radio */
	int nLados;		/*!< Número de lados */
	double **vertices;	/*!< Array con coordenadas de los vértices (double x, double y) */
	double dens; /*!< Densidad de los granos */
	double rozam; /*!< Coeficiente de rozamiento de los granos */
	double rest; /*!< Coeficiente de restitución de los granos */
	
};


/** \struct bodyGrainData
 * \brief Estructura que almacena datos asociados a cada grano.
 * */
struct bodyGrainData {

	bool isGrain;	/*!< Variable lógica que identifica granos */
	int nLados;	/*!< Número de lados que tiene el grano */
	float radio;
};

struct bodyFixtureData {

	bool isObstacle;	/*!< Variable lógica que identifica granos */
	int nLados;	/*!< Número de lados que tiene el grano */
	float obx;
	float oby;
	
};

/** \class GlobalSetup
 * Clase que contiene toda la información necesaria para realizar una simulación
 * */
class GlobalSetup{
public:

	// Parámetros de objetos del modelo
	Contenedor caja; /*!< Recinto de contención */
	int noTipoGranos; /*!< Cantidad de tipos de granos distintos en la simulación */
	tipoGrano **granos; /*!< Array que contiene los distintos tipos de granos */

	//cantidad de obstaculos cambiar a lectura por params.ini
		
	int obn = 5;

	// Parámetros de control de la simulación
	double tStep; /*!< Paso temporal de integración */
	double tMax; /*!< Límite temporal de la simulación */
	int pIter; /*!< Iteraciones para la satisfacción de restricciones de posición */
	int vIter; /*!< Iteraciones para la satisfacción de restricciones de velocidad */
	
	// Parámetros de sistema primario
// 	double frec; /*!< Frecuencia de la excitación armónica */
	double Amp; /*!< Amplitud de la excitación armónica */
	double KRes; /*!< Constante elástica del resorte */
	double C; /*!< Constante del amortiguador viscoso */
	double g; /*!< Aceleración de la gravedad */
	double ZeroSet; /*!< Posición vertical de la caja en la que la fuerza del resorte es nula */
//	string inputFile; /*!< Nombre del archivo con parámetros de control */
	string preOutFile; /*!< Prefijo del nombre del archivo de salida de trayectoria */
	string outFileExt; /*!< Extensión del archivo de salida de trayectoria */
	double tMinReg; /*!< Tiempo a partir del cual se registra la trayectoria */
	int regStep; /*!< Paso de registro de trayectoria */
	double fStart; /*!< Frecuencia inicial de vibración */
	double fEnd; /*!< Frecuencia final de vibración */
	double fStep; /*!< Paso en las frecuencias de vibración */
	void load(string);

	 //numero de obstaculos
	
};

double THD(float cromosoma[10],bool guardar);

int* fitness(float poblacion[][10], int n_ind,int ranking[]);

float* init_population(int n_obs,int n_ind,float poblacion[][10]);

float* reproduccion(float ind1[],float ind2[],float new_ind[]);

void saveFrame(std::ofstream *ff, b2World *w, const float* t, const int* nTG,const int* nTO);
template <typename T>
string NumberToString ( T Number ){
	std::ostringstream ss;
	ss << Number;
	return ss.str();
};

#endif

