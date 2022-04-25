# \file  Makefile
# \brief Makefile
# \author Manuel Carlevaro [IFLYSIB]
# \versión 0.1 
# \date 2018.12.17
# \note Ver: http://makepp.sourceforge.net/1.19/makepp_tutorial.html


CXX = g++
BOX2D = /home/erik/Documentos/ProyectoBox2d/
LIBPATH = -L$(BOX2D)/lib
INCLUDES = -I$(BOX2D)/include -Iusr/local/include -Iusr/local/lib
LIBS = -lbox2d -lm -lgsl
CXXFLAGS = -O3 $(INCLUDES)
LDFLAGS = -O3 -Wall $(LIBPATH) -static $(LIBS) -fexceptions

OBJS = damper.o configuracion.o 

damper: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) 

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ 
 
