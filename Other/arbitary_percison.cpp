#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std::string_literals;

// notice that BigInteger is always positive, so the
// the result of `-` operator is still positive. This 
// is different from the accurate definition of BigInteger

struct BigInteger {
  private:
    std::vector<int> storage_;
    std::string inner_str_;
    unsigned int size_;
  public:
    BigInteger(std::string& input) : size_(input.length()), inner_str_(input) {
        std::for_each(input.rbegin(), input.rend(),
            [&] (char ch_input) {
                storage_.push_back(ch_input - '0');
            }
        );
    }
    BigInteger(const char* input) : size_(sizeof(input)), inner_str_(std::string(input)) {
        std::for_each(input, input + sizeof(input) - 1,
            [&] (char ch_input) {
                storage_.push_back(ch_input - '0');
            }
        );
    }
    BigInteger(const BigInteger& copy) {
        storage_ = copy.storage_;
        inner_str_ = copy.inner_str_;
        size_ = copy.size_;
    }
    BigInteger(BigInteger&& move) {
        storage_ = std::move(move.storage_);
        size_ = move.size_;
        inner_str_ = move.inner_str_;
        move.size_ = 0;
        move.storage_.clear();
        move.storage_.shrink_to_fit();
    }
    BigInteger& operator=(const BigInteger& assgin) {
        storage_ = assgin.storage_;
        size_ = assgin.size_;
        inner_str_ = assgin.inner_str_;
        return *this;
    }
    BigInteger() = default;
    ~BigInteger() = default;
    BigInteger operator+(BigInteger& another) {
        unsigned int max_length = std::max(size_, another.size_);
        BigInteger new_biginteger;
        new_biginteger.storage_.resize(max_length + 1, 0);
        for (int i = 0; i < max_length; ++i) {
            int val_this = (i < storage_.size()) ? storage_[i] : 0;
            int val_another = (i < another.storage_.size()) ? another.storage_[i] : 0;
            new_biginteger.storage_[i] = val_this + val_another;
        }
        for (int i = 0; i < max_length - 1; ++i) {
            if (new_biginteger.storage_[i] >= 10) {
                new_biginteger.storage_[i + 1] += new_biginteger.storage_[i] / 10;
                new_biginteger.storage_[i] %= 10;
            }
        }
        if (new_biginteger.storage_[max_length] == 0 && new_biginteger.storage_.size() != 1) {
            new_biginteger.storage_.resize(max_length);
        }
        new_biginteger.size_ = new_biginteger.storage_.size();
        std::for_each(new_biginteger.storage_.begin(), new_biginteger.storage_.end(),
            [&] (int i) {
                new_biginteger.inner_str_ += std::to_string(i);
            }
        );
        return new_biginteger;
    }
    BigInteger operator-(BigInteger& another) {
        if (*this == another) {
            return BigInteger("0");
        } else if (*this < another) {
            return another - *this;
        }
        unsigned int max_length = std::max(size_, another.size_);
        BigInteger new_biginteger;
        new_biginteger.storage_.resize(max_length, 0);
        for (int i = 0; i < max_length; ++i) {
            int val_this = (i < storage_.size()) ? storage_[i] : 0;
            int val_another = (i < another.storage_.size()) ? another.storage_[i] : 0;
            new_biginteger.storage_[i] = val_this - val_another;
        }
        for (int i = 0; i < max_length - 1; ++i) {
            if (new_biginteger.storage_[i] < 0) {
                new_biginteger.storage_[i + 1] -= 1;
                new_biginteger.storage_[i] += 10;
            }
        }
        unsigned int last_zero = max_length;
        for (int i = max_length - 1; i >= 0; i--) {
            if (new_biginteger.storage_[i] == 0) {
                last_zero = i;
            } else {
                break;
            }
        }
        new_biginteger.storage_.resize(last_zero);
        new_biginteger.size_ = new_biginteger.storage_.size();
        std::for_each(new_biginteger.storage_.begin(), new_biginteger.storage_.end(),
            [&] (int i) {
                new_biginteger.inner_str_ += std::to_string(i);
            }
        );
        return new_biginteger;
    }
    BigInteger operator*(BigInteger& another) {
        BigInteger new_biginteger;
        new_biginteger.storage_.resize(size_ + another.size_, 0);
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < another.size_; ++j) {
                new_biginteger.storage_[i + j] += storage_[i] * another.storage_[j];
            }
        }
        for (int i = 0, m = new_biginteger.storage_.size(); i < m; ++i) {
            if (new_biginteger.storage_[i] >= 10) {
                new_biginteger.storage_[i + 1] += new_biginteger.storage_[i] / 10;
                new_biginteger.storage_[i] %= 10;
            }
        }
        unsigned int last_zero = new_biginteger.storage_.size();
        for (int i = new_biginteger.storage_.size() - 1; i >= 0; i--) {
            if (new_biginteger.storage_[i] == 0) {
                last_zero = i;
            } else {
                break;
            }
        }
        if (last_zero == 0) {
            last_zero = 1;
        }
        new_biginteger.storage_.resize(last_zero);
        new_biginteger.size_ = new_biginteger.storage_.size();
        std::for_each(new_biginteger.storage_.begin(), new_biginteger.storage_.end(),
            [&] (int i) {
                new_biginteger.inner_str_ += std::to_string(i);
            }
        );
        return new_biginteger;
    }
    std::pair<BigInteger, BigInteger> operator/(BigInteger& another) {
        BigInteger big_zero("0"), big_one("1");
        auto floor_multiple_str = another.inner_str_ + std::string(size_ - another.size_, '0');
        BigInteger floor_multiple(floor_multiple_str);
        if (floor_multiple > *this) {
            floor_multiple_str.pop_back();
            floor_multiple = BigInteger(floor_multiple_str);
        }
        auto copy_of_this = *this;
        BigInteger quotient;
        std::string quotient_str = "";
        unsigned int quotient_count = 0;
        if (*this < another) {
            auto zero_pair = std::make_pair(big_zero, *this);
            return zero_pair;
        } else if (*this == another) {
            auto equal_pair = std::make_pair(big_one, big_zero);
            return equal_pair;
        } else {
            while (copy_of_this >= another || floor_multiple_str.length() >= another.size_) {
                quotient_count = 0;
                while (copy_of_this >= floor_multiple) {
                    copy_of_this = copy_of_this - floor_multiple;
                    quotient_count++;
                }
                quotient_str += std::to_string(quotient_count);
                floor_multiple_str.pop_back();
               floor_multiple = BigInteger(floor_multiple_str);
            }
            BigInteger quotient(quotient_str);
            return std::make_pair(quotient, copy_of_this);
        }
    }
    bool operator==(BigInteger& another) {
        if (size_ != another.size_) {
            return false;
        } else {
            for (int i = 0; i <= size_ - 1; ++i) {
                if (storage_[i] != another.storage_[i]) {
                    return false;
                }
            }
            return true;
        }
    }
    bool operator>(BigInteger& another) {
        unsigned int count = 0;
        if (size_ < another.size_) {
            return false;
        } else if (size_ > another.size_) {
            return true;
        } else {
            for (int i = size_ - 1; i >= 0; i--) {
                if (storage_[i] < another.storage_[i]) {
                    return false;
                } else if (storage_[i] == another.storage_[i]) {
                    count++;
                } else {
                    return true;
                }
            }
            return !(count == size_);
        }
    }
    bool operator<(BigInteger& another) {
        unsigned int count = 0;
        if (size_ > another.size_) {
            return false;
        } else if (size_ < another.size_) {
            return true;
        } else {
            for (int i = size_ - 1; i >= 0; i--) {
                if (storage_[i] > another.storage_[i]) {
                    return false;
                } else if (storage_[i] == another.storage_[i]) {
                    count++;
                } else {
                    return true;
                }
            }
            return !(count == size_);
        }
    }
    bool operator<=(BigInteger& another) {
        return (*this < another) || (*this == another);
    }
    bool operator>=(BigInteger& another) {
        return (*this > another) || (*this == another);
    }
    std::string& toString() {
        return inner_str_;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
        std::cout << bi.inner_str_;
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const std::pair<BigInteger, BigInteger> pair_bi) {
        std::cout << std::get<0>(pair_bi) << " " << std::get<1>(pair_bi);
        return os;
    }
};