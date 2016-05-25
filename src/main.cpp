#include <hamiltonian.hpp>
#include <timeevolver.hpp>
#include <measurement.hpp>
#include <fstream>
#include <gnuplot-iostream.hpp>
#include <string>

    //***functions***
    //

cx_vec input_state(char* input,Hamiltonian* h){
    int N = h->get_system_size();
    REP_TYPE state=string_to_state(input,N);
    cout <<"state is: "<<endl;
    print_bits(state,N);
    int pos =h->find_state(state);
    vec res=vec(zeros(h->get_dim()));
    res(pos)=1;
    cx_vec cres=cx_vec(res,zeros(h->get_dim()));
    return cres;
}

cx_vec init_right_up(Hamiltonian* h){ //returns initial state vector with all spins up on the right
    REP_TYPE state=0;
    int n=((h->get_system_size())+(h->get_magnetization()))/2;
    for (int i=0;i<n;i++){
        state+=pow(2,i);  
    }

    int pos = h->find_state(state);
    vec res=vec(zeros(h->get_dim()));
    res=res/norm(res);
    res(pos)=1;
    cx_vec cres=cx_vec(res,zeros(h->get_dim()));
    return cres;
}

void plot_lochschmidt_echo(Hamiltonian *h,cx_vec state,double dt,double T){
    Gnuplot gp;
    state=h->nat_2_eigen(state); //in eigenbasis transformieren
    cx_vec state_0=state;

    ofstream myfile;

    myfile.open("loch1.dat");
    myfile << *h;
    myfile << "# T="<<T<<endl;
    myfile << "# dt="<<dt<<endl;
    
    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double t=0;
    double res=0;
    Timeevolver testTime(h);
    res=norm(cdot(state_0,state));
    myfile << t << "\t" << res << endl;
    while (t<T){
        testTime.time_fw(&state,dt);
        t=t+dt;
        res=norm(cdot(state_0,state));
        myfile << t << "\t" << res << endl;
    }
    myfile.close();
 
    //Gnulot Skript test:
    gp <<"reset"<<endl;
    gp <<"set term eps"<<endl;
    gp <<"set output \"loch1.eps\""<<endl;
    gp <<"set samples 2000"<<endl;
    gp <<"set linetype 10"<<endl;
    gp <<"set xrange [0:"<<T<<"]"<<endl;
    gp <<"p \"loch1.dat\" u 1:2  with lines lc rgb \"red\"  "<<endl;
    gp <<"set output"<<endl;

}

void plot_sz(Hamiltonian* h,cx_vec state,double dt,double T){
    int N=h->get_system_size();
    Gnuplot gp;
    state=h->nat_2_eigen(state); //in eigenbasis transformieren
    ofstream myfile;
    stringstream str;
    str <<"Sz_"<<h->get_lambda()<<"_"<<h->get_mu()<<".dat";
    myfile.open(str.str().c_str());

    Measurement testMes(h);
    Timeevolver testTime(h);

    myfile << *h;
    myfile << "# T="<<T<<endl;
    myfile << "# dt="<<dt<<endl;
    myfile << endl << "#<S_z>"<<endl;

    for (int i=0;i<N;i++)
        myfile <<testMes.sz_i(state,i)<<"\t";
    myfile<<endl;
    /*gp <<"reset"<<endl;
    gp <<"set term eps size 8in, 8in"<<endl;
    gp <<"set output '"<<str2.str()<<"'"<<endl;
    gp <<"set noborder"<<endl;
    gp <<"set autoscale xfix"<<endl;
    gp <<"set autoscale yfix"<<endl;
    gp <<"set autoscale cbfix"<<endl;
    gp <<"load 'RdBu.plt'"<<endl;
    gp <<"set palette negative"<<endl;
    */
    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double t=0;
    while (t<T){
        testTime.time_fw(&state,dt);
        t=t+dt;
        for (int i=0;i<N;i++)
            myfile << testMes.sz_i(state,i)<<"\t";
        myfile << endl;
    }
    /*gp <<"p '"<<str.str()<<"' matrix with image notitle" <<endl;
    gp <<"set output"<<endl;  
    */
    myfile.close(); 
}

void plot_szsz_n(Hamiltonian* h,cx_vec state,int n,double dt, double T){
    int N=h->get_system_size();
    Gnuplot gp;
    state=h->nat_2_eigen(state); //in eigenbasis transformieren
    ofstream myfile;
    stringstream str;
    str <<"SzSz_"<<h->get_lambda()<<"_"<<h->get_mu()<<".dat";
    myfile.open(str.str().c_str());

    Measurement testMes(h);
    Timeevolver testTime(h);

    myfile << *h;
    myfile << "# T="<<T<<endl;
    myfile << "# dt="<<dt<<endl;
    myfile << "# n="<<n<<endl;
    myfile << endl << "#<S_z*S_z+n>"<<endl;

    for (int i=0;i<N;i++){
        myfile <<testMes.sz_i_sz_in(state,i,n)<<"\t";
    }
    myfile<<endl;
    /*gp <<"reset"<<endl;
    gp <<"set term eps size 8in, 8in"<<endl;
    gp <<"set output '"<<str2.str()<<"'"<<endl;
    gp <<"set noborder"<<endl;
    gp <<"set noborder"<<endl;
    gp <<"set autoscale xfix"<<endl;
    gp <<"set autoscale yfix"<<endl;
    gp <<"set autoscale cbfix"<<endl;
    gp <<"load 'RdBu.plt'"<<endl;
    gp <<"set palette negative"<<endl;
    */ 
    //time translation:
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double t=0;
    while (t<T){
        testTime.time_fw(&state,dt);
        t=t+dt;
        for (int i=0;i<N;i++){
            myfile <<testMes.sz_i_sz_in(state,i,n)<<"\t";
        }
        myfile << endl;
    }
    /*
    gp <<"p '"<<str.str()<<"' matrix with image notitle" <<endl;
    gp <<"set output"<<endl;  
    */
    myfile.close(); 
}

void plot_kurz(Hamiltonian* h,cx_vec state,double dt, double T){
    //Gnuplot gp;
    int N=h->get_system_size();
    state=h->nat_2_eigen(state); //in eigenbasis transformieren
    ofstream myfile;
    stringstream str;
    if (N<10)
        str <<"kurzzeit_0"<<N<<".dat";
    else
        str <<"kurzzeit_"<<N<<".dat";
    myfile.open(str.str().c_str());
    Measurement testMes(h);
    Timeevolver testTime(h);
    myfile << *h;
    myfile <<"# T="<<T<<endl;
    myfile <<"# dt="<<dt<<endl;
    myfile << endl << "# t \t <S_z,1>"<<endl;
    cout <<endl<<"<><><><><><><><><><><><><><><><>Zeitentwicklung<><><><><><><><><><><><><><><>"<<endl<<endl;
    double t=0;
    double res=0;
    res = testMes.sz_i(state,1);
    myfile << t << "\t" << res << endl; 
    while (t<T){
        testTime.time_fw(&state,dt);
        t=t+dt;
        res = testMes.sz_i(state,1);
        myfile << t << "\t" << res << endl;
    }
    /*
    gp <<"reset"<<endl;
    gp <<"set term eps"<<endl;
    gp <<"set output \"kurzzeit.eps\""<<endl;
    gp <<"set samples 2000"<<endl;
    gp <<"set linetype 10"<<endl;
    gp <<"set xrange [0:"<<T<<"]"<<endl;
    gp <<"set yrange [-1:1]"<<endl;
    gp <<"f(x)=-0.5+0.5*x**2"<<endl;
    
    gp <<"p \"kurzzeit.dat\" u 1:2  with lines lc rgb \"red\",f(x),-0.5*besj0(2*x)"<<endl;
    gp <<"set output"<<endl;
    */
    myfile.close();
}
    
  
//============================================================================================================
int main()
{
    
    int N; //system size
    cout <<"set system size: ";
    cin >>N;
    
    int m; //total magnetization counted in multiples of 1
    cout <<"set total magnetization (in multiples of 1/2): ";
    cin >>m;
    
    cout <<endl;


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

    char test[testHam.get_system_size()];
    cout << "insert initial state:"<<endl;
    cin.ignore();
    cin.getline(test,testHam.get_system_size()+1);
    cx_vec state=input_state(test,&testHam);
    cout <<"vector is: "<<endl;
    cout << state <<endl;

    
    double T=60;
    double dt=0.01;
    
    double mu=0;
    double lambda=0;
    /*
    while (lambda <= 1){
        testHam.set_ham(mu,lambda); // mu=0,Lambda=0
        cout <<endl<<"<><><><><><><><><><><><><><><><>diagonalisierung<><><><><><><><><><><><><><><>"<<endl<<endl;
        testHam.diagonalize();
        plot_sz(&testHam,state,dt,T);
        T-=5;
        lambda+=0.1;
    } 
    */
    testHam.set_ham(0,0);
    cout <<endl<<"<><><><><><><><><><><><><><><><>diagonalisierung<><><><><><><><><><><><><><><>"<<endl<<endl;
    testHam.diagonalize();
    plot_kurz(&testHam,state,0.01,10);
    //plot_lochschmidt_echo(&testHam,state,0.01,10);  //(ham,dt,T)
    
    //plot_szsz_n(&testHam,state,1,0.1,10); //(ham,n,dt,T)

  /*int i=0;
    for (;;){
        cout << "enter component:"<<endl;
        cin.ignore();
        cin >> i;
        cout << i<<" th spin is "<<get_sz(string_to_state(test,testHam.get_system_size()),i,testHam.get_system_size())*1/2.<<endl;
    }
  */  

    return 0;
}
