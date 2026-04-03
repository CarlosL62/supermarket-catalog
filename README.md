# 🛒 Supermarket Catalog System

## 📌 Descripción

Este proyecto implementa un sistema de gestión de productos de supermercado desarrollado en C++, utilizando múltiples estructuras de datos implementadas desde cero.

El sistema optimiza operaciones como inserción, búsqueda y eliminación dependiendo del tipo de consulta, haciendo uso de estructuras como listas, árboles y tablas hash.

---

## ⚙️ Estructuras utilizadas

- Lista enlazada no ordenada
- Lista enlazada ordenada
- Tabla hash (búsqueda por código de barras)
- Árbol AVL (búsqueda por nombre)
- Árbol B (búsqueda por rango de fechas)
- Árbol B+ (búsqueda por categoría)

---

## 🚀 Funcionalidades

- Agregar productos manualmente
- Eliminar productos por código de barras
- Buscar productos por:
  - Nombre
  - Código de barras
  - Categoría
  - Rango de fechas
- Listar productos ordenados
- Cargar productos desde archivo CSV
- Generar visualizaciones de árboles con Graphviz

---

## 📦 Requisitos

- CMake 4.x o superior
- Make
- Compilador compatible con C++20 (g++, clang++)
- Sistema Linux, macOS o Windows (WSL o MinGW)

---

## 🔧 Compilación

Desde la raíz del proyecto:

```
make build
```

Esto creará una carpeta `build/` donde se generará el ejecutable.

---

## ▶️ Ejecución

Para compilar y ejecutar directamente:

```
make run
```

O manualmente:

```
./build/supermarket_catalog
```

---

## 🧹 Limpieza del proyecto

Para eliminar archivos generados:

```
make clean
```

Esto eliminará la carpeta `build/` y permitirá una compilación limpia.

---

## 📥 Carga de CSV

Ejemplo de ruta relativa:

```
../data/productsExample.csv
```

El sistema:
- valida filas
- omite errores
- muestra resumen de carga

---

## 📊 Visualización

Se generan automáticamente:

- AVL Tree → `avl_tree.png`
- B-Tree → `b_tree.png`
- B+ Tree → `b_plus_tree.png`

Requiere Graphviz:

```
brew install graphviz   # macOS
sudo apt install graphviz  # Linux
```

---