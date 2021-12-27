#include "configuracion.hpp"

void GlobalSetup::load(string inputFile){
    ifstream fin(inputFile.c_str());
    string ident;
    
    while (!fin.eof()) {
    
        fin >> ident;
        if (ident == "Ancho_Caja:") {
		fin >> caja.ancho;
		if (caja.ancho <= 0) {
			cout << "ERROR: La base del recinto debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Altura_Caja:") {
		fin >> caja.altura;
		if (caja.altura <= 0) {
			cout << "ERROR: La altura del recinto debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Altura_Base:") {
		fin >> caja.AltBase;
		if (caja.AltBase <= 0) {
			cout << "ERROR: La altura de la base y la tapa del recinto debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Ancho_Pared:") {
		fin >> caja.AnPar;
		if (caja.AnPar <= 0) {
			cout << "ERROR: El ancho de las paredes del recinto debe ser > 0." << endl;
			exit(1);
		}	
	}
	if (ident == "Caja_dens:") {
		fin >> caja.dens;
		if (caja.dens <= 0) {
			cout << "La densidad de la caja debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Caja_roz:") {
		fin >> caja.roz;
		if (caja.roz <= 0) {
			cout << "ERROR: El coeficiente de fricción debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Caja_rest:") {
		fin >> caja.rest;
		if (caja.rest <= 0) {
			cout << "ERROR: El coeficiente de restitución debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "noTipoGranos:") {
		fin >> noTipoGranos;
		if (noTipoGranos <= 0) {
			cout << "ERROR: El número de tipos granos debe ser > 0." << endl;
			exit(1);
		}
		granos = new tipoGrano*[noTipoGranos];
		for (int i = 0; i < noTipoGranos; i++) {
			granos[i] = new tipoGrano;
			fin >> granos[i]->noGranos;
			fin >> granos[i]->radio;
			fin >> granos[i]->nLados;
			fin >> granos[i]->dens;
			fin >> granos[i]->rozam;
			fin >> granos[i]->rest;
			if (granos[i]->noGranos < 1) {
			cout << "ERROR: El número de granos debe ser > 0." << endl;
			exit(1);
			}
			if (granos[i]->radio < 0.01) {
			cout << "ERROR: El radio de los granos debe ser > 0.01" << endl;
			exit(1);
			}
			if (granos[i]->dens <= 0) {
				cout << "ERROR: La densidad de los granos debe ser > 0." << endl;
				exit(1);
			}
			if (granos[i]->rozam < 0.0) {
				cout << "ERROR: El coeficiente de rozamiento debe ser 0 <= rozam." << endl;
				exit(1);
			}
			if (granos[i]->rest < 0.0 || granos[i]->rest > 1.0) {
				cout << "ERROR: El coeficiente de restitución debe ser 0 <= rest <= 1.0." << endl;
				exit(1);
			}
		}
	}
	if (ident == "timeStep:") {
		fin >> tStep;
		if (tStep < 0.0) {
			cout << "ERROR: El paso de integración debe ser >= 0." << endl;
			exit(1);
		}
	}
	if (ident == "tMax:") {
		fin >> tMax;
		if (tMax < 0.0) {
			cout << "ERROR: el tiempo máximo de simulación debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "pIter:") {
		fin >> pIter;
		if (pIter < 0) {
			cout << "ERROR: El número de iteraciones de posicion debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "vIter:") {
		fin >> vIter;
		if (vIter < 0) {
			cout << "ERROR: El número de iteraciones de velocidad debe ser > 0." << endl;
			exit(1);
		}
	}
// 	if (ident == "Frec_ex:") {
// 		fin >> frec;
// 		if (frec < 0) {
// 			cout << "ERROR: La frecuencia de excitación debe ser > 0." << endl;
// 			exit(1);
// 		}
// 	}
	if (ident == "Frec_Start:") {
		fin >> fStart;
		if (fStart < 0) {
			cout << "ERROR: La frecuencia inicial de excitación debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Frec_End:") {
		fin >> fEnd;
		if (fEnd < fStart) {
			cout << "ERROR: La frecuencia final de excitación debe ser mayor que la inicial." << endl;
			exit(1);
		}
	}
	if (ident == "Frec_Step:") {
		fin >> fStep;
		if (fStep < 0) {
			cout << "ERROR: El paso en las frecuencias de excitación debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "Ampl:") {
		fin >> Amp;
		if (Amp < 0) {
			cout << "ERROR: La amplitud de excitación debe ser > 0." << endl;
			exit(1);
		}
	}		
	if (ident == "KRes:") {
		fin >> KRes;
		if (KRes < 0) {
			cout << "ERROR: La rigidez del resorte debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "C:") {
		fin >> C;
		if (C < 0) {
			cout << "ERROR: El coeficiente de amortiguacion debe ser > 0." << endl;
			exit(1);
		}
	}		
	if (ident == "g:") {
		fin >> g;
	}
	if (ident == "ZeroSet:") {
		fin >> ZeroSet;
	}
	if (ident == "preOutFile:") {
		fin >> preOutFile;
	}
	if (ident == "outFileExt:") {
		fin >> outFileExt;
	}
	if (ident == "tMinReg:") {
		fin >> tMinReg;
		if (tMinReg < 0.0) {
			cout << "ERROR: tMinReg debe ser > 0." << endl;
			exit(1);
		}
	}
	if (ident == "regStep:") {
		fin >> regStep;
		if (regStep < 0) {
			cout << "ERROR: regStep debe ser > 0." << endl;
			exit(1);
		}
	}

    }
};
