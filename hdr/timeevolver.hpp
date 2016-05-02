#ifndef TIMEEVOLVER_hpp
#define TIMEEVOLVER_hpp
#include <hamiltonian.hpp>
#include <armadillo>
#include <complex>

using namespace std;
using namespace arma;

class Timeevolver{
    private:
        cx_vec * _state;
        double _dt;
        complex<double> _J;
        Hamiltonian* _h;
    public:
        Timeevolver(Hamiltonian* h,cx_vec *initstate,double dt);
        void time_fw();
        void time_bw();

};

#endif
        
