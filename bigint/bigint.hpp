#pragma once

#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int>	data;
		int					sign;
		static bigint		compact(bigint const & a); 
	public:
		bigint();
		~bigint();
		bigint(int v);
		bigint(bigint const & o);
		bigint & operator=(bigint const & o);
		std::ostream & write(std::ostream & out) const;
		bool operator==(bigint const & b) const;
		bool operator>(bigint const & b) const;
};

std::ostream & operator<<(std::ostream & out, bigint const & b);
