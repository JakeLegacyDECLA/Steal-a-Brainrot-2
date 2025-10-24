# Proyecto: Steal a Brainrot!
## César Daniel Aguilar Kuri - A01712823
Steal a Brainrot! es un juego de Roblox que consiste en coleccionar y robar diferentes personajes catalogados como "Brainrot", este juego tiene un sistema de rarezas (Común, Raro, Épico, Legendario, BrainrotGOD y Secreto) y costos en cuestión a los personajes que existen, por lo que es más valioso un Brainrot Secreto a un Brainrot de Oro. Usando los diferentes temas que hemos aprendido durante el semestre, este proyecto se designa a facilitar la busqueda y catalogo de los Brainrots que el usuario tiene en el juego, mejorando el ordenamiento en su base dependiendo si quiere ordenarlos por nombre, costo o rareza.

## Descripción del avance 1
En este avance se entrega un primer prototipo de consola que:
+ Pide al usuario diferentes brainrots que añadir a vectores como Nombre, Rareza y Costo.
+ Permite consultar arreglos con datos ya ingresados por el usuario.
+ Implementa un algoritmo de ordenamiento: Bubble Sort.

Permite elegir criterios de orden:
+ (Bubble Sort) Costo (Menor a Mayor).
+ (Insertion Sort) Rareza (Menor a Mayor) PENDIENTE.
+ (Merge Sort) Nombre (Alfabético) PENDIENTE.

## Descripción del avance 2
En este avance se entrega un segundo prototipo de consola que (a diferencia del primero):
+ El usuario decide si añade sus propios brainrots o toma un banco de personajes ya establecido (mediante un csv).
+ Permite consultar arreglos con datos ya ingresados por el usuario.
+ Implementa un mejor algoritmo de ordenamiento (basados en el analisis de complejidad) que Bubble Sort: Merge Sort.
+ Implementa una estructura de datos Stack para poder eliminar/consultar el ultimo personaje añadido (el que se queda en top).

### Cambios sobre el primer avance
1. Cambié mi algoritmo de ordenamiento de Bubble Sort (el único que había programado) porque su análisis de complejidad no lo hacia eficiente al hacer tanto recorrimientos, proponiendo a Merge Sort por su complejidad final en el peor, promedio y mejor caso en los ordenamientos de Costo, Rareza y Nombre.
2. Ahora ya se puede elegir una lista de personajes/brainrots ya existentes para no tener que estar metiendo personaje por personaje cuando se quiera probar una función del programa mediante un CSV implementando el uso de archivos externos.
3. 

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ main.cpp  -std=c++11 -o segundo_avance` 

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./segundo_avance` 

## Descripción de las entradas del avance de proyecto
Para el avance de proyecto 2, se necesita ingresar nombres de personajes brainrot (ejemplo: Tralalero Tralala, Orcalero Orcala, Lirili Larila, Cappuchino Assasino, etc.), su rareza (ejemplo: common, rare, epic, legendary, brainrotgod, secret) y costo (varía, puedes poner cualquier numero que NO sea negativo), O en su defecto, elegir una lista de personajes brainrot por default para facilitar la prueba de este mismo programa. Si no se hace esto al inicio del programa, no te dejará hacer Merge Sort ni consultar los arreglos (los datos permitidos se los hará saber el programa). Al ser personajes creados con IA, en un futuro pueden existir muchisimos más personajes que en el proyecto no se agregan (debido a la gran cantidad, por lo que dejamos al usuario agregar los que el tiene). SE RECOMIENDA AGREGAR MÁS DE 2 PERSONAJES, SI SON 2 PERSONAJES NO SE PODRÁ OBSERVAR EL DESEMPEÑO TOTAL DE LOS ALGORITMOS DE BUSQUEDA NI ESTRUCTURAS DE DATOS.

## Descripción de las salidas del avance de proyecto
Al terminar de ejecutar el avance, se puede obtener:
+ Los arreglos sin ordenar.
+ Los arreglos ordenados por su costo (menor a mayor) con Merge Sort.
+ Los arreglos ordenados por su rareza (menor a mayor) con Merge Sort.
+ Los arreglos ordenados por su nombre (alfábetico) con Merge Sort.
+ El último personaje ingresado al arreglo con la estructura Stack (para evitarnos la iteración completa del arreglo).
+ Retirar el último personaje ingresado al arreglo con la estructura Stack.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
Hice un analisis de complejidad correcto indicando que mi Bubble Sort anteriormente usado no fue la mejor opción para eficiencia del programa, por lo que usé Merge Sort con el ordenamiento de los personajes (Merge Sort por Nombre, Rareza y Costo) para asegurar una complejidad de O(n log n) en el mejor, promedio y peor caso, en vez de la anteriormente propuesta de O(n) (Bubble Sort).

Ahora el proyecto reemplaza Bubble Sort por Merge Sort (como lo mencioné anteriormente) en tres criterios:
+ mergeSortPorCosto
+ mergeSortPorNombre
+ mergeSortPorRareza

Complejidad (los tres):
Tiempo: O(n log n) en mejor/promedio/peor caso (divide y vencerás con fusiones lineales por nivel).
Espacio extra: O(n) por los arreglos temporales de merge + O(log n) de pila (domina O(n)).
Estabilidad: Sí. En empates, el orden previo se respeta. Además:
+ Costo: desempato por nombre para determinismo.
+ Rareza: uso de rarityRank + desempate por nombre.
+ Nombre: comparación alfabética (case-insensitive si activas la versión con keys minúscula).

Dónde se ve: en MergeSortCosto.h, MergeSortNombre.h y en MergeSortRareza.h


#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.
Desde el primer avance me di cuenta que realmente estaba haciendo un análisis de manera incorrecta, por lo que en esta ocasión decidí comentar la mayoría de métodos en mis clases para poder demostrar que hice un analisis de complejidad correcto, incluso en la nueva estructura de datos implementada (Stack):

vector<string> nombres, vector<string> rarezas, vector<float> costos
Acceso por índice: O(1)
Inserción al final (push_back): O(1) amortizado
Recorrido/impresión (mostrarArreglos): O(n)
Búsquedas ad-hoc con std::find (validaciones/duplicados): O(n)

StackPersonajes (pila)
push / pop / top / empty / size: O(1)

Uso en menú:
Consultar último: O(1) (top)
Eliminar último: O(1) (pop) + pop_back sincronizado en los vector
Manejo de vacío: no se cae; imprime mensaje y vuelve al menú (continue)
Carga de archivo (cargarDesdeCSV) O(1)
Procesa línea por línea: O(n) registros
Sanitiza rareza (catálogo fijo) y costo (stof, mínimo 0): cada línea O(1) → total O(n)
Soporta nombre con comillas y comas internas
Operaciones compuestas:
Ordenar + mostrar: O(n log n) + O(n)

Captura manual de k registros: O(k) (inserciones + validaciones)

Resultado: la estructura y cada uso tienen su complejidad identificada y justificada en el contexto del programa.

### SICT0302: Toma decisiones
#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
Migré a Merge Sort para costo/nombre/rareza.

Por qué es el adecuado aquí:
+ Peor caso garantizado O(n log n) (consistente con listas grandes cargadas de CSV).

+ Estable, imprescindible si el usuario quiere reordenar por distintos criterios sin perder coherencia.

+ Modular: misma mecánica, cambia solo la comparación (costo, nombre o rarityRank).

Uso correcto en el código:

+ Rango [l..m] (primera mitad) y [m+1..r] (segunda mitad) bien definidos.

+ Vectores temporales por segmento (necesarios para combinar y generar el merge sort).

+ Desempates definidos.

+ Menú muestra antes y después para validar visualmente el resultado.

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.
Decisión actual y justificación de la estructura de datos (Stack) que decidí usar:

+ Arreglos paralelos con vector: simples, cache-friendly y perfectos para la lógica de ordenamiento por múltiples claves.

+ StackPersonajes: resuelve el requerimiento de “consultar/eliminar el último elemento” en O(1), permitiendo continuar aun si el arreglo está vacio (vuelta al menú).

Estado de uso:

Se sincroniza la pila tras carga CSV y tras captura manual, por lo que el top/pop refleja el estado real de la lista.

Validaciones de entrada evitan datos que rompan las precondiciones del ordenamiento.

### SICT0303: Implementa acciones científicas
#### Implementa mecanismos para consultar información de las estructuras correctos.
Consultas disponibles en el menú:

Mostrar arreglos (vista cruda): O(n)

Ordenar por costo / nombre / rareza y mostrar: O(n log n) + O(n) (esta suma se hace debido a los arreglos temporales que se generan para poder completar el merge sort)

Consultar último (Stack): O(1), con manejo de vacío sin detener el programa

Eliminar último (Stack): O(1), con sincronía en los vector base

La interacción es determinista y resistente a entradas inválidas (reintentos controlados).

Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

Lectura de archivos:

Entrada desde CSV con encabezados (Nombre,Rareza,Costo).

Admite nombres con comillas y comas.

Validación de rarezas contra catálogo y sanitización de costo (no negativo, se transforma para lograr eficiencia en el programa).

Complejidad total: O(n) en el número de filas.

Integración directa al menú, con feedback de registros agregados.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.
Como mencioné anteriormente, creé un archivo CSV en excel para no crear una lista de personajes directa en el main.cpp y limpiar codigo que se puede mover externamente.
Lectura de archivos:

Entrada desde CSV con encabezados (Nombre,Rareza,Costo).

Admite nombres con comillas y comas.

Validación de rarezas contra catálogo y sanitización de costo (no negativo).

Complejidad total: O(n) en el número de filas.

Integración directa al menú, con feedback de registros agregados.