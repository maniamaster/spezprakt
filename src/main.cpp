#include <hamiltonian.hpp>
#include <timeevolver.hpp>
#include <fstream>

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

    testHam.print_basis_list();
    testHam.print_system_size();
    testHam.print_basis_dimension();
    
    //Test der Suchfunktion:
    
   /* if (testpos){
        int pos=0;
        char* out;
         for(int i=0;i<testHam.get_dim();i++){
             REP_TYPE state = testHam.get_basis_state(i);
             pos = testHam.find_state(state); 
             out = int2bin(state,NULL);
             out = &(out[sizeof(REP_TYPE)*CHAR_BIT - N]); //cutoff string, borrowed from utilities.c
             cout <<"integer: " <<state<<" binary: "<<out<<" pos: "<<pos<<endl;
         }
    }
   */ 

    cout <<"\n";
    testHam.print_system_size();
    testHam.print_basis_dimension();
    cout <<"\n";

    //Hamiltonian matrix test:
    testHam.set_ham(0.5);
    //testHam.print_hamiltonian();
    testHam.diagonalize();
    //testHam.print_diagonal();
    //testHam.print_eigval();
    //testHam.print_eigvec();
    
    //Diagonalisierung Test:
    vec initstate(testHam.get_dim());
    initstate.randu();
    initstate=initstate/norm(initstate);
   // initstate.print("state in natural basis: ");
    vec eigenstate=testHam.nat_2_eigen(initstate);

    //Zeitentwicklung Test:
   /* 
    cx_vec  complstate=cx_vec(eigenstate,zeros(testHam.get_dim()));
    complstate.print("converted to complex vector: ");
    double dt;
    double t=0;
    for(;;){
        cout << "insert time interval:"<<endl;
        cin.clear();
        cin >> dt;
        t=t+dt;
        complstate=testHam.time_translate(complstate,dt);
        cout << "t= " <<t<<" :"<<endl<<complstate<<endl;
    }
   */ 
    
    //Plot von <Y(0)|Y(t)> :
    ofstream myfile;
    myfile.open("test.dat");

    cx_vec state=cx_vec(eigenstate,zeros(testHam.get_dim()));
    cx_vec state_0=state;;
   

    double dt=0.01;
    double t=0;
    double res=0;
    Timeevolver testTime(&testHam,&state,dt);
    while (t<10){
        testTime.time_fw();
        res=norm(cdot(state_0,state));
        myfile << t << "\t" << res << endl;
        t=t+dt;
    }
    myfile.close();

    return 0;
}
