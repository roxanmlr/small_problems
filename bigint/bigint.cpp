#include "bigint.hpp"

bigint::bigint():data(),isneg(false){
}

bigint::bigint(int val):data(),isneg(val < 0){
	long long value = val;
	if (value < 0)
		value *= -1;
	if (value == 0){
		data.push_back(0);
		return;
	}
	while(value != 0){
		data.push_back(value % 10);
		value /= 10;
	}
}

bigint::bigint(bigint const & other):data(),isneg(other.isneg){
	if (this == &other)
		return;
	for(std::vector<int>::const_iterator it = other.data.begin(); it != other.data.end(); it++)
		data.push_back(*it);
}

bigint & bigint::operator=(bigint const & other){
	if (this == &other)
		return *this;
	this->isneg = other.isneg;
	data.erase(data.begin(), data.end());
	for ( std::vector<int>::const_iterator it = other.data.begin(); it != other.data.end(); it++)
		data.push_back(*it);
	return *this;
}

void bigint::compact(){
	if (data.size() == 0)
		return;
	std::vector<int>::iterator start = data.begin();
	start++;
		std::vector<int>::iterator end = start;
	for (; start != data.end(); start++){
		for (end = start; *start == 0 && end != data.end() && *end == 0; end++);
		while (*start == 0 && end == data.end()){
			std::vector<int>::iterator tosuppr = start;
			start++;
			data.erase(tosuppr);
			if (start == end)
				break;
		}
	}
}

std::ostream & bigint::write(std::ostream & stream) const{
	if (isneg)
		stream << "-";
	if (data.size() == 0)
		stream << "0";
	std::reverse_iterator<std::vector<int>::const_iterator> it = data.rbegin();
/*	for (;it != data.rend() && *it == 0; it++)
		;
	if (it == data.rend())
		stream << "0";*/
	for (; it != data.rend(); it++)
		stream << *it;
	return stream;
}

bigint bigint::operator+(bigint const & other) const{
	bigint res;
	int reste = 0;
	std::vector<int>::const_iterator it_a = data.begin();
	std::vector<int>::const_iterator it_b = other.data.begin();
	while (it_a != data.end() || it_b != other.data.end() || reste != 0){
		int val_a = 0;
		int val_b = 0;
		if (it_a != data.end()){
			val_a = *it_a * ((isneg)?-1:1);
			it_a++;
		}
		if (it_b != other.data.end()){
			val_b = *it_b * ((other.isneg)?-1:1);
			it_b++;
		}
		int sum = val_a + val_b + reste;
		int digit = sum % 10;
		if (digit < 0)
			digit *= -1;
		res.data.push_back(digit);
		reste = sum / 10;
		if (sum < 0)
			res.isneg = true;
		else if (sum > 0)
			res.isneg = false;
	}
	res.compact();
	return res;
}

bigint & bigint::operator+=(bigint const & other){
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++() {
	*this += bigint(1);
	this->compact();
	return *this;
}

bigint bigint::operator++(int other){
	(void)other;
	bigint ret = *this;
	this->operator++();
	return ret;
}

bigint bigint::operator<<(int dec){
	return this->operator<<(bigint(dec));
}

bigint bigint::operator<<(bigint const dec){
	bigint ret = *this;
	ret <<= dec;
	return ret;
}

bigint &bigint::operator<<=(bigint const dec){
	bigint ndec = dec;
	while (ndec > bigint(0)){
		data.insert(data.begin(), 0);
		ndec = ndec + bigint(-1);
		std::cout << ndec << "\n";
	}
	this->compact();
	return *this;
}

bigint &bigint::operator<<=(int dec){
	return this->operator<<=(bigint(dec));
}

bigint &bigint::operator>>=(bigint const dec){
	bigint ndec = dec;
	while (ndec > bigint(0)){
		if (data.begin() == data.end())
			break;
		data.erase(data.begin());
		ndec = ndec + bigint(-1);
	}
	this->compact();
	return *this;
}

bool bigint::operator>(bigint const other)const{
	if (isneg && !other.isneg)
		return false;
	if (!isneg && other.isneg)
		return false;
	std::vector<int>::const_iterator it_this = data.begin();
	std::vector<int>::const_iterator it_other = other.data.begin();
	bool res = false;
	while(true){
		if (it_this == data.end() && it_other != other.data.end())
			return false;
		if (it_this != data.end() && it_other == other.data.end())
			return true;
		if (it_this == data.end() && it_other == other.data.end())
			return res;
		if (*it_this != *it_other)
			res = *it_this > *it_other;
		it_this++;
		it_other++;
	}
}

bool bigint::operator==(bigint const other)const{
	if (isneg != other.isneg)
		return false;
	std::vector<int>::const_iterator it_this = data.begin();
	std::vector<int>::const_iterator it_other = other.data.begin();
	while(true){
		if (it_this == data.end() && it_other != other.data.end())
			return false;
		if (it_this != data.end() && it_other == other.data.end())
			return false;
		if (it_this == data.end() && it_other == other.data.end())
			return true;
		if (*it_this != *it_other)
			return false;
		it_this++;
		it_other++;
	}
}

bool bigint::operator>=(bigint const other)const{
	return (*this > other || *this == other);
}

bool bigint::operator<(bigint const other)const{
	return !(*this > other || *this == other);
}
bool bigint::operator<=(bigint const other)const{
	return !(*this > other) || *this == other;
}

bool bigint::operator!=(bigint const other)const{
	return !(*this == other);
}

std::ostream & operator<<(std::ostream & stream, bigint const & big){
	return big.write(stream);
}