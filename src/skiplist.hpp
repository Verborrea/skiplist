#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <iostream>
#include <stdlib.h>
#include <time.h>

template <size_t N, typename KType, typename EType>
class Skiplist
{
public:
  Skiplist();
  ~Skiplist();

  size_t max_level() const; // constraint for list height
  size_t level()     const; // level of the higher node
  size_t size()      const; // number of elements
  bool   empty()     const;

  bool  contains(KType key) const;
  EType search(KType key)   const;
  void  insert(KType key, EType value);
  void  erase(KType key);

private:
  size_t _max_level;
  size_t _level;
  size_t _size;

  struct Node
  {
    EType value;
    KType key;
    Node *next[N];

    Node(KType _key, EType _val);
    Node(); // solo para el header
  };

  Node *header;

  size_t randomLevel() const;
};

// ============== constructores ==============

template <size_t N, typename KType, typename EType>
Skiplist<N, KType, EType>::Skiplist()
{
  _max_level = N;
  _level = 0;
  _size = 0;
  header = new Node();

  // para la generacion de aleatorios
  srand (time(NULL));
}

template <size_t N, typename KType, typename EType>
Skiplist<N, KType, EType>::~Skiplist()
{
  while (!empty()) {
    erase(header->next[0]->key);
  }
  delete header;
}

template <size_t N, typename KType, typename EType>
Skiplist<N, KType, EType>::Node::Node(KType _key, EType _val)
{
  key = _key;
  value = _val;
  for (int i = 0; i < N; i++)
    next[i] = nullptr;
}

template <size_t N, typename KType, typename EType>
Skiplist<N, KType, EType>::Node::Node()
{
  for (int i = 0; i < N; i++)
    next[i] = nullptr;
}

// ============== funciones simples ==============

template <size_t N, typename KType, typename EType>
size_t Skiplist<N, KType, EType>::max_level() const
{
  return _max_level;
}

template <size_t N, typename KType, typename EType>
size_t Skiplist<N, KType, EType>::level() const
{
  return _level;
}

template <size_t N, typename KType, typename EType>
size_t Skiplist<N, KType, EType>::size() const
{
  return _size;
}

template <size_t N, typename KType, typename EType>
bool Skiplist<N, KType, EType>::empty() const
{
  return size() == 0;
}

// Function that returns the level of the new node inserted.
// The probabilty of promoting a node one level is 50%, that
// is the same of fliping a coin (fair-coin sequence).
template <size_t N, typename KType, typename EType>
size_t Skiplist<N, KType, EType>::randomLevel() const
{
  size_t new_level = 0;
  while(new_level < max_level() && rand()&1)
    new_level++;
  return new_level;
}

// ============== funciones complejas ==============

template <size_t N, typename KType, typename EType>
bool Skiplist<N, KType, EType>::contains(KType key) const
{
  Node *x = header;
  for (size_t i = level() + 1; i-- > 0;)
    while (x->next[i] && x->next[i]->key < key)
      x = x->next[i];
  x = x->next[0];
  if (x && x->key == key)  
    return true;
  return false;
}

template <size_t N, typename KType, typename EType>
EType Skiplist<N, KType, EType>::search(KType key) const
{
  Node *x = header;
  for (size_t i = level() + 1; i-- > 0;)
    while (x->next[i] && x->next[i]->key < key)
      x = x->next[i];
  x = x->next[0];
  if (x && x->key == key)  
    return x->value;
  throw std::out_of_range("Error: key not in list!");
}

template <size_t N, typename KType, typename EType>
void Skiplist<N, KType, EType>::insert(KType key, EType value)
{
  // Vector with rightmost node at i to the left of the key inserted
  Node *update[max_level()];
  Node *x = header;
  for (size_t i = level() + 1; i-- > 0;) {
    while (x->next[i] && x->next[i]->key < key)
      x = x->next[i];
    update[i] = x;
  }
  x = x->next[0];

  // if key exists, update value
  if (x && x->key == key){
    x->value = value;
  } else {// else, promote with fair coin
    size_t new_level = randomLevel();
    // new_level higher than actual level handling
    if (new_level > level()){
      for (size_t i = level() + 1; i <= new_level; i++)
        update[i] = header;
      _level = new_level;
    }
    x = new Node(key, value);
    for (size_t i = 0; i <= new_level; i++) {
      x->next[i] = update[i]->next[i];
      update[i]->next[i] = x;
    }
    _size++;  // increment size of the skiplist
  }
}

template <size_t N, typename KType, typename EType>
void Skiplist<N, KType, EType>::erase(KType key)
{
  Node *update[max_level()];
  Node *x = header;
  for (size_t i = level() + 1; i-- > 0;) {
    while (x->next[i] && x->next[i]->key < key)
      x = x->next[i];
    update[i] = x;
  }
  x = x->next[0];

  if (x && x->key == key) {
    for (size_t i = 0; i <= level(); i++) {
      if (update[i]->next[i] != x) break;
      update[i]->next[i] = x->next[i];
    }
    delete x;
    // handle level underflow
    while (_level > 0 && header->next[_level] == nullptr)
      _level--;
    _size--; // decrement size
  }
}

#endif // SKIPLIST_HPP