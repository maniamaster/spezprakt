#ifndef HAMILTONIAN_hpp
#define HAMILTONIAN_hpp  
#include <basis.hpp>
#include <armadillo>
#include <iostream>
#include <complex>

using namespace std;
using namespace arma;

class Hamiltonian: public Basis{
    protected:
        mat _ham;
        mat _diag;
        mat _eigvec; //eigenvectors of hamilton matrix
        vec _eigval; //eigenvalues
        cx_vec _cxeigval;
        bool _set;
        bool _diagonalized;
        double _lambda;
        double _mu;
        void fill();

    public:
        Hamiltonian(int N,int m);
        void set_ham(double mu,double lambda);
        void diagonalize();
        bool get_diagonalized();
        double get_lambda();
        double get_mu();
        void print_hamiltonian();
        void print_diagonal();
        void print_eigval();
        cx_vec get_cxeigval();
        void print_eigvec();
        mat get_eigvec();
        cx_vec nat_2_eigen(cx_vec natvec); 
        cx_vec eigen_2_nat(cx_vec eigenbasisvec);
        cx_vec time_translate(cx_vec state,double t);

        friend ostream& operator<<(ostream&, const Hamiltonian& h);
    
};





#endif

