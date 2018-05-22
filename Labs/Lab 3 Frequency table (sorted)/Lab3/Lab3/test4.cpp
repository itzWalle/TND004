#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <string>

#include "BinarySearchTree.h"
#include "Freq.h"
#include "vld.h"

using namespace std;

int main()
{
	BinarySearchTree<Freq> T;
	ifstream file("words.txt");

	if (!file)
	{
		cout << "couldn't open file words.txt" << endl;
		return 1;
	}

	vector<string> V1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
	file.close();

	for (auto i : V1)
	{
		Freq freq(i, 1);
		auto tmp = T.contains(freq);

		if (tmp != T.end())
			++(*tmp);

		else
			T.insert(freq);
	}

	for (auto it = T.begin(); it != T.end(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}