# Parte A: Simulación del Movimiento Browniano

Este directorio contiene el código y los artefactos para la Parte A del proyecto final de Física Computacional II, enfocada en la simulación del movimiento Browniano.

## Descripción

Se simula el movimiento de una partícula browniana inmersa en un medio viscoso utilizando la ecuación de Langevin. La integración numérica se realiza mediante el método de Euler-Maruyama. El proyecto está estructurado con Programación Orientada a Objetos en C++.

El objetivo es observar la trayectoria característica de una partícula browniana y analizar su comportamiento difusivo.

### Clases Principales:
* `Vector3D`: Clase auxiliar para operaciones con vectores en 3D.
* `ParticulaBrowniana`: Representa la partícula, implementando la lógica de la ecuación de Langevin.
* `SimuladorBrowniano`: Gestiona la simulación, el paso del tiempo y el guardado de datos.

## Estructura del Directorio

La estructura del proyecto sigue las buenas prácticas para la organización de código C++.

```text
ParteA/
|-- bin/
|   `-- movimiento_browniano
|-- include/
|   |-- ParticulaBrowniana.h
|   `-- SimuladorBrowniano.h
|-- src/
|   |-- main_browniano.cpp
|   |-- ParticulaBrowniana.cpp
|   |-- SimuladorBrowniano.cpp
|   `-- Vector3D.cpp
|-- scripts/
|   `-- plot_browniano.gp
|-- results/
|   |-- browniano_sim.dat
|   `-- (gráficas .png)
|-- documents/
|   |-- browniano_informe.tex
|   `-- (html_browniano/ y latex_browniano/)
|-- Makefile
|-- Doxyfile
`-- README.md
```

## Compilación
Desde el directorio `ParteA/`, ejecuta:
```bash
make
```
Esto compilará todo el proyecto y creará el ejecutable `bin/movimiento_browniano`. Para una recompilación limpia:
```bash
make clean && make
```

## Ejecución
Desde el directorio `ParteA/`, usa la regla `run` del Makefile o ejecuta el programa directamente.

**Usando Makefile (recomendado):**
```bash
make run
```
Esto ejecutará la simulación con los parámetros por defecto definidos en el `Makefile`.

**Ejecución directa:**
```bash
./bin/movimiento_browniano <tiempo_total> <dt> <semilla> [nombre_base_archivo]
```
Ejemplo:
```bash
./bin/movimiento_browniano 200.0 0.01 42 mi_simulacion
```
Los datos de salida se guardarán en `results/`.

## Visualización
Después de ejecutar la simulación, genera las gráficas con Gnuplot usando la regla del Makefile:
```bash
make plot
```
Esto buscará el archivo `results/browniano_sim.dat` y creará las gráficas correspondientes en la misma carpeta.

## Documentación
El proyecto cuenta con dos formas de documentación:

* **Informe Científico (LaTeX):** El informe detallado se encuentra en `documents/browniano_informe.tex`. Para compilarlo a PDF, necesitarás una distribución de LaTeX (como TeX Live o MiKTeX) y ejecutar desde `ParteA/documents/`:
    ```bash
    pdflatex browniano_informe.tex
    ```
* **Documentación del Código (Doxygen):** Para generar una página web navegable y un PDF con la documentación de todas las clases y funciones, usa las reglas del Makefile desde el directorio `ParteA/`:
    ```bash
    make doc  # Para generar solo el HTML
    make pdf  # Para generar HTML y el PDF final
    ```
    El HTML estará en `ParteA/documents/html_browniano/index.html` y el PDF en `ParteA/documents/latex_browniano/refman.pdf`.

