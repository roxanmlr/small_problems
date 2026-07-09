#pragma once

#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		int					sign;
	public:
		bigint();
		bigint(int val);
		bigint(bigint const & other);
		bigint & operator=(bigint const other);
		std::ostream & write(std::ostream & out) const;
		bool operator>(bigint const & b) const;
		bool operator==(bigint const & b) const;
};

std::ostream &operator<<(std::ostream & out, bigint const & big);