#include <iostream>
#include <fstream>
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
		return 1;
	if (string(argv[2]) != "-n" || string(argv[4]) != "-o")
		return 1;

	ofstream ofs(argv[5]);
	
	srand(time(nullptr));
	size_t n = (size_t) strtod(argv[3], NULL);
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
		delete x;
	}
} 
