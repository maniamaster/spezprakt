#ifndef HAMILTONIAN_hpp
#define HAMILTONIAN_hpp  
#include <basis.hpp>
#include <armadillo>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace arma;

class Hamiltonian: public Basis{
    private:
        mat _ham;
        bool _set;
        void fill();

    public:
        Hamiltonian(int N,int m);
        void set_ham();
        void diagonalize();
        void print_matrix();

            
    
};





#endif

