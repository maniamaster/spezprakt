#include <measurement.hpp>

Measurement::Measurement(Hamiltonian* h){
   _h=h;
   _J=complex<double> (0,1);
}

double Measurement::sz_i(cx_vec state,int i){ //gets state in eigenbasis)
    state=_h->eigen_2_nat(state); 
    i=_h->get_system_size()-i+1; //pos invertieren
    double result=0;
    for (int n=0;n<(_h->get_dim());n++){
        int spin=0;
        
        if (i!=1)
            spin=count_set_bits(_h->get_state(n),i)-count_set_bits(_h->get_state(n),i-1);
        else
            spin=count_set_bits(_h->get_state(n),i);

        result+=norm((state)(n))*(double(spin)-1/2.);
    }
    return result;
}

