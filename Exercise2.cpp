#include "Exercise2.h"

long double function_1(long double x) {
	return (pow(x, 3.0) - pow(x, 2.0) + 3.0) / (pow(x, 4.0) + pow(x, 2.0));
}

long double function_1_INTEGRAL(long double to, long double from) {
	return -3 / to + 0.5 * log(pow(to, 2.0) + 1.0) - 4.0 * atan(to) - (-3.0 / from + 0.5 * log(pow(from, 2.0) + 1.0) - 4.0 * atan(from));
}//x != 0

long double function_2(long double x) {
	return 5 * pow(sin(x), 5) * pow(cos(x), 4);
}

long double function_2_INTEGRAL(long double to, long double from) {
	return pow(cos(4.0 * to), 5) / -4.0 + 5.0 * pow(cos(4.0 * to), 7) / 14.0 - 5.0 * pow(cos(4.0 * to), 9) / 36.0 -
		pow(cos(4.0 * from), 5) / -4.0 + 5.0 * pow(cos(4.0 * from), 7) / 14.0 - 5.0 * pow(cos(4.0 * from), 9) / 36.0;
}

long double function_3(long double x) {
	return pow(asin(x), 2.0);
}//x<-1,1>

long double function_3_INTEGRAL(long double a, long double b) {
	return 2 * sqrt(1 - pow(a, 2)) * asin(a) - 2.0 * a + a * pow(asin(a), 2) -
		(2 * sqrt(1 - pow(b, 2)) * asin(b) - 2.0 * b + b * pow(asin(a), 2));
}//x<-1,1>

long double function_4(long double x) {
	return pow(x, 2) * exp(x);
}

long double function_4_INTEGRAL(long double a, long double b) {
	return exp(a) * (pow(a, 2) - 2.0 * a + 2.0) - (exp(b) * (pow(b, 2) - 2.0 * b + 2.0));
}

long double function_5(long double x) {
	return 1.0 / x;
}

long double function_5_INTEGRAL(long double a, long double b) {
	return log(fabsl(a)) - log(fabsl(b));
}

long double function_6(long double x) {
	return 1.0 / pow(x, 2);
}

long double function_6_INTEGRAL(long double a, long double b) {
	return -1.0 / a + 1.0 * b;
}

// a - g�rna granica ca�kowania
// b - dolna granica ca�kowania
// n - liczba w�z��w

void computeNodes(std::vector<Point>& points, long double from, long double to, INT precision) {
	long double distance = (to - from) / precision; // to > from
	long double presentPosition {from};
	for (auto& point : points) {
		if (presentPosition == 0.0000000) 
			presentPosition = 0.001;//zabezpieczenie ,chodzi o dziedzin�,gdy� wiele powy�szych funkcji nie jest okre�lonych w 0
		else if (presentPosition >= to) //dodatkowe zabezpieczenie ,ale tylko graficzne 
			point.x = to;
		else {
			presentPosition += distance;
			point.x = presentPosition;
		}	
	}
}

// parametr precision odpowiada za dok�adno�� rysowania wykresu funkcji, jendak ma domy�ln� warto�� r�wn� 1080,
// czyli mniej wi�cej co jeden piksel b�dzie obliczona warto�� funkcji
std::vector<Point> computeFunctionValues(long double from, long double to, long double (*function)(long double), INT precision) {
	// dziel� r�wnomiernie przedzia� a,b na "precision" wsp�rz�dnych x
	// u�ywam tutaj kontenera std::vector , kt�ry jest zwyk�� tablic�  dynamiczn�, kt�r� zapewnia biblioteka standardowa
	// dzi�ki temu nie musz� samodzielnie alokowa� oraz dealokowa� pami�ci,kompilator zrobi to za mnie
	std::vector<Point> points{};//pusty kontener
	points.insert(points.begin(), precision, Point{ 0,0 }); // wype�niam kontener zaczynaj�c od jego 0-wego elementu(begin()) n-t� ilo�ci� punkt�w
	// o wsp�rz�dnych (0,0);
	computeNodes(points, from, to, precision);
	for (Point& point : points) { // p�tla zakresowa, kt�ra wykonuje si� dla wszystkich element�w kontenera,dzi�ki jej u�yciu nie musz�
	// si� przejmowa� jego rozmiarem
		point.y = function(point.x);
	}
	return points;// dalej ten kontener idzie do interfejsu ,kt�ry wy�wietla wykres funkcji na podstawie tych punkt�w
}

long double measurementTrapezError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	return fabsl(trapez(a, b, function, nodeNmbr) - function_INTEGRAL(a, b));
}

long double measurementSimpsonError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	return fabsl(simpson(a, b, function, nodeNmbr) - function_INTEGRAL(a, b));
}

// u�ywam tutaj INT64(8 bajt�w) ,gdy� �wiczenie wymaga podania ilo�ci pr�b w postaci 2^m , nale�y pami�ta� ,�e ten typ (jest bez znaku)
// przechowuje maksymalnie liczb� 2^64 * 2,wi�c nale�y mie� to na uwadze podaj�c liczb� w�z��w,oraz nale�y mie� na uwadze koszt obliczeniowy
std::vector<attempt> rtrnTrapezAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablic� pomiar�w metod� trapez�w
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	std::vector<attempt> attemps{};
	INT attemptsNmbr{};
	if (nodeNmbr < 64)
		attemptsNmbr = nodeNmbr; // przypadek dla 2^m w�z��w
	else //przypadek ,gdy zostanie podana konkretna liczba w�z��w,
		attemptsNmbr = log2(nodeNmbr);
	attemps.insert(attemps.begin(), attemptsNmbr, attempt{});// zapis TYP_ZMIENNEJ nazwa_zmiennej {}; oznacza wykorzystanie domy�lnego
	//inicjalizatora zapewnianego przez kompilator ,dzi�ki temu unikn� u�ycia niezainicjalizowanej pami�ci
	INT guardian{ 1 };
	for (auto& attempt : attemps) {
		attempt.nodeNmbr = guardian;
		attempt.msrError = measurementTrapezError(a, b, nodeNmbr, function, function_INTEGRAL);
	}
	return attemps;
}

std::vector<attempt> rtrnSimpsonAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablic� pomiar�w metod� Simpsona
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	std::vector<attempt> attemps{};
	INT attemptsNmbr{};
	if (nodeNmbr < 64)
		attemptsNmbr = nodeNmbr; // przypadek dla 2^m w�z��w
	else //przypadek ,gdy zostanie podana konkretna liczba w�z��w,
		attemptsNmbr = log2(nodeNmbr);
	attemps.insert(attemps.begin(), attemptsNmbr, attempt{});// zapis TYP_ZMIENNEJ nazwa_zmiennej {}; oznacza wykorzystanie domy�lnego
	//inicjalizatora zapewnianego przez kompilator ,dzi�ki temu unikn� u�ycia niezainicjalizowanej pami�ci
	INT guardian{ 1 };
	for (auto& attempt : attemps) {
		attempt.nodeNmbr = guardian;
		attempt.msrError = measurementSimpsonError(a, b, nodeNmbr, function, function_INTEGRAL);
	}
	return attemps;
}