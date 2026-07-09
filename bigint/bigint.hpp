#pragma once
#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		bool 				isneg;
	public:
		bigint();
		bigint(int val);
		bigint(bigint const & other);
		bigint & operator=(bigint const & other);
		std::ostream & write(std::ostream & stream) const;
		bigint operator+(bigint const & other) const;
		bigint &operator+=(bigint const & other) ;
		bigint &operator++() ;
		bigint operator++(int other);
		bigint operator<<(int dec);
		bigint &operator<<=(int dec);
		bigint &operator>>=(int dec);
		bigint &operator>>=(bigint const dec);
		bigint operator<<(bigint const dec);
		bigint &operator<<=(bigint const dec);
		bool operator>(bigint const dec)const;
		bool operator<(bigint const dec)const;
		bool operator==(bigint const other)const;
		bool operator>=(bigint const other)const;
		bool operator<=(bigint const other)const;
		bool operator!=(bigint const other)const;
		void compact();
};

std::ostream & operator<<(std::ostream & stream, bigint const & big);