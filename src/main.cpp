#include <basis.hpp>

int main()
{
    Basis testBasis(4,0);

    testBasis.print_system_size();
    testBasis.generate_basis_list();
    return 0;
}
