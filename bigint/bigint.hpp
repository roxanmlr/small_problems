#pragma once

#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		int					sign;
		bigint sum_abs(bigint const & b) const;
		bigint substr(bigint const & big, bigint const &small) const;
	public:
		bigint();
		bigint(int val);
		bigint(bigint const & other);
		bigint & operator=(bigint const other);
		std::ostream & write(std::ostream & out) const;
		bool operator>(bigint const & b) const;
		bool operator==(bigint const & b) const;
		bigint operator+(bigint const & b) const;
};

std::ostream &operator<<(std::ostream & out, bigint const & big);