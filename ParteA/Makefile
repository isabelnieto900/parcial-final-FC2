# Makefile para la Parte A: Movimiento Browniano

# Compilador y flags
CXX = g++
CXXFLAGS_BASE = -std=c++17 -Wall -g
LDFLAGS = -lm -lstdc++fs

# Directorios
SRCDIR = src
INCDIR = include
BINDIR = bin
DOCDIR = documents
LATEX_DIR = $(DOCDIR)/latex_browniano
RESULTS_DIR = results

# Target ejecutable
TARGET = $(BINDIR)/movimiento_browniano

# Fuentes y cabeceras
# Se asume que todos los .cpp están en src y todos los .h en include
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Flags de compilación finales
CXXFLAGS = $(CXXFLAGS_BASE) -I$(INCDIR)

# Regla principal
all: $(TARGET)

# Regla para enlazar el ejecutable final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo ""
	@echo "----------------------------------------------------"
	@echo "¡Compilación exitosa! Ejecutable en: $(TARGET)"
	@echo "-> 'make run' para ejecutar la simulación."
	@echo "-> 'make plot' para generar las gráficas."
	@echo "-> 'make doc' para generar la documentación HTML."
	@echo "-> 'make pdf' para generar el PDF de la documentación."
	@echo "----------------------------------------------------"

# Reglas de compilación de objetos
# Esta regla genérica funciona para todos los .cpp en SRCDIR
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- REGLAS DE DOCUMENTACIÓN MEJORADAS ---

# Genera la documentación HTML y los fuentes LaTeX
doc:
	@echo "Generando documentación con Doxygen..."
	doxygen Doxyfile
	@echo "Documentación HTML generada. Abre '$(DOCDIR)/html_browniano/index.html'."

# Genera el PDF a partir de los fuentes LaTeX
pdf: doc
	@echo "Compilando la documentación LaTeX a PDF..."
	$(MAKE) -C $(LATEX_DIR)
	@echo "PDF generado en $(LATEX_DIR)/refman.pdf"

# Limpieza
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(SRCDIR)/*.o $(TARGET)
	rm -rf $(BINDIR)
	@echo "Limpiando archivos de resultados..."
	rm -f $(RESULTS_DIR)/*

# Limpieza profunda, incluyendo la documentación generada
distclean: clean
	@echo "Limpiando toda la documentación generada..."
	rm -rf $(DOCDIR)/html_browniano $(DOCDIR)/latex_browniano
	rm -rf $(DOCDIR)/
# Ejecutar la simulación
run: $(TARGET)
	./$(TARGET) 100.0 0.01 12345

# Generar gráficas
plot:
	@if [ -f results/browniano_sim.dat ]; then \
		gnuplot -e "DATFILE='results/browniano_sim.dat'" -e "OUTFILE_BASE='results/browniano_sim_plot'" scripts/plot_browniano.gp; \
		echo "Gráficas generadas en el directorio results/"; \
	else \
		echo "Archivo results/browniano_sim.dat no encontrado. Ejecuta 'make run' primero."; \
	fi

.PHONY: all clean distclean run plot doc pdf

