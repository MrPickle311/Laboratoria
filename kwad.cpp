#include <math.h>
#include "kwad.h"

using INT = uint_fast32_t; // wydajnieszy 32-bitowy(4 bajty) typ unsigned int
using INT64 = uint_fast64_t; // wydajnieszy 64-bitowy(8 bajtów) typ unsigned int

INT abs(INT param) { // przeci¹¿y³em funkcjê abs dla typu INT
    return param ? param > 0 : -1 * param;
}

INT64 abs(INT64 param) { // przeci¹¿y³em funkcjê abs dla typu INT
    return param ? param > 0 : -1 * param;
}

// oblicza calke metoda trapezow
double trapez(double a, double b, double (*pf)(double), INT n){
    double h = (b - a) / (n - 1);
    double sum = 0.5 * (pf(a) + pf(b));
    double x = a;

    for (int i = 1; i < n - 1; ++i){
        x += h;
        sum += pf(x);
    }
    return sum * h;
}

long double trapez(long double a, long double b, long double(*pf)(long double), INT64 n) {
    long double h = (b - a) / (n - 1);
    long double sum = 0.5 * (pf(a) + pf(b));
    long double x = a;

    for (INT64 i = 1; i < n - 1; ++i) {
        x += h;
        sum += pf(x);
    }
    return sum * h;
}

long double simpson(long double a, long double b, long double(*pf)(long double), INT64 n){//dla du¿ych liczb
    long double   x = a;
    INT64         nc = abs((n - 2) / 2 + 1) * 2 + 1;  // poprawione n tak by bylo nieparzyste i >= n_old
    long double   h = (b - a) / (nc - 1);             // dla du¿ych liczb,du¿y koszt
    long double   h2 = h * 2;
    long double   sum = pf(a) + 4. * pf(a + h) + pf(b);

    for (INT64 i = 3; i < nc; i += 2) {
        x += h2;
        sum += 2. * pf(x) + 4. * pf(x + h);
    }
    return sum * h / 3.;
}

// oblicza calke metoda simpsona
double simpson(double a, double b, double (*pf)(double), INT n){
    double   x = a;
    INT      nc = abs((n - 2) / 2 + 1) * 2 + 1;  // poprawione n tak by bylo nieparzyste i >= n_old
    double   h = (b - a) / (nc - 1);            
    double   h2 = h * 2;
    double   sum = pf(a) + 4. * pf(a + h) + pf(b);

    for (INT i = 3; i < nc; i += 2){
        x += h2;
        sum += 2. * pf(x) + 4. * pf(x + h);
    }
    return sum * h / 3.;
}


