#include <measurement.hpp>

Measurement::Measurement(Hamiltonian* h){
   _h=h;
   _J=complex<double> (0,1);
}

double Measurement::sz_i(cx_vec* state,int i){
    *state= // konvertierung in natural basis (problem da umwandlung bis jetzt nur mit reellen vektoren geht.)
    double result=0;
    for (int n=0;n<(_h->get_dim());n++){
        int spin=0;
        if (i!=1)
            spin=count_set_bits(_h->get_state(n),i)-count_set_bits(_h->get_state(n),i-1);
        else
            spin=count_set_bits(_h->get_state(n),i);
        result+=norm((*state)(n)*(*state)(n))*(double(spin)-1/2.);
    }
    return result;
}

