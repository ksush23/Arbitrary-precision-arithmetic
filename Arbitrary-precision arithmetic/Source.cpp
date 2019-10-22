#include "Integer.h"
#include <iostream>

using namespace math;

Integer gcdXY(Integer a, Integer b, Integer &x, Integer &y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	Integer x1, y1;
	Integer d = gcdXY(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
Integer gcd(Integer a, Integer b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

Integer findX(Integer num[], Integer rem[], Integer k) {
	Integer M("1");
	for (int i = 0; i < k; i++) {
		M = M * rem[i];
	}
	Integer X("0");
	for (int i = 0; i < k; i++) {
		Integer Mi = M / rem[i];
		Integer x, y;
		Integer g = gcdXY(Mi, rem[i], x, y);
		x = (x % rem[i] + rem[i]) % rem[i];
		X = X + (num[i] * Mi * x);
	}
	return X % M;
}

int main()
{
	Integer a("12345678901234567890234567890345678");
	Integer b("123456789");
	Integer c("3");
	Integer d("24523748428234567");
	Integer f("7");

	Integer num[] = { 1, 3, 2 }, rem[] = { 4, 5, 7 };
	Integer x = findX(num, rem, 3);

	Integer num1[] = { 2, 5, 5, 6 }, rem1[] = { 7, 8, 9, 11 };
	Integer x1 = findX(num1, rem1, 4);
	Integer mod("98723459723");
	std::cout << a << " " << d << " " << (a * d) << "\n" << (a * d / d) << "\n";
	std::cout << x << "\n";
	std::cout << x1 << "\n";
	std::cout << (c % f) << "\n";
	std::cout << (a ^ c) << "\n";
	std::cout << (c.pow_mod(10, f)) << "\n";
	std::cout << (d.pow_mod(650, mod)) << "\n";
	std::cout << (a + b) << " " << (a * b) << "\n";
	std::cout << (a < b) << ' ' << (a > b) << ' ' << (a == b) << "\n";
	std::cout << (a.plus_mod(b, 1000000000000)) << "\n";

	system("pause");
	return 0;
}