#include <hamiltonian.hpp>

Hamiltonian::Hamiltonian(int N,int m){
    _N=N;
    _m=m;
    _set=0;
    generate_basis_list();
    fill();

}

void Hamiltonian::set_ham(){
    int j=0; 
    int b=0; //position of flipped state
    REP_TYPE flipstate=0;
    for (int a=0;a<_dim;a++){
        cout <<"a= "<<a<<endl;
        for (int i=0;i<_N;i++){
            j=(i+1)%_N;
            if (compare_bits(_list[a],i,_list[a],j,_N)){
                cout <<"i= "<<i<<endl;
                _ham(a,a)+=double(1/4.);
            }
            else{
                _ham(a,a)-=double(1/4.);
                flipstate=swap_bits(_list[a],_N,i,j);
                b=find_state(flipstate);
                _ham(a,b)=double(1/2.);
            }
        }
    }
    _set=1;
}

void Hamiltonian::fill(){
    _ham=mat(_dim,_dim,fill::zeros);
}

void Hamiltonian::print_matrix(){
    if (_set)
        cout << _ham<<endl;
    else
        cout << "Hamiltonian has not yet been set up."<<endl;
}
    
