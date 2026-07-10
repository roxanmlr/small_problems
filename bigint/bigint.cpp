#include "bigint.hpp"

bigint	bigint::compact(bigint const & a){
	bigint b(a);
	if (b.data.size() <= 1)
		return b;
	while(true){
		if (b.data.size() <= 1)
			return b;
		std::vector<int>::iterator it = b.data.end();
		it--;
		if (*it != 0)
			return b;
		b.data.erase(it, b.data.end());
	}
}

bigint::bigint():data(),sign(1){
	data.push_back(0);
}

bigint::~bigint(){
}

bigint::bigint(int v):data(),sign(1){
	long long val = v;
	if (val == 0)
		data.push_back(0);
	if (val < 0){
		val = -val;
		sign = -1;
	}
	while (val != 0){
		data.push_back(val % 10);
		val /= 10;
	}
}

bigint::bigint(bigint const & o){
	if (this == &o)
		return;
	data.resize(0);
	for(std::vector<int>::const_iterator it = o.data.begin(); it != o.data.end(); it++)
		data.push_back(*it);
	sign = o.sign;
}

bigint & bigint::operator=(bigint const & o){
	if (this == &o)
		return *this;
	data.resize(0);
	for(std::vector<int>::const_iterator it = o.data.begin(); it != o.data.end(); it++)
		data.push_back(*it);
	sign = o.sign;
	return *this;
}

std::ostream & bigint::write(std::ostream & out) const{
	if (this->sign == -1)
		out << "-";
	for(std::reverse_iterator<std::vector<int>::const_iterator> it = this->data.rbegin(); it != this->data.rend(); it++)
		out << *it;
	return out;
}

std::ostream & operator<<(std::ostream & out, bigint const & b){
	return b.write(out);
}

bool bigint::operator==(bigint const & o) const{
	bigint a = bigint::compact(*this);
	bigint b = bigint::compact(o);

	if (a.sign != b.sign || a.data.size() != b.data.size())
		return false;
	std::vector<int>::const_iterator it_a = a.data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	while (true){
		if (it_a == a.data.end())
			return true;
		if (*it_a != *it_b)
			return false;	
		it_a++;
		it_b++;
	}
}

bool bigint::operator!=(bigint const & o) const{
	return !this->operator==(o);
}

bool bigint::operator>(bigint const & o) const{
	bigint a = bigint::compact(*this);
	bigint b = bigint::compact(o);

	if (a.sign != b.sign)
		return a.sign > b.sign;
	if (a.data.size() != b.data.size()){
		if (a.sign == 1)
			return a.data.size() > b.data.size();
		return a.data.size() < b.data.size();
	}
	std::reverse_iterator<std::vector<int>::const_iterator> it_a = a.data.rbegin();
	std::reverse_iterator<std::vector<int>::const_iterator> it_b = b.data.rbegin();
	while (true){
		if (it_a == a.data.rend())
			return false;
		if (*it_a != *it_b){
			if (a.sign == 1)
				return *it_a > *it_b;
			return *it_a < *it_b;
		}
		it_a++;
		it_b++;
	}
}

bool bigint::operator>=(bigint const & o) const{
	return this->operator==(o) || this->operator>(o);
}

bool bigint::operator<(bigint const & o) const{
	return this->operator!=(o) && !this->operator>(o);
}

bool bigint::operator<=(bigint const & o) const{
	return this->operator==(o) || this->operator<(o);
}

bigint		bigint::add_abs(bigint const & a, bigint const & b){
	bigint ret;
	ret.data.resize(0);
	std::vector<int>::const_iterator it_a = a.data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	int carry = 0;
	while (it_a != a.data.end() || it_b != b.data.end() || carry != 0){
		int val_a = 0;
		int val_b = 0;
		if (it_a != a.data.end()){
			val_a = *it_a;
			it_a++;
		}
		if (it_b != b.data.end()){
			val_b = *it_b;
			it_b++;
		}
		int sum = val_a + val_b + carry;
		ret.data.push_back(sum % 10);
		carry = sum / 10;
	}
	ret.sign = a.sign;
	return bigint::compact(ret);
}

bigint		bigint::substr(bigint const & a, bigint const & b){
	bigint ret;
	ret.data.resize(0);
	std::vector<int>::const_iterator it_a = a.data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	int borrow = 0;
	while (it_a != a.data.end() || it_b != b.data.end() || borrow != 0){
		int val_a = 0;
		int val_b = 0;
		if (it_a != a.data.end()){
			val_a = *it_a;
			it_a++;
		}
		if (it_b != b.data.end()){
			val_b = *it_b;
			it_b++;
		}
		int diff;
		if (val_a >= (val_b + borrow)){
			diff = val_a - (val_b + borrow);
			borrow = 0;
		}else{
			diff = 10 + val_a - (val_b + borrow);
			borrow = 1;
		}
		ret.data.push_back(diff);
	}
	return bigint::compact(ret);
}

bigint	 bigint::operator+(bigint const & o) const{
	bigint a = bigint::compact(*this);
	bigint b = bigint::compact(o);

	if (a.sign == b.sign)
		return bigint::add_abs(a, b);
	a.sign = 1;
	b.sign = 1;
	bigint ret;
	if (a > b){
		ret = substr(a , b);
		ret.sign = this->sign;
	} else if(a < b) {
		ret = substr(b , a);
		ret.sign = o.sign;
	}
	return ret;
}
