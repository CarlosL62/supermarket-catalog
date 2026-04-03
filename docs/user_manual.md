# Supermarket Catalog System - Manual de Usuario

## 1. Introducción

Este sistema permite gestionar productos de supermercado mediante diferentes estructuras de datos, facilitando operaciones como inserción, búsqueda, eliminación y visualización.

---

## 2. Ejecución del sistema

Para ejecutar el programa:

```
make run
```

O manualmente:

```
./build/supermarket_catalog
```

---

## 3. Menú principal

Al iniciar el sistema, se muestra un menú con las siguientes opciones:

1. Agregar producto
2. Eliminar producto
3. Buscar por nombre
4. Buscar por código de barras
5. Buscar por categoría
6. Buscar por rango de fechas
7. Listar productos
8. Comparar rendimiento (opcional)
9. Cargar productos desde CSV
10. Generar visualizaciones
0. Salir

---

## 4. Funcionalidades

### 4.1 Agregar producto

Permite ingresar manualmente los datos de un producto:
- Nombre
- Código de barras
- Categoría
- Fecha de caducidad
- Marca
- Precio
- Stock

*No se permiten campos vacíos.*

---

### 4.2 Eliminar producto

Se elimina un producto utilizando su código de barras.

El sistema garantiza que el producto se elimine de todas las estructuras.

---

### 4.3 Buscar por nombre

Busca un producto utilizando su nombre.

Internamente utiliza un Árbol AVL.

---

### 4.4 Buscar por código de barras

Permite encontrar un producto rápidamente mediante su código.

Utiliza una tabla hash para eficiencia.

---

### 4.5 Buscar por categoría

Muestra todos los productos pertenecientes a una categoría.

Utiliza un Árbol B+.

Los resultados se muestran separados para facilitar lectura.

---

### 4.6 Buscar por rango de fechas

Permite obtener productos dentro de un rango de fechas.

Formato de fecha:
```
YYYY-MM-DD
```

Los resultados se muestran ordenados y separados visualmente.

---

### 4.7 Listar productos

Muestra todos los productos ordenados alfabéticamente.

---

### 4.8 Comparar rendimiento

Permite comparar el rendimiento de búsqueda entre distintas estructuras de datos.

El sistema mide el tiempo promedio (en microsegundos) utilizando:
- N consultas por prueba
- M repeticiones de cada prueba

Se evalúan los siguientes casos:
- Búsquedas exitosas
- Búsquedas fallidas
- Búsquedas en extremos (primer y último elemento)

Estructuras comparadas:
- Lista enlazada no ordenada
- Lista enlazada ordenada
- Árbol AVL
- Tabla hash

Para obtener resultados representativos, se recomienda:
- Cargar previamente un archivo CSV (ej. `products_1000.csv`)
- Ejecutar esta opción después de cargar datos

El sistema mostrará los tiempos promedio por estructura y un resumen teórico de complejidad.

---

### 4.9 Cargar productos desde CSV

Permite cargar múltiples productos desde un archivo.

Ejemplo de ruta:

```
../data/products_7.csv
```

También se puede utilizar:

```
../data/products_1000.csv
```

El sistema:
- valida cada fila
- ignora errores
- muestra resumen de carga

---

### 4.10 Generar visualizaciones

Genera archivos de imagen de las estructuras:

- AVL Tree
- B-Tree
- B+ Tree

Los archivos se guardan en la carpeta `/data`.

---

## 5. Mensajes del sistema

El sistema puede mostrar:

- "Producto agregado correctamente"
- "No se encontraron resultados"
- "No se cargaron productos desde el CSV"

---

## 6. Consideraciones

- Las rutas de archivos son relativas al ejecutable
- Se recomienda usar datasets de prueba pequeños antes de usar grandes
- Requiere Graphviz para visualización

---

## 7. Recomendaciones

- Usar `products_7.csv` para pruebas rápidas
- Usar `products_1000.csv` para pruebas completas
- Verificar formato del CSV antes de cargar

---

## 8. Salida del sistema

Después de cada operación:

- El sistema solicitará presionar Enter
- La pantalla se limpiará automáticamente

Esto mejora la experiencia del usuario

---