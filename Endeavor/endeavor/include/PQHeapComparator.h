#if !defined (PQHEAPCOMPARATOR_H)
#define PQHEAPCOMPARATOR_H

#include "HeapArrayComparator.h"

template < class T >
class PQHeapComparator
{

   private:
      HeapArrayComparator<T>* ha;

   public:
      PQHeapComparator(Comparator<T>* comp);
      virtual ~PQHeapComparator();

      bool pqIsEmpty();
      int pqSize();
      void pqInsert(T* item);
      T* pqRemove();
      T* pqPeek();

};

template < class T >
PQHeapComparator<T>::PQHeapComparator(Comparator<T>* comp) 
{
   ha = new HeapArrayComparator<T>(comp);
}  

template < class T >
PQHeapComparator<T>::~PQHeapComparator() 
{ 
   delete ha;
}  

template < class T >
bool PQHeapComparator<T>::pqIsEmpty() 
{
   return (ha->heapSize() == 0);
}

template < class T >
int PQHeapComparator<T>::pqSize() 
{
   return ha->heapSize();
} 

template < class T >
void PQHeapComparator<T>::pqInsert(T* item)
{
   ha->heapInsert(item);
} 

template < class T >
T* PQHeapComparator<T>::pqRemove()
{
   T* item = NULL;
   int sz = ha->heapSize();
   if (sz > 0)
   {
      item = ha->heapRemove();
   }

   return item;
}

template < class T >
T* PQHeapComparator<T>::pqPeek()
{
   T* item = NULL;
   int sz = ha->heapSize();
   if (sz > 0)
   {
      item = ha->heapPeek();
   }

   return item;
} 

#endif
