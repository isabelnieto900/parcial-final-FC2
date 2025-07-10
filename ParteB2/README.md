### README.md Actualizado

# Parte B2: Integración de e^(-x^2) por Monte Carlo

Este directorio contiene el código y los artefactos para la Parte B2 del proyecto final de Física Computacional II, enfocada en la aplicación del método de Monte Carlo para la integración numérica.

## Descripción

Se implementa un programa para calcular la integral definida de la función $f(x) = e^{-x^2}$ en el intervalo $[0, 1]$ utilizando el método de Monte Carlo por muestreo simple. Se analiza la convergencia del valor estimado de la integral y su error en función del número de muestras utilizadas.

El valor teórico de esta integral es $\\frac{\\sqrt{\\pi}}{2}\\text{erf}(1) \\approx 0.74682413$.

### Clases Principales:

  * `IntegradorMonteCarlo`: Clase que encapsula la lógica para realizar la integración por Monte Carlo de una función univariable dada.

## Estructura del Directorio `ParteB2`

```
ParteB2/
├── bin/
│   └── integrador_montecarlo    # Ejecutable compilado
├── include/
│   └── IntegradorMonteCarlo.h
├── src/
│   ├── main_montecarlo_integral.cpp
│   └── IntegradorMonteCarlo.cpp
├── scripts/
│   └── plot_integral_error.gp   # Script Gnuplot para visualización
├── results/
│   ├── integral_error_Nmax_1e7.dat # Datos de convergencia (valor y error vs N)
│   └── (*.png)                     # Gráficas generadas
├── documents/
│   ├── integral_mc_informe.tex  # Informe LaTeX específico para esta parte
│   └── (html_integral_mc/ y latex_integral_mc/ de Doxygen)
├── Makefile                       # Makefile para compilar esta parte
├── Doxyfile                       # Configuración de Doxygen para esta parte
└── README.md                      # Este archivo
```

Adicionalmente, el documento `../../documents/montecarlo_fisica_estadistica.tex` (en el directorio `documents` raíz del proyecto) contiene la investigación teórica asociada a esta parte.

-----

## Flujo de Trabajo Recomendado

### 1\. Compilación

Desde el directorio `ParteB2/`, compila el proyecto:

```bash
make
```

Esto generará el ejecutable `bin/integrador_montecarlo`.

  * **Nota**: El `Makefile` utiliza el estándar C++11. El código hace uso de `std::erf`, que es estándar a partir de C++17 pero suele estar disponible en compiladores modernos como una extensión.

Para limpiar los archivos compilados:

```bash
make clean
```

### 2\. Ejecución de la Simulación

La forma recomendada de ejecutar la simulación es usando el `Makefile`:

```bash
make run
```

Este comando se encarga de:

1.  Crear el directorio `results/` si no existe.
2.  Ejecutar la simulación con una semilla predeterminada.
3.  Guardar los datos de salida en `results/integral_error_Nmax_1e7.dat`.

### 3\. Visualización de Resultados

Una vez generados los datos, crea las gráficas con:

```bash
make plot
```

Este comando invoca a Gnuplot con los parámetros correctos y guarda las tres gráficas (`.png`) en el directorio `results/`.

-----

## Opciones Avanzadas

### Ejecución Manual

Si deseas utilizar una semilla de generador de números aleatorios diferente, puedes ejecutar el programa manualmente.
Desde el directorio `ParteB2/`:

```bash
# Asegúrate de que el directorio de resultados exista
mkdir -p results

# Ejecuta el programa con la semilla que elijas
./bin/integrador_montecarlo [semilla]
```

Ejemplo:

```bash
./bin/integrador_montecarlo 42
```

### Documentación

  * **Informe LaTeX:** El informe detallado de esta parte se encuentra en `ParteB2/documents/integral_mc_informe.tex`. Para compilarlo:
    ```bash
    cd ParteB2/documents/
    pdflatex integral_mc_informe.tex
    pdflatex integral_mc_informe.tex
    cd ../..
    ```
  * **Documentación Doxygen:** Para generar la documentación del código:
    Desde el directorio `ParteB2/`:
    ```bash
    doxygen Doxyfile
    ```
    La salida HTML estará en `ParteB2/documents/html_integral_mc/`.
