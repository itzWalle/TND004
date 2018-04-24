#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set () // FUNKAR FUNKAR
	: head(new Node(0, tail, nullptr)),  tail(new Node(0, nullptr, head)), counter(0)
{
	//IMPLEMENT before HA session on week 15
}


//Conversion constructor
Set::Set (int n) // FUNKAR FUNKAR
	:head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(1)
{
    tail->prev = new Node(n, tail, head);
    head->next = tail->prev;
//	Node *newNode = new Node(n, tail, head);
//	head->next = tail->prev = newNode;

}

void Set::inserter(Node *p, int val) // FUNKAR FUNKAR
{
	Node* newNode = new Node(val, p, p->prev); //steps 1 and 2
	p->prev = p->prev->next = newNode; //steps 3 and 4

	counter++;
}


//Constructor to create a Set from a sorted array
Set::Set (int a[], int n) // a is sorted // FUNKAR FUNKAR
	:head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(1)

{
	for (int i = 0; i < n;i++)
	{
		inserter(tail, a[i]);
	}
}

Set::~Set() // FUNKAR FUNKAR
{
    Node *temp = head->next;
	Node *prev = head;

	while (prev != nullptr)
	{
		temp = prev->next;
		delete prev;

		prev = temp;
	}
	//IMPLEMENT before HA session on week 15
}


//Copy constructor
Set::Set (const Set& source) // FUNKAR FUNKAR
	:head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(source.counter)
{

	Node *emptyComp = source.head->next;

	if (emptyComp != source.tail)
	{

		Node *dummy = source.head->next;

		while (dummy->next != source.tail)
		{
			inserter(tail, dummy->value);

				dummy = dummy->next;
		}

		inserter(tail, dummy->value);
	}

	//IMPLEMENT before HA session on week 15
}


//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter // FUNKAR FUNKAR
Set& Set::operator=(Set source)
{
	swap(head, source.head);
	swap(tail, source.tail);
	swap(counter, source.counter);

	return *this;
}


//Test whether a set is empty
bool Set::_empty () const // FUNKAR FUNKAR
{
    return (!counter);
}


//Test set membership
bool Set::is_member (int val) const    // FUNKAR FUNKAR
{
	//IMPLEMENT before HA session on week 15
	Node *temp = head->next;

    while(temp != tail)
    {
        if(temp->value == val)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}



//Return number of elements in the set
unsigned Set::cardinality() const
{
	unsigned counter = 0;
	Node *p = head;

	while (p->next != tail)
	{
		p = p->next;
		counter++;
	}

	return counter;
}


//Make the set empty
void Set::make_empty()
{
	//IMPLEMENT before HA session on week 15

	Node *temp = head;

    while( temp->next != tail)
    {
        Node *p = temp;
        temp = temp->next;
        delete p;
        counter--;
    }
    head->next = tail;
    tail->prev = head;
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)
{
    Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (s != S.tail && t != tail)
	{
        if ( s->value == t->value)
        {
            inserter(t, t->value);
            s = s->next;
            t = t->next;
        }

		else if (t->value < s->value)
		{
            inserter(t, t->value);
			t = t->next;
		}

		else if (t->value > s->value)
		{
			inserter(t, s->value);
			s = s->next;
		}
	}
////		if (s->value < t->value || t == tail)
////		{
////			inserter(t, s->value);
////			s = s->next;
////		}
////
////		else if (s->value > t->value)
////		{
////			t = t->next;
////		}
////
////		else
////		{
////			s = s->next;
////		}
//	}

	return *this;
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	//IMPLEMENT
    Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (t != tail)
	{
        if ( s->value == t->value)
        {
            inserter(t, t->value);
            s = s->next;
            t = t->next;
        }

		else if (t->value > s->value)
		{
			s = s->next;
		}

		else if (t->value < s->value)
		{
			t = t->next;
		}
	}
	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
    //IMPLEMENT
	Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (t != tail)
	{
        if ( s->value == t->value)
        {
            s = s->next;
            t = t->next;
        }

		else if (t->value > s->value)
		{
			s = s->next;
		}

		else if (t->value < s->value)
		{
			inserter(t, t->value);
			t = t->next;
			s = s->next;
		}
	}

	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
	//IMPLEMENT

	Node *t = head->next; // iterator in this set
	Node *s = b.head->next; // iterator in  b set

	while (s != b.tail && t != tail)
	{
		if (s->value < t->value || t == tail)
		{
			return false;
		}

		else if (s->value > t->value)
		{
			t = t->next;
		}

		else if (s->value == t->value)
		{
			s = s->next;
			t = t->next;
		}
	}

	return true; //remove this line
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
	//IMPLEMENT

	Node *t = head->next; // iterator in this set
	Node *s = b.head->next; // iterator in  b set

	while (s != b.tail && t != tail)
	{
		if (s->value == t->value)
		{
			s = s->next;
			t = t->next;
		}

		else
        {
            return false;
        }
	}

	return true; //remove this line
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
	//IMPLEMENT

	Node *t = head->next; // iterator in this set
	Node *s = b.head->next; // iterator in  b set

	while (s != b.tail && t != tail)
	{
		if (s->value != t->value)
		{
			s = s->next;
			t = t->next;
		}

		else
        {
            return false;
        }
	}

	return true; //remove this line
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


