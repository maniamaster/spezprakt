#include <hamiltonian.hpp>
#include <timeevolver.hpp>
#include <measurement.hpp>
#include <fstream>


    //***functions***
    //
vec init_right_up(Hamiltonian* h){ //returns initial state vector with all spins up on the right
    REP_TYPE state=0;
    int n=((h->get_system_size())+(h->get_magnetization()))/2;
    for (int i=0;i<n;i++){
        state+=pow(2,i);  
    }

    int pos = h->find_state(state);
    vec res=vec(zeros(h->get_dim()));
    res(pos)=1;
    return res;
}



int main()
{

    int N; //system size
    cout <<"set system size: ";
    cin >>N;
    
    int m; //total magnetization counted in multiples of 1
    cout <<"set total magnetization (in multiples of 1/2): ";
    cin >>m;
    cout <<"\n";

    bool testpos=0; //test the position finder of the states. Set to 1 for test.

    Hamiltonian testHam(N,m);

    
    //Test der Suchfunktion:
    
    if (testpos){
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
    

    cout <<"\n";
    testHam.print_basis_list();
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
    vec initstate=init_right_up(&testHam);
    //vec initstate(testHam.get_dim());
    //initstate.randu();
    initstate=initstate/norm(initstate);
    initstate.print("state in natural basis: ");
    
    cx_vec state=cx_vec(initstate,zeros(testHam.get_dim()));
   
    state.print("state in natural basis (complex): ");

    state=testHam.nat_2_eigen(state); //in eigenbasis transformieren
    
    state.print("state in eigenbasis (complex): ");
    
    cx_vec state_0=state;
    

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

    

    //Test der Messung einzelner Spins:
    Measurement testMes(&testHam);
    for (int i=1;i<=testHam.get_system_size();i++)
       cout <<"S_"<<i<<" : "<<testMes.sz_i(&state,i)<<endl; 





    double dt=0.01;
    double t=0;
    double res=0;
    Timeevolver testTime(&testHam);
    res=norm(cdot(state_0,state));
    myfile << t << "\t" << res << endl;
    while (t<100){
        testTime.time_fw(&state,dt);
        t=t+dt;
        res=norm(cdot(state_0,state));
        myfile << t << "\t" << res << endl;
    }
    myfile.close();

    return 0;
}
