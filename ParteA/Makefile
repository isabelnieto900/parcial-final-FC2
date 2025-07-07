# Makefile para la Parte A: Movimiento Browniano

# Compilador y flags
CXX = g++
# CXXFLAGS_BASE se define en el Makefile raíz o aquí si es independiente
CXXFLAGS_BASE = -std=c++11 -Wall -g
LDFLAGS = -lm # Enlazar librería matemática (para std::sqrt, M_PI, etc.)

# Directorios relativos a este Makefile (ParteA/)
SRCDIR = src
INCDIR = include
BINDIR = bin
COMMON_INCDIR = ../common/include # Ruta al include común
COMMON_SRCDIR = ../common/src   # Ruta al src común

# Target ejecutable
TARGET = $(BINDIR)/movimiento_browniano

# Fuentes específicas de ParteA y fuentes comunes
SOURCES_SPECIFIC = $(SRCDIR)/main_browniano.cpp $(SRCDIR)/ParticulaBrowniana.cpp $(SRCDIR)/SimuladorBrowniano.cpp
SOURCES_COMMON = $(COMMON_SRCDIR)/Vector3D.cpp

# Objetos a partir de las fuentes
OBJECTS_SPECIFIC = $(SOURCES_SPECIFIC:.cpp=.o)
OBJECTS_COMMON = $(SOURCES_COMMON:.cpp=.o)
OBJECTS = $(OBJECTS_SPECIFIC) $(OBJECTS_COMMON)

# Flags de compilación específicos para esta parte, incluyendo rutas de include
CXXFLAGS = $(CXXFLAGS_BASE) -I$(INCDIR) -I$(COMMON_INCDIR)

# Regla principal para construir el target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR) # Asegurar que el directorio bin exista
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para compilar archivos .cpp específicos de ParteA a .o
# Los archivos objeto se crearán en el mismo directorio que los fuentes para simplificar.
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h $(COMMON_INCDIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar archivos .cpp comunes a .o
$(COMMON_SRCDIR)/%.o: $(COMMON_SRCDIR)/%.cpp $(COMMON_INCDIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ # CXXFLAGS ya incluye COMMON_INCDIR


# Limpieza
clean:
	rm -f $(SRCDIR)/*.o $(COMMON_SRCDIR)/*.o $(TARGET)
	rm -f $(BINDIR)/* # Si los objetos se pusieran en bin/obj
	# No eliminar resultados ni scripts con 'make clean' por defecto
	# Se puede añadir una regla 'distclean' más agresiva si es necesario

# Para ejecutar (ejemplo)
run: $(TARGET)
	./$(TARGET) 10 0.001 12345 # tiempo_total, dt, semilla

# Para generar gráficas (ejemplo, asumiendo que los datos ya existen)
plot:
	@if [ -f results/browniano.dat ]; then \
		gnuplot scripts/plot_browniano.gp "DATFILE='results/browniano.dat'" "OUTFILE_BASE='results/browniano_sim'"; \
		echo "Gráficas generadas en results/"; \
	else \
		echo "Archivo results/browniano.dat no encontrado. Ejecuta la simulación primero."; \
	fi


.PHONY: all clean run plot
