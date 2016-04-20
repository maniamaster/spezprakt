#ifndef BASIS_H
#define BASIS_H

#include <utilities.h>
#include <iostream>
#include <vector>

using namespace std;

class Basis
{
private: 
	int _N;
	int _dim;
    float _m; //total magnetization
    vector<REP_TYPE> _list; //list of basis states with dimension _dim

    void generate_basis_list();
public:
 	Basis(int N, int m);
	void print_system_size();
};


#endif
