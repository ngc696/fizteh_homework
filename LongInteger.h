#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <limits>
#include <iterator>
#include <string>
#include <typeinfo>
#include <cstring>
#include <cstddef>

template<bool> struct CTAssert;
template<> struct CTAssert<true> {};

template <unsigned int base>
class LongInteger {
private:
	std::vector<unsigned int> number_;

	template <typename data_type, typename vector_type, bool is_const>
	class basic_iterator: public std::iterator<std::random_access_iterator_tag, data_type>  {
	private:
		size_t index;
		vector_type number_;
		
		basic_iterator(vector_type new_number_, unsigned int new_index) {
			index = new_index;
			number_ = new_number_;
		}

	public:
		basic_iterator() {};

		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		basic_iterator(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) {
			this->index = other.index;
			this->number_ = other.number_;
		}

		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator <(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return this->index < other.index;
		}
		
		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator >(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return ( other < (*this) );
		}
		
		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator ==(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return ( !((*this) < other) && !(other < (*this)) );
		}
	
		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator !=(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return ( !((*this) == other) );
		}
	
		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator <=(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return ( !((*this) > other) );
		}
	
		template <typename other_data_type, typename other_vector_type, bool other_is_const>
		bool operator >=(const basic_iterator<other_data_type, other_vector_type, other_is_const> &other) const {
			return ( !((*this) < other) );
		}
		
		basic_iterator& operator ++() {
			++index;
			return (*this);
		}

		basic_iterator operator ++(int) {
			basic_iterator ans = *this;
			++index;
			return ans;
		}

		basic_iterator& operator --() {
			assert(index > 0);
			--index;
			return (*this);
		}

		basic_iterator operator --(int) {
			assert(index > 0);
			basic_iterator ans = *this;
			--index;
			return ans;
		}

		basic_iterator& operator +=(ptrdiff_t shift) {
			assert((ptrdiff_t)index + shift >= 0);
			index += shift;
			return (*this);
		}

		basic_iterator operator +(ptrdiff_t shift) const {
			basic_iterator ans = *this;
			ans += shift;
			return ans;
		}

		friend basic_iterator operator +(ptrdiff_t shift, const basic_iterator &other) {
			return other + shift;
		}

		basic_iterator& operator -=(ptrdiff_t shift) {
			assert((ptrdiff_t)index - shift >= 0);
			index -= shift;
			return (*this);
		}

		basic_iterator operator -(ptrdiff_t shift) const {
			basic_iterator ans = *this;
			ans -= shift;
			return ans;
		}
		
		ptrdiff_t operator -(const basic_iterator &other) const {
			return this->index - other.index;
		}

		data_type &operator *() const {
			static data_type null(0);
			if (is_const) {
				if (index < number_->size())
					return ((*number_)[index]);
				else
					return null;
			}
			else {
				assert(index < number_->size());
				return ((*number_)[index]);
			}
		}

		data_type operator [](ptrdiff_t shift) const {
			return *(*this + shift);
		}

		friend class LongInteger;

		friend class basic_iterator<const data_type, const vector_type, is_const>;
	};

	LongInteger operator <<(ptrdiff_t shift) const {
		LongInteger ans;
		ans.number_.reserve(shift + this->number_.size());
		ans.number_.resize(shift, 0);
		ans.number_.insert(ans.number_.end(), this->number_.begin(), this->number_.end());
		return ans;
	}

	LongInteger operator >>(ptrdiff_t shift) const {
		LongInteger ans;
		ans.number_.assign(this->number_.begin() + shift, this->number_.end());
		return ans;
	}

	static int compare(const LongInteger &first, const LongInteger &second) {
		if (first.number_.size() < second.number_.size()) {
			return -1;
		}
		if (first.number_.size() > second.number_.size()) {
			return 1;
		}

		for (ptrdiff_t i = first.number_.size() - 1; i >= 0; --i) {
			if (first.number_[i] < second.number_[i]) {
				return -1;
			}
			if (first.number_[i] > second.number_[i]) {
				return 1;
			}
		}

		return 0;
	}

public:
	LongInteger() {
		number_.push_back(0);
	}
    
	LongInteger(unsigned long long num) {
		do {
			number_.push_back(num % base);
			num = num / base;
		} while ( num != 0 );
	}

	LongInteger(const LongInteger& other):
		number_(other.number_) {
	}

	static LongInteger parse(const char *str) {
		CTAssert<base == 10> ();
		LongInteger ans;
		ans.number_.clear();
		for (ptrdiff_t i = strlen(str) - 1; i >= 0; --i) {
			ans.number_.push_back(str[i] - '0');
		}
		return ans;
	}

	LongInteger &operator =(const LongInteger &other) {
		if (this != &other) {
			number_ = other.number_;
		}
		return (*this);
	} 

	void swap(LongInteger &other) {
		this->number_.swap(other.number_);
	}

	size_t size() const {
		return number_.size();
	}

	typedef basic_iterator<unsigned int, std::vector<unsigned int>*, false> iterator;
	typedef basic_iterator<const unsigned int, const std::vector<unsigned int>*, true> const_iterator;

	iterator begin() {
		return iterator(&number_, 0);
	}

	iterator end() {
		return iterator(&number_, number_.size());
	}

	const_iterator cbegin() const {
		return const_iterator(&number_, 0);
	}

	const_iterator cend() const {
		return const_iterator(&number_, number_.size());
	}

	friend bool operator <(const LongInteger &left, const LongInteger &right) {
		return LongInteger::compare(left, right) < 0;
	}

	friend bool operator >(const LongInteger &left, const LongInteger &right) {
		return ( right < left );
	}

	friend bool operator ==(const LongInteger &left, const LongInteger &right) {
		return LongInteger::compare(left, right) == 0;
	}

	friend bool operator !=(const LongInteger &left, const LongInteger &right) {
		return ( !(left == right) );
	}

	friend bool operator <=(const LongInteger &left, const LongInteger &right) {
		return ( !(left > right) );
	}

	friend bool operator >=(const LongInteger &left, const LongInteger &right) {
		return ( !(left < right) );
	}

	void operator +=(const LongInteger &other) {
		size_t new_size = std::max(this->number_.size(), other.number_.size());
		this->number_.resize(new_size, 0);
		
		int div = 0;
		for (size_t i = 0; i < new_size; ++i) {
			unsigned long long temp = this->number_[i];
			if (i < other.number_.size()) {
				temp += other.number_[i];
			}
			temp += div;

			div = temp / base;
			this->number_[i] = temp % base;
		}

		if (div != 0) {
			this->number_.push_back(div);
		}
	}

	LongInteger operator +(const LongInteger &other) const {
		LongInteger ans = (*this);
		ans += other;
		return ans;
	}
	
	void operator -=(const LongInteger &other) {
		assert((*this) >= other);

		for (ptrdiff_t i = other.number_.size() - 1; i >= 0; --i) {
			if (this->number_[i] < other.number_[i]) {
				this->number_[i] += base;
				
				ptrdiff_t j = i + 1;
				while (this->number_[j] == 0) {
					this->number_[j] = base - 1;
					++j;
				}
				--this->number_[j];
			}

			this->number_[i] -= other.number_[i];
		}

		size_t new_size = this->number_.size();
		while ( (this->number_[new_size - 1] == 0) && new_size > 1) {
			--new_size;
		}
		this->number_.resize(new_size);
	}

	LongInteger operator -(const LongInteger &other) const {
		LongInteger ans = (*this);
		ans -= other;
		return ans;
	}

	LongInteger operator *(unsigned int other) const {
		LongInteger ans;
		if (other == 0) {
			return ans;
		}

		size_t new_size = this->number_.size();
		ans.number_.resize(new_size, 0);
		unsigned int div = 0;

		for (size_t i = 0; i < new_size; ++i) {
			unsigned long long temp = this->number_[i];
			temp *= other;
			temp += div;
			div = temp / base;
			ans.number_[i] = (temp % base);
		}

		if (div != 0) {
			ans.number_.push_back(div);
		}

		return ans;
	}

	LongInteger operator *(const LongInteger &other) const {
		LongInteger min;
		LongInteger max;
		min = other;
		max = (*this);
		if ((*this) < other) {
			min.swap(max);
		}

		LongInteger ans;
		for (size_t i = 0; i < min.number_.size(); ++i) {
			LongInteger temp = max * min.number_[i];
			temp = temp << i;
			ans += temp;
		}

		return ans;
	}	

	void operator *=(const LongInteger &other) {
		(*this) = (*this) * other;
	}

	LongInteger operator /(const LongInteger &other) const {
		LongInteger div, mod;
		mod = *this;

		assert(other != (unsigned long long)0);

		if (*this < other)
			return div;
		div.number_.clear();
		
		LongInteger temp = other;
		while (temp << 1 < mod)
				temp = temp << 1;
		
		LongInteger null;
		while (temp >= other) {	
			int left = 0, right = base + 1;
			while (left < right - 1) {
				int mid = left + (right - left) / 2;
				if (temp * mid > mod)
					right = mid;
				else
					left = mid;
			}

			mod -= temp * left;
			div.number_.push_back(left);

			temp = temp >> 1;
		}
		
		reverse(div.number_.begin(), div.number_.end());
		return div;
	}
	
	void operator /=(const LongInteger &other) {
		(*this) = (*this) / other;
	}

	LongInteger operator %(const LongInteger &other) const {
		return (*this) - (*this / other) * other;
	}

	void operator %=(const LongInteger &other) {
		(*this) = (*this) % other;
	}
	
	unsigned long long to_int() const {
		assert(*this <= std::numeric_limits<unsigned long long>::max());
		
		unsigned long long ans = 0;
		unsigned long long power = 1;
		for (size_t i = 0; i < this->number_.size(); ++i) {
			ans += power * this->number_[i];
			power *= base;
		}

		return ans;
	}

	template <unsigned int other_base>
	LongInteger(LongInteger<other_base> other) {
		LongInteger<10> temp;
		LongInteger<10> power(1);
		LongInteger<10> long_other_base(other_base);

		typename LongInteger<other_base>::const_iterator cit;
		for (cit = other.cbegin(); cit != other.cend(); cit++) {
			temp += power * (*cit);
			power *= long_other_base;
		}

		this->number_.clear();
		LongInteger<10> null;
		LongInteger<10> long_base(base);
		
		if (temp == null)
			this->number_.push_back((temp % long_base).to_int());

		while (temp > null) {
			this->number_.push_back((temp % long_base).to_int());
			temp /= long_base;
		}
	}
};

namespace std {
	template <unsigned int base>
	void swap(LongInteger<base> &first, LongInteger<base> &second) {
		first.swap(second);
	}
}

template<unsigned int base>
std::ostream& operator <<(std::ostream& out, const LongInteger<base> &value) {
	LongInteger<10> ans(value);
	std::reverse_iterator<LongInteger<10>::const_iterator> r_iter(ans.cend());
	std::reverse_iterator<LongInteger<10>::const_iterator> r_end(ans.cbegin());
	for (; r_iter != r_end; ++r_iter) {
		out << *r_iter;
	}
	return out;
}

std::istream& operator >>(std::istream& in, LongInteger<10> &value) {
	std::string str;
	in >> str;
	LongInteger<10> temp = LongInteger<10>::parse(str.c_str());
	value.swap(temp);
	return in;
}
