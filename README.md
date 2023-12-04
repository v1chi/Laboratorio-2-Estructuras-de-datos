# Laboratorio-2-Estructuras-de-datos

## Diseño del Juego

-Se utiliza una matriz bidimensional para representar el tablero del juego y se emplea la estructura Nodo para construir un árbol de posibles movimientos durante el uso del algoritmo minimax.

-El código incluye funciones para imprimir el tablero, realizar movimientos de los jugadores, verificar victorias, y manejar la lógica de la IA con el algoritmo minimax.


## Minimax y Decisiones de Diseño

-La clase Minimax implementa el algoritmo minimax para que la IA elija la mejor jugada posible, evaluando las posiciones del tablero y buscando la mejor estrategia. Se implementa con diferentes niveles de dificultad (Fácil, Medio, Difícil).

-La dificultad de la IA se ajusta según la profundidad del árbol de búsqueda en el algoritmo minimax. Esto permite variar la capacidad de la IA para tomar decisiones estratégicas.

-Optimización de Código: El código incluye optimizaciones para evitar calcular nodos que no contribuyen a la decisión final, reduciendo así el costo computacional del algoritmo minimax.


## Resultados de Pruebas

-Comparación de Dificultades: Se proporcionan tres niveles de dificultad (Fácil, Medio, Difícil) para la IA. La elección de la dificultad afecta la profundidad de búsqueda del algoritmo minimax, lo que se traduce en una mayor o menor capacidad estratégica.

-Guardado y Carga de Partidas: Los jugadores tienen la opción de guardar y cargar partidas. Esto proporciona flexibilidad y permite a los jugadores continuar partidas en otro momento.


##Minimax con PODA vs sin PODA
La elección entre Minimax con o sin poda depende de las necesidades específicas del juego y del entorno de ejecución. Aquí hay algunas consideraciones generales:

-Para Juegos Sencillos o Tableros Pequeños: Minimax sin poda puede ser suficiente y es más fácil de implementar.

-Para Juegos Complejos o Tableros Grandes: Minimax con poda es preferible para mejorar la eficiencia y reducir los tiempos de respuesta.

-En casos intermedios, donde la complejidad computacional es un factor importante pero la eficiencia también es necesaria, es mejor implementar el PODA
