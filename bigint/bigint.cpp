#include "bigint.hpp"

bigint::bigint():data(),sign(1){
	data.push_back(0);
}

bigint::bigint(int v):data(),sign(1){
	long long val = v;
	if (val < 0){
		sign = -1;
		val = -val;
	}
	while (val != 0){
		data.push_back(val % 10);
		val /= 10;
	}
	
}

bigint::bigint(bigint const & other):data(){
	if (this == &other)
		return ;
	sign = other.sign;
	for (std::vector<int>::const_iterator it = other.data.begin();
		it != other.data.end(); it++ )
		data.push_back(*it);
}

bigint & bigint::operator=(bigint const other){
	if (this == &other)
		return *this;
	sign = other.sign;
	data.resize(0);
	for (std::vector<int>::const_iterator it = other.data.begin();
		it != other.data.end(); it++ )
		data.push_back(*it);
	return *this;
}

std::ostream & bigint::write(std::ostream & out) const{
	if (sign == -1)
		out << "-";
	for (std::reverse_iterator<std::vector<int>::const_iterator> it = data.rbegin();
		it != data.rend(); it++)
		out << *it;
	return out;
}

std::ostream &operator<<(std::ostream & out, bigint const & big){
	return big.write(out);
}

bool bigint::operator>(bigint const & b) const{
	if (sign != b.sign)
		return sign > b.sign;
	if (b.data.size() != data.size()){
		if (sign == 1)
			return data.size() > b.data.size();
		return data.size() < b.data.size();
	}
	std::vector<int>::const_iterator it_a = data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	while (true){
		if (it_a == data.end())
			return false;
		if (*it_a == *it_b){
			it_a++;
			it_b++;
			continue;
		}
		if (sign == 1)
			return *it_a > *it_b;
		return *it_a < *it_b;
	}
}

bool bigint::operator==(bigint const & b) const{
	if (sign != b.sign)
		return false;
	if (b.data.size() != data.size())
		return false;
	std::vector<int>::const_iterator it_a = data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	while (true){
		if (it_a == data.end())
			return true;
		if (*it_a == *it_b){
			it_a++;
			it_b++;
			continue;
		}
		return false;
	}
}