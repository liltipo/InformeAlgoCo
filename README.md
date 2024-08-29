# Informe de Algoritmos y Complejidad

Este repositorio incluye tres carpetas principales: `sortingAlgorithms`, `matrixMultiplication` y `benchmarks`.

## `sortingAlgorithms`

La carpeta `sortingAlgorithms` contiene dos subcarpetas:

1. **`codes`**: 
   - Esta subcarpeta incluye el código de 5 algoritmos de ordenamiento: 
     - `bubbleSort`
     - `mergeSort`
     - `quickSort`
     - `stlSort` (implementación de la función `.sort()` de la STL)
     - `bogoSort` (agregado como una implementación adicional)
   
2. **`dataset`**:
   - Contiene dos conjuntos de datos para pruebas de rendimiento con tamaños de 10,000 y 1,000,000 números ordenados en:
     - Orden ascendente
     - Orden descendente
     - Orden aleatorio
   - Además, incluye un conjunto especial de datos de 12 elementos para `bogoSort`.

### Makefile
En la carpeta `sortingAlgorithms` también se encuentra un `Makefile` que proporciona los siguientes comandos:

- **`make`**: Compila todos los algoritmos de ordenamiento.
- **`make run`**: Ejecuta los algoritmos de ordenamiento utilizando los conjuntos de datos de 1,000,000 de números (por defecto).
- **`make runBogo`**: Ejecuta `bogoSort` con su conjunto especial de 12 elementos.
- **`make clean`**: Elimina todos los archivos creados.

## `matrixMultiplication`

La carpeta `matrixMultiplication` contiene 5 archivos principales:

1. `naiveMM`
2. `cacheOptimizedMM`
3. `strassenMM`
4. `strassenMM2`
5. `strassenMM3`

### Makefile
En la carpeta `matrixMultiplication`, se incluye un `Makefile` que proporciona los siguientes comandos:

- **`make`**: Compila todos los algoritmos de multiplicación de matrices.
- **`make run`**: 
    - Ejecuta los archivos con matrices de tamaño:
    - 2048x2048, 1024x1024, y 512x512 para `naiveMM`, `cacheOptimizedMM`, y `strassenMM`.
    - 512x512 para `strassenMM2` y `strassenMM3`.
- **`make clean`**: Elimina todos los archivos creados.

**Nota:** No se incluye un dataset predefinido para la multiplicación de matrices, ya que cada archivo genera dos matrices del tamaño especificado en la entrada del `Makefile`.

La carpeta `benchmarks`, contiene ocho imágenes:
- Una para la multiplicación de matrices.
- Seis imágenes para los algoritmos de ordenamiento, distribuidas de la siguiente manera:
  - Dos para orden ascendente (1,000,000 y 10,000 elementos).
  - Dos para orden descendente (mismos tamaños).
  - Dos para orden aleatorio (mismos tamaños).
- Una para `bogoSort` y su dataset.
