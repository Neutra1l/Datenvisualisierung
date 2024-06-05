
#include <iostream>

using namespace std;


int main()
{
    float *ptr = new float [5];
    for(int i = 0 ; i<5; i++)
    {
        *ptr++ = i;
    }

    std::cout << ptr[3];

}
