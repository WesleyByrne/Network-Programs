#if !defined NULL
	#define NULL 0
#endif

#if !defined QUAD_TREE_NODE
#define QUAD_TREE_NODE

template < class T >
class QuadTreeNode
{
	private:
		T* item;
	  
		QuadTreeNode<T>* top_left;
		QuadTreeNode<T>* top_right;
		QuadTreeNode<T>* bottom_left;
		QuadTreeNode<T>* bottom_right;

	public:
		QuadTreeNode();
		virtual ~QuadTreeNode();
		
		QuadTreeNode<T>* getTopLeft();
		QuadTreeNode<T>* getTopRight();
		QuadTreeNode<T>* getBottomRight();
		QuadTreeNode<T>* getBottomLeft();
		
		void setTopLeft(QuadTreeNode<T>* qNode);
		void setTopRight(QuadTreeNode<T>* qNode);
		void setBottomRight(QuadTreeNode<T>* qNode);
		void setBottomLeft(QuadTreeNode<T>* qNode);
		
		void setItem(T* item);
		T* getItem();
};

template < class T >
QuadTreeNode<T>::QuadTreeNode()
{
	item = NULL;
	
	top_left = NULL;
	top_right = NULL;
	bottom_left = NULL;
	bottom_right = NULL;
}

template < class T >
QuadTreeNode<T>::~QuadTreeNode()
{}

template < class T >
void QuadTreeNode<T>::setItem(T* item)
{
	this->item = item;
}

template < class T >
T* QuadTreeNode<T>::getItem()
{
	return item;
}

template < class T >
QuadTreeNode<T>* QuadTreeNode<T>::getTopLeft()
{
	return top_left;
}

template < class T >
void QuadTreeNode<T>::setTopLeft(QuadTreeNode<T>* qNode)
{
	top_left = qNode;
}

template < class T >
QuadTreeNode<T>* QuadTreeNode<T>::getTopRight()
{
	return top_right;
}

template < class T >
void QuadTreeNode<T>::setTopRight(QuadTreeNode<T>* qNode)
{
	top_right = qNode;
}

template < class T >
QuadTreeNode<T>* QuadTreeNode<T>::getBottomRight()
{
	return bottom_right;
}

template < class T >
void QuadTreeNode<T>::setBottomRight(QuadTreeNode<T>* qNode)
{
	bottom_right = qNode;
}

template < class T >
QuadTreeNode<T>* QuadTreeNode<T>::getBottomLeft()
{
	return bottom_left;
}

template < class T >
void QuadTreeNode<T>::setBottomLeft(QuadTreeNode<T>* qNode)
{
	bottom_left = qNode;
}

#endif
