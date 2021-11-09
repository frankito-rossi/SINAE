#Make de la tarea 1, correspondiente al lab0 de Prog4 2021. Este modulo se encargará de construir, compilar, borrar, restablecer; los diferentes archivos de pricipal con respecto a sus modulos dentro de sus correspondientes datatypes y clases, generandose los .o corresponiodentes para la construccion de dichos objetos
all: principal

# Objetivos que no son archivos.
.PHONY: all clean rebuild


# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj


MODULOS = fecha grafoPtosVacunacion lista listaPersonas persona sinae vacunas


PUNTOH = fecha grafoPtosVacunacion lista listaPersonas persona sinae vacunas
# lista de archivos, con directorio y extensión
HS   = $(PUNTOH:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.cpp)
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

LIB=lab4.a

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -g -I$(HDIR)


$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# cada .o depende de su .cpp
# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

$(LIB):$(ODIR)/$(PRINCIPAL).o $(OS)
	ar -qc $@ $^

biblioteca:$(LIB)

# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE): $(ODIR)/$(PRINCIPAL).o $(OS)
	$(CC) $(CCFLAGS) $^ -o $@
	
clean:
	rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS) $(LIB)
	
	
rebuild:
	make clean
	make
