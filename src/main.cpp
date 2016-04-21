#include <basis.hpp>
#include <hamiltonian.hpp>

int main()
{

    int N=4; //System size
    int m=0; //total magnetization counted in multiples of 1

    Hamiltonian testHam(N,m);

    testHam.print_system_size();
    testHam.print_basis_list();
    testHam.print_basis_dimension();
    
    //Test der Suchfunktion:
    int pos=0;
    for(int i=0;i<testHam.get_dim();i++){
        REP_TYPE state = testHam.get_state(i);
        pos = testHam.find_state(state); 
        cout <<"Position des integers: " <<state<<" ist: "<<pos<<endl;
    }

    return 0;
}
