# Makefile para la Parte B1: Caminata Aleatoria Autoevitante (SAW)

# Compilador y flags
CXX = g++
CXXFLAGS_BASE = -std=c++11 -Wall -g
LDFLAGS = -lm

# Directorios relativos a este Makefile (ParteB1/)
SRCDIR = src
INCDIR = include
BINDIR = bin
# COMMON_INCDIR = ../common/include # Si Vector3D de common fuera necesario
# COMMON_SRCDIR = ../common/src   # Si Vector3D de common fuera necesario

# Target ejecutable
TARGET = $(BINDIR)/saw_simulador

# Fuentes específicas de ParteB1
# Si SAWSimulador.cpp o .h usan Vector3D.h de common, añadir $(COMMON_SRCDIR)/Vector3D.cpp a SOURCES
# y ajustar CXXFLAGS para incluir $(COMMON_INCDIR)
SOURCES_SPECIFIC = $(SRCDIR)/main_saw.cpp $(SRCDIR)/SAWSimulador.cpp
# SOURCES_COMMON = # Descomentar y añadir si Vector3D.cpp es necesario
OBJECTS_SPECIFIC = $(SOURCES_SPECIFIC:.cpp=.o)
# OBJECTS_COMMON = # Descomentar si es necesario
OBJECTS = $(OBJECTS_SPECIFIC) # $(OBJECTS_COMMON)

# Flags de compilación específicos para esta parte
CXXFLAGS = $(CXXFLAGS_BASE) -I$(INCDIR) # -I$(COMMON_INCDIR) si es necesario

# Regla principal para construir el target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para compilar archivos .cpp específicos de ParteB1 a .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h # $(COMMON_INCDIR)/*.h si es necesario
	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Regla para compilar archivos .cpp comunes a .o (si se usan)
# $(COMMON_SRCDIR)/%.o: $(COMMON_SRCDIR)/%.cpp $(COMMON_INCDIR)/*.h
#	$(CXX) $(CXXFLAGS_BASE) -I$(COMMON_INCDIR) -c $< -o $@

# Limpieza
clean:
	rm -f $(SRCDIR)/*.o $(TARGET) # $(COMMON_SRCDIR)/*.o si se compilan aquí
	rm -f $(BINDIR)/*
	# No eliminar resultados ni scripts con 'make clean'

# Para ejecutar (ejemplo con parámetros por defecto)
run: $(TARGET)
	./$(TARGET) 50 10000 123 # N_max_pasos, num_simulaciones, semilla

# Para generar gráficas (ejemplo)
# Esto asume que los datos se generaron con N_max_pasos=50 y num_simulaciones=10000
# y que el script de gnuplot está configurado para esos nombres o los toma como argumentos
plot:
	@echo "Generando gráficas para SAW con N=50..."
	@if [ -f results/saw_resultados_N50_sim10000.dat ] && [ -f results/saw_camino_ejemplo_N50.dat ]; then \
		gnuplot -e "N_PASOS='50'; DATFILE_RESULTADOS='results/saw_resultados_N50_sim10000.dat'; DATFILE_CAMINO='results/saw_camino_ejemplo_N50.dat'; OUTFILE_BASE='results/saw_plot_N50'" scripts/plot_saw.gp; \
		echo "Gráficas generadas en results/"; \
	else \
		echo "Archivos de datos no encontrados para N=50. Ejecuta la simulación primero (ej: make run)."; \
	fi

.PHONY: all clean run plot
