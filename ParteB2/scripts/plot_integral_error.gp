# Gnuplot script para graficar resultados de la Integración Monte Carlo

# --- Gráfica del Error Estimado vs Número de Muestras ---
set title "Error de Integración Monte Carlo vs N"
set xlabel "Número de Muestras (N)"
set ylabel "Error Estimado"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"
set grid
set key top right

# Archivo de datos generado por main_montecarlo_integral.cpp
# Formato esperado: # N_muestras Valor_Integral Error_Estimado
DATA_FILE = '../results/integral_error.dat'

# Salida a PNG
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output '../results/integral_mc_error_vs_N.png'

# Graficar Error_Estimado (columna 3) vs N_muestras (columna 1)
plot DATA_FILE using 1:3 with linespoints title "Error Estimado", \
     (x**(-0.5)) * (sqrt(0.1)) title "Referencia (N^{-1/2})" lw 2 lc rgb "red" dt 2
     # El factor sqrt(0.1) para la referencia es arbitrario, ajustar para que se alinee visualmente
     # La idea es mostrar la tendencia N^{-1/2}

# --- Gráfica del Valor Estimado de la Integral vs Número de Muestras ---
set title "Valor Estimado de la Integral (e^{-x^2}) vs N"
set xlabel "Número de Muestras (N)"
set ylabel "Valor Estimado de la Integral"
set logscale x
unset logscale y # Usualmente se quiere ver la convergencia en escala lineal para el valor
set format x "10^{%L}"
set format y "%.6f"
set grid
set key right

# Valor teórico aproximado
VALOR_TEORICO = 0.74682413

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output '../results/integral_mc_valor_vs_N.png'

plot DATA_FILE using 1:2 with linespoints title "Integral Estimada", \
     VALOR_TEORICO title "Valor Teórico" lw 2 lc rgb "red" dt 2

unset output
print "Script 'plot_integral_error.gp' creado."
print "Asegúrate que '../results/integral_error.dat' existe y tiene el formato: N_muestras Valor_Integral Error_Estimado"
# pause -1 "Presiona Enter para salir."
