#include "bigint.hpp"

bigint::bigint():data(),sign(1){
	data.push_back(0);
}

bigint::bigint(int v):data(),sign(1){
	long long val = v;
	if (val == 0)
		data.push_back(0);
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

bigint bigint::sum_abs(bigint const & b) const {
	bigint ret;
	ret.data.resize(0);
	ret.sign = sign;
	std::vector<int>::const_iterator it_a = data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	int reste = 0;
	while (it_a != data.end() || it_b != b.data.end() || reste != 0){
		int val_a = 0;
		int val_b = 0;
		if (it_a != data.end()){
			val_a = *it_a;
			it_a++;
		}
		if (it_b != b.data.end()){
			val_b = *it_b;
			it_b++;
		}
		int sum = val_a + val_b + reste;
		reste = sum / 10;
		ret.data.push_back(sum % 10);
	}
	return ret;
}

bigint bigint::substr(bigint const & a, bigint const & b) const{
	bigint ret;
	ret.data.resize(0);
	ret.sign = a.sign;
	std::vector<int>::const_iterator it_a = a.data.begin();
	std::vector<int>::const_iterator it_b = b.data.begin();
	int pret = 0;
	while(it_a != a.data.end() || it_b != b.data.end() || pret != 0){
		int val_a = 0;
		int val_b = 0;
		if (it_a != data.end()){
			val_a = *it_a;
			it_a++;
		}
		if (it_b != b.data.end()){
			val_b = *it_b;
			it_b++;
		}
		int diff;
		if (val_a < (val_b + pret)){
			diff = 10 + val_a - (val_b + pret);
			pret = 1;
		}else{
			diff = val_a - (val_b + pret);
			pret = 0;
		}
		ret.data.push_back(diff);
	}
	return ret;
}

bigint bigint::operator+(bigint const & b) const{
	if (sign == b.sign)
		return this->sum_abs(b);
	bigint a =  *this;
	bigint d = b;
	a.sign = 1;
	d.sign = 1;
	bigint ret;
	if (a > d){
		ret = substr(a, d);
		ret.sign = this->sign;
	}
	else{
		ret = substr(d, a);
		ret.sign = b.sign;
	}
	std::vector<int>::iterator start = ret.data.begin();
	std::vector<int>::iterator end = start;
	for (; start != ret.data.end(); start++){
		for(end = start; end != ret.data.end() && *end == 0; end++)
			;
		if (end == ret.data.end()){
			ret.data.erase(start, end);
			break;
		}
	}
	if (ret.data.size() == 0){
		ret.sign = 1;
		ret.data.push_back(0);
	}
	return ret;
}