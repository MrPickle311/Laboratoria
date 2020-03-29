#ifndef KWAD_H
#define KWAD_H
#include <iostream>

using INT = uint_fast32_t; // wydajnieszy 32-bitowy(4 bajty) typ unsigned int
using INT64 = uint_fast64_t; // wydajnieszy 64-bitowy(8 bajtów) typ unsigned int

//////////////////////////////////////////////////////////////////
// oblicza metoda trapezow calke funkcji pf w przedziale <a,b> 
// w oparciu o n punktow (n >= 2)
//////////////////////////////////////////////////////////////////
double trapez( double a, double b, double (*pf)(double), INT n);

//////////////////////////////////////////////////////////////////
// oblicza metoda simpsona calke funkcji pf w przedziale <a,b> 
// w oparciu o n punktow (n >= 2)
//////////////////////////////////////////////////////////////////
double simpson( double a, double b, double (*pf)(double), INT n);

/////////////////Przeci¹¿one funkcje by zyskaæ wiêksz¹ precyzjê
long double trapez(long double a,long double b,long double (*pf)(long double), INT64 n);
long double simpson(long double a, long double b,long double (*pf)(long double), INT64 n);
#endif // KWAD_H