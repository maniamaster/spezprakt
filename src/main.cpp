#include <hamiltonian.hpp>
#include <timeevolver.hpp>
#include <measurement.hpp>
#include <fstream>
#include <gnuplot-iostream.hpp>


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

void plot_lochschmidt_echo(Hamiltonian &h){
   Gnuplot loch1;
   vec initstate=init_right_up(&h);
   initstate=initstate/norm(initstate);
   cx_vec state=cx_vec(initstate,zeros(h.get_dim()));
   state=h.nat_2_eigen(state); //in eigenbasis transformieren
   cx_vec state_0=state;

//Plot von <Y(0)|Y(t)> :
    ofstream myfile;
    myfile.open("loch1.dat");
    
    //Test der Messung einzelner Spins:
   /*
    Measurement testMes(&h);
    cout << "Measurement of Sz_i before time translation:" <<endl; 
    for (int i=1;i<=h.get_system_size();i++)
       cout <<"S_"<<i<<" : "<<testMes.sz_i(&state,i)<<endl; 
    */
    
    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double dt=0.01;
    double t=0;
    double res=0;
    Timeevolver testTime(&h);
    res=norm(cdot(state_0,state));
    myfile << t << "\t" << res << endl;
    while (t<100){
        testTime.time_fw(&state,dt);
        t=t+dt;
        res=norm(cdot(state_0,state));
        myfile << t << "\t" << res << endl;
    }
    myfile.close();
   
    /*
    state.print("state in eigenbasis (complex): ");
    cout <<"norm des eigenbasisvektors: "<<norm(state)<<endl; 
    cx_vec natstate=h.eigen_2_nat(state);
    natstate.print("state in natbasis (complex): ");
    cout <<"norm des natbasisvektors: "<<norm(natstate)<<endl; 
    //erneutes Messen von Sz nach zeitentwicklung:
    cout << "Measurement of Sz_i after time translation:" <<endl; 
    for (int i=1;i<=h.get_system_size();i++)
       cout <<"S_"<<i<<" : "<<testMes.sz_i(&state,i)<<endl; 
    */ 
 
    //Gnulot Skript test:
    loch1 <<"reset"<<endl;
    loch1 <<"set term eps"<<endl;
    loch1 <<"set output \"loch1.eps\""<<endl;
    loch1 <<"set samples 2000"<<endl;
    loch1 <<"set linetype 10"<<endl;
    loch1 <<"set autoscale"<<endl;
    loch1 <<"p \"loch1.dat\" u 1:2  with points lc rgb \"red\" ps 0.1 "<<endl;
    loch1 <<"set output"<<endl;

}

void plot_sz(Hamiltonian &h){
    Gnuplot sz;
    vec initstate=init_right_up(&h);
    initstate=initstate/norm(initstate);
    cx_vec state=cx_vec(initstate,zeros(h.get_dim()));
    state=h.nat_2_eigen(state); //in eigenbasis transformieren
    cx_vec state_0=state;
    ofstream myfile;
    myfile.open("sz.dat");
    Measurement testMes(&h);
    Timeevolver testTime(&h);
    for (int i=1;i<=h.get_system_size();i++)
        myfile <<i<<"\t"<<testMes.sz_i(&state,i)<<endl;sz <<"reset"<<endl;
    myfile.close();
    sz <<"reset"<<endl;
    sz <<"set term eps"<<endl;
    sz <<"set output 'sz.eps'"<<endl;
    sz <<"set samples 2000"<<endl;
    sz <<"set yrange [-0.6:0.6]"<<endl;
    sz <<"p 'sz.dat' u 1:2  with points lc rgb \"red\" ps 1 "<<endl;
    sz <<"set output"<<endl;
 
    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double dt=0.1;
    double t=0;
    while (t<100){
        testTime.time_fw(&state,dt);
        t=t+dt;
        myfile.open("sz.dat");
        for (int i=1;i<=h.get_system_size();i++)
            myfile <<i<<"\t"<<testMes.sz_i(&state,i)<<endl;
        sz <<"reset"<<endl;
        sz <<"set term eps"<<endl;
        sz <<"set output 'sz.eps'"<<endl;
        sz <<"set samples 2000"<<endl;
        sz <<"p 'sz.dat' u 1:2  with points lc rgb \"red\" ps 1 "<<endl;
        sz <<"set output"<<endl;  
        myfile.close(); 
        sleep(1);
    }

   myfile.close();
}
//-------------------------------------------------------------------------------------------------------------------------------
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
    testHam.set_ham(2); // mu=0.5
    //testHam.print_hamiltonian();
    cout <<endl<<"<><><><><><><><><><><><><><><><>Diagonalisierung<><><><><><><><><><><><><><><>"<<endl<<endl;
    testHam.diagonalize();
    //testHam.print_diagonal();
    //testHam.print_eigval();
    //testHam.print_eigvec();
    
  

//Diagonalisierung Test:
    /*
    vec initstate=init_right_up(&testHam);
    //vec initstate(testHam.get_dim());
    //initstate.randu();
    initstate=initstate/norm(initstate);
    initstate.print("state in natural basis: ");
    
    cx_vec state=cx_vec(initstate,zeros(testHam.get_dim()));
   
    state.print("state in natural basis (complex): ");
    cout <<"norm des natvektors: "<<norm(state)<<endl;
    state=testHam.nat_2_eigen(state); //in eigenbasis transformieren
    state.print("state in eigenbasis (complex): "); 
    cout <<"norm des eigenbasisvektors: "<<norm(state)<<endl;

    cx_vec state_0=state;
    */ 

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
 
   //plot_lochschmidt_echo(testHam); 

   plot_sz(testHam);
//Plot von <Y(0)|Y(t)> :
    /*
    ofstream myfile;
    myfile.open("test.dat");
    
    //Test der Messung einzelner Spins:
    Measurement testMes(&testHam);
    cout << "Measurement of Sz_i before time translation:" <<endl; 
    for (int i=1;i<=testHam.get_system_size();i++)
       cout <<"S_"<<i<<" : "<<testMes.sz_i(&state,i)<<endl; 

    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
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
     
    state.print("state in eigenbasis (complex): ");
    cout <<"norm des eigenbasisvektors: "<<norm(state)<<endl; 
    cx_vec natstate=testHam.eigen_2_nat(state);
    natstate.print("state in natbasis (complex): ");
    cout <<"norm des natbasisvektors: "<<norm(natstate)<<endl; 
    //erneutes Messen von Sz nach zeitentwicklung:
    cout << "Measurement of Sz_i after time translation:" <<endl; 
    for (int i=1;i<=testHam.get_system_size();i++)
       cout <<"S_"<<i<<" : "<<testMes.sz_i(&state,i)<<endl; 
   
    plot_lochschmidt_echo();
   */ 
    
    
    
    return 0;
}
