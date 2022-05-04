#include "configuracion.hpp"
#include <typeinfo>

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

double THD(float cromosoma[10],bool guardar){
//creamos el mundo
	
	extern GlobalSetup conf;
	Contenedor caja = conf.caja;
	
	//cout << "# Creación del sistema (desde funciòn fitness) ..." << endl;
// Definición del mundo
	b2Vec2 gravedad(0.0f, conf.g);
	b2World world(gravedad);
	//cout << "\t- Objeto mundo creado." << endl;

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
	int aux=0;
	
	
	bodyFixtureData FixtureData[conf.obn+4];

	for (int i=0;i<conf.obn;i++){
		
		b2CircleShape ob1shape;
		ob1shape.m_radius = 0.75;
		ob1shape.m_p = {cromosoma[aux],cromosoma[aux+1]};

		b2FixtureDef ob1fixDef;
		ob1fixDef.shape = &ob1shape;
		ob1fixDef.density = caja.dens;
		ob1fixDef.friction = caja.roz;
		ob1fixDef.restitution = caja.rest;
	
		//cargamos el user data del fixture
		
		FixtureData[i].isObstacle = true;
		FixtureData[i].nLados = 1;
		FixtureData[i].obx = cromosoma[aux];
		FixtureData[i].oby = cromosoma[aux+1];
		ob1fixDef.userData.pointer = uintptr_t(&FixtureData[i]);
		caja_body->CreateFixture(&ob1fixDef);
		
		aux=aux+2;
	};
	aux=0;
	//Creamos el fixture de la base
	
	b2FixtureDef caja_Base_fix;
	caja_Base_fix.shape = &caja_Base_Shape;
	caja_Base_fix.density = caja.dens;
	caja_Base_fix.friction = caja.roz;
	caja_Base_fix.restitution = caja.rest;
	

	FixtureData[conf.obn].isObstacle = false;
	FixtureData[conf.obn].nLados = 4;
	caja_Base_fix.userData.pointer = uintptr_t(&FixtureData[conf.obn]);
	
	caja_body->CreateFixture(&caja_Base_fix);
	
	//creamos el fixture de la pared izquierda
	
	b2FixtureDef caja_PareI_fix;
	caja_PareI_fix.shape = &caja_PareI_Shape;
	caja_PareI_fix.density = caja.dens;
	caja_PareI_fix.friction = caja.roz;
	
	FixtureData[conf.obn+1].isObstacle = false;
	FixtureData[conf.obn+1].nLados = 4;
	caja_PareI_fix.userData.pointer = uintptr_t(&FixtureData[conf.obn+1]);
	
	caja_body->CreateFixture(&caja_PareI_fix);
	
	//creamos el fixture de la pared derecha
	
	b2FixtureDef caja_PareD_fix;
	caja_PareD_fix.shape = &caja_PareD_Shape;
	caja_PareD_fix.density = caja.dens;
	caja_PareD_fix.friction = caja.roz;
	caja_PareD_fix.restitution = caja.rest;
	
	FixtureData[conf.obn+2].isObstacle = false;
	FixtureData[conf.obn+2].nLados = 4;
	caja_PareD_fix.userData.pointer = uintptr_t(&FixtureData[conf.obn+2]);
	
	caja_body->CreateFixture(&caja_PareD_fix);
	
	//creamos el fixture de la tapa
	
	b2FixtureDef caja_Tapa_fix;
	caja_Tapa_fix.shape = &caja_Tapa_Shape;
	caja_Tapa_fix.density = caja.dens;
	caja_Tapa_fix.friction = caja.roz;
	caja_Tapa_fix.restitution = caja.rest;
	
	FixtureData[conf.obn+3].isObstacle = false;
	FixtureData[conf.obn+3].nLados = 4;
	caja_Tapa_fix.userData.pointer = uintptr_t(&FixtureData[conf.obn+3]);
	
	caja_body->CreateFixture(&caja_Tapa_fix);

	//restriccion
	//EJE DE MOVIMIENTO TIERRA CAJA
	b2PrismaticJointDef mov2;
	mov2.Initialize(tierra, caja_body, b2Vec2(0.0f, conf.ZeroSet), b2Vec2(0.0f, 1.0f));
	mov2.enableMotor = false;
	b2PrismaticJoint* mov2_joint = (b2PrismaticJoint*)world.CreateJoint(&mov2);
	//cout << "\t- Caja y restricción prismática creadas." << endl;
	
	//preguntar restricciìon prismàtica.	-------------------------------------------------------------------------------
		
// Generación de granos.

	//float cajaInf,cajaSup,cajaIzq,cajaDer;
	float x,y;
	float mg = 0.0;
	int noTotGranos = 0;
	/*cajaInf = 0.05f*caja.altura;
	cajaSup = 0.5f*caja.altura;
	cajaIzq = 0.5f*(-caja.ancho+caja.AnPar)*0.8;
	cajaDer = 0.5f*(caja.ancho-caja.AnPar)*0.8;*/
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
				
				//if (j == 0) cout << "\t- Grano de tipo " << i << " creado con masa " << grain->GetMass() << " kg." << endl;
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
				
				//if (j == 0) cout << "\t- Grano de tipo " << i << " creado con masa " << grain->GetMass() << " kg." << endl;
			}
			noTotGranos++;
		} // Fin loop sobre el número de granos de cada tipo.
	} // Fin loop sobre tipo de granos	
	//cout << "\t- Número total de granos = " << noTotGranos << endl;
	//cout << "\t- Masa total de granos = " << mg << " kg."<< endl;
	//cout << "... sistema creado." << endl;

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
	//cout << "# Inicio de la simulación..." << endl;
	int tamano = int((conf.tMax-conf.tMinReg)/timeStep);
	float array_pcaja [tamano];
	int cont_array = 0;

	while (frec <= conf.fEnd) {
		float w = 2 * b2_pi * frec;
		float t = 0.0;
		float u = 0.0;
		float vu = 0.0;
		//cout << " Frecuencia: " << frec << endl;
		std::ofstream trayFile;
		ffname = conf.preOutFile + "ok" + '.' + conf.outFileExt;
		
		trayFile.open(ffname.c_str());
		
		while (t < conf.tMax) {
			t += timeStep;
			if (t > conf.tMinReg){
				saveT = true;
				array_pcaja [cont_array] = pos_caja.y;
				cont_array = cont_array+1;
				};
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
				
			if (saveT && !(nStep % conf.regStep)){
				if (guardar==true){
					saveFrame(&trayFile, &world, &t, &noTotGranos,&nTO);
					nStep = 0;
				}
				
			}
			
			nStep++;
		}
		trayFile.close();
		frec += conf.fStep;
		cont_array=0;
	}

	//cout << " ... simulación finalizada." << endl;
	
	int modulo = 0;
	bool buscando = true;
	int potencia = 1;
	
	while (buscando = true){
		if (pow(2,potencia)<=tamano){
			modulo=pow(2,potencia);
			potencia=potencia+1;
		}
		if (pow(2,potencia)>tamano){
			break;
		};
	};
	
	//cout << "tamaño de la muestra procesada: " << modulo <<endl;
	//cout << "tamaño de la simulaciòn : " << tamano <<endl;
	
	
	double fft_pos[modulo*2];
	double hann[modulo];
	double pi = 3.14159265;
	float xfft[modulo];
	
	double modfft [modulo];
	
	for(int i=0;i<modulo;i++){
		double a0 = cos(2.0*pi*(i/(modulo-1.0)));
		hann[i]=0.5*(1.0-a0);
		REAL(fft_pos,i)=array_pcaja[i]*hann[i];
		IMAG(fft_pos,i)=0.0;
		a0 = 0.0;
		xfft[i]=i/(modulo*timeStep);
	};
	
	gsl_fft_complex_radix2_dif_backward(fft_pos,1,modulo);
	
	for(int i=0;i<modulo;i++){
		modfft[i]=((REAL(fft_pos,i)*REAL(fft_pos,i))+(IMAG(fft_pos,i)*IMAG(fft_pos,i)));
	};
	
	double max = 0.0;
	int u_max =0;
	for (int i=0;i<modulo;i++){
		if (modfft[i]>max){
			max=modfft[i];
			u_max=i;
		}
	};
	
	double suma_mod = 0.0;
	double suma_pico = 0.0;
	
	for (int i=0;i<modulo;i++){
		suma_mod=suma_mod+modfft[i];
	};
	
	for (int i=-10;i<11;i++){
		suma_pico=suma_pico+modfft[u_max+i];
	};
	
	double THD = 100.0 * sqrt(abs(suma_mod-suma_pico)/suma_pico);
	
	return THD;
};

float* init_population(int n_obs,int n_ind,float poblacion[][10]){
		
		extern GlobalSetup conf;
		Contenedor caja = conf.caja;
		
		extern RandomGenerator get_random;
		double xmin= -caja.ancho/2 + 0.75;
		double xmax= caja.ancho/2 - 0.75;
		double ymin=0.75;
		double ymax=caja.altura - 0.75;
		
		

		for (int i=0;i<n_ind;i++){
			int contador=0;
			for(int j=0;j<(n_obs*2);j++){
				
				if (contador==0){
					
					poblacion[i][j] = get_random.getAB(xmin,xmax);
					contador = 1;
				}
				else if(contador==1){
				
					poblacion[i][j] = get_random.getAB(ymin,ymax);
					contador = 0;
				}	
			};
		};
		return *poblacion;
	};

float* reproduccion(float ind1[],float ind2[],float new_ind[]){

	extern RandomGenerator get_random;
	
	int A = int(get_random.getAB(0.0,8.5));
	int B = int(get_random.getAB(A+1,9.5));
	
	 //los primeros 10 elementos corresponden al primer nuevo individuo y los ùltimos 10 al segundo nuevo individuo
	
	for(int i = 0; i<10;i++){
		if(i<=A or i>B){
			new_ind[i]=ind1[i];
			new_ind[i+10]=ind2[i];
		};
		if(i>A and i<=B){
			new_ind[i]=ind2[i];
			new_ind[i+10]=ind1[i];
		}
	};

	return new_ind;
};
	
int* fitness(float poblacion[][10], int n_ind,int ranking[]){
	//cout << "Simulando población..." <<endl;
	float THDPoblacion[n_ind];
	int repetidos = 0;
	for(int i=0;i<n_ind;i++){
		THDPoblacion[i] = THD(poblacion[i],false);
	};
	
	for(int i=0;i<n_ind;i++){
		int contador = 0;
		int repetidos = 0;
		for (int j=0;j<n_ind;j++){
			if(THDPoblacion[i]>THDPoblacion[j] and i != j){
				contador = contador + 1;
			};
			if(THDPoblacion[i] == THDPoblacion[j] and i > j){
				repetidos = repetidos + 1;
			};
		};
				
		ranking[i]=contador+repetidos+1;
		
	};	
	//cout << "simulación terminada" <<endl;
	return ranking;
};


void saveFrame(std::ofstream *ff, b2World *w, const float* t, const int* nTG,const int* nTO){
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
				
				for(obsfix; n1<*nTO+4; obsfix = obsfix->GetNext()){
					
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
	*(ff) << std::flush;
}

