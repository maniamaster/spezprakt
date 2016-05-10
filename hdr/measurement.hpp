#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP
#include <hamiltonian.hpp>
#include <armadillo>
#include <complex>

using namespace std;
using namespace arma;

class Measurement{
    private:
        complex<double> _J;
        Hamiltonian* _h;
    public:
        Measurement(Hamiltonian* h);
        double sz_i(cx_vec state,int i);
        double sz_i_sz_in(cx_vec state,int i,int n);

};

#endif
