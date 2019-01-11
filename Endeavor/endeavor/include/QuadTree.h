#if !defined QUAD_TREE
#define QUAD_TREE

#include "QuadTreeNode.h"

template < class T >
class QuadTree
{
	private:
		QuadTreeNode<T>* root;
		
		int quad_tree_top;
		int quad_tree_left;
		int quad_tree_height;
		int quad_tree_width;
		
		QuadTreeNode<T>* insertItem(int rec_level, QuadTreeNode<T>* qNode, T* item, int item_top, int item_left, int item_height, int item_width, int curr_top, int curr_left, int curr_height, int curr_width);
		T* retrieveItem(QuadTreeNode<T>* qNode, int x_click, int y_click, int curr_top, int curr_left, int curr_height, int curr_width);
		void deleteQuadTree(QuadTreeNode<T>* qNode);
		
	public:
		QuadTree(int left, int top, int width, int height);
		virtual ~QuadTree();
		
		void insert(T* item, int item_left, int item_top, int item_width, int item_height);
		T* retrieve(int x_click, int y_click);
};

template < class T >
QuadTree<T>::QuadTree(int left, int top, int width, int height)
{
	root = NULL;
	
	quad_tree_left = left;
	quad_tree_top = top;
	quad_tree_width = width;
	quad_tree_height = height;
}

template < class T >
QuadTree<T>::~QuadTree()
{
	deleteQuadTree(root);
}

template < class T >
void QuadTree<T>::deleteQuadTree(QuadTreeNode<T>* qNode)
{
	if (qNode == NULL) return;
	
	QuadTreeNode<T>* top_left = qNode->getTopLeft();
	deleteQuadTree(top_left);
	QuadTreeNode<T>* top_right = qNode->getTopRight();
	deleteQuadTree(top_right);
	QuadTreeNode<T>* bottom_right = qNode->getBottomRight();
	deleteQuadTree(bottom_right);
	QuadTreeNode<T>* bottom_left = qNode->getBottomLeft();
	deleteQuadTree(bottom_left);
	
	delete qNode;
}

template < class T >
T* QuadTree<T>::retrieve(int x_click, int y_click)
{
	return retrieveItem(root, x_click, y_click, quad_tree_top, quad_tree_left, quad_tree_height, quad_tree_width);
}

template < class T >
T* QuadTree<T>::retrieveItem(QuadTreeNode<T>* qNode, int x_click, int y_click, int curr_top, int curr_left, int curr_height, int curr_width)
{
	if (qNode == NULL) return NULL;  //a miss
	
	else if (qNode->getItem() != NULL)
	{
		return qNode->getItem();  //a hit
	}
	
	else  //figure out which child to follow
	{
		int curr_width_adj_1 = curr_width/2;
		int curr_height_adj_1 = curr_height/2;

		int x_center = curr_left + curr_width_adj_1;
		int y_center = curr_top + curr_height_adj_1;
		
		int curr_width_adj_2 = curr_width - curr_width_adj_1;
		int curr_height_adj_2 = curr_height - curr_height_adj_1;
		
		if (x_click < x_center && x_click >= x_center - curr_width_adj_1 && y_click < y_center && y_click >= y_center - curr_height_adj_1)
		{
			//PRINT("follow top left")
			return retrieveItem(qNode->getTopLeft(), x_click, y_click, curr_top, curr_left, curr_height_adj_1, curr_width_adj_1);
		}
		else if (x_click >= x_center && x_click < x_center + curr_width_adj_2 && y_click < y_center && y_click >= y_center - curr_height_adj_1)
		{
			//PRINT("follow top right")
			return retrieveItem(qNode->getTopRight(), x_click, y_click, curr_top, curr_left + curr_width_adj_1, curr_height_adj_1, curr_width_adj_2);
		}
		else if (x_click < x_center && x_click >= x_center - curr_width_adj_1 && y_click >= y_center && y_click < y_center + curr_height_adj_2)
		{
			//PRINT("follow bottom left")
			return retrieveItem(qNode->getBottomLeft(), x_click, y_click, curr_top + curr_height_adj_1, curr_left, curr_height_adj_2, curr_width_adj_1);
		}
		else if (x_click >= x_center && x_click < x_center + curr_width_adj_2 && y_click >= y_center && y_click < y_center + curr_height_adj_2)
		{
			//PRINT("follow bottom right")
			return retrieveItem(qNode->getBottomRight(), x_click, y_click, curr_top + curr_height_adj_1, curr_left + curr_width_adj_1, curr_height_adj_2, curr_width_adj_2);
		}
		else return NULL;
	}

}

template < class T > 
void QuadTree<T>::insert(T* item, int item_left, int item_top, int item_width, int item_height)
{
	if (item_left < quad_tree_left || item_top < quad_tree_top || item_width > quad_tree_width || item_height > quad_tree_height)
	{
		return;
	}
	
	//DO THIS: check that the item is at least partially within the dimensions of the quadtree
	root = insertItem(1, root, item, item_top, item_left, item_height, item_width, quad_tree_top, quad_tree_left, quad_tree_height, quad_tree_width);
}

template < class T >
QuadTreeNode<T>* QuadTree<T>::insertItem(int rec_level, QuadTreeNode<T>* qNode, T* item, int item_top, int item_left, int item_height, int item_width, int curr_top, int curr_left, int curr_height, int curr_width)
{
	if (qNode == NULL)
	{
		qNode = new QuadTreeNode<T>();
	}
	
	//the item is completely contained within the node's bounds, so we are done
	//note that the item will appear many times in the quadtree if it is relatively large
	//each quadtree leaf contains exactly one reference
	if ((item_top <= curr_top) && (item_left <= curr_left) &&  (item_top + item_height >= curr_top + curr_height) && (item_left + item_width >= curr_left + curr_width))
	{
		qNode->setItem(item);
	}

	//the item is not completely contained within the node's bounds, so we are not done
	else
	{
		//at most four recursive calls here
		int curr_width_half = curr_width/2;
		int curr_height_half = curr_height/2;
		
		int x_center = curr_left + curr_width_half;
		int y_center = curr_top + curr_height_half;
		
		int curr_height_q1 = y_center - curr_top;
		int curr_width_q1 = x_center - curr_left;

		//checking to see if item is partially in the top left quadrant
		if (x_center > item_left && y_center > item_top)
		{
			int curr_height_new = curr_height_q1;
			int curr_width_new = curr_width_q1;
			int curr_top_new = curr_top;
			int curr_left_new = curr_left;
			
			qNode->setTopLeft(insertItem(rec_level + 1, qNode->getTopLeft(), item, item_top, item_left, item_height, item_width, curr_top_new, curr_left_new, curr_height_new, curr_width_new));
		}
			
		//top right check
		if (x_center < (item_left + item_width) && y_center > item_top)
		{
			int curr_height_new = curr_height_q1;
			int curr_width_new = curr_width - curr_width_q1;
			int curr_top_new = curr_top;
			int curr_left_new = curr_left + curr_width_q1;

			qNode->setTopRight(insertItem(rec_level + 1, qNode->getTopRight(), item, item_top, item_left, item_height, item_width, curr_top_new, curr_left_new, curr_height_new, curr_width_new));
		}
			
		//bottom left check
		if (x_center > item_left && y_center < (item_top + item_height))
		{
			int curr_height_new = curr_height - curr_height_q1;
			int curr_width_new = curr_width_q1;
			int curr_top_new = curr_top + curr_height_q1;
			int curr_left_new = curr_left;

			qNode->setBottomLeft(insertItem(rec_level + 1, qNode->getBottomLeft(), item, item_top, item_left, item_height, item_width, curr_top_new, curr_left_new, curr_height_new, curr_width_new));
		}

		//bottom right check
		if (x_center < (item_left + item_width) && y_center <  (item_top + item_height))
		{
			int curr_height_new = curr_height - curr_height_q1;
			int curr_width_new = curr_width - curr_width_q1;
			int curr_top_new = curr_top + curr_height_q1;
			int curr_left_new = curr_left + curr_width_q1;

			qNode->setBottomRight(insertItem(rec_level + 1, qNode->getBottomRight(), item, item_top, item_left, item_height, item_width, curr_top_new, curr_left_new, curr_height_new, curr_width_new));
		}
	}
		
	return qNode;
}

#endif
