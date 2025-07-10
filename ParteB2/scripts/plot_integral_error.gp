# Gnuplot script para graficar resultados de la Integración Monte Carlo de e^(-x^2)

# --- Argumentos y Valores por Defecto ---
# Argumentos que se pueden pasar al script:
# DATFILE: Nombre del archivo de datos de entrada
# OUTFILE_BASE: Nombre base para los archivos de imagen de salida (sin extensión)
# VAL_TEORICO: Valor teórico de la integral para referencia
if (!exists("DATFILE")) DATFILE = 'results/integral_error_Nmax_1e7.dat'
if (!exists("OUTFILE_BASE")) OUTFILE_BASE = 'results/integral_mc_exp_neg_x2'
if (!exists("VAL_TEORICO")) VAL_TEORICO = 0.7468241328124271

set key top right
set grid
set datafile commentschars "#"

# --- Lectura de datos para la línea de referencia N^{-1/2} ---
# Se construye el comando para awk y se ejecuta con system() para que la variable DATFILE se expanda.
first_N_str = system("awk 'NR==2 {print $1}' " . DATFILE)
first_Error_str = system("awk 'NR==2 {print $3}' " . DATFILE)
first_N = real(first_N_str)
first_Error = real(first_Error_str)

# Escalar la referencia para que pase (aproximadamente) por el primer punto de datos
if (exists("first_N") && exists("first_Error") && first_N > 0 && first_Error > 0) {
    FitConstant = first_Error * sqrt(first_N)
} else {
    FitConstant = 0.1 # Valor por defecto si no se puede leer el archivo
}


# --- Gráfica 1: Error Estimado vs. N (log-log) ---
set title "Error de Integración MC (e^{-x^2}) vs. N"
set xlabel "Número de Muestras (N)"
set ylabel "Error Estimado"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"

set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output OUTFILE_BASE . '_error_vs_N.png'

plot DATFILE using 1:3 with linespoints pt 7 title "Error Estimado", \
     FitConstant * (x**(-0.5)) title sprintf("%.2e * N^{-1/2}", FitConstant) lw 2 lc rgb "red" dt 2


# --- Gráfica 2: Valor Estimado vs. N (semilog-x) ---
set title "Valor Estimado de la Integral de e^{-x^2} vs. N"
set xlabel "Número de Muestras (N)"
set ylabel "Valor Estimado de la Integral"
set logscale x
unset logscale y
set format x "10^{%L}"
set format y "%.7f"
set key bottom right

set output OUTFILE_BASE . '_valor_vs_N.png'

plot DATFILE using 1:2 with linespoints pt 7 title "Integral Estimada", \
     VAL_TEORICO title sprintf("Valor Teórico (%.7f)", VAL_TEORICO) lw 2 lc rgb "red" dt 2


# --- Gráfica 3: Diferencia Absoluta vs. N (log-log) ---
set title "Diferencia Absoluta |Estimado - Teórico| vs. N"
set xlabel "Número de Muestras (N)"
set ylabel "|Valor Estimado - Valor Teórico|"
set logscale x
set logscale y
set format x "10^{%L}"
set format y "10^{%L}"
set key top right

set output OUTFILE_BASE . '_diff_abs_vs_N.png'

plot DATFILE using 1:5 with linespoints pt 7 title "Diferencia Absoluta", \
     FitConstant * (x**(-0.5)) title sprintf("%.2e * N^{-1/2} (Ref. Error)", FitConstant) lw 2 lc rgb "red" dt 2


unset output
print "Script de Gnuplot ejecutado correctamente."
