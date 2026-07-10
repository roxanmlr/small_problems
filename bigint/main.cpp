 #include "bigint.hpp"
 #include <cassert>

void test_add(int a, int b, int expected)
{
	bigint x(a);
	bigint y(b);
	bigint z(expected);

	std::cerr << x << " + " << y << " = " << z << " gives " << (x + y) << " ";
	assert(x + y == z);
	std::cerr << "OK\n";
}

int main(void){
	{
		bigint zero;
		bigint un(1);
		bigint a(un);
		bigint j (42);

		std::cout << "zero = " << zero << "\n";
		std::cout << "un = " << un << "\n";
		std::cout << "a = " << a << "\n";
		std::cout << "j = " << j << "\n";
		bigint k(125665);
		std::cout << "k = " << k << "\n";
		k = j;
		std::cout << "k = " << k << "\n";
		bigint p(-4678);
		std::cout << "p = " << p << "\n";

		bigint b(j);
		std::cout << "j == b = " << (j == b) << "\n";
		std::cout << "j > b = " << (j > b) << "\n";
		bigint i(102);
		k = i;
		std::cout << "k > j = " << (k > j) << "\n";
		std::cout << "j > k = " << (j > k) << "\n";
		std::cout << "j == k = " << (j == k) << "\n";
		std::cout << "k > p = " << (k > p) << "\n";
		bigint mp(-4679);
		std::cout << "mp > p = " << (mp > p) << "\n";
		std::cout << "p > mp = " << (p > mp) << "\n";
		std::cout << "p == mp = " << (p == mp) << "\n";
	}
	{
		// Sans retenue
		test_add(0, 0, 0);
		test_add(1, 2, 3);
		test_add(12, 34, 46);
		test_add(123, 456, 579);

		// Avec retenue
		test_add(5, 7, 12);
		test_add(9, 1, 10);
		test_add(18, 5, 23);
		test_add(99, 1, 100);
		test_add(999, 1, 1000);

		// Retenues en chaîne
		test_add(999, 999, 1998);
		test_add(555, 555, 1110);
		test_add(9999, 1, 10000);

		// Tailles différentes
		test_add(123, 7, 130);
		test_add(7, 123, 130);
		test_add(1000, 1, 1001);
		test_add(1000000, 999, 1000999);

		// Négatifs + négatifs
		test_add(-1, -2, -3);
		test_add(-12, -34, -46);
		test_add(-999, -1, -1000);

		// Positif + négatif
		test_add(8, -3, 5);
		test_add(3, -8, -5);
		test_add(100, -1, 99);
		test_add(100, -99, 1);
		test_add(100, -100, 0);

		// Négatif + positif
		test_add(-3, 8, 5);
		test_add(-8, 3, -5);
		test_add(-100, 1, -99);
		test_add(-100, 100, 0);

		// Autour de zéro
		test_add(0, 5, 5);
		test_add(5, 0, 5);
		test_add(0, -5, -5);
		test_add(-5, 0, -5);
		test_add(-5, 5, 0);
		test_add(5, -5, 0);
	}
}