# Makefile para la Parte B1: Caminata Aleatoria Autoevitante (SAW)
# Versión mejorada y robusta

# ---------------------------------------------------------------------------
# 1. CONFIGURACIÓN DEL COMPILADOR Y DIRECTORIOS
# ---------------------------------------------------------------------------
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -I$(INCDIR)
LDFLAGS = -lm

# Directorios del proyecto
SRCDIR = src
INCDIR = include
BINDIR = bin
RESULTSDIR = results
SCRIPTSDIR = scripts
DOCDIR = documents
LATEX_DIR = $(DOCDIR)/latex_saw

# ---------------------------------------------------------------------------
# 2. ARCHIVOS FUENTE Y OBJETIVO
# ---------------------------------------------------------------------------
# Target ejecutable
TARGET = $(BINDIR)/saw_simulador

# Detección automática de todos los archivos .cpp en el directorio src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# Generación automática de los nombres de los archivos objeto (.o)
OBJECTS = $(SOURCES:.cpp=.o)

# ---------------------------------------------------------------------------
# 3. PARÁMETROS DE SIMULACIÓN POR DEFECTO
# ---------------------------------------------------------------------------
# Se pueden sobreescribir desde la línea de comandos, ej: make run N_STEPS=100
N_STEPS ?= 80
N_SIMS  ?= 20000
# Genera una semilla basada en la hora actual si no se especifica una
SEED    ?= $(shell date +%s)

# ===========================================================================
# REGLAS PRINCIPALES
# ===========================================================================

# La regla por defecto que se ejecuta con 'make'
all: $(TARGET)

# Regla para construir el ejecutable final a partir de los archivos objeto
$(TARGET): $(OBJECTS)
	@echo "-> Enlazando para crear el ejecutable..."
	# MEJORA: Crea los directorios bin y results si no existen
	@mkdir -p $(BINDIR) $(RESULTSDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "¡Compilación completada! Ejecutable en: $(TARGET)"

# Regla genérica para compilar cualquier archivo .cpp de src a un .o
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "-> Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===========================================================================
# REGLAS DE UTILIDAD
# ===========================================================================

# Regla para ejecutar la simulación
# Uso: make run [N_STEPS=...] [N_SIMS=...] [SEED=...]
run: $(TARGET)
	@echo "-> Ejecutando simulación con N=$(N_STEPS), Sims=$(N_SIMS), Seed=$(SEED)..."
	./$(TARGET) $(N_STEPS) $(N_SIMS) $(SEED)
doc:
	@echo "Generando documentación con Doxygen..."
	doxygen Doxyfile
	@echo "Documentación HTML generada. Abre '$(DOCDIR)/html_browniano/index.html'."

# Genera el PDF a partir de los fuentes LaTeX
pdf: doc
	@echo "Compilando la documentación LaTeX a PDF..."
	$(MAKE) -C $(LATEX_DIR)
	@echo "PDF generado en $(LATEX_DIR)/refman.pdf"


# Regla para generar las gráficas con Gnuplot
# Asume que los datos ya fueron generados por 'make run'
plot:
	@echo "-> Generando gráficas para N=$(N_STEPS) y Sims=$(N_SIMS)..."
	@# Verifica si el archivo de datos principal existe antes de intentar graficar
	@if [ -f "$(RESULTSDIR)/saw_resultados_N$(N_STEPS)_sim$(N_SIMS).dat" ]; then \
		gnuplot -e "N_PASOS='$(N_STEPS)'; NUM_SIMS='$(N_SIMS)'" $(SCRIPTSDIR)/plot_saw.gp; \
		echo "Gráficas generadas en $(RESULTSDIR)/"; \
	else \
		echo "Error: Archivo de datos no encontrado."; \
		echo "Ejecuta 'make run N_STEPS=$(N_STEPS) N_SIMS=$(N_SIMS)' primero."; \
	fi

# Regla para limpiar solo los archivos generados por la compilación
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(SRCDIR)/*.o $(TARGET)
	rm -rf $(BINDIR)
	@echo "Limpiando archivos de resultados..."
	rm -f $(RESULTSDIR)/*

# Regla para una limpieza total, borrando también los resultados
distclean: clean
	@echo "Limpiando toda la documentación generada..."
	rm -rf $(DOCDIR)/html_saw $(DOCDIR)/latex_saw
	rm -f $(DOCDIR)/*.pdf $(DOCDIR)/*.log $(DOCDIR)/*.aux $(DOCDIR)/*.toc $(DOCDIR)/*.out
# Declaración de reglas que no son archivos para evitar conflictos
.PHONY: all run plot clean distclean doc pdf

