#pragma once
#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		bool 				isneg;
		void compact(); // unique 8
	public:
		bigint();
		bigint(int val);
		bigint(bigint const & other);
		bigint & operator=(bigint const & other); // Unique 1
		std::ostream & write(std::ostream & stream) const; // Unique 2
		bigint operator+(bigint const & other) const; // Unique 3
		bigint operator<<(int dec); // unique 4
		bigint operator<<(bigint const dec); // unique 5
		bool operator>(bigint const dec)const; // unique 6
		bool operator==(bigint const other)const; // unique 7
		bigint &operator+=(bigint const & other) ; // *this = *this + other
		bigint &operator++() ; // *this = *this + bigint(1)
		bigint operator++(int other); // avec le precedent
		bigint &operator<<=(int dec); // avec le precedent
		bigint &operator>>=(int dec); //  avec les autres
		bigint &operator>>=(bigint const dec);// avec le precedent
		bigint &operator<<=(bigint const dec);// avec le precedent
		bool operator>=(bigint const other)const;
		bool operator<(bigint const other)const;
		bool operator<=(bigint const other)const;
		bool operator!=(bigint const other)const;
};

std::ostream & operator<<(std::ostream & stream, bigint const & big);