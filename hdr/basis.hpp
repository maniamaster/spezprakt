#ifndef BASIS_H
#define BASIS_H

extern "C"{
#include <utilities.h>
}
#include <iostream>
#include <vector>

using namespace std;

class Hamiltonian;
class Basis
{
protected: 
	int _N;
	int _dim;
    int _m; //2x the total magnetization
    vector<REP_TYPE> _list; //list of basis states with dimension _dim

public:
 	Basis(int N, int m);
 	Basis(){};
	void print_system_size();
    void generate_basis_list();
    void print_basis_list();
    void print_basis_dimension();
};


#endif
