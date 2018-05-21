/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int infinity = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    /// *** TODO ***
	int  *dist = new int[size+1];
	int  *path = new int[size+1];
	bool *done = new bool[size+1];

	for (int v = 0; v <= size; v++)
	{
		dist[v] = infinity;
		path[v] = 0;
		done[v] = false;
	}

	int start = 1;
	int totalWeight = 0;
	dist[start] = 0;
	done[start] = true;
	int v = 1;

	while (true)
	{
		Node *u = array[v].getFirst();

		while (u)
		{
			if (done[u->vertex] == false && dist[u->vertex] > u->weight)
			{
				dist[u->vertex] = u->weight;
				path[u->vertex] = v;
			}
			u = u->next;
		}

		int shortest = 0;

		for (int i = 1; i <= size; i++)
		{
			if (!done[i] && dist[i] < dist[shortest])
				shortest = i;
		}

		v = shortest;

		if (v == 0) break;
		done[v] = true;

		if (dist[shortest] == infinity)
			break;
		totalWeight += dist[v];
	}
	cout << "Total weight = " << totalWeight << endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    /// *** TODO ***
	Heap<Edge> H;
	DSets D(size);
	int counter = 0, totalWeight = 0;

	///Build heap of edges
	for (int i = 1; i <= size; i++)
	{
		Node* u = array[i].getFirst();

		while (u)
		{
			if (u->vertex < i)
				H.insert(Edge(u->vertex, i, u->weight));
		}
		u = array[i].getNext();
	}

}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
