#include <basis.hpp>

Basis::Basis(int N,int m)
{
	_N=N;
    _m=m;
    _dim=0;
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
        if (2*count_set_bits(s,_N) == (int(_m+_N))){
            a+=1;
            basisList.push_back (s);
        }
    }
    _dim=a;
    _list=basisList;
}

void Basis::print_basis_list(){
    for (int i=0;i<_dim;i++){
        print_bits(_list[i], _N);
    }
}

void Basis::print_basis_dimension(){
    if (_dim!=0)
        cout <<"Basis Dimension is: "<< _dim << endl;
}
