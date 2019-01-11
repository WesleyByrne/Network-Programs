#if !defined (HEAPARRAYCOMPARATOR_H)
#define HEAPARRAYCOMPARATOR_H

#include "Comparator.h"

template < class T >
class HeapArrayComparator
{

   private:
      int max_list;
      T** items;
      Comparator<T>* comp;
      int sz;

      void heapRebuild();
      void arrayResize(int new_size);

   public:
      HeapArrayComparator(Comparator<T>* comp);
      virtual ~HeapArrayComparator();

      bool heapIsEmpty();
      int heapSize();
      void heapInsert(T* item);
      T* heapRemove();
      T* heapPeek();

};

#endif

// this is a MINHEAP (smallest items to top for alphabetical order)
template < class T >
HeapArrayComparator<T>::HeapArrayComparator(Comparator<T>* c) 
{
   comp = c;
   max_list = 16;
   items = new T*[max_list];
   sz = 0;
}

template < class T >
HeapArrayComparator<T>::~HeapArrayComparator()
{
   //delete comp;
   delete[] items;
}

template < class T >
bool HeapArrayComparator<T>::heapIsEmpty()
{
   return sz == 0;
}

template < class T >
int HeapArrayComparator<T>::heapSize()
{
   return sz;
}

template < class T >
void HeapArrayComparator<T>::heapInsert(T* item)
{
   if (sz == max_list) 
   {
      arrayResize(2*max_list); //double the size of the array
   } 

   // place the new item at the end of the heap
   items[sz] = item;

   // trickle new item up to its proper position
   int place = sz;
   int parent = (place - 1)/2; //array location of parent

   while (place > 0 && comp->compare(items[place], items[parent]) < 0)
   {
      // swap items[place] and items[parent]
      T* swap_item = items[parent];
      items[parent] = items[place];
      items[place] = swap_item;

      place = parent;
      parent = (place - 1)/2;
   }  

   sz++;
} 

template < class T >
T* HeapArrayComparator<T>::heapRemove()
{
   T* root_item = NULL;
   if (!heapIsEmpty()) 
   {
      root_item = items[0];  //dequeue smallest
      items[0] = items[sz - 1];
      items[sz - 1] = NULL;
      sz--;
      heapRebuild();

   }  

   return root_item;
}

template < class T >
T* HeapArrayComparator<T>::heapPeek() 
{
   T* root_item = NULL;
   if (!heapIsEmpty()) 
   {
      root_item = items[0];
   }
   return root_item;
} 

template < class T >
void HeapArrayComparator<T>::heapRebuild() 
{
   bool swap = true;

   int parent = 0;
   int child = 2*parent + 1;  //index of parent's left  child, if any

   while (child < sz && swap)
   {
      swap = false;

      // root is not a leaf, so it has a left child at child
      int right_child = child + 1;  //index of right child, if any

      //if parent has a right child, find smaller child
      //note that using a Heap, FIFO order may not be maintained for items with the same priority
      if (right_child < sz)
      {
         if (comp->compare(items[right_child], items[child]) < 0)
         {
            child = right_child;  //index of smaller child
         }
      } 

      // if the parent's value is larger than the
      // value in the smaller child, swap values
      if (comp->compare(items[child], items[parent]) < 0)
      {
         T* swap_item = items[parent];
         items[parent] = items[child];
         items[child] = swap_item;
         swap = true;
      }

      parent = child;
      child = 2*parent + 1; //if out of bounds, we are done
   }
}

template < class T >
void HeapArrayComparator<T>::arrayResize(int new_size)
{
   max_list = new_size;
   T** temp = new T*[max_list];

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[i];
   }

   delete[] items;
   items = temp;
}
