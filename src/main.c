#include <stdio.h>
#include "Lab_0.h"



int main (int argc, char** argv)
{
    const uint32_t addThis = 42;
    runStaticFunction(addThis);
    runStaticFunction(addThis);
    runStaticFunction(addThis);

    // Since the function is static, its scope is local only to 
    // the Lab_0.c translation unit.  
    //
    // Since the variable inside the function is static (baseNum) 
    // it will maintain its value across successive calls to the function
    // regardless of when that function goes out of scope


    return 0;
}

