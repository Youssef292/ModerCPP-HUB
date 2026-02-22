#include "StringPhares_StringView.hpp"
#include <sstream>

class counter
{
    private:
    
};
int main(void)
{
    
    counter c1;
    ++c1;
    ++c1;
    c1++;
    c1++;
    std::cout << c1.getCount() << std::endl;

    return 0;
}