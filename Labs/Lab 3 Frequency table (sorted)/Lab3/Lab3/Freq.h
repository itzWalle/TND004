#include "dsexceptions.h"
#include <iomanip>
#include "vld.h"

using namespace std;

class Freq
{
public:
	Freq(string i, int p) 
		: word{ i }, quantity{ p } 
	{

	}

	Freq(const Freq &f)
		: word{ f.word }, quantity{ f.quantity }
	{

	}

	bool operator<(const Freq &f) const  //contains
	{
		return word < f.word;
	}

	void operator++()
	{
		quantity += 1;
	}

	friend ostream& operator<<(ostream& out, const Freq& f)
	{
		out << f.word << setw(3) << f.quantity;
		return out;
	}

private:
	string word;
	int quantity;

};