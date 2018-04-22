#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set ()
{
	init();
}


//Conversion constructor
Set::Set (int value)
{
	init();

	insert(value);
}


//Constructor to create a Set from a sorted array
Set::Set (int a[], int n) // a is sorted
{
	init();

	for (int i = 0; i < n; i++)
	{
		insert(a[i]);
	}

}

Set::~Set()
{
	clearSet();
	delete head;
	delete tail;
}

// h 3 [5] 7 12 t, 
// h 3 t, 
//Copy constructor
Set::Set (const Set& source)
{
	////head = new Node(0, tail, nullptr);
	////tail = new Node(0, nullptr, head);

	//Node* ptr = source.head->next;
	//Node* pos = head;

	//for (int i = 0; i < source.counter; i++)
	//{
	//	Node* newNode = new Node(ptr->value, tail, tail->prev);
	//	//counter++;

	//	newNode->prev->next = newNode;
	//	newNode->next->prev = newNode; 

	//	pos = pos->next;
	//	ptr = ptr->next;
	//}

	init();

	Node* current = source.head->next;

	while (true)
	{
		if (current == source.tail)
			break;

		insert(current->value);

		current = current->next;
	}
}


//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter
Set& Set::operator=(Set source)
{
	Set temp(source);

	swap(temp.head, head);
	swap(temp.tail, tail);
	swap(temp.counter, counter); //såklart

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const
{
	return (!counter);
}


//Test set membership
bool Set::is_member (int val) const
{
	
	Node* pos = head;

	if (head->next == nullptr)
	{
		return false;
	}

	while (true)
	{
		if (pos->value == val)
			return true;

		if (pos->next == nullptr)
			return false;

		pos = pos->next; ///Next node
	}
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}


//Make the set empty
void Set::clearSet()
{
	Node* current = head->next;

	while (true)
	{
		if (current == tail)
		{
			head->next = tail;
			tail->prev = head;
			break;
		}

		current = current->next;
		delete current->prev;
	}
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)
{
	//IMPLEMENT before HA session on week 15

	return *this;
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT

	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
	//IMPLEMENT

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	//IMPLEMENT

	return false; //remove this line
}


// Overloaded operator<<
ostream& operator<<(ostream& os, const Set& b)
{
	if (b._empty())
		os << "Set is empty!" << endl;
	else
	{
		auto temp = b.head->next;

		os << "{ ";
		while (temp != b.tail)
		{
			os << temp->value << " ";
			temp = temp->next;
		}

		os << "}" << endl;
	}

	return os;
}

///Initialize
void Set::init()
{
	head = new Node(0, nullptr, nullptr);
	tail = new Node(0, nullptr, nullptr);

	head->next = tail;
	tail->prev = head;
	counter = 0;
}

/// Insert
void Set::insert(int val)
{
	//h 3 5 {7} (12) t, insert(7)
	Node* current = head->next;

	while (true)
	{
		if (current == tail)
		{
			insertBefore(val, current);
			break;
		}
		
		if (current->value == val)
		{
			break;
		}

		if (current->value > val)
		{
			insertBefore(val, current);
			break;
		}

		current = current->next;
	}
}

/// Insert before
void Set::insertBefore(int val, Node* node)
{
	Node* newNode = new Node(val, node, node->prev);

	node->prev->next = newNode;
	node->prev = newNode;
	counter++;
}

