#include <fstream>
#include <iostream>
#include <algorithm>
#include "LongInteger.h"

using namespace std;

int main() {
	std::cout << "Main:" << std::endl;
    {
		LongInteger<8> a(99);
		std::cout << "99 : " << a << std::endl;

        LongInteger<10> s = LongInteger<10>::parse("123");
        const LongInteger<10> &c = s;

        std::cout << "123 : " << s << std::endl;
        std::cout << "123 : " << c << std::endl;

        LongInteger<10>::iterator ncb = s.begin(), nce = s.end();
        LongInteger<10>::const_iterator cb = c.cbegin(), ce = c.cend();

        std::cout << "321 : ";
        for (LongInteger<10>::iterator i = ncb; i != nce; ++i) {
            std::cout << *i;
        }
        std::cout << std::endl;

        std::cout << "321 : ";
        for (LongInteger<10>::const_iterator i = cb; i != ce; ++i) {
            std::cout << *i; 
        }
        std::cout << std::endl;

        std::cout << "321 : ";
        for (size_t i = 0; i < s.size(); ++i) {
            std::cout << s.begin()[i];
        }
        std::cout << std::endl;

        std::cout << "321 : ";
        for (size_t i = 0; i < c.size(); ++i) {
            std::cout << c.cbegin()[i];
        }
        std::cout << std::endl;

        for (LongInteger<10>::iterator i = s.begin(); i != s.end(); ++i) {
            ++*i;
        }
        std::cout << "234 : " << s << std::endl;

        *(s.begin() + 1) = 0;
        std::cout << "204 : " << s << std::endl;
	}

    std::cout << "\nIterators:" << std::endl;
    {
        LongInteger<10> s = LongInteger<10>::parse("1234567");
        const LongInteger<10> &c = s; // force ConstIterator
        size_t length = s.size();
        std::cout << "7 : " << length << std::endl;
        
        std::cout << "1 : " << (s.begin() == c.cbegin()) << std::endl;
        std::cout << "1 : " << (c.cbegin() == s.begin()) << std::endl;
        std::cout << "1 : " << (s.end() == c.cend()) << std::endl;
        std::cout << "1 : " << (c.cend() == s.end()) << std::endl;
        std::cout << "1 : " << (s.begin() != s.end()) << std::endl;
        std::cout << "1 : " << (s.begin() != c.cend()) << std::endl;
        std::cout << "1 : " << (c.cbegin() != s.end()) << std::endl;

        std::cout << "1 : " << (s.begin()++ == s.begin()) << std::endl;
        std::cout << "1 : " << (++s.begin() == s.begin() + 1) << std::endl;
        std::cout << "1 : " << (s.end()-- == s.end()) << std::endl;
        std::cout << "1 : " << (--s.end() == s.end() - 1) << std::endl;

        std::cout << "1 : " << (s.begin() + length == s.end()) << std::endl;
		std::cout << "1 : " << (length + s.begin() == s.end()) << std::endl;
        {
            LongInteger<10>::iterator i = s.begin();
            i += length;
            std::cout << "1 : " << (i == s.end()) << std::endl;
            std::cout << "1 : " << ((i -= length) == s.begin()) << std::endl;
        }
        std::cout << "1 : " << (s.end() - length == s.begin()) << std::endl;
        {
            LongInteger<10>::iterator i = s.end();
            i -= length;
            std::cout << "1 : " << (i == s.begin()) << std::endl;
            std::cout << "1 : " << ((i += length) == s.end()) << std::endl;
        }
        std::cout << "1 : " << ( (s.end() - s.begin()) == static_cast<ptrdiff_t>(length) ) << std::endl;

        std::cout << "1 : " << (s.begin() < s.end()) << std::endl;
        std::cout << "1 : " << (s.begin() <= s.end()) << std::endl;
        std::cout << "0 : " << (s.begin() > s.end()) << std::endl;
        std::cout << "0 : " << (s.begin() >= s.end()) << std::endl;
        std::cout << "1 : " << (s.begin() < c.cend()) << std::endl;
        std::cout << "1 : " << (s.begin() <= c.cend()) << std::endl;
        std::cout << "0 : " << (s.begin() > c.cend()) << std::endl;
        std::cout << "0 : " << (s.begin() >= c.cend()) << std::endl;
        std::cout << "1 : " << (c.cbegin() < s.end()) << std::endl;
        std::cout << "1 : " << (c.cbegin() <= s.end()) << std::endl;
        std::cout << "0 : " << (c.cbegin() > s.end()) << std::endl;
        std::cout << "0 : " << (c.cbegin() >= s.end()) << std::endl;

		LongInteger<10> a = LongInteger<10>::parse("123");
		LongInteger<10>::const_iterator cit = a.cbegin();

		std::cout << "3210000000 : ";

		for (size_t i = 0; i < 10; ++i) {
			std::cout << *cit;
			++cit;
		}
		
		std::cout << endl;

    }

    std::cout << "\nSwap:" << std::endl;
    {
        LongInteger<10> s1 = LongInteger<10>::parse("123"), s2 = LongInteger<10>::parse("456");
        LongInteger<10>::iterator s1b = s1.begin(), s2b = s2.begin();
        std::cout << "123 456 : " << s1 << " " << s2 << std::endl;
        std::swap(s1, s2);
        std::cout << "456 123 : " << s1 << " " << s2 << std::endl;
    }

    std::cout << "\nComparison (simple):" << std::endl;
    {
        LongInteger<10> s1 = LongInteger<10>::parse("123"), s2 = LongInteger<10>::parse("456");
        std::cout << "1 : " << (s1 < s2) << std::endl;
        std::cout << "1 : " << (s1 <= s2) << std::endl;
        std::cout << "0 : " << (s1 > s2) << std::endl;
        std::cout << "0 : " << (s1 >= s2) << std::endl;
        std::cout << "0 : " << (s2 < s1) << std::endl;
        std::cout << "0 : " << (s2 <= s1) << std::endl;
        std::cout << "1 : " << (s2 > s1) << std::endl;
        std::cout << "1 : " << (s2 >= s1) << std::endl;
    }

    std::cout << "\nComparison (123, 1234):" << std::endl;
    {
        LongInteger<10> s1 = LongInteger<10>::parse("123"), s2 = LongInteger<10>::parse("1234");
        std::cout << "1 : " << (s1 < s2) << std::endl;
        std::cout << "1 : " << (s1 <= s2) << std::endl;
        std::cout << "0 : " << (s1 > s2) << std::endl;
        std::cout << "0 : " << (s1 >= s2) << std::endl;
        std::cout << "0 : " << (s2 < s1) << std::endl;
        std::cout << "0 : " << (s2 <= s1) << std::endl;
        std::cout << "1 : " << (s2 > s1) << std::endl;
        std::cout << "1 : " << (s2 >= s1) << std::endl;
    }

    std::cout << "\nComparison (LongInteger<10>() = 0):" << std::endl;
    {
		std::cout << "0 : " << (LongInteger<10>() == LongInteger<10>::parse("1")) << std::endl;
        std::cout << "1 : " << (LongInteger<10>() != LongInteger<10>::parse("1")) << std::endl;
        std::cout << "1 : " << (LongInteger<10>() < LongInteger<10>::parse("1")) << std::endl;
        std::cout << "1 : " << (LongInteger<10>() <= LongInteger<10>::parse("1")) << std::endl;
        std::cout << "0 : " << (LongInteger<10>() > LongInteger<10>::parse("1")) << std::endl;
        std::cout << "0 : " << (LongInteger<10>() >= LongInteger<10>::parse("1")) << std::endl;
		std::cout << "1 : " << (LongInteger<10>() == LongInteger<10>::parse("0")) << std::endl;
    }

	std::cout << "\nOperator + :" << std::endl;
    {
		LongInteger<10> a = LongInteger<10>::parse("199");
		LongInteger<10> b = LongInteger<10>::parse("1814");

		std::cout << "1 : " << (a + b == LongInteger<10>::parse("2013")) << std::endl;
		std::cout << "1 : " << (a + b == b + a) << std::endl;

		b += a;
		std::cout << "1 : " << (b == LongInteger<10>::parse("2013")) << std::endl;

		std::cout << "1 : " << (b + LongInteger<10>((unsigned long long) 0) == b) << std::endl;
		std::cout << "1 : " << (LongInteger<10>((unsigned long long) 0) + b == b) << std::endl;
	}

	std::cout << "\nOperator - :" << std::endl;
    {
		LongInteger<10> a = LongInteger<10>::parse("199");
		LongInteger<10> b = LongInteger<10>::parse("1814");

		std::cout << "1 : " << (b - a == LongInteger<10>::parse("1615")) << std::endl;
		std::cout << "1 : " << (b - a + a == b) << std::endl;

		b -= a;
		std::cout << "1 : " << (b == LongInteger<10>::parse("1615")) << std::endl;
		b -= (unsigned long long)0;
		std::cout << "1 : " << (b == LongInteger<10>::parse("1615")) << std::endl;
		
		std::cout << "1 : " << (b - LongInteger<10>((unsigned long long)0) == b) << std::endl;
		std::cout << "1 : " << (b - b == LongInteger<10>((unsigned long long)0)) << std::endl;
	}

	std::cout << "\nOperator * :" << std::endl;
    {
		LongInteger<10> a = LongInteger<10>::parse("199");
		LongInteger<10> b = LongInteger<10>::parse("1814");

		std::cout << "1 : " << (a * b == LongInteger<10>::parse("360986")) << std::endl;
		std::cout << "1 : " << (a * b == b * a) << std::endl;

		b *= a;
		std::cout << "1 : " << (b == LongInteger<10>::parse("360986")) << std::endl;

		std::cout << "1 : " << (b * LongInteger<10>(1) == b) << std::endl;
		std::cout << "1 : " << (LongInteger<10>(1) * b == b) << std::endl;
		std::cout << "1 : " << (b * LongInteger<10>((unsigned long long)0) == LongInteger<10>((unsigned long long)0)) << std::endl;
		std::cout << "1 : " << (LongInteger<10>((unsigned long long)0) * b == LongInteger<10>((unsigned long long)0)) << std::endl;
	}

	std::cout << "\nOperator / :" << std::endl;
    {
		LongInteger<10> a = LongInteger<10>::parse("199");
		LongInteger<10> b = LongInteger<10>::parse("1814");

		std::cout << "1 : " << (b / a == LongInteger<10>::parse("9")) << std::endl;
		std::cout << "1 : " << (b / a * a <= b) << std::endl;
		std::cout << "1 : " << (b / a * a > b - a) << std::endl;

		b /= a;
		std::cout << "1 : " << (b == LongInteger<10>::parse("9")) << std::endl;
		b /= 1;
		std::cout << "1 : " << (b == LongInteger<10>::parse("9")) << std::endl;
		
		std::cout << "1 : " << (b / LongInteger<10>(1) == b) << std::endl;
		std::cout << "1 : " << (b / b == LongInteger<10>(1)) << std::endl;

	}

	std::cout << "\nOperator % :" << std::endl;
    {
		LongInteger<10> a = LongInteger<10>::parse("199");
		LongInteger<10> b = LongInteger<10>::parse("1814");

		std::cout << "1 : " << (b % a == LongInteger<10>::parse("23")) << std::endl;
		std::cout << "1 : " << (b % a < a) << std::endl;
		std::cout << "1 : " << (b / a * a + b % a == b) << std::endl;

		b %= a;
		std::cout << "1 : " << (b == LongInteger<10>::parse("23")) << std::endl;
		
		std::cout << "1 : " << (b % LongInteger<10>(1) == LongInteger<10>((unsigned long long)0)) << std::endl;
		std::cout << "1 : " << (b % b == LongInteger<10>((unsigned long long)0)) << std::endl;

	}

	std::cout << "\nChange base :" << std::endl;
    {
		LongInteger<2> a(199);
		std::reverse_iterator<LongInteger<2>::const_iterator> r_iter2(a.cend());
		std::reverse_iterator<LongInteger<2>::const_iterator> r_end2(a.cbegin());
		std::cout << "11000111 : ";
		for (; r_iter2 != r_end2; ++r_iter2) {
			std::cout << *r_iter2;
		}
		std::cout << std::endl;
		

		LongInteger<3> b(a);
		std::reverse_iterator<LongInteger<3>::const_iterator> r_iter3(b.cend());
		std::reverse_iterator<LongInteger<3>::const_iterator> r_end3(b.cbegin());
		std::cout << "21101 : ";
		for (; r_iter3 != r_end3; ++r_iter3) {
			std::cout << *r_iter3;
		}
		std::cout << std::endl;

		LongInteger<10> c(b);
		std::cout << "199 : " << c << std::endl;

		std::cout << "1 : " << (LongInteger<10>() == LongInteger<10>(LongInteger<7>())) << std::endl;
	}

	std::cout << "\nBinary operators test :" << std::endl;
    {
		std::cout << "1 : " << (LongInteger<10>(123) == 123) << std::endl;
		std::cout << "1 : " << (123 == LongInteger<10>(123)) << std::endl;
		std::cout << "0 : " << (LongInteger<10>(123) != 123) << std::endl;
		std::cout << "0 : " << (123 != LongInteger<10>(123)) << std::endl;
		std::cout << "0 : " << (LongInteger<10>(123) > 123) << std::endl;
		std::cout << "0 : " << (123 > LongInteger<10>(123)) << std::endl;
		std::cout << "0 : " << (LongInteger<10>(123) < 123) << std::endl;
		std::cout << "0 : " << (123 < LongInteger<10>(123)) << std::endl;
		std::cout << "1 : " << (LongInteger<10>(123) >= 123) << std::endl;
		std::cout << "1 : " << (123 >= LongInteger<10>(123)) << std::endl;
		std::cout << "1 : " << (LongInteger<10>(123) <= 123) << std::endl;
		std::cout << "1 : " << (123 <= LongInteger<10>(123)) << std::endl;


	}

    return 0;
}
