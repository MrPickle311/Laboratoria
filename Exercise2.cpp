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

// a - górna granica ca³kowania
// b - dolna granica ca³kowania
// n - liczba wêz³ów

void computeNodes(std::vector<Point>& points, long double from, long double to, INT precision) {
	long double distance = (to - from) / precision; // to > from
	long double presentPosition {from};
	for (auto& point : points) {
		if (presentPosition == 0.0000000) 
			presentPosition = 0.001;//zabezpieczenie ,chodzi o dziedzinê,gdy¿ wiele powy¿szych funkcji nie jest okreœlonych w 0
		else if (presentPosition >= to) //dodatkowe zabezpieczenie ,ale tylko graficzne 
			point.x = to;
		else {
			presentPosition += distance;
			point.x = presentPosition;
		}	
	}
}

// parametr precision odpowiada za dok³adnoœæ rysowania wykresu funkcji, jendak ma domyœln¹ wartoœæ równ¹ 1080,
// czyli mniej wiêcej co jeden piksel bêdzie obliczona wartoœæ funkcji
std::vector<Point> computeFunctionValues(long double from, long double to, long double (*function)(long double), INT precision) {
	// dzielê równomiernie przedzia³ a,b na "precision" wspó³rzêdnych x
	// u¿ywam tutaj kontenera std::vector , który jest zwyk³¹ tablic¹  dynamiczn¹, któr¹ zapewnia biblioteka standardowa
	// dziêki temu nie muszê samodzielnie alokowaæ oraz dealokowaæ pamiêci,kompilator zrobi to za mnie
	std::vector<Point> points{};//pusty kontener
	points.insert(points.begin(), precision, Point{ 0,0 }); // wype³niam kontener zaczynaj¹c od jego 0-wego elementu(begin()) n-t¹ iloœci¹ punktów
	// o wspó³rzêdnych (0,0);
	computeNodes(points, from, to, precision);
	for (Point& point : points) { // pêtla zakresowa, która wykonuje siê dla wszystkich elementów kontenera,dziêki jej u¿yciu nie muszê
	// siê przejmowaæ jego rozmiarem
		point.y = function(point.x);
	}
	return points;// dalej ten kontener idzie do interfejsu ,który wyœwietla wykres funkcji na podstawie tych punktów
}

long double measurementTrapezError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	return fabsl(trapez(a, b, function, nodeNmbr) - function_INTEGRAL(a, b));
}

long double measurementSimpsonError(long double a, long double b, INT64 nodeNmbr,
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	return fabsl(simpson(a, b, function, nodeNmbr) - function_INTEGRAL(a, b));
}

// u¿ywam tutaj INT64(8 bajtów) ,gdy¿ æwiczenie wymaga podania iloœci prób w postaci 2^m , nale¿y pamiêtaæ ,¿e ten typ (jest bez znaku)
// przechowuje maksymalnie liczbê 2^64 * 2,wiêc nale¿y mieæ to na uwadze podaj¹c liczbê wêz³ów,oraz nale¿y mieæ na uwadze koszt obliczeniowy
std::vector<attempt> rtrnTrapezAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablicê pomiarów metod¹ trapezów
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	std::vector<attempt> attemps{};
	INT attemptsNmbr{};
	if (nodeNmbr < 64)
		attemptsNmbr = nodeNmbr; // przypadek dla 2^m wêz³ów
	else //przypadek ,gdy zostanie podana konkretna liczba wêz³ów,
		attemptsNmbr = log2(nodeNmbr);
	attemps.insert(attemps.begin(), attemptsNmbr, attempt{});// zapis TYP_ZMIENNEJ nazwa_zmiennej {}; oznacza wykorzystanie domyœlnego
	//inicjalizatora zapewnianego przez kompilator ,dziêki temu uniknê u¿ycia niezainicjalizowanej pamiêci
	INT guardian{ 1 };
	for (auto& attempt : attemps) {
		attempt.nodeNmbr = guardian;
		attempt.msrError = measurementTrapezError(a, b, nodeNmbr, function, function_INTEGRAL);
	}
	return attemps;
}

std::vector<attempt> rtrnSimpsonAttempts(long double a, long double b, INT64 nodeNmbr, //funkcja zwraca tablicê pomiarów metod¹ Simpsona
	long double (*function)(long double), long double (*function_INTEGRAL)(long double a, long double b)) {
	std::vector<attempt> attemps{};
	INT attemptsNmbr{};
	if (nodeNmbr < 64)
		attemptsNmbr = nodeNmbr; // przypadek dla 2^m wêz³ów
	else //przypadek ,gdy zostanie podana konkretna liczba wêz³ów,
		attemptsNmbr = log2(nodeNmbr);
	attemps.insert(attemps.begin(), attemptsNmbr, attempt{});// zapis TYP_ZMIENNEJ nazwa_zmiennej {}; oznacza wykorzystanie domyœlnego
	//inicjalizatora zapewnianego przez kompilator ,dziêki temu uniknê u¿ycia niezainicjalizowanej pamiêci
	INT guardian{ 1 };
	for (auto& attempt : attemps) {
		attempt.nodeNmbr = guardian;
		attempt.msrError = measurementSimpsonError(a, b, nodeNmbr, function, function_INTEGRAL);
	}
	return attemps;
}