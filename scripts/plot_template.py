import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def plot_data(data_file, output_image_file, title="Gráfico de Datos", xlabel="X", ylabel="Y"):
    """
    Función de plantilla para graficar datos desde un archivo.
    Asume un archivo de datos con columnas separadas por espacios.
    La primera columna es X, la segunda es Y.
    """
    try:
        # Intentar cargar con numpy (simple para archivos solo numéricos)
        # data = np.loadtxt(data_file)
        # x = data[:, 0]
        # y = data[:, 1]

        # Usar pandas para más flexibilidad (maneja cabeceras comentadas, diferentes delimitadores)
        # Asumimos que los comentarios empiezan con '#'
        data_pd = pd.read_csv(data_file, delim_whitespace=True, comment='#', header=None)

        if data_pd.shape[1] < 2:
            print(f"Error: El archivo de datos {data_file} tiene menos de dos columnas.")
            return

        x = data_pd.iloc[:, 0]
        y = data_pd.iloc[:, 1]

        # Crear la gráfica
        plt.figure(figsize=(10, 6))
        plt.plot(x, y, marker='o', linestyle='-', label='Datos')

        # Añadir títulos y etiquetas
        plt.title(title)
        plt.xlabel(xlabel)
        plt::ylabel(ylabel)
        plt.legend()
        plt.grid(True)

        # Guardar la figura
        plt.savefig(output_image_file)
        print(f"Gráfica guardada en {output_image_file}")
        # plt.show() # Descomentar si quieres mostrar la gráfica interactivamente

    except Exception as e:
        print(f"Error al procesar o graficar el archivo {data_file}: {e}")

if __name__ == '__main__':
    # Ejemplo de uso (esto no se ejecutará cuando se llame desde el Makefile usualmente)
    # Crear un archivo de datos de ejemplo si no existe
    if not os.path.exists("../results/example_data.dat"):
        with open("../results/example_data.dat", "w") as f:
            f.write("# Ejemplo de datos\n")
            f.write("0 0\n")
            f.write("1 1\n")
            f.write("2 4\n")
            f.write("3 9\n")
            f.write("4 16\n")

    # plot_data("../results/example_data.dat", "../results/example_plot.png",
    #           title="Ejemplo de Gráfica", xlabel="Tiempo (s)", ylabel="Posición (m)")

    print("Script de plantilla de graficación. Modifícalo para tus necesidades específicas.")
    print("Por ejemplo, para el movimiento Browniano, podrías querer graficar x vs y, o MSD vs t.")
    print("Para SAW, x vs y de la caminata, o R^2 vs N.")
    print("Para la integral, error vs N_muestras.")
