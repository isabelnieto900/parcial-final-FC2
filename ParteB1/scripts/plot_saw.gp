# Gnuplot script para graficar resultados de la Caminata Aleatoria Autoevitante (SAW)

# Argumentos que se pueden pasar al script:
# DATFILE_RESULTADOS: Nombre del archivo con los resultados de múltiples caminatas
# DATFILE_CAMINO: Nombre del archivo con una trayectoria de ejemplo
# OUTFILE_BASE: Nombre base para los archivos de imagen de salida (sin extensión)
# N_PASOS: El N_max_pasos usado en la simulación (para títulos)

# Valores por defecto
if (!exists("N_PASOS")) N_PASOS = "N" # Placeholder si no se pasa
if (!exists("DATFILE_RESULTADOS")) DATFILE_RESULTADOS = '../results/saw_resultados_N'.N_PASOS.'_sim1000.dat' # Asume un nombre común
if (!exists("DATFILE_CAMINO")) DATFILE_CAMINO = '../results/saw_camino_ejemplo_N'.N_PASOS.'.dat'
if (!exists("OUTFILE_BASE")) OUTFILE_BASE = '../results/saw_plot_N'.N_PASOS

# --- Gráfica de una Trayectoria de Ejemplo (2D) ---
set title "SAW - Trayectoria de Ejemplo (N=".N_PASOS.")"
set xlabel "Posición X"
set ylabel "Posición Y"
set size square # Mismo tamaño para los ejes
set grid
set key off

# Salida a PNG
set terminal pngcairo size 800,800 enhanced font 'Verdana,10'
set output OUTFILE_BASE.'_trayectoria.png'

# Formato esperado en DATFILE_CAMINO: x y (una línea por paso)
plot DATFILE_CAMINO using 1:2 with linespoints pt 7 ps 0.5 title "Camino SAW"

# --- Histograma de Longitudes Reales de Caminatas ---
set title "Histograma de Longitudes Reales de Caminatas (Objetivo N=".N_PASOS.")"
set xlabel "Longitud Real Alcanzada"
set ylabel "Frecuencia"
set style fill solid 0.5
set boxwidth 0.9 relative
set grid
set key off

set output OUTFILE_BASE.'_longitudes_hist.png'

# Asumiendo DATFILE_RESULTADOS: # N_objetivo Longitud_Real R2 Exito(1_o_0)
# Necesitamos calcular el ancho del bin. Si N_PASOS es pequeño, binwidth=1.
# Si N_PASOS es grande, podríamos necesitar agrupar.
# Gnuplot puede hacer histogramas simples.
# bin_width = 1
# bin_column = 2 # Columna de Longitud_Real
# bin_start(x) = floor(x/bin_width)*bin_width
# plot DATFILE_RESULTADOS using (bin_start(column(bin_column))):(1.0) smooth freq with boxes title "Distribución de Longitudes"
# Para un histograma más directo y controlable, Python/Matplotlib es mejor.
# Este es un intento simple:
plot DATFILE_RESULTADOS using 2:(1.0) smooth frequency with boxes title "Frecuencia de Longitudes"


# --- Gráfica de R^2 vs Longitud Real (para caminatas exitosas) ---
set title "<R^2> vs Longitud de Caminata (N=".N_PASOS.")"
set xlabel "Longitud Real de Caminata (N)"
set ylabel "R^2 (Desplazamiento Cuadrático Medio)"
unset logscale x
unset logscale y
set grid
set key top left

set output OUTFILE_BASE.'_R2_vs_N.png'

# DATFILE_RESULTADOS: # N_objetivo Longitud_Real R2 Exito(1_o_0)
# Filtramos para caminatas exitosas (columna 4 == 1)
# Y graficamos R2 (columna 3) vs Longitud_Real (columna 2)
# Esto será un scatter plot si no se promedian los datos antes.
# Para <R^2> vs N real, se necesitaría un script de preprocesamiento.
plot DATFILE_RESULTADOS using ($4==1 ? $2 : 1/0):($4==1 ? $3 : 1/0) with points pt 7 ps 0.5 title "R^2 (caminatas exitosas)"

# Podríamos intentar un ajuste si hay suficientes datos y una tendencia clara.
# Por ejemplo, para SAW, se espera R^2 ~ A * N^(2*nu), con nu ~ 0.588 (para d=3) o nu=0.75 (para d=2)
# f(x) = a * x**(2*0.75) # Para 2D
# fit f(x) DATFILE_RESULTADOS using ($4==1 ? $2 : 1/0):($4==1 ? $3 : 1/0) via a
# plot DATFILE_RESULTADOS using ($4==1 ? $2 : 1/0):($4==1 ? $3 : 1/0) with points title "R^2", \
#      f(x) title sprintf("Ajuste A*N^{1.5} (A=%.2f)", a)


print "Script 'plot_saw.gp' ejecutado."
print "Se generaron (o se intentó generar) gráficas en el directorio '../results/' con base '".OUTFILE_BASE."'"
print "Asegúrate que los archivos de datos existan:"
print "  ".DATFILE_RESULTADOS
print "  ".DATFILE_CAMINO
print "El histograma de longitudes y el ajuste de R^2 son ejemplos básicos y podrían necesitar adaptación o pre-procesamiento de datos."

unset output
# pause -1 "Presiona Enter para salir."
