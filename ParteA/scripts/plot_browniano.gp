# Gnuplot script para graficar resultados del Movimiento Browniano

# Argumentos que se pueden pasar al script:
# DATFILE: Nombre del archivo de datos de entrada
# OUTFILE_BASE: Nombre base para los archivos de imagen de salida (sin extensión)
# TITLE_SUFFIX: Un sufijo para añadir a los títulos de las gráficas (ej. "T=300K, r=1um")

# Valores por defecto si no se pasan argumentos (útil para pruebas directas)
if (!exists("DATFILE")) DATFILE = '../results/browniano.dat'
if (!exists("OUTFILE_BASE")) OUTFILE_BASE = '../results/browniano_plot'
if (!exists("TITLE_SUFFIX")) TITLE_SUFFIX = ''

# --- Gráfica de Trayectoria 2D (X vs Y) ---
set title "Movimiento Browniano - Trayectoria XY ".TITLE_SUFFIX
set xlabel "Posición X (m)"
set ylabel "Posición Y (m)"
set size ratio -1 # Aspect ratio 1:1
set grid
set key top right

set terminal pngcairo size 800,800 enhanced font 'Verdana,10'
set output OUTFILE_BASE.'_trayectoria_xy.png'

# Asumiendo que DATFILE tiene el formato:
# tiempo x1 y1 z1 vx1 vy1 vz1 ...
# Columna 1: tiempo
# Columna 2: x
# Columna 3: y
# Columna 4: z
plot DATFILE using 2:3 with lines title "Trayectoria XY"

# --- Gráfica de Posición X vs Tiempo ---
set title "Movimiento Browniano - Posición X vs Tiempo ".TITLE_SUFFIX
set xlabel "Tiempo (s)"
set ylabel "Posición X (m)"
set size ratio 0.5
set grid
set key top right

set output OUTFILE_BASE.'_x_vs_t.png'
plot DATFILE using 1:2 with lines title "X(t)"

# --- Gráfica de Posición Y vs Tiempo ---
set title "Movimiento Browniano - Posición Y vs Tiempo ".TITLE_SUFFIX
set xlabel "Tiempo (s)"
set ylabel "Posición Y (m)"
# set size ratio 0.5 # ya está seteado
set grid
set key top right

set output OUTFILE_BASE.'_y_vs_t.png'
plot DATFILE using 1:3 with lines title "Y(t)"


# --- Gráfica de Desplazamiento Cuadrático Medio (MSD) vs Tiempo ---
# Esto requiere pre-procesar el archivo DATFILE para calcular el MSD.
# Gnuplot no es ideal para este cálculo si involucra múltiples partículas o promediado.
# Se asume que un script externo (Python, C++, awk) genera un archivo msd.dat
# con formato: tiempo MSD_x MSD_y MSD_z MSD_total

MSD_DATA_FILE = OUTFILE_BASE.'_msd.dat' # Nombre esperado del archivo de MSD

# Comprobar si el archivo MSD existe antes de intentar graficarlo
# Esto es un poco avanzado para un script simple de gnuplot, usualmente el Makefile se encarga.
# Aquí solo se incluye la plantilla de graficación.

set title "Movimiento Browniano - MSD vs Tiempo ".TITLE_SUFFIX
set xlabel "Tiempo (s)"
set ylabel "MSD <(\\Delta r)^2> (m^2)"
set logscale xy # A menudo útil para ver la relación lineal en log-log
set format x "10^{%L}"
set format y "10^{%L}"
set grid
set key bottom right

set output OUTFILE_BASE.'_msd_vs_t.png'

# Ahora sí graficar el MSD si existe el archivo
plot MSD_DATA_FILE using 1:5 with linespoints title "MSD Simulado", \
     x * (6*10) title "Ajuste Teórico (6Dt, D=10)" lw 2 lc rgb "red" dt 2

print "Script 'plot_browniano.gp' ejecutado."
print "Se generaron (o se intentó generar):"
print "- ".OUTFILE_BASE."_trayectoria_xy.png"
print "- ".OUTFILE_BASE."_x_vs_t.png"
print "- ".OUTFILE_BASE."_y_vs_t.png"

unset output
# Para salir si se ejecuta interactivamente:
# pause -1 "Presiona Enter para salir."
