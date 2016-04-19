#ifndef BASIS_H
#define BASIS_H

#include <utilities.h>
#include <iostream>

using namespace std;

class Basis
{
private: 
	int _N;
	int _dim;
public:
 	Basis(int N);
	void print_system_size();
};


#endif
