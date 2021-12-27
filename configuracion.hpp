

#ifndef _CONFIGURACION_H
#define _CONFIGURACION_H

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

	double ancho = 12.25; /*!< Ancho del contenedor */
	double altura = 7.0; /*!< Altura del contenedor */
	double AltBase = 1; /*!< Altura de la base del contenedor */
	double AnPar = 1; /*!< Ancho de la pared del contenedor */
	double start; /*!< No sé qué es del contenedor */
	double dens = 0.0090745; /*!< Densidad del material del contenedor */
	double roz = 0.5; /*!< Coeficiente de rozamiento del contenedor */
	double rest = 0.5; /*!< Coeficiente de restitución del contenedor */
	
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

	int noGranos = 100;	/*!< Cantidad de granos de este tipo */
	double radio = 0.25;	/*!< Radio */
	int nLados = 1;		/*!< Número de lados */
	double **vertices;	/*!< Array con coordenadas de los vértices (double x, double y) */
	double dens = 0.01905; /*!< Densidad de los granos */
	double rozam = 0.5; /*!< Coeficiente de rozamiento de los granos */
	double rest = 0.058; /*!< Coeficiente de restitución de los granos */
	
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
class GlobalSetup {
public:

	// Parámetros de objetos del modelo
	Contenedor caja; /*!< Recinto de contención */
	tipoGrano conf_gran;
	int noTipoGranos = 1; /*!< Cantidad de tipos de granos distintos en la simulación */
	tipoGrano granos; /*!< Array que contiene los distintos tipos de granos */

	//cantidad de obstaculos
		
	int obn = 1;

	// Parámetros de control de la simulación
	double tStep =0.005; /*!< Paso temporal de integración */
	double tMax = 30.0; /*!< Límite temporal de la simulación */
	int pIter = 12; /*!< Iteraciones para la satisfacción de restricciones de posición */
	int vIter = 12; /*!< Iteraciones para la satisfacción de restricciones de velocidad */
	
	// Parámetros de sistema primario
// 	double frec; /*!< Frecuencia de la excitación armónica */
	double Amp = 1.0; /*!< Amplitud de la excitación armónica */
	double KRes = 2.77; /*!< Constante elástica del resorte */
	double C = 0.056; /*!< Constante del amortiguador viscoso */
	double g = -9.81; /*!< Aceleración de la gravedad */
	double ZeroSet = 5.0; /*!< Posición vertical de la caja en la que la fuerza del resorte es nula */
//	string inputFile; /*!< Nombre del archivo con parámetros de control */
	string preOutFile = "tray"; /*!< Prefijo del nombre del archivo de salida de trayectoria */
	string outFileExt; /*!< Extensión del archivo de salida de trayectoria */
	double tMinReg = 3.0; /*!< Tiempo a partir del cual se registra la trayectoria */
	int regStep = 30 ; /*!< Paso de registro de trayectoria */
	double fStart = 5.0; /*!< Frecuencia inicial de vibración */
	double fEnd = 5.0; /*!< Frecuencia final de vibración */
	double fStep = 0.4; /*!< Paso en las frecuencias de vibración */
	void load(string);	
};

#endif

