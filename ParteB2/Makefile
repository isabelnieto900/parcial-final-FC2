# Makefile para la Parte B2: Integración Monte Carlo

# Compilador y flags
CXX = g++
CXXFLAGS_BASE = -std=c++11 -Wall -g
LDFLAGS = -lm # Para std::exp, std::sqrt, std::erf (este último puede necesitar -std=c++17 o superior en algunos compiladores)

# Directorios relativos a este Makefile (ParteB2/)
SRCDIR = src
INCDIR = include
BINDIR = bin
# COMMON_INCDIR = ../common/include # No se usa Vector3D aquí directamente
# COMMON_SRCDIR = ../common/src

# Target ejecutable
TARGET = $(BINDIR)/integrador_montecarlo

# Fuentes específicas de ParteB2
SOURCES_SPECIFIC = $(SRCDIR)/main_montecarlo_integral.cpp $(SRCDIR)/IntegradorMonteCarlo.cpp
OBJECTS_SPECIFIC = $(SOURCES_SPECIFIC:.cpp=.o)
OBJECTS = $(OBJECTS_SPECIFIC)

# Flags de compilación específicos para esta parte
# Si IntegradorMonteCarlo.h o main usaran Vector3D.h, se añadiría -I$(COMMON_INCDIR)
CXXFLAGS = $(CXXFLAGS_BASE) -I$(INCDIR)

# Regla principal para construir el target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR) # Asegurar que el directorio bin exista
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para compilar archivos .cpp específicos de ParteB2 a .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpieza
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
	rm -f $(BINDIR)/*
	# No eliminar resultados ni scripts con 'make clean'

# Para ejecutar (ejemplo con semilla por defecto)
run: $(TARGET)
	./$(TARGET) 12345 # semilla

# Para generar gráficas (ejemplo)
# Asume que los datos se generaron con el nombre de archivo por defecto del main.
plot:
	@echo "Generando gráficas para Integración Monte Carlo..."
	@if [ -f results/integral_error_Nmax_1e7.dat ]; then \
		gnuplot -e "DATFILE='results/integral_error_Nmax_1e7.dat'; OUTFILE_BASE='results/integral_mc_exp_neg_x2'" scripts/plot_integral_error.gp; \
		echo "Gráficas generadas en results/"; \
	else \
		echo "Archivo results/integral_error_Nmax_1e7.dat no encontrado. Ejecuta la simulación primero (ej: make run)."; \
	fi

.PHONY: all clean run plot
