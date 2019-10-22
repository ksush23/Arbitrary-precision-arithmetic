#pragma once
#define MATH_INTEGER_H

#include "Unsigned.h"

namespace math
{
	class Integer
	{
	public:
		Integer(std::int32_t u = 0) :
			sign((u > 0) - (u < 0)),
			mag(u < 0 ? -u : u)
		{
			// empty
		}

		Integer(const Unsigned& u) :
			sign(u == 0 ? 0 : 1),
			mag(u)
		{
			// empty
		}

		Integer(const std::string& s) :
			sign(0),
			mag()
		{
			std::istringstream iss(s);
			iss >> *this;
			if (iss.fail() || !iss.eof())
			{
				throw std::runtime_error("Error: Integer::string");
			}
		}

		Integer(const Integer& copy) :
			sign(copy.sign),
			mag(copy.mag)
		{
			// empty
		}

		Integer gcdY(Integer a, Integer b, Integer &x, Integer &y) {
			if (a == 0) {
				x = 0; y = 1;
				return b;
			}
			Integer x1, y1;
			Integer d = gcdY(b%a, a, x1, y1);
			x = y1 - (b / a) * x1;
			y = x1;
			y = Integer("0") - y;
			return d;
		}

		Integer Mon(Integer b) {
			Integer a(*this);
			Integer t = a * b;
			Integer x, y;
			Integer r = a.length();
			gcdY(r, Integer("-1"), x, y);
			Integer u = (t + (t * y % r)) / r;
			while (u >= 1) {
				u = u - 1;
			}
			return u;
		}

		Integer ith_digit_finder(Integer n, long i) {
			/**
				n = number whose digits we need to extract
				b = radix in which the number if represented
				i = the ith bit (ie, index of the bit that needs to be extracted)
			**/
			while (i > 0) {
				n /= 2;
				i--;
			}
			return (n%2);
		}

		Integer ModExp(Integer b, Integer m) {
			Integer p = this->Calculate(b, m);
			Integer r("1");
			for (int i = 0; i < this->mag.bits(); i++) {
				r = 2 ^ i;
				if (r > m)
					break;
			}
			return p / r;
		}

		Integer Calculate(Integer b, Integer m) {
			Integer a(*this);
			Integer p("0");
			for (int i = 0; i < a.mag.bits(); i++) {
				p = p + ith_digit_finder(a, i) * b;
			}
			if (ith_digit_finder(p, 0) == 1)
				p = p - m;
			p = p / 2;
			if (p > m)
				p = p - m;
			return p;
		}

		Integer plus_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w = w + v;
			w %= mod;
			return w;
		}

		Integer minus_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w = w - v;
			w %= mod;
			return w;
		}

		Integer mult_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w = w * v;
			w %= mod;
			return w;
		}

		Integer divide_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w = w / v;
			w %= mod;
			return w;
		}

		Integer mod_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w %= v;
			w %= mod;
			return w;
		}

		Integer pow_mod(const Integer& v, Integer mod) {
			Integer w(*this);
			w = w ^ v;
			w = w % mod;
			return w;
		}

		Integer& operator= (const Integer& rhs)
		{
			sign = rhs.sign;
			mag = rhs.mag;
			return *this;
		}

		Integer operator+ () const
		{
			return *this;
		}

		Integer operator- () const
		{
			Integer w(*this);
			w.sign = -sign;
			return w;
		}

		Integer operator++ (int)
		{
			Integer w(*this);
			++(*this);
			return w;
		}

		Integer& operator++ ()
		{
			if (sign < 0)
			{
				if (--mag == 0)
				{
					sign = 0;
				}
			}
			else
			{
				sign = 1;
				++mag;
			}
			return *this;
		}

		Integer operator-- (int)
		{
			Integer w(*this);
			--(*this);
			return w;
		}

		Integer& operator-- ()
		{
			if (sign > 0)
			{
				if (--mag == 0)
				{
					sign = 0;
				}
			}
			else
			{
				sign = -1;
				++mag;
			}
			return *this;
		}

		friend Integer operator+ (Integer u, const Integer& v)
		{
			u += v;
			return u;
		}

		Integer& operator+= (const Integer& rhs)
		{
			if (sign == 0)
			{
				*this = rhs;
			}
			else if (rhs.sign != 0)
			{
				if (sign == rhs.sign)
				{
					mag += rhs.mag;
				}
				else if (rhs.mag < mag)
				{
					mag -= rhs.mag;
				}
				else if (rhs.mag == mag)
				{
					sign = 0;
					mag = 0;
				}
				else
				{
					sign = rhs.sign;
					mag = rhs.mag - mag;
				}
			}
			return *this;
		}

		friend Integer operator- (const Integer& u, const Integer& v)
		{
			return u + (-v);
		}

		Integer& operator-= (const Integer& rhs)
		{
			*this += -rhs;
			return *this;
		}

		friend Integer operator* (Integer u, const Integer& v)
		{
			u *= v;
			return u;
		}

		Integer& operator*= (const Integer& rhs)
		{
			sign *= rhs.sign;
			mag *= rhs.mag;
			return *this;
		}

		friend Integer operator/ (Integer u, const Integer& v)
		{
			u /= v;
			return u;
		}

		Integer& operator/= (const Integer& rhs)
		{
			sign *= rhs.sign;
			mag /= rhs.mag;
			if (mag == 0)
			{
				sign = 0;
			}
			return *this;
		}

		friend Integer operator% (Integer u, const Integer& v)
		{
			u %= v;
			return u;
		}

		Integer& operator%= (const Integer& rhs)
		{
			mag %= rhs.mag;
			if (mag == 0)
			{
				sign = 0;
			}
			return *this;
		}

		friend Integer operator<< (Integer u, size_t v)
		{
			u <<= v;
			return u;
		}

		Integer& operator<<= (size_t rhs)
		{
			mag <<= rhs;
			return *this;
		}

		friend Integer operator>> (Integer u, size_t v)
		{
			u >>= v;
			return u;
		}

		Integer& operator>>= (size_t rhs)
		{
			mag >>= rhs;
			if (mag == 0)
			{
				sign = 0;
			}
			return *this;
		}

		Integer operator~ () const
		{
			Integer w = -(*this);
			return --w;
		}

		friend Integer operator& (Integer u, const Integer& v)
		{
			u &= v;
			return u;
		}

		Integer& operator&= (Integer rhs)
		{
			if (sign < 0 && rhs.sign < 0)
			{
				// -u & -v == -((u-1) | (v-1) + 1)
				--mag;
				mag |= --rhs.mag;
				++mag;
			}
			else
			{
				if (sign > 0 && rhs.sign < 0)
				{
					// u & -v == u & ~(v-1)
					mag = mag.and_not(--rhs.mag);
				}
				else if (sign < 0 && rhs.sign > 0)
				{
					--mag;
					mag = rhs.mag.and_not(mag);
				}
				else
				{
					mag &= rhs.mag;
				}
				sign = (mag == 0 ? 0 : 1);
			}
			return *this;
		}

		friend Integer operator^ (Integer u, const Integer& v)
		{
			//u ^= v;
			if (v == Integer("0")) {
				return Integer("1");
			}
			Integer mult(u);
			for (int i = 0; i < v - 1; i++) {
				u *= mult;
			}
			if (u % Integer("2") != Integer("0"))
				u.sign = 0;
			return u;
		}

		Integer& operator^= (Integer rhs)
		{
			if (sign < 0 && rhs.sign < 0)
			{
				// -u ^ -v == (u-1) ^ (v-1)
				--mag;
				mag ^= --rhs.mag;
				sign = (mag == 0 ? 0 : 1);
			}
			else if (sign > 0 && rhs.sign < 0)
			{
				// u ^ -v == -(u ^ (v-1) + 1)
				sign = -1;
				mag ^= --rhs.mag;
				++mag;
			}
			else if (sign < 0 && rhs.sign > 0)
			{
				--mag;
				mag ^= rhs.mag;
				++mag;
			}
			else
			{
				sign |= rhs.sign;
				mag ^= rhs.mag;
				if (mag == 0)
				{
					sign = 0;
				}
			}
			return *this;
		}

		friend Integer operator| (Integer u, const Integer& v)
		{
			u |= v;
			return u;
		}

		Integer& operator|= (Integer rhs)
		{
			if (sign < 0 && rhs.sign < 0)
			{
				// -u | -v == -((u-1) & (v-1) + 1)
				--mag;
				mag &= --rhs.mag;
				++mag;
			}
			else if (sign > 0 && rhs.sign < 0)
			{
				// u | -v == -((v-1) & ~u + 1)
				sign = -1;
				--rhs.mag;
				mag = rhs.mag.and_not(mag);
				++mag;
			}
			else if (sign < 0 && rhs.sign > 0)
			{
				--mag;
				mag = mag.and_not(rhs.mag);
				++mag;
			}
			else
			{
				sign |= rhs.sign;
				mag |= rhs.mag;
			}
			return *this;
		}


		friend bool operator< (const Integer& u, const Integer& v)
		{
			return (u.sign < v.sign || (u.sign == v.sign &&
				((u.sign < 0) ? (v.mag < u.mag) : (u.mag < v.mag))));
		}

		friend bool operator> (const Integer& u, const Integer& v)
		{
			return (v < u);
		}

		friend bool operator<= (const Integer& u, const Integer& v)
		{
			return !(v < u);
		}

		friend bool operator>= (const Integer& u, const Integer& v)
		{
			return !(u < v);
		}

		friend bool operator== (const Integer& u, const Integer& v)
		{
			return (u.sign == v.sign && u.mag == v.mag);
		}

		friend bool operator!= (const Integer& u, const Integer& v)
		{
			return (u.sign != v.sign || u.mag != v.mag);
		}

		std::int32_t signum() const
		{
			return sign;
		}

		Unsigned abs() const
		{
			return mag;
		}

		std::string to_string() const
		{
			std::ostringstream oss;
			oss << *this;
			return oss.str();
		}

		friend std::ostream& operator<< (std::ostream& os, const Integer& u)
		{
			if (u.sign < 0)
			{
				os << "-";
			}
			os << u.mag;
			return os;
		}

		friend std::istream& operator>> (std::istream& is, Integer& u)
		{
			char sign = '\0';
			is >> sign;
			if (is.good())
			{
				if (std::isdigit(sign))
				{
					is.putback(sign);
					sign = '+';
				}
				if ((sign == '+' || sign == '-') && std::isdigit(is.peek()))
				{
					is >> u.mag;
					u.sign = (sign == '-' ? -1 : 1);
					if (u.mag == 0)
					{
						u.sign = 0;
					}
				}
				else
				{
					is.setstate(std::ios_base::failbit);
				}
			}
			else
			{
				is.setstate(std::ios_base::failbit);
			}
			return is;
		}

	unsigned length() {
		return mag.BITS;
	}

	private:
		std::int32_t sign;
		Unsigned mag;
	};
}