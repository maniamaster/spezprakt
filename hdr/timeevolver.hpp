#ifndef TIMEEVOLVER_hpp
#define TIMEEVOLVER_hpp
#include <hamiltonian.hpp>
#include <armadillo>
#include <complex>

using namespace std;
using namespace arma;

class Timeevolver{
    private:
        complex<double> _J;
        Hamiltonian* _h;
    public:
        Timeevolver(Hamiltonian* h);
        void time_fw(cx_vec* state,double dt);
        void time_bw(cx_vec* state,double dt);

};

#endif
        
