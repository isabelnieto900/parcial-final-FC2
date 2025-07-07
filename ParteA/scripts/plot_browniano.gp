# Gnuplot script para graficar resultados del Movimiento Browniano

# --- Gráfica de Trayectoria (Ejemplo 2D) ---
set title "Movimiento Browniano - Trayectoria 2D"
set xlabel "Posición X"
set ylabel "Posición Y"
set size ratio -1 # Aspect ratio 1:1 para que los ejes se vean proporcionales
set grid

# Definir el archivo de salida de la imagen
# El Makefile podría pasar esto como variable o definirlo aquí directamente
# Por ejemplo: set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
#              set output 'results/trayectoria_browniano.png'
# Para visualización interactiva, no se necesita set terminal ni set output explícitos
# a menos que se quiera un formato específico.

# Graficar la trayectoria x vs y de la primera partícula
# Asumiendo que results/browniano.dat tiene el formato:
# tiempo x1 y1 z1 vx1 vy1 vz1 ... (si hay más partículas, se añaden más columnas)
# Para una sola partícula: tiempo x y z vx vy vz
# Columna 1: tiempo
# Columna 2: x
# Columna 3: y
# Columna 4: z
# (Ajustar los 'using' según el formato exacto del archivo de datos)

plot '../results/browniano.dat' using 2:3 with lines title "Trayectoria Partícula 1"

# Pausar para ver la gráfica si se ejecuta interactivamente
# pause -1 "Presiona Enter para continuar..."

# --- Gráfica de Desplazamiento Cuadrático Medio (MSD) vs Tiempo ---
# Esto requeriría un pre-procesamiento de los datos de browniano.dat
# o un archivo separado con los valores de MSD calculados.
# Suponiendo que tienes un archivo 'results/msd_browniano.dat' con formato:
# tiempo MSD

# set title "Movimiento Browniano - Desplazamiento Cuadrático Medio"
# set xlabel "Tiempo (s)"
# set ylabel "MSD <(\\Delta r)^2>"
# set grid
# set key top left

# set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
# set output 'results/msd_browniano.png'

# plot '../results/msd_browniano.dat' using 1:2 with linespoints title "MSD Simulado", \
#      2*D*x title sprintf("Ajuste Lineal (2Dt, D=%.2e)", D) # Necesitarías definir D o ajustarlo

# unset output
# pause -1 "Presiona Enter para salir."

# Nota: Para calcular y graficar el MSD, probablemente necesitarás:
# 1. Ejecutar múltiples simulaciones de movimiento Browniano.
# 2. Para cada simulación, calcular (\Delta r(t))^2 = (x(t)-x(0))^2 + (y(t)-y(0))^2 + (z(t)-z(0))^2.
# 3. Promediar (\Delta r(t))^2 sobre todas las simulaciones para obtener MSD(t).
# 4. Guardar estos valores de MSD(t) vs t en un archivo (e.g., msd_browniano.dat).
# Este script de Gnuplot es solo una plantilla para graficar una vez que tengas esos datos.
# El cálculo del MSD usualmente se hace en C++ después de las simulaciones o con un script de post-procesamiento.

print "Script de Gnuplot 'plot_browniano.gp' creado."
print "Descomenta y adapta las secciones según los datos que generes."
print "Para la trayectoria, asegúrate que 'results/browniano.dat' existe y tiene el formato esperado."
print "Para el MSD, necesitarás generar 'results/msd_browniano.dat' con tiempo en la primera columna y MSD en la segunda."
