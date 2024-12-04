#ifndef ARBITARY_PERCISION_H
#define ARBITARY_PERCISION_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std::string_literals;

/**
 * @author: AshGrey
 * @date:   2024-12-01
 */
struct BigInteger {
  public:
    BigInteger(const std::string& input);
    BigInteger(const char* input);
    BigInteger(const BigInteger& copy);
    BigInteger(BigInteger&& move);
    BigInteger& operator=(const BigInteger& assgin);

    BigInteger() = default;
    ~BigInteger() = default;

    BigInteger operator+(const BigInteger& another) const;
    BigInteger operator-(const BigInteger& another) const;
    BigInteger operator-() const;
    BigInteger operator*(const BigInteger& another) const;
    std::pair<BigInteger, BigInteger> operator/(const BigInteger& another) const;

    bool operator==(const BigInteger& another) const;
    bool operator!=(const BigInteger& another) const;
    bool operator>(const BigInteger& another) const;
    bool operator<(const BigInteger& another) const;
    bool operator>=(const BigInteger& another) const;
    bool operator<=(const BigInteger& another) const;

    std::string& toString();
    size_t length();
    bool isPositive();

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
    friend std::ostream& operator<<(std::ostream& os, const std::pair<BigInteger, BigInteger> pair_bi);
    

  private:
    std::vector<int> storage_;  // storage_ stores each digit
    std::string inner_str_;     // inner_str_ is the std::string format of BigInteger
    size_t size_;               // the size of BigInteger
    bool is_positive_;          // TRUE when positive, FALSE when negative
};

#endif