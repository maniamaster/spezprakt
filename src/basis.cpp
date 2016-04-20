#include <basis.hpp>

Basis::Basis(int N,int m)
{
	_N=N;
    _m=m;
}  

void Basis::print_system_size()
{
	cout << "the system size is " << _N << endl;
}

void Basis::generate_basis_list()
{
    int max=(1<<_N)-1;
    int a=0; //initialization, position of basis vector in list
    vector<REP_TYPE> basisList;
    for (int s=0;s<=max;s++){
        if (count_set_bits == (int(_m+_N/2.))){
            a+=1;
            basisList.push_back (s);
        }
    }
    _dim=a;
    _list=basisList;
            
}
