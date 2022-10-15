# Skiplist

Versión no concurrente finalizada. Cuenta con las siguientes funciones:

- `size_t max_level()`: Retorna el nivel máximo de la lista
- `size_t level()`: Retorna el nivel del nodo más alto de la lista
- `size_t size()`: Retorna el número de elementos
- `bool   empty()`: Retorna si la lista está vacia o no

&nbsp;

- `bool  contains(KType key)`: Retorna si la lista contiene al elemento o no
- `EType search(KType key)`: Retorna el valor asociado al elemento con dicha llave o error si no lo encuentra
- `void  insert(KType key, EType value)`: Inserta un nuevo elemento en la lista
- `void  erase(KType key)`: Elimina al elemento de la lista
