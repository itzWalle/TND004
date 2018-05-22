#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "vld.h"

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {

    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy_ = rhs;
        std::swap( *this, copy_ );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            preOrder( root, 0 );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        root = insert( x, root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        root = insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        root = remove( x, root );
    }

	Comparable getParent(Comparable x)	const																							///getParent
	{
		BinaryNode* investigator = root;
		if (investigator->element == x)
			return Comparable();


		while (investigator != nullptr)
		{
			if (investigator->element > x)
				investigator = investigator->left;

			else if (investigator->element < x)
				investigator = investigator->right;

			else if (investigator->element == x)
				return investigator->parent->element;
		}

		return Comparable();
	}
																																		///FIND_PRED_SUCC
	void find_pred_succ(const Comparable& x, Comparable& pred, Comparable& succ) const
	{
		BinaryNode* current = root;

		while (current != nullptr)
		{
			if (current->element == x)
			{
				BinaryNode* pre = find_predecessor(current);
				BinaryNode* suc = find_successor(current);

				if (pre != nullptr)
					pred = pre->element;

				if (suc != nullptr)
					succ = suc->element;

				return;
			}
			else if (current->element < x)
			{
				pred = current->element;
				current = current->right;
			}
			else
			{
				succ = current->element;
				current = current->left;
			}
		}
	}

																																			///PRIVATE HERE YES
  private:

    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
		///
		BinaryNode *parent;

		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
			: element{ theElement }, left{ lt }, right{ rt }, parent{ pt } { }

		BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
			: element{ std::move(theElement) }, left{ lt }, right{ rt }, parent{ pt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the root of the subtree.
     */
    BinaryNode* insert( const Comparable & x, BinaryNode* t)
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr, nullptr};
		else if (x < t->element)
		{
			t->left = insert(std::move(x), t->left);
			t->left->parent = t;
		}
		else if (t->element < x)
		{
			t->right = insert(std::move(x), t->right);
			t->right->parent = t;
		}
        else
        {
            ;  // Duplicate; do nothing   (If duplicate, do nothing???)
        }

        return t;
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the root of the subtree.
     */
    BinaryNode* insert( Comparable && x, BinaryNode* t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr, nullptr};
		else if (x < t->element)
		{
			t->left = insert(std::move(x), t->left);
			t->left->parent = t;
		}
		else if (t->element < x)
		{
			t->right = insert(std::move(x), t->right);
			t->right->parent = t;
		}
        else
        {
             ;  // Duplicate; do nothing
        }

        return t;
    }


    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the root of the subtree.
     */
    BinaryNode* remove( const Comparable & x, BinaryNode *t )																		///Remove
    {
        if( t == nullptr )
            return t;   // Item not found
        if( x < t->element )
            t->left = remove( x, t->left );
        else if( t->element < x )
            t->right = remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            t->right = remove( t->element, t->right );
        }
			else
			{
				BinaryNode *oldNode = t;
				t = ( t->left != nullptr ) ? t->left : t->right;
				delete oldNode;
			}

         return t;
    }


    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    static BinaryNode * findMin( BinaryNode *t )
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left ); //recursive call
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    static BinaryNode * findMax( BinaryNode *t )
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
/*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void printTree( BinaryNode *t, ostream & out ) const																			///printTree
    {
        if( t != nullptr )
        {
			preOrder(t, 0);

            /*printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );*/
        }
    }

	void preOrder(BinaryNode* t, int indentation) const																				///preOrder
	{
		if (t != nullptr)
		{
			cout << setw(indentation) << t->element << endl;

			if (indentation == 0)
				indentation += 4;
			else
				indentation += 2;

			preOrder(t->left, indentation);
			preOrder(t->right, indentation);
		}
	}

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
		else
		{
			BinaryNode* temp = new BinaryNode{ t->element, clone(t->left), clone(t->right), nullptr };
			
			if (temp->left != nullptr)
				temp->left->parent = temp; 
			if (temp->right != nullptr)
				temp->right->parent = temp;

			return temp;
		}
    }

	///Find Successor																												///find_successor
	static BinaryNode * find_successor(BinaryNode *t)
	{
		if (t == nullptr)
			return nullptr;

		else if (t->right)
		{
			t = t->right;
			return findMin(t);
		}

		while (t->parent != nullptr && t->parent->left != t)
		{
			t = t->parent;
		}
		return t->parent;
	}


	///Find Predecessor																												///find_predecessor
	static BinaryNode * find_predecessor(BinaryNode *t)
	{
		if (t == nullptr)
			return nullptr;

		else if (t->left)
		{
			t = t->left;
			return findMax(t);
		}

		while (t->parent != nullptr && t->parent->right != t)
		{
			t = t->parent;
		}
		return t->parent;
	}




	public:																																			///PUBLIC AGAIN

																																						///BSTIterator
		class BiIterator
		{
		public:
			BiIterator() = default;

			BiIterator(BinaryNode* t) { current = t; }

			Comparable& operator*() const { return current->element; }

			Comparable* operator->() const { return &(current->element); }

			bool operator==(const BiIterator &t) const { return current == t.current; }

			bool operator!=(const BiIterator &t) const { return current != t.current; }

			BiIterator& operator++()
			{
				current = find_successor(current);
				return *this;
			}

			//BiIterator& operator++(int )   i++
			//{
			//	current = find_successor(current);
			//	return *this;
			//}

			BiIterator& operator--()
			{
				current = find_predecessor(current);
				return *this;
			}

		private:
			BinaryNode* current;
		};

		BiIterator begin() const
		{
			if (isEmpty()) return end();

			return BiIterator(findMin(root));
		}

		BiIterator end() const
		{
			return BiIterator();
		}

																														///Containers
		BiIterator contains(const Comparable& x)
		{
			return contains(x, root);
		}

		/**
		* Internal method to test if an item is in a subtree.
		* x is item to search for.
		* t is the node that roots the subtree.
		*/
		BiIterator contains(const Comparable & x, BinaryNode *t) const
		{
			if (t == nullptr)
				return false;
			else if (x < t->element)
				return contains(x, t->left);
			else if (t->element < x)
				return contains(x, t->right);
			else
				return BiIterator(t);    // Match
		}		
};

#endif
