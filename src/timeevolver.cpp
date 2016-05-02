#include <timeevolver.hpp>

Timeevolver::Timeevolver(Hamiltonian *h,cx_vec *initstate,double dt){
    _h=h;
    _state=initstate;
    _dt=dt;
    _J=complex<double> (0,1);

}

void Timeevolver::time_fw(){
    if (_h->get_diagonalized()){
        for (int i=0;i < _h->get_dim();i++){
            (*_state)(i)=exp(-_J*_h->get_cxeigval()(i)*_dt)*(*_state)(i);
       }
    }
}

void Timeevolver::time_bw(){
    if (_h->get_diagonalized()){
        for (int i=0;i < _h->get_dim();i++){
            (*_state)(i)=exp(_J*_h->get_cxeigval()(i)*_dt)*(*_state)(i);
        }
    }
}
