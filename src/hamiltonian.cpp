#include <hamiltonian.hpp>


Hamiltonian::Hamiltonian(int N,int m){
    _N=N;
    _m=m;
    _lambda=0;
    _set=0;
    _diagonalized=0;
    generate_basis_list();
    fill();

}

void Hamiltonian::set_ham(double mu){
    int j=0; 
    int k=0;
    int b=0; //position of flipped state
    REP_TYPE flipstate=0;
    for (int a=0;a<_dim;a++){
        for (int i=0;i<_N;i++){
            j=(i+1)%_N;
            if (compare_bits(_list[a],i,_list[a],j,_N)){
                _ham(a,a)+=mu*double(1/4.);
            }
            else{
                _ham(a,a)-=mu*double(1/4.);
                flipstate=swap_bits(_list[a],_N,i,j);
                b=find_state(flipstate);
                _ham(a,b)+=double(1/2.);
            }
            k=(i+2)%_N;
            if (compare_bits(_list[a],i,_list[a],k,_N)){
                _ham(a,a)+=_lambda*mu*double(1/4.);
            }
            else{
                _ham(a,a)-=_lambda*mu*double(1/4.);
                flipstate=swap_bits(_list[a],_N,i,k);
                b=find_state(flipstate);
                _ham(a,b)+=_lambda*double(1/2.);
            }
        }
    }
    _set=1;
}

void Hamiltonian::fill(){
    _ham=mat(_dim,_dim,fill::zeros);
}

void Hamiltonian::print_hamiltonian(){
    if (_set){
        _ham.print("H=");
    }
    else
        cout << "Hamiltonian has not yet been set up."<<endl;
}

void Hamiltonian::diagonalize(){
    
    eig_sym(_eigval,_eigvec,_ham);

    _diag = _eigvec.t()*_ham*_eigvec;
    _cxeigval = cx_vec(_eigval,zeros(_dim));

    _diagonalized=1;

}

void Hamiltonian::print_diagonal(){
    if (_diagonalized)
        _diag.print("P^(-1)*H*P=");
    else
        cout << "Hamiltonian not yet diagonalied."<<endl;

}

void Hamiltonian::print_eigenvalues(){
    if (_diagonalized)
        _eigval.print("eigenvalues: ");
    else
        cout << "Hamiltonian not yet diagonalied."<<endl;
}

void Hamiltonian::print_eigenvectors(){
    if (_diagonalized)
        _eigvec.print("P= ");
    else
        cout << "Hamiltonian not yet diagonalied."<<endl;
}

vec Hamiltonian::nat_2_eigen(vec natvec){ 
    if (_diagonalized){
        vec res= _eigvec.t()*natvec;
        return res;
    } 
    cout << "Hamiltonian not yet diagonalied."<<endl;
    return natvec;
}

vec Hamiltonian::eigen_2_nat(vec eigenbasisvec){ 
    if (_diagonalized){
        vec res= _eigvec*eigenbasisvec;
        return res;
    } 
    cout << "Hamiltonian not yet diagonalied."<<endl;
    return eigenbasisvec;
}

cx_vec Hamiltonian::time_translate(cx_vec state,double dt){
    if (_diagonalized){
        complex<double> J= complex<double> (0,1) ;
        for (int i=0;i<_dim;i++){
            state(i)=exp(-J*_cxeigval(i)*dt)*state(i);
        }
        return state;
    }
    cout << "not diagonalized yet."<<endl;
    return state;
}
