#include "bigint.hpp"

int main(void)
{
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);
	// base test
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;

	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "a + c = " << a + c << std::endl;
	std::cout << "a + d = " << a + d << std::endl;
	bigint int_max(2147483647);
	std::cout << "int_max + int_max  = " << int_max + int_max << std::endl;
	std::cout << "int_max + int_max + int_max + int_max  = " << int_max + int_max + int_max + int_max << std::endl;
	bigint int_min(-2147483648);
	std::cout << "int_min + int_max  = " << int_min + int_max << std::endl;
	std::cout << "int_min + int_min  = " << int_min + int_min << std::endl;
	c += a;
	std::cout << "(c += a) = " << c << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;
	std::cout << "b = " << b << std::endl;

	// b = 23, b << 10 -> 23000000000 + 42 = 23000000042
	std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << ", d: " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << ", d: " << d << std::endl;

	std::cout << "a = " << a << std::endl; // a = 42
	std::cout << "d = " << d << std::endl; // d = 5348

	std::cout << "(d < a) = " << (d < a) << std::endl; // (d < a) = 0
	std::cout << "(d > a) = " << (d > a) << std::endl; // (d > a) = 1
	std::cout << "(d == d) = " << (d == d) << std::endl; // (d == d) = 1
	std::cout << "(d != a) = " << (d != a) << std::endl; // (d != a) = 1
	std::cout << "(d <= a) = " << (d <= a) << std::endl; // (d <= a) = 0
	std::cout << "(d >= a) = " << (d >= a) << std::endl; // (d >= a) = 1

	bigint h(9099);
	bigint j(10000);
	std::cout << "(h > j) = " << (h > j) << "\n"; // (h > j) == 0
	std::cout << "(h >= j) = " << (h >= j) << "\n"; // (h >= j) == 0
	std::cout << "(h < j) = " << (h < j) << "\n"; // (h < j) == 1
	std::cout << "(h <= j) = " << (h <= j) << "\n"; // (h <= j) == 1

	// extra
	bigint x(12345678); bigint y(5);
	std::cout << "(x << y) = " << (x << y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >>= y) = " << (x >>= y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	std::cout << "x= " << (x <<= 5) << ", y= " << (y <<= 12) << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;
	return (0);
}