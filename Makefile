# Makefile Principal del Proyecto Final de Física Computacional II

# --- Variables ---
# Compiladores y herramientas (pueden ser sobrescritos por Makefiles de subdirectorios si es necesario)
CXX = g++
PDFLATEX = pdflatex -interaction=nonstopmode
DOXYGEN = doxygen

# Directorios de las partes
PART_A_DIR = ParteA
PART_B1_DIR = ParteB1
PART_B2_DIR = ParteB2
DOCS_DIR = documents

# --- Targets Principales ---

# Compilar todos los subproyectos
all: all_parts

all_parts: part_a part_b1 part_b2
	@echo "Todas las partes compiladas."

part_a:
	@echo "Compilando Parte A: Movimiento Browniano..."
	$(MAKE) -C $(PART_A_DIR) all

part_b1:
	@echo "Compilando Parte B1: Caminata Aleatoria Autoevitante..."
	$(MAKE) -C $(PART_B1_DIR) all

part_b2:
	@echo "Compilando Parte B2: Integración Monte Carlo..."
	$(MAKE) -C $(PART_B2_DIR) all

# Generar toda la documentación (LaTeX de raíz y Doxygen de cada parte)
docs: docs_pdf_root doxygen_all
	@echo "Documentación generada."

# Generar PDFs de los documentos LaTeX en el directorio raíz 'documents'
DOCS_TEX_ROOT = $(wildcard $(DOCS_DIR)/*.tex)
# Excluir los .tex que están dentro de los subdirectorios de las partes
DOCS_TEX_ROOT_FILTERED = $(filter-out $(DOCS_DIR)/reporte_principal.tex, $(DOCS_TEX_ROOT)) # Excluir reporte principal si se genera de otra forma o incluye los otros
# Podríamos ser más específicos:
DOC_INVESTIGACION_ALEATORIOS = $(DOCS_DIR)/investigacion_aleatorios.pdf
DOC_MONTECARLO_FISICA = $(DOCS_DIR)/montecarlo_fisica_estadistica.pdf
DOC_REPORTE_PRINCIPAL = $(DOCS_DIR)/reporte_principal.pdf


docs_pdf_root: $(DOC_REPORTE_PRINCIPAL) $(DOC_INVESTIGACION_ALEATORIOS) $(DOC_MONTECARLO_FISICA)
	@echo "Documentos LaTeX raíz generados."

$(DOCS_DIR)/%.pdf: $(DOCS_DIR)/%.tex
	$(PDFLATEX) -output-directory=$(DOCS_DIR) $<
	$(PDFLATEX) -output-directory=$(DOCS_DIR) $< # Segunda pasada para referencias

# Generar documentación Doxygen para todas las partes
doxygen_all: doxygen_part_a doxygen_part_b1 doxygen_part_b2
	@echo "Documentación Doxygen generada para todas las partes."

doxygen_part_a:
	@echo "Generando Doxygen para Parte A..."
	(cd $(PART_A_DIR) && $(DOXYGEN) Doxyfile)

doxygen_part_b1:
	@echo "Generando Doxygen para Parte B1..."
	(cd $(PART_B1_DIR) && $(DOXYGEN) Doxyfile)

doxygen_part_b2:
	@echo "Generando Doxygen para Parte B2..."
	(cd $(PART_B2_DIR) && $(DOXYGEN) Doxyfile)


# Limpieza
clean: clean_parts clean_docs_root
	@echo "Limpieza completa del proyecto raíz."

clean_parts:
	@echo "Limpiando Parte A..."
	$(MAKE) -C $(PART_A_DIR) clean
	@echo "Limpiando Parte B1..."
	$(MAKE) -C $(PART_B1_DIR) clean
	@echo "Limpiando Parte B2..."
	$(MAKE) -C $(PART_B2_DIR) clean

clean_docs_root:
	@echo "Limpiando documentos LaTeX raíz y Doxygen de partes..."
	rm -f $(DOCS_DIR)/*.pdf $(DOCS_DIR)/*.log $(DOCS_DIR)/*.aux $(DOCS_DIR)/*.toc $(DOCS_DIR)/*.out $(DOCS_DIR)/*.synctex.gz
	# Doxygen clean se hace dentro de cada parte si es necesario, o aquí:
	rm -rf $(PART_A_DIR)/$(DOCS_DIR)/html_browniano $(PART_A_DIR)/$(DOCS_DIR)/latex_browniano
	rm -rf $(PART_B1_DIR)/$(DOCS_DIR)/html_saw $(PART_B1_DIR)/$(DOCS_DIR)/latex_saw
	rm -rf $(PART_B2_DIR)/$(DOCS_DIR)/html_integral_mc $(PART_B2_DIR)/$(DOCS_DIR)/latex_integral_mc
	@echo "Limpieza de documentación completada."


# Ejecutar todos los programas (ejemplo, puede necesitar ajustes)
run_all:
	@echo "--- Ejecutando Parte A ---"
	$(MAKE) -C $(PART_A_DIR) run
	@echo "--- Ejecutando Parte B1 ---"
	$(MAKE) -C $(PART_B1_DIR) run
	@echo "--- Ejecutando Parte B2 ---"
	$(MAKE) -C $(PART_B2_DIR) run

# Generar todas las gráficas (ejemplo)
plot_all:
	@echo "--- Graficando Parte A ---"
	$(MAKE) -C $(PART_A_DIR) plot
	@echo "--- Graficando Parte B1 ---"
	$(MAKE) -C $(PART_B1_DIR) plot
	@echo "--- Graficando Parte B2 ---"
	$(MAKE) -C $(PART_B2_DIR) plot

# Target para la entrega final (compilar, ejecutar, generar docs y plots)
entrega: all_parts run_all docs plot_all
	@echo "Proceso de 'entrega' completado (compilado, ejecutado, docs y plots generados)."
	@echo "Revisar los directorios 'results' y 'documents' en cada parte."
	@echo "No olvides crear el archivo ZIP/TAR.GZ para la entrega."

.PHONY: all all_parts part_a part_b1 part_b2 docs docs_pdf_root doxygen_all doxygen_part_a doxygen_part_b1 doxygen_part_b2 clean clean_parts clean_docs_root run_all plot_all entrega
