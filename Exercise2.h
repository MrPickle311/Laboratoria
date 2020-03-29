#ifndef EXERCISE_2_H
#define EXERCISE_2_H

#include <cmath>
#include "kwad.h"
#include <vector> //vector to kontener,który bardzo u³atwi to æwiczenie

long double function_1(long double x);

long double function_1_INTEGRAL(long double a, long double b);

long double function_2(long double x);

long double function_2_INTEGRAL(long double a, long double b);

long double function_3(long double x);

long double function_3_INTEGRAL(long double a, long double b);

long double function_4(long double x);

long double function_4_INTEGRAL(long double a, long double b);

long double function_5(long double x);

long double function_5_INTEGRAL(long double a, long double b);

long double function_6(long double x);

long double function_6_INTEGRAL(long double a, long double b);

struct Point { //punkt wykresu(wêze³)
	long double x;
	long double y;
};

// a - górna granica ca³kowania
// b - dolna granica ca³kowania
// n - liczba wêz³ów

void computeNodes(std::vector<Point>& points, long double a, long double b, INT precision);

// parametr precision odpowiada za dok³adnoœæ rysowania wykresu funkcji, jendak ma domyœln¹ wartoœæ równ¹ 1080,
// czyli mniej wiêcej co jeden piksel bêdzie obliczona wartoœæ funkcji
std::vector<Point> computeFunctionValues(long double a, long double b, long double (*function)(long double), INT precision = 1080);

long double measurementTrapezError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

long double measurementSimpsonError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

struct attempt { // struktura reprezentuj¹ca jeden pomiar
	INT64 nodeNmbr; // liczba wêz³ów
	long double msrError; // b³¹d miêdzy ca³kowaniem numerycznym , a analitycznym
};

// u¿ywam tutaj INT64(8 bajtów) ,gdy¿ æwiczenie wymaga podania iloœci prób w postaci 2^m , nale¿y pamiêtaæ ,¿e ten typ (jest bez znaku)
// przechowuje maksymalnie liczbê 2^64 * 2,wiêc nale¿y mieæ to na uwadze podaj¹c liczbê wêz³ów,oraz nale¿y mieæ na uwadze koszt obliczeniowy
std::vector<attempt> rtrnTrapezAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablicê pomiarów metod¹ trapezów
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

std::vector<attempt> rtrnSimpsonAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablicê pomiarów metod¹ Simpsona
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));


#endif //EXERCISE_2_H





