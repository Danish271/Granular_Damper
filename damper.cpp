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
//#include <stdlib.h>


void saveFrame(std::ofstream *ff, b2World *w, const float* t, const int* nTG,const int* nTO);
template <typename T>
string NumberToString ( T Number )	{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

int main(){

//instanciamos la configuracion

	GlobalSetup conf;
	conf.load("params.ini");
	Contenedor caja = conf.caja;
	
	obstaculos ob1;
	
//creamos el mundo
	
	cout << "# Creación del sistema ..." << endl;
// Definición del mundo
	b2Vec2 gravedad(0.0f, conf.g);
	b2World world(gravedad);
	cout << "\t- Objeto mundo creado." << endl;

//creamos el suelo - nivel cero

	b2BodyDef tr_def;
	tr_def.position.Set(0.0f, -10.0f);
	
	bodyGrainData trInfo;
	trInfo.isGrain = false;
	trInfo.nLados = 10;
	tr_def.userData.pointer = uintptr_t(&trInfo);
	
	b2Body* tierra = world.CreateBody(&tr_def);
	b2EdgeShape linea;
	linea.SetTwoSided(b2Vec2(-40.0f,-10.0f), b2Vec2(40.0f,-10.0f));
	
	
	tierra->CreateFixture(&linea, 0.0f);
	
	
//creamos la caja
// Definición de la caja

	
	b2BodyDef caja_def;
	caja_def.type = b2_dynamicBody;
	caja_def.allowSleep = false;
	caja_def.position.Set(0.0f, conf.ZeroSet);
	
	//asociamos la userdata al cuerpo
	bodyGrainData cajaInfo;
	cajaInfo.isGrain = false;
	cajaInfo.nLados = 4;
	cajaInfo.radio = caja.altura;
	caja_def.userData.pointer = uintptr_t(&cajaInfo);
	
	b2Body* caja_body = world.CreateBody(&caja_def);
	
	b2PolygonShape caja_Base_Shape;
	caja_Base_Shape.SetAsBox(0.5f*caja.ancho, 0.5f*caja.AltBase);


	b2PolygonShape caja_PareI_Shape;
	caja_PareI_Shape.SetAsBox(0.5f*caja.AnPar, 0.5f*caja.altura+caja.AltBase, 
								b2Vec2(0.5f*(-caja.ancho-caja.AnPar), 
								0.5f*(caja.altura+caja.AltBase)), 0.00f);

	b2PolygonShape caja_PareD_Shape;
	caja_PareD_Shape.SetAsBox(0.5f*caja.AnPar, 0.5f*caja.altura+caja.AltBase, 
								b2Vec2(0.5f*(caja.ancho+caja.AnPar), 
								0.5f*(caja.altura+caja.AltBase)), 0.00f);

	b2PolygonShape caja_Tapa_Shape;
	caja_Tapa_Shape.SetAsBox(0.5f*caja.ancho, 0.5f*caja.AltBase, 
								b2Vec2(0.0f,(caja.altura+caja.AltBase)), 0.00f);
								
	
//definimos el shape de los obstaculos
	
	
	b2CircleShape ob1shape;
	ob1shape.m_radius = ob1.obr;
	ob1shape.m_p = {ob1.obx,ob1.oby};
	
	b2FixtureDef ob1fixDef;
	ob1fixDef.shape = &ob1shape;
	ob1fixDef.density = caja.dens;
	ob1fixDef.friction = caja.roz;
	ob1fixDef.restitution = caja.rest;
	
	//cargamos el user data del fixture
	
	bodyFixtureData FixtureData;
	FixtureData.isObstacle = true;
	FixtureData.nLados = 1;
	FixtureData.obx = ob1.obx;
	FixtureData.oby = ob1.oby;
	ob1fixDef.userData.pointer = uintptr_t(&FixtureData);
	
	caja_body->CreateFixture(&ob1fixDef);
	
	//Creamos el fixture de la base
	
	b2FixtureDef caja_Base_fix;
	caja_Base_fix.shape = &caja_Base_Shape;
	caja_Base_fix.density = caja.dens;
	caja_Base_fix.friction = caja.roz;
	caja_Base_fix.restitution = caja.rest;
	
	bodyFixtureData FixtureDataBase;
	FixtureDataBase.isObstacle = false;
	FixtureDataBase.nLados = 4;
	caja_Base_fix.userData.pointer = uintptr_t(&FixtureDataBase);
	
	caja_body->CreateFixture(&caja_Base_fix);
	
	//creamos el fixture de la pared izquierda
	
	b2FixtureDef caja_PareI_fix;
	caja_PareI_fix.shape = &caja_PareI_Shape;
	caja_PareI_fix.density = caja.dens;
	caja_PareI_fix.friction = caja.roz;
	
	bodyFixtureData FixtureDataParedI;
	FixtureDataParedI.isObstacle = false;
	FixtureDataParedI.nLados = 4;
	caja_PareI_fix.userData.pointer = uintptr_t(&FixtureDataParedI);
	
	caja_body->CreateFixture(&caja_PareI_fix);
	
	//creamos el fixture de la pared derecha
	
	b2FixtureDef caja_PareD_fix;
	caja_PareD_fix.shape = &caja_PareD_Shape;
	caja_PareD_fix.density = caja.dens;
	caja_PareD_fix.friction = caja.roz;
	caja_PareD_fix.restitution = caja.rest;
	
	bodyFixtureData FixtureDataParedD;
	FixtureDataParedD.isObstacle = false;
	FixtureDataParedD.nLados = 4;
	caja_PareD_fix.userData.pointer = uintptr_t(&FixtureDataParedD);
	
	caja_body->CreateFixture(&caja_PareD_fix);
	
	//creamos el fixture de la tapa
	
	b2FixtureDef caja_Tapa_fix;
	caja_Tapa_fix.shape = &caja_Tapa_Shape;
	caja_Tapa_fix.density = caja.dens;
	caja_Tapa_fix.friction = caja.roz;
	caja_Tapa_fix.restitution = caja.rest;
	
	bodyFixtureData FixtureDataTapa;
	FixtureDataTapa.isObstacle = false;
	FixtureDataTapa.nLados = 4;
	caja_Tapa_fix.userData.pointer = uintptr_t(&FixtureDataTapa);
	
	caja_body->CreateFixture(&caja_Tapa_fix);

	//restriccion
	//EJE DE MOVIMIENTO TIERRA CAJA
	b2PrismaticJointDef mov2;
	mov2.Initialize(tierra, caja_body, b2Vec2(0.0f, conf.ZeroSet), b2Vec2(0.0f, 1.0f));
	mov2.enableMotor = false;
	b2PrismaticJoint* mov2_joint = (b2PrismaticJoint*)world.CreateJoint(&mov2);
	cout << "\t- Caja y restricción prismática creadas." << endl;
	
	//preguntar restricciìon prismàtica.	-------------------------------------------------------------------------------
		
// Generación de granos.

	float cajaInf,cajaSup,cajaIzq,cajaDer,x,y;
	float mg = 0.0;
	int noTotGranos = 0;
	cajaInf = 0.05f*caja.altura;
	cajaSup = 0.5f*caja.altura;
	cajaIzq = 0.5f*(-caja.ancho+caja.AnPar)*0.8;
	cajaDer = 0.5f*(caja.ancho-caja.AnPar)*0.8;
	x = 0.5f * (-caja.ancho+caja.AnPar);
	y = conf.ZeroSet;
	
	bodyGrainData gInfo [conf.noTipoGranos];
	
	for (int i = 0; i < conf.noTipoGranos; i++) { // Loop sobre tipos de granos.

		gInfo[i].isGrain = true;
		gInfo[i].nLados = conf.granos[i]->nLados;
		gInfo[i].radio = conf.granos[i]->radio;
		
		if (i == 0) y += 2.0 * conf.granos[i]->radio;
		for (int j = 0; j < conf.granos[i]->noGranos; j++) { // Loop sobre el número de granos de cada tipo.
// 			x = RandomFloat(cajaIzq,cajaDer);
// 			y = RandomFloat(cajaInf,cajaSup)+globalSetup->ZeroSet;
			x += 2.1* conf.granos[i]->radio;
			if (x > 0.5f * (caja.ancho - caja.AnPar)-conf.granos[i]->radio) {
				x = 0.5f*(-caja.ancho+caja.AnPar) + conf.granos[i]->radio;
				y += 2.1 * conf.granos[i]->radio;
			};
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(x,y);
			bd.angle = 0.0;
			
			bd.userData.pointer = uintptr_t(&gInfo[i]);
			
			b2Body* grain = world.CreateBody(&bd);
			
			if (conf.granos[i]->nLados == 1) {
			
				b2CircleShape circle;
				circle.m_radius = conf.granos[i]->radio;
				b2FixtureDef fixDef;
				fixDef.shape = &circle;
				fixDef.density = conf.granos[i]->dens;
				fixDef.friction = conf.granos[i]->rozam;
				fixDef.restitution = conf.granos[i]->rest;
				
				bodyFixtureData FixtureData;
				FixtureData.isObstacle = false;
				FixtureData.nLados = 1;
				fixDef.userData.pointer = uintptr_t(&FixtureData);
				
				b2Fixture* gfixture = grain->CreateFixture(&fixDef);
				mg += grain->GetMass();
				
				if (j == 0) cout << "\t- Grano de tipo " << i << " creado con masa " << grain->GetMass() << " kg." << endl;
			}
			else {
				b2PolygonShape poly;
				int vertexCount = conf.granos[i]->nLados;
				b2Vec2 vertices[8];
				for (int k = 0; k < conf.granos[i]->nLados; k++) 
					vertices[k].Set(conf.granos[i]->vertices[k][0],conf.granos[i]->vertices[k][1]);
				poly.Set(vertices,vertexCount);
				b2FixtureDef fixDef;
				fixDef.shape = &poly;
				fixDef.density = conf.granos[i]->dens;
				fixDef.friction = conf.granos[i]->rozam;
				fixDef.restitution = conf.granos[i]->rest;
				b2Fixture* gfixture = grain->CreateFixture(&fixDef);
				mg += grain->GetMass();
				
				if (j == 0) cout << "\t- Grano de tipo " << i << " creado con masa " << grain->GetMass() << " kg." << endl;
			}
			noTotGranos++;
		} // Fin loop sobre el número de granos de cada tipo.
	} // Fin loop sobre tipo de granos	
	cout << "\t- Número total de granos = " << noTotGranos << endl;
	cout << "\t- Masa total de granos = " << mg << " kg."<< endl;
	cout << "... sistema creado." << endl;

	// Preparamos los parámetros de la simulación. 
	float timeStep = conf.tStep;
	int pIterations = conf.pIter;
	int vIterations = conf.vIter;
	b2Vec2 pos_caja;
	b2Vec2 vel_caja;
	b2Vec2 FNet;
	float FResort, FAmort;
	float estRes, lRes = conf.ZeroSet;
	float C = conf.C;
	float Amp = conf.Amp;
	float KRes = conf.KRes;
	float frec = conf.fStart;
	string ffname;

	int nStep = 0;
	bool saveT = false;
	int nTO = conf.obn;
	cout << "# Inicio de la simulación..." << endl;

	while (frec <= conf.fEnd) {
		float w = 2 * b2_pi * frec;
		float t = 0.0;
		float u = 0.0;
		float vu = 0.0;
		cout << " Frecuencia: " << frec << endl;
		std::ofstream trayFile;
		ffname = conf.preOutFile + '_'+NumberToString(frec) + '.' + conf.outFileExt;
		
		trayFile.open(ffname.c_str());
		
		while (t < conf.tMax) {
			t += timeStep;
			if (t > conf.tMinReg) saveT = true;
			u = Amp * cos(w * t);
			vu = -w * Amp * sin(w * t);
			pos_caja = caja_body->GetPosition();
			vel_caja = caja_body->GetLinearVelocity();
			estRes = pos_caja.y - u - lRes;
			FResort = -KRes * estRes;
			FAmort = -C * (vel_caja.y - vu);
			FNet = b2Vec2(0.0f, FResort+FAmort);
			caja_body->ApplyForce(FNet,pos_caja,true);
			world.Step(timeStep,pIterations,vIterations);
			world.ClearForces();
			
			if (saveT && !(nStep % conf.regStep)) {
				saveFrame(&trayFile, &world, &t, &noTotGranos,&nTO);
				nStep = 0;
			}
			nStep++;
		}
		trayFile.close();
		frec += conf.fStep;
	}

	cout << " ... simulación finalizada." << endl;
	
	return 0;
};


void saveFrame(std::ofstream *ff, b2World *w, const float* t, const int* nTG,const int* nTO) {
	// Cálculo del centro de masa, valores mínimo y máximo
	double y, x, ymin, ymax, ycm, MT, suma;
	double ycaja, vcaja;
	ymin = 1E8; ymax = -1E8; MT = 0.0; suma = 0.0;
	int n = 0;
	int idg = 1;
	*(ff) << fixed << setw(8) << "# tiempo = "<< *t << " (id del grano - pos x - pos y - radio)" << endl;
	for (b2Body* bd = w->GetBodyList(); n < *nTG + 1; bd = bd->GetNext()) {

		bodyGrainData* infGr = (bodyGrainData*) (bd->GetUserData()).pointer;	
		if (infGr->isGrain) {
			y = bd->GetPosition().y;
			x = bd->GetPosition().x;
			
				// Guardo trayectorias
			*(ff) << fixed << "G"<< idg << " ";
			*(ff) << fixed << setw(8) << x << " ";
			*(ff) << fixed << setw(8) << y << " ";
			*(ff) << fixed << setw(8) << infGr->radio << " ";
			*(ff) << endl;
			idg=idg+1;
		}
		else {
			if (infGr->nLados == 4) {
				ycaja = bd->GetPosition().y;
//				vcaja = bd->GetLinearVelocity().y;

				int idb = 1;
				int n1 = 0;
				b2Fixture* obsfix = bd->GetFixtureList();
				
				for(obsfix; n1<*nTO + 4; obsfix = obsfix->GetNext()){
					
					bodyFixtureData* infobs = (bodyFixtureData*) (obsfix->GetUserData()).pointer;	
					if(infobs->isObstacle == true){
						b2Shape* shapeobs = obsfix->GetShape();
						*(ff) << "Ob" << " " << idb << " " << infobs->obx << " " << infobs->oby + ycaja << " " << shapeobs->m_radius << endl;
						idb = idb + 1;
					
					};
					n1++;
				};

				*(ff) << fixed << "caja " << ycaja << " " << infGr->radio << endl;
			}
		}
		n++;
	}
	idg=1;
	*(ff) << flush;
}

