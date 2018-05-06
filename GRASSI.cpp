#include <iostream>
#include <new>
#include <exception>
#include <cstdlib>
#include <vector>

#define MIN_ARGS 1
#define MAX_ARGS 5

using namespace std;

struct Complex {
	double re;
	double im;
};

int main(int argc, char * argv[])
{
	if (argc != 5)
		throw exception::logic_error::invalid_argument e;
	if (string(argv[2]) != "-n" || string(argv[4]) != "-o")
		throw exception::logic_error_invalid_argument e;

	ofstream ofs;
	ofs.open(argv[5]);
	
	srand(time(nullptr));
	size_t n = argv[3];
	vector <vector<Complex*>*> v(n);
	for (auto row : v) {
		row = new vector <Complex *>;
		for (auto column : v) {
			column = new Complex;
			column->re = rand() / 100;
			column->im = rand() / 100;
		}
	}

	for (auto x : v)
		for (auto y : x)
			ofs << *y;

	ofs.close();

	for (auto x : v) {
		for (auto y : row) {
			delete y;
		}
		delete x
	}
} 
