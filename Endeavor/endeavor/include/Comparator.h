#if !defined (COMPARATOR_H)
#define COMPARATOR_H

template < class T >
class Comparator
{
   private:

   public:
      Comparator();
      virtual ~Comparator();

      virtual int compare(T* item_1, T* item_2) = 0;
};

template < class T >
Comparator<T>::Comparator()
{}

template < class T >
Comparator<T>::~Comparator()
{}

#endif