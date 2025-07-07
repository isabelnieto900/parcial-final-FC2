# Parte B1: Caminata Aleatoria Autoevitante (SAW)

Este directorio contiene el código y los artefactos para la Parte B1 del proyecto final de Física Computacional II, enfocada en la simulación de Caminatas Aleatorias Autoevitantes (SAW).

## Descripción

Se implementa un algoritmo para generar Caminatas Aleatorias Autoevitantes en una retícula cuadrada 2D. Una SAW es una secuencia de movimientos en una retícula donde ningún sitio puede ser visitado más de una vez.

El objetivo es simular estas caminatas, medir su longitud promedio, el desplazamiento cuadrático medio ($R^2$) de las caminatas que alcanzan una longitud objetivo, y analizar el rendimiento del algoritmo simple de crecimiento.

### Clases Principales:
*   `SAWSimulador`: Gestiona la generación y simulación de una caminata autoevitante. Mantiene el rastro de los sitios visitados y selecciona aleatoriamente los siguientes pasos válidos.
*   `Point2D` (struct): Una estructura simple para representar coordenadas enteras (x,y) en la retícula.

## Estructura del Directorio `ParteB1`

```
ParteB1/
├── bin/
│   └── saw_simulador           # Ejecutable compilado
├── include/
│   └── SAWSimulador.h
├── src/
│   ├── main_saw.cpp
│   └── SAWSimulador.cpp
├── scripts/
│   └── plot_saw.gp             # Script Gnuplot para visualización
├── results/
│   ├── saw_resultados_N*.dat   # Datos de múltiples simulaciones
│   ├── saw_camino_ejemplo_N*.dat # Datos de una trayectoria de ejemplo
│   └── (*.png)                 # Gráficas generadas
├── documents/
│   ├── saw_informe.tex         # Informe LaTeX específico para esta parte
│   └── (html_saw/ y latex_saw/ de Doxygen)
├── Makefile                    # Makefile para compilar esta parte
├── Doxyfile                    # Configuración de Doxygen para esta parte
└── README.md                   # Este archivo
```
Adicionalmente, el documento `../../documents/investigacion_aleatorios.tex` (en el directorio `documents` raíz del proyecto) contiene la investigación teórica asociada a esta parte.

## Compilación
Desde el directorio `ParteB1/`:
```bash
make
```
Esto generará el ejecutable `bin/saw_simulador`.

Para limpiar los archivos compilados:
```bash
make clean
```

## Ejecución
Desde el directorio `ParteB1/`:
```bash
./bin/saw_simulador [N_max_pasos] [num_simulaciones] [semilla]
```
Argumentos opcionales:
*   `N_max_pasos`: Longitud objetivo de las caminatas (defecto: 50).
*   `num_simulaciones`: Número de caminatas a generar para estadísticas (defecto: 10000).
*   `semilla`: Semilla para el generador de números aleatorios (defecto: aleatoria).

Ejemplo:
```bash
./bin/saw_simulador 100 50000 42
```
Los datos de salida se guardarán en `ParteB1/results/`. El nombre del archivo de resultados incluirá `N_max_pasos` y `num_simulaciones`.

## Visualización
Después de ejecutar la simulación, los datos se pueden graficar usando Gnuplot.
Desde el directorio `ParteB1/scripts/`:
```bash
gnuplot -e "N_PASOS='<valor_N_usado>'" plot_saw.gp
```
Reemplaza `<valor_N_usado>` con el `N_max_pasos` que usaste en la simulación. Por ejemplo, si ejecutaste `./bin/saw_simulador 100 ...`:
```bash
gnuplot -e "N_PASOS='100'" plot_saw.gp
```
Esto generará gráficas (ej. trayectoria de ejemplo, histograma de longitudes, $R^2$) en `ParteB1/results/`.

## Documentación
*   **Informe LaTeX:** El informe detallado de esta parte se encuentra en `ParteB1/documents/saw_informe.tex`. Para compilarlo:
    ```bash
    cd ParteB1/documents/
    pdflatex saw_informe.tex
    pdflatex saw_informe.tex # Segunda vez para referencias
    cd ../..
    ```
*   **Documentación Doxygen:** Para generar la documentación del código de esta parte:
    Desde el directorio `ParteB1/`:
    ```bash
    doxygen Doxyfile
    ```
    La salida HTML estará en `ParteB1/documents/html_saw/`.
```
