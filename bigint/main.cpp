 #include "bigint.hpp"

int main(void){
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