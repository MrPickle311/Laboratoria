#ifndef EXERCISE_2_H
#define EXERCISE_2_H

#include <cmath>
#include "kwad.h"
#include <vector> //vector to kontener,kt�ry bardzo u�atwi to �wiczenie

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

struct Point { //punkt wykresu(w�ze�)
	long double x;
	long double y;
};

// a - g�rna granica ca�kowania
// b - dolna granica ca�kowania
// n - liczba w�z��w

void computeNodes(std::vector<Point>& points, long double a, long double b, INT precision);

// parametr precision odpowiada za dok�adno�� rysowania wykresu funkcji, jendak ma domy�ln� warto�� r�wn� 1080,
// czyli mniej wi�cej co jeden piksel b�dzie obliczona warto�� funkcji
std::vector<Point> computeFunctionValues(long double a, long double b, long double (*function)(long double), INT precision = 1080);

long double measurementTrapezError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

long double measurementSimpsonError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

struct attempt { // struktura reprezentuj�ca jeden pomiar
	INT64 nodeNmbr; // liczba w�z��w
	long double msrError; // b��d mi�dzy ca�kowaniem numerycznym , a analitycznym
};

// u�ywam tutaj INT64(8 bajt�w) ,gdy� �wiczenie wymaga podania ilo�ci pr�b w postaci 2^m , nale�y pami�ta� ,�e ten typ (jest bez znaku)
// przechowuje maksymalnie liczb� 2^64 * 2,wi�c nale�y mie� to na uwadze podaj�c liczb� w�z��w,oraz nale�y mie� na uwadze koszt obliczeniowy
std::vector<attempt> rtrnTrapezAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablic� pomiar�w metod� trapez�w
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));

std::vector<attempt> rtrnSimpsonAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablic� pomiar�w metod� Simpsona
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b));


#endif //EXERCISE_2_H





