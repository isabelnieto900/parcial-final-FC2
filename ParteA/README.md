# Parte A: Simulación del Movimiento Browniano

Este directorio contiene el código y los artefactos para la Parte A del proyecto final de Física Computacional II, enfocada en la simulación del movimiento Browniano.

## Descripción

Se simula el movimiento de una partícula browniana inmersa en un medio viscoso utilizando la ecuación de Langevin. La integración numérica se realiza mediante el método de Euler-Maruyama.

El objetivo es observar la trayectoria característica de una partícula browniana y analizar su comportamiento difusivo, por ejemplo, calculando el desplazamiento cuadrático medio (MSD).

### Clases Principales:
*   `Vector3D`: Clase auxiliar para operaciones con vectores en 3D (ubicada en `../common/`).
*   `ParticulaBrowniana`: Representa la partícula browniana, implementando la lógica de la ecuación de Langevin.
*   `SimuladorBrowniano`: Gestiona la simulación, incluyendo una o más partículas, el paso del tiempo y el guardado de datos.

## Estructura del Directorio `ParteA`

```
ParteA/
├── bin/
│   └── movimiento_browniano    # Ejecutable compilado
├── include/
│   ├── ParticulaBrowniana.h
│   └── SimuladorBrowniano.h
├── src/
│   ├── main_browniano.cpp
│   ├── ParticulaBrowniana.cpp
│   └── SimuladorBrowniano.cpp
├── scripts/
│   └── plot_browniano.gp       # Script Gnuplot para visualización
├── results/
│   ├── browniano.dat           # Datos de salida de la simulación
│   └── (gráficas .png)         # Gráficas generadas por el script
├── documents/
│   ├── browniano_informe.tex   # Informe LaTeX específico para esta parte
│   └── (html_browniano/ y latex_browniano/ de Doxygen)
├── Makefile                    # Makefile para compilar esta parte
├── Doxyfile                    # Configuración de Doxygen para esta parte
└── README.md                   # Este archivo
```

## Compilación
Desde el directorio `ParteA/`:
```bash
make
```
Esto generará el ejecutable `bin/movimiento_browniano`.

Para limpiar los archivos compilados:
```bash
make clean
```

## Ejecución
Desde el directorio `ParteA/`:
```bash
./bin/movimiento_browniano [tiempo_total] [dt] [semilla] [temperatura_K] [radio_particula_um] [pasos_guardado]
```
Argumentos opcionales:
*   `tiempo_total`: Duración total de la simulación en segundos (defecto: 10.0).
*   `dt`: Paso de tiempo en segundos (defecto: 0.001).
*   `semilla`: Semilla para el generador de números aleatorios (defecto: aleatoria).
*   `temperatura_K`: Temperatura en Kelvin (defecto: 300).
*   `radio_particula_um`: Radio de la partícula en micrómetros (defecto: 1.0).
*   `pasos_guardado`: Frecuencia de guardado de datos (defecto: 100).

Ejemplo:
```bash
./bin/movimiento_browniano 20 0.0005 42
```
Los datos de salida se guardarán en `ParteA/results/`. El nombre del archivo incluirá algunos de los parámetros de simulación.

## Visualización
Después de ejecutar la simulación, los datos se pueden graficar usando Gnuplot:
Desde el directorio `ParteA/scripts/`:
```bash
gnuplot plot_browniano.gp
```
Esto utilizará el archivo de datos más reciente (o uno especificado) en `../results/` y generará gráficas (ej. trayectoria, X(t), Y(t)) en `../results/`.
Es posible que necesites editar `plot_browniano.gp` para apuntar al archivo de datos correcto si cambiaste los parámetros de salida o el nombre.

## Documentación
*   **Informe LaTeX:** El informe detallado de esta parte se encuentra en `ParteA/documents/browniano_informe.tex`. Para compilarlo:
    ```bash
    cd ParteA/documents/
    pdflatex browniano_informe.tex
    pdflatex browniano_informe.tex # Segunda vez para referencias
    cd ../..
    ```
*   **Documentación Doxygen:** Para generar la documentación del código de esta parte:
    Desde el directorio `ParteA/`:
    ```bash
    doxygen Doxyfile
    ```
    La salida HTML estará en `ParteA/documents/html_browniano/`.
```
