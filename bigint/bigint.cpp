#include "bigint.hpp"

bigint		bigint::compact(bigint const & a){ 
	bigint b(a);
	if (b.data.size() == 0){
		b.data.push_back(0);
		b.sign = 1;
		return b;
	}
	std::vector<int>::iterator start = b.data.begin();
	std::vector<int>::iterator end = start;
	for(; start != b.data.end() && end != b.data.end(); ++start){
		for (end = start; *start == 0 && end != b.data.end() && *end == 0; ++end);
	}
	if (end == b.data.end() && start != b.data.end() && *start == 0)
		b.data.erase(start, end);
	if (b.data.size() == 0){
		b.data.push_back(0);
		b.sign = 1;
	}
	return b;
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
	std::vector<int>::const_iterator it_a = a.data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	while (true){
		if (it_a == a.data.end())
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
