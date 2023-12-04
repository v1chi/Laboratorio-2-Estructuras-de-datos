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


## Minimax con PODA vs sin PODA

Minimax sin Poda:

Ventajas:

--La implementación es más clara y sencilla sin la lógica de poda.

-- Brinda la seguridad de encontrar la mejor jugada posible al explorar todo el espacio de búsqueda.

Desventajas:

--Es costoso computacionalmente, especialmente en juegos complejos con un alto factor de ramificación y profundidad.

--Puede conducir a tiempos de respuesta lentos.

Minimax con Poda Alfa-Beta:

Ventajas:

--Reduce significativamente la cantidad de nodos explorados, mejorando el rendimiento computacional.

--Permite tomar decisiones más rápidas, crucial para juegos complejos.

Desventajas:

--La implementación requiere manejar la lógica de poda, lo que puede aumentar la complejidad del código.

--En situaciones extremas, la poda podría pasar por alto la mejor jugada si se realiza demasiado pronto.

Eficiencia del Algoritmo: La eficiencia del algoritmo es crítica en juegos estratégicos como Conecta 4. La poda Alfa-Beta destaca al reducir significativamente el número de nodos evaluados, lo que se traduce en una mejora notable en el tiempo de ejecución sin comprometer la calidad de las decisiones.
