//Compilar con: g++ -o damper damper.cpp -Iinclude/ -Llib/ -lbox2d

#include <iostream>
using namespace std;
#include "include/box2d/box2d.h"
#include "configuracion.hpp"
#include<string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "random.hpp"

GlobalSetup conf;
RandomGenerator get_random;




int main(){

	//instanciamos la configuracion

	extern GlobalSetup conf;
	conf.load("params.ini");
		
	//provisorio --------------------
	int n_obs = 5;
	int n_ind = 20;
	
	float poblacion[n_ind][10];  //matriz de la poblaciòn
		
	int ranking[n_ind];
		
	float reproductores[n_ind][10];
	//provisorio -------------------
		
	init_population(n_obs,n_ind,poblacion); 
	
	for(int g=1;g<3;g++){
		cout << "generación: " << g << endl;
		 //genero la matriz de la poblaciòn;
		
		fitness(poblacion,n_ind,ranking);
		
		for (int i=0;i<n_ind;i++){
			if (ranking[i]==1){
				cout << "Mejor THD de la poblacion: " << THD(poblacion[i],false) << endl;
			};
		};
			
		for (int i=0;i<n_ind;i++){
			int A = int(get_random.getAB(0.0,20.0));
			int B = int(get_random.getAB(0.0,20.0));
			while (A==B){
				B= int(get_random.getAB(0.0,20.0));
			};
			float C = get_random.getAB(0.0,1.0);
			int contador=0;
			if (contador==0){
				if (ranking[A]<ranking[B] and C<0.9){
					for (int j=0;j<10;j++){
						reproductores[i][j]=poblacion[A][j];
					};
					
				}
				else{
					for (int j=0;j<10;j++){
						reproductores[i][j]=poblacion[B][j];
					};
				};
			};
		};
		
		int atraccion [n_ind]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
		
		for (int i=0;i<30;i++){
			int A = int(get_random.getAB(0.0,20.0));
			int B = int(get_random.getAB(0.0,20.0));
			int aux=atraccion[A];
			atraccion[A]=atraccion[B];
			atraccion[B]=aux;
		};
		
		float hijos[n_ind][10];
		int contador=0;
		for (int i=0;i<n_ind/2;i++){
			float new_ind[n_ind];
			
			reproduccion(reproductores[atraccion[i]],reproductores[atraccion[i+10]],new_ind);
			
			for (int j=0;j<10;j++){
				hijos[contador][j]=new_ind[j];
				hijos[contador+1][j]=new_ind[j+10];
			};
			contador=contador+2;
		};
		contador=0;
		
		/*for (int i=0;i<n_ind;i++){
			for (int j=0;j<10;j++){
			
				cout << hijos[i][j] << " - ";
			
			};
			 cout<<endl;
		};*/
	
		int rank_hijos[n_ind];
		fitness(hijos, n_ind,rank_hijos);
		
		for (int i=0;i<n_ind;i++){
			if (rank_hijos[i]==1){
				cout << "Mejor THD de los hijos: " << THD(hijos[i],false) << endl;
			};
		};
		
		
		float new_pob[20][10];
		int aux=0;
		for (int i=0;i<n_ind;i++){
			
			if(ranking[i]<6){
				for(int j=0;j<10;j++){
					new_pob[aux][j]=poblacion[i][j];
				};
				aux=aux+1;
			};
			
		};
		
		
		for (int i=0;i<n_ind;i++){
			if(rank_hijos[i]<16){
				for(int j=0;j<10;j++){
					new_pob[aux][j]=hijos[i][j];
				};
				aux=aux+1;
			};
			
		};
		aux=0;
		
		for (int i=0;i<20;i++){
			for (int j=0;j<10;j++){
				poblacion[i][j]=new_pob[i][j];
			};
		};
		//------------------------
		Contenedor caja = conf.caja;
		
		double xmin= -caja.ancho/2 + 0.75;
		double xmax= caja.ancho/2 - 0.75;
		double ymin=0.75;
		double ymax=caja.altura - 0.75;
		//----------------------
		for (int i=0;i<20;i++){
			for (int j=0;j<10;j++){
				float A = get_random.get01();
				
				if (A<0.05){
					if(j/2 != 0){
						poblacion[i][j]=get_random.getAB(ymin,ymax);
					}
					else{
						poblacion[i][j] = get_random.getAB(xmin,xmax);
					};
				};
				
			};
		};
	
	};
	
	
	return 0;
};

