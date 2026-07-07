#include <vector>
#include <iostream>

class bigint {
	private:
		std::vector<int> data;
		bool			 isneg;
	public:
		bigint():data(),isneg(false){}
		bigint(int value):data(){
			if (value == 0){
				data.push_back(0);	
				return	;
			}
			long long v = value;
			isneg = v< 0;	
			if (isneg)
				v= -v;
			while(v != 0){
				data.push_back(v % 10);
				v /= 10;
			}
		}
		bigint(bigint const & other){
			if (*this == other)
				return ;
			*this = other;
		}
		bigint & operator=(bigint const & other){
			if (*this == other)
				return *this;
			for(auto it = other.data.begin(); it != other.data.end(); it++)
				this->data.push_back(*it);
			return *this;
		}
		bigint  operator+(bigint const & other) const{
			bigint ret;
			auto a = this->data.begin();
			auto b = other.data.begin();
			int reste = 0;
			while (a != this->data.end() || b != other.data.end() || reste != 0){ //Tout consommer avant de sortir
				int val_a = 0;
				int val_b = 0;
				if (a != this->data.end()){
					val_a = *a;
					++a;
				}
				if (b != other.data.end()){
					val_b = *b;
					++b;
				}
				int sum = val_a + val_b + reste;
				ret.data.push_back(sum % 10);
				reste = sum / 10;
			}
			return ret;
		}
		bigint  operator+(int other){
			bigint o(other);
			return *this + o;
		}
		bigint  operator+=(bigint const & other){
			*this = *this + other;
			return *this;
		}
		/*bigint const & operator++(int other){
			return *this + bigint(1);
		}*/
		bigint  operator++(int other){
			return *this + bigint(1);
		}
		bigint  operator<<(int dec){
			if (dec < 0)
				return *this;
			while (dec != 0){
				this->data.insert(this->data.begin(), 0);
				dec /= 10;
			}
			return *this;
		}
		bigint  operator<<=(int dec){
			return *this << dec;
		}
		bigint  operator>>=(int dec){
			if (dec == 1){
				data.erase(data.begin());
				return *this;
			}
			auto begin = data.begin();
			auto end = data.begin();
			for (int i = 0; i < dec && end != data.end(); i++, end++)
				;
			data.erase(begin, end);
			return *this;
		}
		bool	 operator<(bigint const & other){ return true;}
		bool	 operator<=(bigint const & other){ return true;}

		bool	 operator==(bigint const & other){ return true;}

		bool	 operator!=(bigint const & other){ return true;}

		bool	 operator>(bigint const & other){ return true;}

		bool	 operator>=(bigint const & other){ return true;}

};

std::ostream& operator<<(std::ostream& os, bigint const & b){
		return os;
}

int main(void)
{
	const bigint a(42);
	bigint b(21), c, d(1337), e(d);

	// base test
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;

	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "a + c = " << a + c << std::endl;
	std::cout << "(c += a) = " << (c += a) << std::endl;

	std::cout << "b = " << b << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;

	// b = 23, b << 10 -> 23000000000 + 42 = 23000000042
	std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << ", d: " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << ", d: " << d << std::endl;

	std::cout << "a = " << a << std::endl; // a = 42
	std::cout << "d = " << d << std::endl; // d = 5348

	std::cout << "(d < a) = " << (d < a) << std::endl; // (d < a) = 0
	std::cout << "(d > a) = " << (d > a) << std::endl; // (d > a) = 1
	std::cout << "(d == d) = " << (d == d) << std::endl; // (d == d) = 1
	std::cout << "(d != a) = " << (d != a) << std::endl; // (d != a) = 1
	std::cout << "(d <= a) = " << (d <= a) << std::endl; // (d <= a) = 0
	std::cout << "(d >= a) = " << (d >= a) << std::endl; // (d >= a) = 1

	// extra
	bigint x(12345678); bigint y(5);
	std::cout << "(x << y) = " << (x << y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >>= y) = " << (x >>= y) << ", x: " << x << ", y: " << y << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	std::cout << "x= " << (x <<= 5) << ", y= " << (y <<= 12) << std::endl;
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	return (0);
}
