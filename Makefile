# Makefile para el Proyecto Final de Física Computacional II

# Compilador y flags
CXX = g++
CXXFLAGS_COMMON = -std=c++11 -Wall
LDFLAGS = -lm # Enlazar librería matemática si es necesario (ej. para sqrt, exp en Vector3D o mains)

# Directorios Raíz
ROOTDIR = .
COMMON_INCDIR = $(ROOTDIR)/common/include
COMMON_SRCDIR = $(ROOTDIR)/common/src
DOCDIR = $(ROOTDIR)/documents

# --- Parte A: Movimiento Browniano ---
PART_A_DIR = $(ROOTDIR)/ParteA
PART_A_SRCDIR = $(PART_A_DIR)/src
PART_A_INCDIR = $(PART_A_DIR)/include
PART_A_BINDIR = $(PART_A_DIR)/bin
PART_A_RESULTSDIR = $(PART_A_DIR)/results
TARGET_A = $(PART_A_BINDIR)/movimiento_browniano
SOURCES_A_SPECIFIC = $(PART_A_SRCDIR)/main_browniano.cpp $(PART_A_SRCDIR)/ParticulaBrowniana.cpp $(PART_A_SRCDIR)/SimuladorBrowniano.cpp
SOURCES_COMMON = $(COMMON_SRCDIR)/Vector3D.cpp
OBJECTS_A = $(SOURCES_A_SPECIFIC:.cpp=.o) $(SOURCES_COMMON:.cpp=.o)
CXXFLAGS_A = $(CXXFLAGS_COMMON) -I$(COMMON_INCDIR) -I$(PART_A_INCDIR)

# --- Parte B1: Caminata Aleatoria Autoevitante (SAW) ---
PART_B1_DIR = $(ROOTDIR)/ParteB1
PART_B1_SRCDIR = $(PART_B1_DIR)/src
PART_B1_INCDIR = $(PART_B1_DIR)/include
PART_B1_BINDIR = $(PART_B1_DIR)/bin
PART_B1_RESULTSDIR = $(PART_B1_DIR)/results
TARGET_B1 = $(PART_B1_BINDIR)/saw_simulador
SOURCES_B1_SPECIFIC = $(PART_B1_SRCDIR)/main_saw.cpp $(PART_B1_SRCDIR)/SAWSimulador.cpp
# Vector3D.cpp de common podría no ser necesario si Point2D es suficiente y no se usa Vector3D.h en SAWSimulador.h
# Si SAWSimulador.h usa Vector3D.h (aunque la plantilla usa Point2D), se debe añadir COMMON_SRCDIR)/Vector3D.cpp
# Por ahora, asumimos que no lo necesita directamente o que Point2D es suficiente.
OBJECTS_B1 = $(SOURCES_B1_SPECIFIC:.cpp=.o)
CXXFLAGS_B1 = $(CXXFLAGS_COMMON) -I$(COMMON_INCDIR) -I$(PART_B1_INCDIR)

# --- Parte B2: Integración Monte Carlo ---
PART_B2_DIR = $(ROOTDIR)/ParteB2
PART_B2_SRCDIR = $(PART_B2_DIR)/src
PART_B2_INCDIR = $(PART_B2_DIR)/include
PART_B2_BINDIR = $(PART_B2_DIR)/bin
PART_B2_RESULTSDIR = $(PART_B2_DIR)/results
TARGET_B2 = $(PART_B2_BINDIR)/integrador_montecarlo
SOURCES_B2_SPECIFIC = $(PART_B2_SRCDIR)/main_montecarlo_integral.cpp $(PART_B2_SRCDIR)/IntegradorMonteCarlo.cpp
OBJECTS_B2 = $(SOURCES_B2_SPECIFIC:.cpp=.o)
CXXFLAGS_B2 = $(CXXFLAGS_COMMON) -I$(COMMON_INCDIR) -I$(PART_B2_INCDIR)

# Regla principal: compilar todos los ejecutables
all: $(TARGET_A) $(TARGET_B1) $(TARGET_B2)

# Reglas para compilar cada parte
$(TARGET_A): $(OBJECTS_A)
	mkdir -p $(PART_A_BINDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(TARGET_B1): $(OBJECTS_B1)
	mkdir -p $(PART_B1_BINDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(TARGET_B2): $(OBJECTS_B2)
	mkdir -p $(PART_B2_BINDIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Reglas genéricas para compilar archivos .cpp a .o
# Para fuentes específicas de cada parte
$(PART_A_SRCDIR)/%.o: $(PART_A_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS_A) -c $< -o $@

$(PART_B1_SRCDIR)/%.o: $(PART_B1_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS_B1) -c $< -o $@

$(PART_B2_SRCDIR)/%.o: $(PART_B2_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS_B2) -c $< -o $@

# Para fuentes comunes
$(COMMON_SRCDIR)/%.o: $(COMMON_SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS_COMMON) -I$(COMMON_INCDIR) -c $< -o $@


# --- Documentación ---
DOC_BROWNIANO = $(DOCDIR)/browniano.pdf
DOC_ALEATORIOS = $(DOCDIR)/investigacion_aleatorios.pdf
DOC_MONTECARLO_FISICA = $(DOCDIR)/montecarlo_fisica_estadistica.pdf
DOC_PRINCIPAL = $(DOCDIR)/reporte_principal.pdf

PDFLATEX = pdflatex -interaction=nonstopmode -output-directory=$(DOCDIR)

# Generar todos los PDFs de LaTeX
docs_pdf: $(DOC_PRINCIPAL) $(DOC_BROWNIANO) $(DOC_ALEATORIOS) $(DOC_MONTECARLO_FISICA)

$(DOCDIR)/%.pdf: $(DOCDIR)/%.tex
	$(PDFLATEX) $<
	$(PDFLATEX) $< # Compilar dos veces para referencias

# Generar documentación Doxygen
doxygen_doc: Doxyfile
	doxygen Doxyfile

docs: doxygen_doc docs_pdf

# --- Limpieza ---
clean:
	rm -f $(PART_A_SRCDIR)/*.o $(PART_A_BINDIR)/*
	rm -f $(PART_B1_SRCDIR)/*.o $(PART_B1_BINDIR)/*
	rm -f $(PART_B2_SRCDIR)/*.o $(PART_B2_BINDIR)/*
	rm -f $(COMMON_SRCDIR)/*.o
	rm -f $(PART_A_RESULTSDIR)/*.dat $(PART_A_RESULTSDIR)/*.png
	rm -f $(PART_B1_RESULTSDIR)/*.dat $(PART_B1_RESULTSDIR)/*.png
	rm -f $(PART_B2_RESULTSDIR)/*.dat $(PART_B2_RESULTSDIR)/*.png
	rm -f $(DOCDIR)/*.pdf $(DOCDIR)/*.log $(DOCDIR)/*.aux $(DOCDIR)/*.toc $(DOCDIR)/*.out $(DOCDIR)/*.synctex.gz
	rm -rf $(DOCDIR)/html $(DOCDIR)/latex # Directorios de Doxygen

# Target para generar todos los informes y la documentación
informe: docs
	@echo "Informes y documentación generados."

.PHONY: all clean docs docs_pdf doxygen_doc informe
