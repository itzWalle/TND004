#include "set.h"

/*****************************************************
* Implementation of the member functions             *
******************************************************/

//Default constructor
Set::Set()
	: head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(0)
{}

//Conversion constructor
Set::Set(int n)
	: head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(0)
{
    cout << "------------------ Conversion constructor ------------------" << endl;
//    Aniisas Version
//    tail->prev = new Node(n, tail, head);
//    head->next = tail->prev;

//    Vår första verison
//    Node *newNode = new Node(n, tail, head);
//    head->next = newNode;
//    tail->prev = newNode;

    InsertNode(tail, n);
    counter++;
    cout << "n = " << n << ", this = " << *this << endl;
}

//Constructor to create a Set from a sorted array
Set::Set(int a[], int n) // a is sorted
	: head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(0)
{
    cout << "------------------ Constructor from array ------------------" << endl;
    for(int i = 0; i < n; i++){
        InsertNode(tail, a[i]);
        counter++;
    }
}

//Destructor
Set::~Set()
{
    cout << "------------------ Destructor ------------------" << endl;
//	Node *prev = head;
//	Node *temp;
//
//	while(prev->next != nullptr)
//	{
//		temp = prev;
//		prev = prev->next;
//		delete temp;
//	}
//	delete temp;
//	delete prev;

	Node *temp = head->next;
	Node *prev = head;

	while(prev != nullptr)
	{
	    cout << "prev = " << prev->value << endl;
		temp = prev->next;
		delete prev;
		prev = temp;
	}
}

void Set::InsertNode(Node* p, int nodeVal)
{
    // p = tail of set, nodeVal = value of node to be inserted
    Node *newNode = new (nothrow) Node(nodeVal, p, p->prev);
    p->prev = p->prev->next = newNode;
}

void Set::RemoveNode(Node* p)
{
    // p = node to be removed
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
}

//Copy constructor
Set::Set(const Set& source)
	: head(new Node(0, tail, nullptr)), tail(new Node(0, nullptr, head)), counter(source.counter)
{
    cout << "------------------ Copy constructor ------------------" << endl;
//	Node *tmpH = source.head->next;
//    while(tmpH != source.tail){
//        InsertNode(tail, tmpH->value);
//        counter++;
//        tmpH = tmpH->next;
//    }
    Node *tmp = source.head->next;
    if(tmp != source.tail)
    {
        while(tmp->next != source.tail)
        {
            InsertNode(tail, tmp->value);
            counter++;
            tmp = tmp->next;
        }
        InsertNode(tail, tmp->value);
        counter++;
    }
}

// Move constructor
Set::Set(Set&& source)
    : head(source.head), tail(source.tail), counter(source.counter)
{
    source.head = new Node(0, tail, nullptr);
    source.tail = new Node(0, nullptr, head);
    source.head->next = source.tail;
    source.counter = 0;
}

//Copy-and-swap assignment operator
//Note that call-by-value is used for source parameter
Set& Set::operator=(Set source)
{
    std::swap(head, source.head);
    std::swap(tail, source.tail);
    swap(counter, source.counter);

    return *this;
}

//Test whether a set is empty
bool Set::_empty() const
{
	return (!counter);
}

//Test set membership
bool Set::is_member(int val) const
{
	Node* ptr = head->next;
    while(ptr != tail)
    {
        if(ptr->value == val){
            return true;
        }
        ptr = ptr->next;
    }
	return false; //remove this line
}

//Return number of elements in the set
unsigned Set::cardinality() const
{
	return counter;
}

//Make the set empty
void Set::make_empty()
{
    Node *temp = head->next;
    Node *ptr;

    while( temp->next != tail)
    {
        ptr = temp;
        temp = temp->next;
        delete ptr;
        counter--;
    }
    counter--;
    head->next = tail;
    tail->prev = head;
    delete temp;
}

//Modify *this such that it becomes the union of *this with Set S
//Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)
{
	Node *t = head->next; // iterator in this set
	Node *s = S.head->next; // iterator in  b set

	while (s != S.tail && t != tail)
	{
        if (s->value == t->value)
        {
            s = s->next;
            t = t->next;
        }
		else if (t->value < s->value)
		{
			t = t->next;
		}
		else if (t->value > s->value)
		{
			InsertNode(t, s->value);
			counter++;
			s = s->next;
		}
	}
	if(t == tail)
    {
        while(s != S.tail){
            InsertNode(t, s->value);
            counter++;
			s = s->next;
        }
    }
	return *this;
}


//Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S)
{
	if(S._empty())  // Check if Set S is empty
    {
        make_empty();
	}
	else
	{
        Node *t = head->next;   // Iterator in this set
        Node *s = S.head->next; // Iterator in S set

        while(s != S.tail && t != tail)
        {
            if(s->value == t->value)
            {
                s = s->next;
                t = t->next;
            }
            else if(t->value < s->value)
            {
                RemoveNode(t);
                t = t->next;
                counter--;
            }
            else if(t->value > s->value)
            {
                s = s->next;
            }
        }
        if(s == S.tail)
        {
            while(t != tail)
            {
                RemoveNode(t);
                t = t->next;
                counter--;
            }
        }
	}
	return *this;
}


//Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
    Node *t = head->next;   // Iterator in this set
    Node *s = S.head->next; // Iterator in S set

    while(s != S.tail && t != tail)
    {
        if(s->value == t->value)
        {
            RemoveNode(t);
            counter--;
            t = t->next;
            s = s->next;
        }
        else if(t->value < s->value)
        {
            t = t->next;
        }
        else if(t->value > s->value)
        {
            s = s->next;
        }
    }
	return *this;
}

//Return true, if the set is a subset of b, otherwise false
//a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const
{
    Node *t = head->next;   // Iterator in this set

    while(t != tail)
    {
        if(!b.is_member(t->value))
        {
            return false;
        }
        t = t->next;
    }
    return true;
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const
{
    if(b<=*this && *this<=b)
    {
        return true;
    }
	return false; //remove this line
}


//Return true, if the set is different from set b
//a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const
{
    if(!(b<=*this)) //*this<=b??
    {
        return true;
    }
	return false; //remove this line
}


//Return true, if the set is a strict subset of b, otherwise false
//a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const
{
	if(*this<=b && *this!=b)
	{
	    return true;
	}
	return false; //remove this line
}

Set Set::operator+(const int n)
{
    cout << "INT +++++++" << endl;
    Node *t = head->next;   // Iterator in this set

    if(!this->is_member(n))
    {
        while(t != tail)
        {
            if(t->value < n)
            {
                t = t->next;
            }
            else if(t->value > n)
            {
                InsertNode(t, n);
                counter++;
                return *this;
            }
        }
        InsertNode(tail, n);
        counter++;
    }
    return *this;
}

Set Set::operator-(const int n)
{
    Node *t = head->next;   // Iterator in this set

    if(this->is_member(n))
    {
        while(t != tail)
        {
            if(t->value == n)
            {
                RemoveNode(t);
                counter--;
                break;
            }
            t = t->next;
        }
    }
    return *this;
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


