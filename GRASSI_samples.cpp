#include <iostream>
#include <new>
#include <exception>
#include <vector>

class Complex {
	double re;
	double im;
};

using Matrix = Vector <Vector <Complex*> *>;

Matrix& load_samples(ifstream& input_file, size_t n)
{
	try
	{
		Matrix A(n);
		for (Vector* row : A) {
			row = new Vector;
			for (Complex* column : A) {
				Column = new Complex;
				input_file >> *Column;
			}
		}
		return A;
	}

	catch (exception& e)
	{
		for (Vector* row : A) {
			for (Complex* column : A) {
				delete column;
			}
			delete row;
		}
		throw e;
	}
}

int main() {
	return 0;
}
