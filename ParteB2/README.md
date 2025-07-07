# Parte B2: Integración de e^(-x^2) por Monte Carlo

Este directorio contiene el código y los artefactos para la Parte B2 del proyecto final de Física Computacional II, enfocada en la aplicación del método de Monte Carlo para la integración numérica.

## Descripción

Se implementa un programa para calcular la integral definida de la función $f(x) = e^{-x^2}$ en el intervalo $[0, 1]$ utilizando el método de Monte Carlo por muestreo simple. Se analiza la convergencia del valor estimado de la integral y su error en función del número de muestras utilizadas.

El valor teórico de esta integral es $\frac{\sqrt{\pi}}{2}\text{erf}(1) \approx 0.74682413$.

### Clases Principales:
*   `IntegradorMonteCarlo`: Clase que encapsula la lógica para realizar la integración por Monte Carlo de una función univariable dada.

## Estructura del Directorio `ParteB2`

```
ParteB2/
├── bin/
│   └── integrador_montecarlo   # Ejecutable compilado
├── include/
│   └── IntegradorMonteCarlo.h
├── src/
│   ├── main_montecarlo_integral.cpp
│   └── IntegradorMonteCarlo.cpp
├── scripts/
│   └── plot_integral_error.gp  # Script Gnuplot para visualización
├── results/
│   ├── integral_error_Nmax_1e7.dat # Datos de convergencia (valor y error vs N)
│   └── (*.png)                 # Gráficas generadas
├── documents/
│   ├── integral_mc_informe.tex # Informe LaTeX específico para esta parte
│   └── (html_integral_mc/ y latex_integral_mc/ de Doxygen)
├── Makefile                    # Makefile para compilar esta parte
├── Doxyfile                    # Configuración de Doxygen para esta parte
└── README.md                   # Este archivo
```
Adicionalmente, el documento `../../documents/montecarlo_fisica_estadistica.tex` (en el directorio `documents` raíz del proyecto) contiene la investigación teórica asociada a esta parte, enfocándose en los conceptos generales de MC y esta aplicación.

## Compilación
Desde el directorio `ParteB2/`:
```bash
make
```
Esto generará el ejecutable `bin/integrador_montecarlo`.

Para limpiar los archivos compilados:
```bash
make clean
```

## Ejecución
Desde el directorio `ParteB2/`:
```bash
./bin/integrador_montecarlo [semilla]
```
Argumentos opcionales:
*   `semilla`: Semilla para el generador de números aleatorios (defecto: aleatoria).

Ejemplo:
```bash
./bin/integrador_montecarlo 42
```
El programa calculará la integral para un rango de número de muestras (de $10^1$ a $10^7$) y guardará los resultados (N, Valor Estimado, Error Estimado, Valor Teórico, Diferencia Absoluta) en `ParteB2/results/integral_error_Nmax_1e7.dat`.

## Visualización
Después de ejecutar la simulación, los datos de convergencia se pueden graficar usando Gnuplot:
Desde el directorio `ParteB2/scripts/`:
```bash
gnuplot plot_integral_error.gp
```
Esto utilizará el archivo `../results/integral_error_Nmax_1e7.dat` y generará gráficas del valor de la integral vs. N y del error vs. N en `../results/`.

## Documentación
*   **Informe LaTeX:** El informe detallado de esta parte se encuentra en `ParteB2/documents/integral_mc_informe.tex`. Para compilarlo:
    ```bash
    cd ParteB2/documents/
    pdflatex integral_mc_informe.tex
    pdflatex integral_mc_informe.tex # Segunda vez para referencias
    cd ../..
    ```
*   **Documentación Doxygen:** Para generar la documentación del código de esta parte:
    Desde el directorio `ParteB2/`:
    ```bash
    doxygen Doxyfile
    ```
    La salida HTML estará en `ParteB2/documents/html_integral_mc/`.
```
