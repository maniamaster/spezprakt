#include <hamiltonian.hpp>

Hamiltonian::Hamiltonian(int N,int m){
    _N=N;
    _m=m;
    generate_basis_list();


}
