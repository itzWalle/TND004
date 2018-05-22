/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>


using namespace std;

#include "digraph.h"
#include "queue.h"

static const int infinity = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    /// *** TODO ***																											TODO
	Queue<int> Q;

	for (int v = 1; v <= size; v++)
	{
		dist[v] = infinity;
		path[v] = 0;
	}

	dist[s] = 0;
	Q.enqueue(s);

	while (!Q.isEmpty())
	{
		int v = Q.getFront();
		Node *u = array[v].getFirst();
		Q.dequeue();

		while (u != nullptr)
		{
			if (dist[u->vertex] == infinity)
			{
				dist[u->vertex] = dist[v] + 1;
				path[u->vertex] = v;
				Q.enqueue(u->vertex);
			}
			u = u->next;
		}
	}
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
	if (s < 1 || s > size)
	{
		cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
		return;
	}
    /// *** TODO ***																											TODO									

	for (int v = 1; v <= size; v++)
	{
		dist[v] = infinity;
		path[v] = 0;
		done[v] = false;
	}

	dist[s] = 0;
	done[s] = true;
	int v = s;

	while (true)
	{
		Node *u = array[v].getFirst();

		while (u != nullptr)
		{
			if (done[u->vertex] == false && dist[u->vertex] > dist[v] + u->weight)
			{
				dist[u->vertex] = dist[v] + u->weight;
				path[u->vertex] = v;
			}
			u = u->next;
		}
		///Function: find_smallest_undone_distance_vertex(); Here
		v = find_smallest_dist();

		if (v == 0) break;
		done[v] = true;
	}
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;
	for (int v = 1; v <= size; v++)
	{
		cout << setw(4) << v << " : ";
		array[v].print();
	}
    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;
    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }
    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }
    /// *** TODO ***																										TODO

	printRecursive(t);

	cout << "     (" << dist[t] << ")" << endl;
}

void Digraph::printRecursive(int t) const
{
	//Do recursive here
	if (path[t] == 0)
	{
		cout << "     " << t;
		return;
	}
	else if (t != 0)
	{
		printRecursive(path[t]);
		cout << "     " << t;
	}
}