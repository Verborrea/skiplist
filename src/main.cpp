#include "skiplist.hpp"
#include <chrono>

#define ELEMS  1000000
#define MAXLVL 20

using namespace std::chrono;

int main()
{
  Skiplist<MAXLVL,int,int> L;

  std::cout << "Tiempo para insertar " << ELEMS << " elementos: ";
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (int i = 0; i < ELEMS; i++)
    L.insert(i,i * 10);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << "" << time_span.count() << " seconds." << std::endl;

  std::cout << "Tiempo para buscar " << ELEMS << " elementos: ";
  t1 = high_resolution_clock::now();
  for (int i = 0; i < ELEMS; i++)
    L.contains(i);
  t2 = high_resolution_clock::now();
  time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << "" << time_span.count() << " seconds." << std::endl;

  std::cout << "Tiempo para eliminar " << ELEMS << " elementos: ";
  t1 = high_resolution_clock::now();
  for (int i = 0; i < ELEMS; i++)
    L.erase(i);
  t2 = high_resolution_clock::now();
  time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << "" << time_span.count() << " seconds." << std::endl;

  // Prueba de error en search cuando L esta vacia
  try
  {
    std::cout << L.search(3) << std::endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}