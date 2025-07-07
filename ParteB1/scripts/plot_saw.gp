# Gnuplot script para graficar resultados de la Caminata Aleatoria Autoevitante (SAW)

# --- Gráfica de una Trayectoria de Ejemplo (2D) ---
set title "SAW - Trayectoria de Ejemplo"
set xlabel "Posición X"
set ylabel "Posición Y"
set size ratio -1 # Aspect ratio 1:1
set grid

# Archivo de datos generado por SAWSimulador::GuardarCamino()
# Formato esperado: x y (una línea por paso)
DATA_FILE_CAMINO = '../results/saw_camino_ejemplo.dat' # Ajustar si el main lo guarda con otro nombre

# Salida a PNG
set terminal pngcairo size 800,800 enhanced font 'Verdana,10'
set output '../results/saw_trayectoria_ejemplo.png'

plot DATA_FILE_CAMINO using 1:2 with linespoints title "Camino SAW"

# --- Gráfica de <R^2> vs N y Error vs N ---
# Esto requiere que el archivo 'saw_resultados.dat' contenga datos procesados.
# El main_saw.cpp actual guarda: # N_pasos_intentados Longitud_Real_Camino R^2 Exito(1_o_0)
# Para graficar <R^2> vs N, necesitaríamos promediar R^2 para caminatas de la misma longitud N exitosa.
# O, si N_max_pasos es fijo y solo consideramos las exitosas:
# Podríamos graficar la distribución de R^2, o si variamos N_max_pasos en el main, graficar <R^2> vs N_max_pasos.

# Asumamos que queremos graficar R^2 de cada caminata exitosa vs su longitud real.
# O, si se hacen múltiples corridas para distintos N_max_pasos y se promedia:
# DATA_FILE_ESTADISTICAS = '../results/saw_estadisticas_vs_N.dat'
# Formato esperado para DATA_FILE_ESTADISTICAS:
# N_pasos <R^2> Error_R^2 Fraccion_Exitosas

set title "<R^2> vs Longitud de la Caminata (N)"
set xlabel "Longitud de la Caminata (N)"
set ylabel "<R^2>"
set grid
set key top left

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output '../results/saw_R2_vs_N.png'

# Ejemplo si 'saw_resultados.dat' tuviera N (longitud real) y R^2 para caminatas exitosas
# Esto es más un scatter plot de las R^2 individuales si no se promedian antes.
# Para un gráfico de <R^2> vs N, se necesitaría un script de preprocesamiento (Python/awk)
# para calcular los promedios desde 'saw_resultados.dat'.

# Si 'saw_resultados.dat' tiene (col 2: Longitud_Real, col 3: R^2, col 4: Exito)
# Podríamos intentar filtrar y ajustar, aunque es más complejo en gnuplot directamente.
# plot '../results/saw_resultados.dat' using ($4==1 ? $2 : 1/0):($4==1 ? $3 : 1/0) with points title "R^2 para caminatas exitosas"
# Lo anterior mostraría puntos individuales. Para un promedio, se necesita pre-procesamiento.

print "Script 'plot_saw.gp' creado."
print "Para la trayectoria, asegúrate que '../results/saw_camino_ejemplo.dat' existe."
print "Para <R^2> vs N, necesitarás procesar 'saw_resultados.dat' para obtener promedios."
print "Una alternativa es graficar R^2 vs N para cada corrida exitosa (scatter plot)."

unset output
# pause -1 "Presiona Enter para salir."
