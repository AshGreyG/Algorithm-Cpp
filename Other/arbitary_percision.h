#ifndef ARBITARY_PERCISION_H
#define ARBITARY_PERCISION_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>

using namespace std::string_literals;

// notice that BigInteger is always positive, so the
// the result of `-` operator is still positive. This 
// is different from the accurate definition of BigInteger

/**
 * @author: AshGrey
 * @date:   2024-12-01
 */
struct BigInteger {
  public:
    /**
     * @program:     BigInteger::BigInteger
     * @description: When the parameter of Constructor is std::string, copy it to the storage_
     */
    BigInteger(const std::string& input) {
        int has_signed, index = -1;
        std::string correct;

        // has_signed aims to avoid get the sign of the explicit signed BigInteger.
        // index aims to find the +000000001234
        //                                 ^ (position of the tail of continous 0 head)
        // correct aims to deal with the wrong syntax
        
        for (int i = 0; i < input.size(); ++i) {
            try {
                if (((input[i] == '-' || input[i] == '+') && i != 0)                            // such as -000-89
                 || (input[i] < '0' && input[i] > '9' && input[i] != '-' && input[i] != '+')) { // such as 00^^
                    throw std::invalid_argument(input + "\n" +
                                                std::string(i, ' ') + 
                                                "^ Invalid " + input[i] + " character.\n");
                }
                if (input[i] >= '1' && input[i] <= '9' && index == -1) {
                    index = i;
                }
            } catch (std::invalid_argument& err) {
                std::cerr << err.what();
            }
        }

        // 1. -00000000
        //            ^ index = -1
        // 2. -000000123
        //           ^ index
        // 3. +1234
        //     ^ index
        // 4. 1234
        //    ^ index
        // 5. 0000012034
        //         ^ index

        if ((input[0] == '+' || input[0] == '-') && index != -1) {
            correct = std::string(1, input[0]) + input.substr(index);
        } else if (input[0] != '+' && input[0] != '-') {
            correct = input.substr(index);
        } else if (index == -1) {
            correct = "0";
        }

        if (correct[0] == '+') {
            has_signed = 1;
            is_positive_ = true;
            size_ = correct.size() - 1;
            inner_str_ = correct;
        } else if (correct[0] == '-') {
            has_signed = 1;
            is_positive_ = false;
            size_ = correct.size() - 1;
            inner_str_ = correct;
        } else {
            has_signed = 0;
            is_positive_ = true;
            size_ = correct.size();
            inner_str_ = "+" + correct;
            
            // When there is no sign, we consider the BigInteger is positive by default.
        }

        for (auto it = correct.rbegin(); it != correct.rend() - has_signed; ++it) {
            const auto char_input = *it;
            storage_.push_back(char_input - '0');
        }
    }

    /**  
     * @program:     BigInteger::BigInteger
     * @description: When the parameter of Constructor is const char* (that means 
                    the parameter is the style of "123" but not "123"s), copy it.
     */
    BigInteger(const char* input) {
        int has_signed, index = -1;
        std::string input_str(input), correct;

        // has_signed aims to avoid get the sign of the explicit signed BigInteger.

        for (int i = 0; i < input_str.size(); ++i) {
            try {
                if (((input_str[i] == '-' || input_str[i] == '+') && i != 0)                            
                 || (input_str[i] < '0' && input_str[i] > '9' && input_str[i] != '-' && input_str[i] != '+')) { 
                    throw std::invalid_argument(input_str + "\n" +
                                                std::string(i, ' ') + 
                                                "^ Invalid " + input_str[i] + " character.\n");
                }
                if (input_str[i] >= '1' && input_str[i] <= '9' && index == -1) {
                    index = i;
                }
            } catch (std::invalid_argument& err) {
                std::cerr << err.what();
            }
        }
        if (input_str[0] == '+' || input_str[0] == '-') {
            correct = std::string(1, input_str[0]) + input_str.substr(index);
        } else {
            correct = input_str.substr(index);
        }

        if (correct[0] == '+') {
            has_signed = 1;
            is_positive_ = true;
            size_ = correct.size() - 1;
            inner_str_ = correct;
        } else if (correct[0] == '-') {
            has_signed = 1;
            is_positive_ = false;
            size_ = correct.size() - 1;
            inner_str_ = correct;
        } else {
            has_signed = 0;
            is_positive_ = true;
            size_ = correct.size();
            inner_str_ = "+" + correct;
            
            // When there is no sign, we consider the BigInteger is positive by default.
        }

        for (auto it = correct.rbegin(); it != correct.rend() - has_signed; ++it) {
            const auto char_input = *it;
            storage_.push_back(char_input - '0');
        }
    }

    /**
     * @program:     BigInteger::BigInteger
     * @description: A Copy Constructor.
     */
    BigInteger(const BigInteger& copy) {
        storage_ = copy.storage_;
        inner_str_ = copy.inner_str_;
        size_ = copy.size_;
        is_positive_ = copy.is_positive_;
    }

    /**
     * @program:     BigInteger::BigInteger
     * @description: A Move Construtor.
     */
    BigInteger(BigInteger&& move) {
        storage_ = std::move(move.storage_);
        size_ = move.size_;
        inner_str_ = move.inner_str_;
        is_positive_ = move.is_positive_;
        move.size_ = 0;
        move.storage_.clear();
        move.storage_.shrink_to_fit();
        move.is_positive_ = false;
    }

    /**
     * @program:     operator=
     * @description: The = operator function, same to Copy Constructor.
     */
    BigInteger& operator=(const BigInteger& assgin) {
        storage_ = assgin.storage_;
        size_ = assgin.size_;
        inner_str_ = assgin.inner_str_;
        is_positive_ = assgin.is_positive_;
        return *this;
    }
    BigInteger() = default;
    ~BigInteger() = default;

    /**
     * @program:     operator+
     * @description: The + operator function.
     */
    BigInteger operator+(BigInteger& another) {
        unsigned int max_length = std::max(size_, another.size_);
        BigInteger new_biginteger;
        new_biginteger.storage_.resize(max_length + 1, 0);

        // For a + b, max_length = max(len(a), len(b)), to make the space of new BigInteger

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

    /**
     * @program:     operator==
     * @description: Check if the two BigInteger is equal. O(n)
     * @another:     Refference to another BigInteger object.
     */
    bool operator==(BigInteger& another) {
        if (size_ != another.size_) {
            return false;   // If size is not equal, then they are not equal.
        } else if (is_positive_ != another.is_positive_) {
            return false;   // If sign is not equal, then they are not equal.
        } else {
            for (int i = 0; i <= size_ - 1; ++i) {
                if (storage_[i] != another.storage_[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    /**
     * @program:     operator>
     * @description: Check if a > b is true. O(n)
     * @another:     Refference to another BigInteger object.
     */
    bool operator>(BigInteger& another) {
        unsigned int count = 0;

        // count is for comparing with the size.

        if (is_positive_ && another.is_positive_ && size_ < another.size_) {
            return false;   // a,b > 0, len(a) < len(b) => a < b
        } else if (is_positive_ && another.is_positive_ && size_ > another.size_) {
            return true;    // a,b > 0, len(a) > len(b) => a > b
        } else if (!is_positive_ && !another.is_positive_ && size_ < another.size_) {
            return true;    // a,b < 0, len(a) < len(b) => a > b
        } else if (!is_positive_ && !another.is_positive_ && size_ > another.size_) {
            return false;   // a,b < 0, len(a) > len(b) => a < b
        } else if (!is_positive_ && another.is_positive_) {
            return false;   // sign(a) = -, sign(b) = + => a < b
        } else if (is_positive_ && !another.is_positive_) {
            return true;    // sign(a) = +, sign(b) = - => a > b
        } else if (size_ == another.size_) {
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
        } else {
            for (int i = size_ - 1; i >= 0; i--) {
                if (storage_[i] < another.storage_[i]) {
                    return true;
                } else if (storage_[i] == another.storage_[i]) {
                    count++;
                } else {
                    return false;
                }
            }
            return !(count == size_);
        }
    }

    /**
     * @program:     operator<
     * @description: a < b = !(a == b or a > b)
     * @another:     Refference to another BigInteger object.
     */
    bool operator<(BigInteger& another) {
        return !((*this > another) || (*this == another));
    }

    /**
     * @program:     operator<
     * @description: a <= b = a < b or a == b
     * @another:     Refference to another BigInteger object.
     */
    bool operator<=(BigInteger& another) {
        return (*this < another) || (*this == another);
    }
    
    /**
     * @program:     operator<
     * @description: a >= b = a > b or a == b
     * @another:     Refference to another BigInteger object.
     */
    bool operator>=(BigInteger& another) {
        return (*this > another) || (*this == another);
    }

    /**
     * @program:     operator<
     * @description: a != b = !(a == b)
     * @another:     Refference to another BigInteger object.
     */
    bool operator!=(BigInteger& another) {
        return !(*this == another);
    }
    
    /**
     * @program:     toString()
     * @description: Return the string format of BigInteger object, including the sign.
     */
    std::string& toString() {
        return inner_str_;
    }

    /**
     * @program:     operator<<
     * @description: Bind with ostream, output the single BigInteger object.
     * @os:          An ostream object.
     * @bi:          An BigInteger object.
     */
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
        std::cout << bi.inner_str_;
        return os;
    }

    /**
     * @program:     operator<<
     * @description: Bind with ostream, output the pair of BigInteger objects, the 
                     return value of operator/.
     * @os:          An ostream object.
     * @pair_bi:     A pair of BigInteger objects, std::pair<BigInteger, BigInteger>.
     */
    friend std::ostream& operator<<(std::ostream& os, const std::pair<BigInteger, BigInteger> pair_bi) {
        std::cout << std::get<0>(pair_bi) << " " << std::get<1>(pair_bi);
        return os;
    }

  private:
    std::vector<int> storage_;  // storage_ stores each digit
    std::string inner_str_;     // inner_str_ is the std::string format of BigInteger
    unsigned int size_;         // the size of BigInteger
    bool is_positive_;          // TRUE when positive, FALSE when negative
};

#endif