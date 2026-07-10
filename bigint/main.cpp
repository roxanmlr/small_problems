#include "bigint.hpp"
#include <cassert>
#include <iostream>

#include <limits.h>

void test_add(int a, int b){
	bigint e(a);
	bigint f(b);
	bigint g(a + b);

	std::cerr << e << " + " << f << " = " << (e + f) << " , exepected " << a + b << std::endl;
	assert (e + f == g);
}

void test_equal(int a, int b){
	bigint e(a);
	bigint f(b);
	std::cerr << e << " == " << f << " = " << (e == f) << " , exepected " << (a == b) << std::endl;
	assert ((e == f) == (a == b));
}

void test_sup(int a, int b){
	bigint e(a);
	bigint f(b);
	std::cerr << e << " > " << f << " = " << (e > f) << " , exepected " << (a > b) << std::endl;
	assert ((e > f) == (a > b));
}

int main(void){

	/*Egalité*/
	test_equal(0, 0);
	test_equal(-1, -1);
	test_equal(1, 1);
	test_equal(INT_MAX, INT_MAX);
	test_equal(INT_MIN, INT_MIN);
	test_equal(INT_MIN, INT_MAX);
	test_equal(4242, 4242);
	test_equal(4242, 242);
	test_equal(-4242, -4242);

	/*Superieur*/
	test_sup(0, 0);
	test_sup(0, 15);
	test_sup(15, 0);
	test_sup(-15, 0);
	test_sup(-1, -1);
	test_sup(1, -1);
	test_sup(12, 15);
	test_sup(-12, -15);
	test_sup(-1, 1);
	test_sup(1, 1);
	test_sup(INT_MAX, INT_MAX);
	test_sup(INT_MIN, INT_MIN);
	test_sup(INT_MIN, INT_MAX);
	test_sup(4242, 4242);
	test_sup(4242, 242);
	test_sup(242, -4242);
	test_sup(-4242, -242);
	test_sup(-4242, -4342);
	test_sup(-242, -4242);
 	
	/*Summ*/
	test_add(0, 0);
	test_add(1, 0);
	test_add(0, 1);
	test_add(20, 32);
	test_add(-20, -32);
	test_add(-32, -20);
	test_add(-32, 0);
	test_add(0, -32);
	test_add(40, -32);
	test_add(-40, 32);
	test_add(-32, 40);
}
