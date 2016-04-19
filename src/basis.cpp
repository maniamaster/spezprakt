#include <basis.hpp>

Basis::Basis(int N)
{
	_N=N;
}

void Basis::print_system_size()
{
	cout << "the system size is " << _N << endl;
	
}
