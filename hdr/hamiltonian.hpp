#ifndef HAMILTONIAN_hpp
#define HAMILTONIAN_hpp  
#include <basis.hpp>
#include <armadillo>
#include <iostream>

using namespace std;

class Hamiltonian: public Basis{
    private:
        arma::mat _ham;
        void fill();
        

    public:
        Hamiltonian(int N,int m);
        void diagonalize();
        void print_matrix();

            
    
};





#endif

