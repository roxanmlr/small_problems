#pragma once

#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		int					sign;
		static bigint		compact(bigint const & a); 
		static bigint		add_abs(bigint const & a, bigint const & b);
		static bigint		substr(bigint const & a, bigint const & b);
	public:
		bigint();
		~bigint();
		bigint(int v);
		bigint(bigint const & o);
		bigint & operator=(bigint const & o);
		bigint	 operator+(bigint const & o) const;
		std::ostream & write(std::ostream & out) const;
		bool operator==(bigint const & b) const;
		bool operator!=(bigint const & b) const;
		bool operator>(bigint const & b) const;
		bool operator>=(bigint const & b) const;
		bool operator<(bigint const & b) const;
		bool operator<=(bigint const & b) const;
};

std::ostream & operator<<(std::ostream & out, bigint const & b);
