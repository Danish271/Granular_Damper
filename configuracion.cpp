#include "configuracion.hpp"

void GlobalSetup::load(string inputFile){
    ifstream fin(inputFile.c_str());
    string ident;
    
    while (!fin.eof()) {
    
        fin >> ident;
        if (ident == "outFileExt:") {
            fin >> outFileExt;
        }

    }
};
