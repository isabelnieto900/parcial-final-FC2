# Makefile para la Parte B2: Integración Monte Carlo

# Compilador y flags
CXX = g++
CXXFLAGS_BASE = -std=c++11 -Wall -g
LDFLAGS = -lm # Para std::exp, std::sqrt, std::erf

# Directorios relativos a este Makefile (ParteB2/)
SRCDIR = src
INCDIR = include
BINDIR = bin
DOCDIR = documents
LATEX_DIR = $(DOCDIR)/latex_integral_mc

# Target ejecutable
TARGET = $(BINDIR)/integrador_montecarlo

# Fuentes y objetos
SOURCES_SPECIFIC = $(SRCDIR)/main_montecarlo_integral.cpp $(SRCDIR)/IntegradorMonteCarlo.cpp
OBJECTS_SPECIFIC = $(SOURCES_SPECIFIC:.cpp=.o)
OBJECTS = $(OBJECTS_SPECIFIC)

# Flags de compilación
CXXFLAGS = $(CXXFLAGS_BASE) -I$(INCDIR)

# --- Reglas Principales ---

# Regla por defecto para construir el ejecutable
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regla para compilar archivos .cpp a .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Reglas de Ejecución y Visualización ---

run: $(TARGET)
	@echo "Ejecutando la simulación Monte Carlo..."
	@mkdir -p results
	./$(TARGET) 12345

plot:
	@echo "Generando gráficas para Integración Monte Carlo..."
	@if [ -f results/integral_error_Nmax_1e7.dat ]; then \
		gnuplot -e "DATFILE='results/integral_error_Nmax_1e7.dat'; OUTFILE_BASE='results/integral_mc_exp_neg_x2'" scripts/plot_integral_error.gp; \
		echo "Gráficas generadas en results/"; \
	else \
		echo "Archivo results/integral_error_Nmax_1e7.dat no encontrado. Ejecuta la simulación primero (ej: make run)."; \
	fi

# --- Reglas de Documentación ---

# Genera la documentación (HTML y PDF)
doc:
	@echo "Generando archivos de documentación con Doxygen..."
	@doxygen Doxyfile
	@echo "Compilando el PDF de la documentación LaTeX..."
	@# Usamos $(MAKE) para invocar la compilación dentro del subdirectorio
	@$(MAKE) -C $(LATEX_DIR)
	@echo "--------------------------------------------------------"
	@echo "Proceso de documentación finalizado."
	@echo "HTML en: $(DOCDIR)/html_integral_mc/index.html"
	@echo "PDF en:  $(LATEX_DIR)/refman.pdf"
	@echo "--------------------------------------------------------"

# --- Reglas de Limpieza ---

clean:
	@echo "Limpiando archivos de compilación..."
	rm -f $(SRCDIR)/*.o
	rm -rf $(BINDIR)

clean-doc:
	@echo "Limpiando documentación generada por Doxygen..."
	rm -rf $(DOCDIR)/html_integral_mc
	rm -rf $(LATEX_DIR)

clean-all: clean clean-doc
	@echo "Limpieza completa finalizada."


.PHONY: all clean run plot doc clean-doc clean-all

