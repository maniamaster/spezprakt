#include <basis.hpp>
#include <hamiltonian.hpp>

int main()
{
    Hamiltonian testHam(4,0);

    testHam.print_system_size();
    testHam.print_basis_list();
    testHam.print_basis_dimension();

    return 0;
}
