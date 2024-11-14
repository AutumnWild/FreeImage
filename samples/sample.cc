#include <iostream>
#include "FreeImage.h"
int main(int argc, char const *argv[])
{
    const char * freeimageVer  = FreeImage_GetVersion( ) ;
    std::  cout << "freeimageVer = " << freeimageVer <<std:: endl;
    return 0;
}
