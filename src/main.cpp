#include <basis.hpp>

int main()
{
    Basis testBasis(3,0);

    testBasis.print_system_size();
    testBasis.generate_basis_list();
    testBasis.print_basis_list();
    return 0;
}
