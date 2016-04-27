#ifndef HAMILTONIAN_hpp
#define HAMILTONIAN_hpp  
#include <basis.hpp>
#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;

class Hamiltonian: public Basis{
    private:
        mat _ham;
        mat _diag;
        mat _eigvec; //eigenvectors of hamilton matrix
        vec _eigval; //eigenvalues
        bool _set;
        bool _diagonalized;
        double _lambda;
        void fill();

    public:
        Hamiltonian(int N,int m);
        void set_ham(double mu);
        void diagonalize();
        void print_hamiltonian();
        void print_diagonal();
        void print_eigenvalues();
        void print_eigenvectors();
        vec nat_2_eigen(vec natvec); 
        vec blub(vec blah){
            return blah;
        }
    
};





#endif

