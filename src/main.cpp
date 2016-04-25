#include <basis.hpp>
#include <hamiltonian.hpp>

int main()
{
    int N; //system size
    cout <<"set system size: ";
    cin >>N;
    
    int m; //total magnetization counted in multiples of 1
    cout <<"set total magnetization (in multiples of 1/2): ";
    cin >>m;
    cout <<"\n";

    bool testpos=1; //test the position finder of the states. Set to 1 for test.

    Hamiltonian testHam(N,m);

    //testHam.print_system_size();
    //testHam.print_basis_list();
    //testHam.print_basis_dimension();
    
    //Test der Suchfunktion:
    if (testpos){
        int pos=0;
        char* out;
         for(int i=0;i<testHam.get_dim();i++){
             REP_TYPE state = testHam.get_state(i);
             pos = testHam.find_state(state); 
             out = int2bin(state,NULL);
             out = &(out[sizeof(REP_TYPE)*CHAR_BIT - N]); //cutoff string, borrowed from utilities.c
             cout <<"integer: " <<state<<" binary: "<<out<<" pos: "<<pos<<endl;
         }
    }
    
    cout <<"\n";
    testHam.print_system_size();
    testHam.print_basis_dimension();
    cout <<"\n";

    //Hamiltonian matrix test:
    testHam.set_ham(0.5);
    testHam.print_matrix();
    return 0;
}
