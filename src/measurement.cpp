#include <measurement.hpp>

Measurement::Measurement(Hamiltonian* h){
   _h=h;
   _J=complex<double> (0,1);
}

double Measurement::sz_i(cx_vec state,int i){ //gets state in eigenbasis)
    state=_h->eigen_2_nat(state); 
    double result=0;
    int spin=0;
    int N = _h->get_system_size();
    i=N-i-1;
    for (int n=0;n<(_h->get_dim());n++){
        spin=get_sz(_h->get_state(n), i,N);    
        result+=norm(state(n))*(double(spin)/2.);
    }
    return result;
}

double Measurement::sz_i_sz_in(cx_vec state,int i,int n){
    state=_h->eigen_2_nat(state);
    double res=0;
    double s=0;
    int N= _h->get_system_size();
    for (int k=0;k<(_h->get_dim());k++){
        s=(compare_bits(_h->get_state(k), i,_h->get_state(k), i+n,N)*2-1)/4.;
        res+=norm(state(k))*s;
    }
    return  res;
}
