#!/usr/bin/env python3
# filepath: scripts/calculate_msd.py
"""
Script para calcular el Desplazamiento Cuadrático Medio (MSD) 
a partir de los datos de simulación del movimiento browniano.
"""

import numpy as np
import sys
import os

def calculate_msd(data_file, output_file):
    """
    Calcula el MSD a partir de un archivo de datos de trayectoria.
    
    Formato esperado del archivo de entrada:
    tiempo x y z vx vy vz energia_cinetica
    """
    try:
        # Leer los datos
        data = np.loadtxt(data_file)
        
        if data.size == 0:
            print(f"Error: El archivo {data_file} está vacío.")
            return False
            
        # Extraer columnas
        tiempo = data[:, 0]
        x = data[:, 1]
        y = data[:, 2]
        z = data[:, 3]
        
        n_points = len(tiempo)
        
        # Inicializar arrays para MSD
        msd_x = np.zeros(n_points)
        msd_y = np.zeros(n_points)
        msd_z = np.zeros(n_points)
        msd_total = np.zeros(n_points)
        
        # Calcular MSD para cada tiempo
        # MSD(t) = <[r(t) - r(0)]^2>
        # Para una sola partícula, es simplemente [r(t) - r(0)]^2
        
        x0, y0, z0 = x[0], y[0], z[0]  # Posición inicial
        
        for i in range(n_points):
            dx = x[i] - x0
            dy = y[i] - y0
            dz = z[i] - z0
            
            msd_x[i] = dx**2
            msd_y[i] = dy**2
            msd_z[i] = dz**2
            msd_total[i] = dx**2 + dy**2 + dz**2
        
        # Guardar resultados
        header = "# Tiempo\tMSD_x\tMSD_y\tMSD_z\tMSD_total\n"
        header += "# Col 1: tiempo, Col 2: MSD_x, Col 3: MSD_y, Col 4: MSD_z, Col 5: MSD_total\n"
        
        with open(output_file, 'w') as f:
            f.write(header)
            for i in range(n_points):
                f.write(f"{tiempo[i]:.6f}\t{msd_x[i]:.6f}\t{msd_y[i]:.6f}\t{msd_z[i]:.6f}\t{msd_total[i]:.6f}\n")
        
        print(f"MSD calculado y guardado en: {output_file}")
        
        # Mostrar estadísticas básicas
        print(f"Puntos procesados: {n_points}")
        print(f"Tiempo final: {tiempo[-1]:.2f}")
        print(f"MSD final (total): {msd_total[-1]:.6f}")
        
        # Estimar coeficiente de difusión (pendiente de MSD vs tiempo)
        if n_points > 10:
            # Usar solo la segunda mitad de los datos para el ajuste
            idx_start = n_points // 2
            t_fit = tiempo[idx_start:]
            msd_fit = msd_total[idx_start:]
            
            # Ajuste lineal: MSD = 6*D*t (para 3D)
            coeff = np.polyfit(t_fit, msd_fit, 1)
            pendiente = coeff[0]
            D_estimado = pendiente / 6.0  # Para 3D
            
            print(f"Pendiente estimada: {pendiente:.6f}")
            print(f"Coeficiente de difusión estimado (3D): D = {D_estimado:.6f}")
            print(f"Valor teórico esperado: D = kT/gamma = 1.0/0.1 = 10.0")
        
        return True
        
    except Exception as e:
        print(f"Error al procesar {data_file}: {e}")
        return False

def main():
    if len(sys.argv) < 2:
        print("Uso: python3 calculate_msd.py <archivo_datos> [archivo_salida]")
        print("Ejemplo: python3 calculate_msd.py results/browniano_sim.dat")
        sys.exit(1)
    
    data_file = sys.argv[1]
    
    if len(sys.argv) >= 3:
        output_file = sys.argv[2]
    else:
        # Generar nombre automático
        base_name = os.path.splitext(data_file)[0]
        if 'browniano_sim' in base_name:
            output_file = base_name.replace('browniano_sim', 'browniano_sim_plot') + '_msd.dat'
        else:
            output_file = base_name + '_msd.dat'
    
    if not os.path.exists(data_file):
        print(f"Error: El archivo {data_file} no existe.")
        sys.exit(1)
    
    print(f"Calculando MSD de: {data_file}")
    print(f"Archivo de salida: {output_file}")
    
    success = calculate_msd(data_file, output_file)
    
    if success:
        print("¡MSD calculado exitosamente!")
    else:
        print("Error al calcular el MSD.")
        sys.exit(1)

if __name__ == "__main__":
    main()