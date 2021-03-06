// Lektion_1_ex3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "vld.h"
#include <iostream>
#include <vector>
using std::vector;


int foo(const vector<int>& V, int left, int right)
{
	if (left == right) //base case
		return 1;

	int mid = (left + right) / 2;

	int ll = foo(V, left, mid);
	int rr = foo(V, mid + 1, right);
	/* If:
	int ll = foo(V, left, mid-1);
	int rr = foo(V, mid, right);
	// - We've got a stack overflow bcs of the Recursive function will call itself over and over */ 
	return ll + rr;
}

int main()
{


    return 0;
}

