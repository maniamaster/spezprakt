#include <timeevolver.hpp>

Timeevolver::Timeevolver(Hamiltonian *h){
    _h=h;
    _J=complex<double> (0,1);

}

void Timeevolver::time_fw(cx_vec* state,double dt){
    if (_h->get_diagonalized()){
        for (int i=0;i < _h->get_dim();i++){
            (*state)(i)=exp(-_J*_h->get_cxeigval()(i)*dt)*(*state)(i);
       }
    }
}

void Timeevolver::time_bw(cx_vec* state,double dt){
    if (_h->get_diagonalized()){
        for (int i=0;i < _h->get_dim();i++){
            (*state)(i)=exp(_J*_h->get_cxeigval()(i)*dt)*(*state)(i);
        }
    }
}
