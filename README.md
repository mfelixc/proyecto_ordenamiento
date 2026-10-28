# proyecto_ordenamiento

Comparación empírica de dos algoritmos de ordenamiento en C++: **inserción** (método directo, O(n²)) y **quicksort** (método logarítmico, partición de Lomuto con pivote central, O(n log n) esperado). Proyecto de la Unidad 01 (evaluación de producto).

**Estudiante:** [Mauricio Alex Felix Camacho] (mfelixc@unjbg.edu.pe) — Universidad Nacional Jorge Basadre Grohmann, Tacna, Perú.

## Algoritmos seleccionados
- Ordenamiento por inserción (versión canónica, estable, iterativo).
- Quicksort (Lomuto, pivote central, recursivo, inestable).

## Requisitos
- g++ con soporte C++11 (probado con g++ 15.2.0, MSYS2).
- Opcional para gráficas: Python 3 con `matplotlib` (`src/analisis.py`), o abrir `graficar.html` en un navegador y cargar `results/resultados.csv` (no requiere instalar nada).

## Cómo reproducir
```bash
# 1. compilar
g++ -O2 -std=c++11 -Iinclude src/experimento.cpp -o experimento
g++ -O2 -std=c++11 -Iinclude src/estabilidad.cpp -o estabilidad

# 2. correr el experimento (commit actual, archivo de salida, repeticiones)
./experimento $(git rev-parse --short HEAD) results/resultados.csv 30

# 3. estabilidad y análisis estadístico/gráficas
./estabilidad
python src/analisis.py        # o abrir graficar.html y cargar el csv
```
Para que el `commit_hash` del csv sea real, haz commit del código antes del paso 2.

## Entorno experimental
| Componente | Valor |
|---|---|
| Equipo | Laptop HP |
| CPU | AMD Ryzen 7 7445HS, 3.20 GHz base, 6 núcleos / 12 hilos, caché L3 16 MB |
| RAM | 8 GB (7.23 GB utilizables) |
| Almacenamiento | SSD |
| GPU | NVIDIA RTX 3050 6 GB y Radeon 740M (no utilizadas) |
| SO | Windows 11 Home Single Language 26H2 (compilación 26300.9711), 64 bits |
| Compilador | g++ 15.2.0 (Rev13, MSYS2) |
| Flags | `-O2 -std=c++11 -Iinclude` |
| Energía | Equipo conectado a la corriente |
| Temporizador | `std::chrono::steady_clock`, sin E/S de disco |

## Tamaños, patrones y semillas
- Tamaños: n ∈ {1 000, 10 000, 100 000}.
- Patrones: aleatorio, ascendente, descendente, casi ordenado (5 % permutado) y duplicados (15 valores únicos).
- 30 repeticiones por condición (algoritmo × patrón × tamaño) = 900 ejecuciones.
- Semilla de la repetición r: `2024 + r` (2025 a 2054), registrada en el csv. Ambos algoritmos reciben copias idénticas de la misma entrada.

## Archivos
- `include/comunes.h`: patrones, generador con semilla y funciones auxiliares.
- `src/experimento.cpp`: algoritmos instrumentados y experimento (genera el csv).
- `src/estabilidad.cpp`: comprobación práctica de estabilidad.
- `src/analisis.py`: tabla de estadística descriptiva y gráficas (opcional).
- `src/avance.cpp`, `src/Quicksort.cpp`, `src/Incersion.cpp`: avances y demos iniciales.
- `results/resultados.csv`: datos crudos (`algoritmo, n, patron, repeticion, tiempo_ms, comparaciones, intercambios, profundidad_recursion, semilla, commit_hash`).
- `results/resumen_estadistico.csv`: media, mediana, desviación estándar, mínimo y máximo del tiempo.
- `results/entorno.txt`: hardware, SO y compilador.
- `docs/articulo.docx` y `docs/articulo.pdf`: manuscrito. `docs/figuras/`: gráficas.

## Principales resultados
Tiempo medio (ms) con n = 100 000:

| Patrón | Inserción | Quicksort |
|---|---|---|
| Aleatorio | 1645.0 | 4.3 |
| Ascendente | 0.09 | 1.1 |
| Descendente | 3335.4 | 1.4 |
| Casi ordenado | 108.6 | 2.2 |
| Duplicados | 1573.4 | 220.9 |

- Inserción crece ≈ n² (pendiente log-log ≈ 2.0) salvo en entrada ascendente (≈ 0.9–1.0, lineal), donde le gana a quicksort.
- Quicksort crece ≈ n log n (pendiente ≈ 1.03–1.13), pero con pocos valores únicos la partición de Lomuto (`<=`) se degrada hacia cuadrático (pendiente ≈ 1.89; profundidad media de recursión ≈ 6 807 con n = 100 000).
- Estabilidad: inserción es estable; quicksort no (ver salida de `./estabilidad`).

## Video de demostración
Enlace a YouTube:

## Commit de la versión final
Identificador: 
