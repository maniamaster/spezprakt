#ifndef HAMILTONIAN_hpp
#define HAMILTONIAN_hpp  
#include <basis.hpp>
#include <armadillo>
#include <iostream>
#include <complex>

using namespace std;
using namespace arma;

class Hamiltonian: public Basis{
    private:
        mat _ham;
        mat _diag;
        mat _eigvec; //eigenvectors of hamilton matrix
        vec _eigval; //eigenvalues
        cx_vec _cxeigval;
        bool _set;
        bool _diagonalized;
        double _lambda;
        void fill();

    public:
        Hamiltonian(int N,int m);
        void set_ham(double mu);
        void diagonalize();
        bool get_diagonalized();
        void print_hamiltonian();
        void print_diagonal();
        void print_eigval();
        cx_vec get_cxeigval();
        void print_eigvec();
        mat get_eigvec();
        cx_vec nat_2_eigen(cx_vec natvec); 
        cx_vec eigen_2_nat(cx_vec eigenbasisvec);
        cx_vec time_translate(cx_vec state,double t);
    
};





#endif

