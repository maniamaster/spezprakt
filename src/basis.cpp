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
    REP_TYPE max=(1<<_N)-1;
    int a=0; //initialization, position of basis vector in list
    vector<REP_TYPE> basisList;
    for (REP_TYPE s=0;s<=max;s++){
        if (count_set_bits(s,_N) == (int(_m+_N))){
            a+=1;
            basisList.push_back (s);
        }
    }
    _dim=a;
    _list=basisList;
            
}
