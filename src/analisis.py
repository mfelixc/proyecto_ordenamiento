# analisis.py  

import csv
import math
import os
import statistics
from collections import defaultdict

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

RUTA_CSV = "results/resultados.csv"
RUTA_RESUMEN = "results/resumen_estadistico.csv"
CARPETA_FIG = "docs/figuras"

PATRONES = ["aleatorio", "ascendente", "descendente", "casi_ordenado", "duplicados"]
ALGORITMOS = ["insercion", "quicksort"]
COLORES = {"insercion": "tab:red", "quicksort": "tab:blue"}

os.makedirs(CARPETA_FIG, exist_ok=True)


datos = defaultdict(list)
with open(RUTA_CSV) as f:
    for fila in csv.DictReader(f):
        clave = (fila["algoritmo"], fila["patron"], int(fila["n"]))
        datos[clave].append(fila)

tamanios = sorted({k[2] for k in datos})


def valores(clave, columna):
    return [float(x[columna]) for x in datos[clave]]


with open(RUTA_RESUMEN, "w", newline="") as f:
    w = csv.writer(f)
    w.writerow(["algoritmo", "patron", "n", "repeticiones",
                "media_ms", "mediana_ms", "desv_ms", "min_ms", "max_ms",
                "comparaciones_media", "intercambios_media", "profundidad_max_media"])
    for alg in ALGORITMOS:
        for pat in PATRONES:
            for n in tamanios:
                t = valores((alg, pat, n), "tiempo_ms")
                w.writerow([
                    alg, pat, n, len(t),
                    round(statistics.mean(t), 4), round(statistics.median(t), 4),
                    round(statistics.stdev(t), 4), round(min(t), 4), round(max(t), 4),
                    round(statistics.mean(valores((alg, pat, n), "comparaciones")), 1),
                    round(statistics.mean(valores((alg, pat, n), "intercambios")), 1),
                    round(statistics.mean(valores((alg, pat, n), "profundidad_recursion")), 1),
                ])
print("Escrito", RUTA_RESUMEN)

fig, ejes = plt.subplots(2, 3, figsize=(13, 7))
for i, pat in enumerate(PATRONES):
    ax = ejes[i // 3][i % 3]
    for alg in ALGORITMOS:
        medias = [statistics.mean(valores((alg, pat, n), "tiempo_ms")) for n in tamanios]
        ax.plot(tamanios, medias, marker="o", color=COLORES[alg], label=alg)
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_title(pat)
    ax.set_xlabel("n")
    ax.set_ylabel("tiempo medio (ms)")
    ax.grid(True, which="both", alpha=0.3)
    ax.legend()
ejes[1][2].axis("off")
plt.tight_layout()
plt.savefig(CARPETA_FIG + "/n_vs_tiempo.png", dpi=200)
plt.close()

n_max = tamanios[-1]
fig, ejes = plt.subplots(1, 2, figsize=(12, 4.5))
for ax, alg in zip(ejes, ALGORITMOS):
    cajas = [valores((alg, pat, n_max), "tiempo_ms") for pat in PATRONES]
    ax.boxplot(cajas)
    ax.set_xticks(range(1, len(PATRONES) + 1))
    ax.set_xticklabels(PATRONES)   
    ax.set_title(alg + " (n = " + str(n_max) + ")")
    ax.set_ylabel("tiempo (ms)")
    ax.tick_params(axis="x", rotation=20)
    ax.grid(True, axis="y", alpha=0.3)
plt.tight_layout()
plt.savefig(CARPETA_FIG + "/boxplot_tiempo.png", dpi=200)
plt.close()

fig, ejes = plt.subplots(1, 2, figsize=(12, 4.5), sharey=True)
for ax, alg in zip(ejes, ALGORITMOS):
    for pat in PATRONES:
        m = [statistics.mean(valores((alg, pat, n), "comparaciones")) for n in tamanios]
        ax.plot(tamanios, m, marker="o", label=pat)
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_title(alg)
    ax.set_xlabel("n")
    ax.set_ylabel("comparaciones (media)")
    ax.grid(True, which="both", alpha=0.3)
    ax.legend(fontsize=8)
plt.tight_layout()
plt.savefig(CARPETA_FIG + "/n_vs_comparaciones.png", dpi=200)
plt.close()

print("\nPendiente log-log del tiempo (entre n minimo y n maximo):")
for alg in ALGORITMOS:
    for pat in PATRONES:
        t0 = statistics.mean(valores((alg, pat, tamanios[0]), "tiempo_ms"))
        t1 = statistics.mean(valores((alg, pat, tamanios[-1]), "tiempo_ms"))
        pend = (math.log(t1) - math.log(t0)) / (math.log(tamanios[-1]) - math.log(tamanios[0]))
        print("  %-10s %-14s %.2f" % (alg, pat, pend))
