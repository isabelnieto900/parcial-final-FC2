# Gnuplot script para graficar resultados de la Integración Monte Carlo de e^(-x^2)

# Argumentos que se pueden pasar al script:
# DATFILE: Nombre del archivo de datos de entrada
# OUTFILE_BASE: Nombre base para los archivos de imagen de salida (sin extensión)
# VAL_TEORICO: Valor teórico de la integral para referencia

# Valores por defecto
if (!exists("DATFILE")) DATFILE = '../results/integral_error_Nmax_1e7.dat' # Ajustar si el nombre del main cambia
if (!exists("OUTFILE_BASE")) OUTFILE_BASE = '../results/integral_mc_exp_neg_x2'
if (!exists("VAL_TEORICO")) VAL_TEORICO = 0.7468241328124271

set key top right
set grid
set datafile commentschars "#" # Ignorar líneas que comienzan con #

# --- Gráfica del Error Estimado vs Número de Muestras (log-log) ---
set title "Error de Integración MC (e^{-x^2}) vs N"
set xlabel "Número de Muestras (N)"
set ylabel "Error Estimado"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output OUTFILE_BASE.'_error_vs_N.png'

# Columna 1: N_muestras, Columna 3: Error_Estimado
# La pendiente de referencia N^{-1/2} se puede visualizar mejor si ajustamos la constante
# Encontremos el primer valor de error para escalar la referencia
# Esto es un poco complejo en gnuplot puro, se puede hacer un ajuste o simplemente mostrar la pendiente
first_N = `awk 'NR==2 {print $1}' {DATFILE}` # Leer el primer N del archivo de datos
first_Error = `awk 'NR==2 {print $3}' {DATFILE}` # Leer el primer Error del archivo de datos
# Escalar la referencia para que pase (aproximadamente) por el primer punto
if (exists("first_N") && exists("first_Error") && first_N > 0 && first_Error > 0) {
    FitConstant = first_Error * sqrt(first_N)
} else {
    FitConstant = 0.1 # Un valor por defecto si no se puede leer el archivo
}

plot DATFILE using 1:3 with linespoints pt 7 title "Error Estimado", \
     FitConstant * (x**(-0.5)) title sprintf("%.2e * N^{-1/2}", FitConstant) lw 2 lc rgb "red" dt 2

# --- Gráfica del Valor Estimado de la Integral vs Número de Muestras (semilog-x) ---
set title "Valor Estimado de la Integral de e^{-x^2} vs N"
set xlabel "Número de Muestras (N)"
set ylabel "Valor Estimado de la Integral"
set logscale x
unset logscale y # Escala lineal para el valor de la integral
set format x "10^{%L}"
set format y "%.7f" # Más precisión para el valor de la integral
set grid
set key bottom right # Mover la leyenda para no tapar los datos

set output OUTFILE_BASE.'_valor_vs_N.png'

# Columna 1: N_muestras, Columna 2: Valor_Integral_Estimado
plot DATFILE using 1:2 with linespoints pt 7 title "Integral Estimada", \
     VAL_TEORICO title sprintf("Valor Teórico (%.7f)", VAL_TEORICO) lw 2 lc rgb "red" dt 2

# --- Gráfica de la Diferencia Absoluta vs Número de Muestras (log-log) ---
set title "Diferencia Absoluta |Estimado - Teórico| vs N"
set xlabel "Número de Muestras (N)"
set ylabel "|Valor Estimado - Valor Teórico|"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"
set grid
set key top right

set output OUTFILE_BASE.'_diff_abs_vs_N.png'

# Columna 1: N_muestras, Columna 5: Diferencia_Absoluta
plot DATFILE using 1:5 with linespoints pt 7 title "Diferencia Absoluta", \
     FitConstant * (x**(-0.5)) title sprintf("%.2e * N^{-1/2} (Ref. Error)", FitConstant) lw 2 lc rgb "red" dt 2


unset output
print "Script '".GPFILE."' ejecutado."
print "Se generaron (o se intentó generar) gráficas en el directorio '../results/' con base '".OUTFILE_BASE."'"
print "Asegúrate que el archivo de datos '".DATFILE."' existe y tiene el formato correcto."
# pause -1 "Presiona Enter para salir."
