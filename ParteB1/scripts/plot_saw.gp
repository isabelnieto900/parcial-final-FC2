# Script de Gnuplot para visualizar los resultados de la simulación SAW
# Versión final corregida para ser compatible con el ejecutable C++

# --- Parámetros ---
# Se pasan desde la línea de comandos con 'make plot', ej: make plot N_STEPS=80
if (!exists("N_PASOS")) N_PASOS = "80"
if (!exists("NUM_SIMS")) NUM_SIMS = "20000"

# --- Nombres de archivos ---
DATFILE_RESULTADOS = sprintf("results/saw_resultados_N%s_sim%s.dat", N_PASOS, NUM_SIMS)
DATFILE_CAMINO = sprintf("results/saw_camino_ejemplo_N%s.dat", N_PASOS)
OUTFILE_BASE = sprintf("results/saw_plot_N%s", N_PASOS)

# --- Configuración general ---
set terminal pngcairo enhanced font "Helvetica,12" size 1024,768
set grid

# ===================================================================
# Gráfico 1: Trayectoria de una caminata de ejemplo
# ===================================================================
set output OUTFILE_BASE . "_trayectoria.png"
set title sprintf("Ejemplo de Caminata Aleatoria Autoevitante (N=%s)", N_PASOS)
set xlabel "Coordenada X"
set ylabel "Coordenada Y"
set size square # Mantener la proporción de aspecto 1:1 para ver la forma real

# Graficar el camino, destacando el inicio y el final
plot DATFILE_CAMINO using 1:2 with lines lw 2 lc "gray" title "Camino", \
     '' using 1:2:(0) every ::0::0 with points pt 7 ps 2 lc "green" title "Inicio (0,0)", \
     '' using 1:2:(0) every ::-1::-1 with points pt 7 ps 2 lc "red" title "Final"

# ===================================================================
# Gráfico 2: Histograma de longitudes de las caminatas
# ===================================================================
set output OUTFILE_BASE . "_histograma_longitudes.png"
set title sprintf("Histograma de Longitudes Finales (N_{max}=%s, %s simulaciones)", N_PASOS, NUM_SIMS)
set xlabel "Longitud de la Caminata"
set ylabel "Frecuencia"
set style fill solid 0.6 border -1
set boxwidth 0.9 relative
unset size # Volver a la proporción por defecto

# --- Extraer estadísticas del encabezado del archivo para mostrarlas en el gráfico ---
# CORRECCIÓN FINAL: Se ajustaron los números de columna ($8, $9, $7) para que apunten a los valores numéricos correctos.
longitud_promedio_str = system(sprintf("awk '/# Longitud promedio de todas las caminatas:/{print $8}' %s", DATFILE_RESULTADOS))
caminos_exitosos_str = system(sprintf("awk '/# Numero de caminatas exitosas/{print $9}' %s", DATFILE_RESULTADOS))
R2_promedio_str = system(sprintf("awk '/# R.2 promedio para caminatas exitosas:/{print $7}' %s", DATFILE_RESULTADOS))

# Convertir los strings leídos a números para poder formatearlos
longitud_promedio = real(longitud_promedio_str)
R2_promedio = real(R2_promedio_str)

# Colocar las etiquetas con las estadísticas en el gráfico
set label 1 sprintf("Longitud promedio: %.2f", longitud_promedio) at graph 0.65, graph 0.9 font ",10"
set label 2 sprintf("Caminatas exitosas (N=%s): %s", N_PASOS, caminos_exitosos_str) at graph 0.65, graph 0.85 font ",10"
set label 3 sprintf("<R^2> para exitosas: %.2f", R2_promedio) at graph 0.65, graph 0.80 font ",10"

# --- Graficar el histograma ---
binwidth=1
bin(x,width)=width*floor(x/width)
plot DATFILE_RESULTADOS using (bin($1,binwidth)):(1.0) smooth freq with boxes lc "blue" title "Distribución de Longitudes"

# Limpiar las etiquetas para futuros gráficos
unset label 1
unset label 2
unset label 3

# --- Mensajes finales en la consola ---
print "--- Gráficas generadas ---"
print "Trayectoria: ", OUTFILE_BASE . "_trayectoria.png"
print "Histograma:  ", OUTFILE_BASE . "_histograma_longitudes.png"
print "--------------------------"
print "¡Proceso completado!"

