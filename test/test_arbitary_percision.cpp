#include "../Other/arbitary_percision.h"
#include <iostream>
#include <string>

void testValid(std::string&& a) {
    std::cout << a << "\n"
              << "---------------------\n";
    BigInteger big_a(a);
    std::cout << big_a.toString() << "\n"
              << "---------------------\n\n";
}

void testForComparison(std::string&& a, std::string&& b) {
    BigInteger big_a(a), big_b(b);
    auto boolean = [=] (bool f) -> std::string { return f ? "True" : "False"; };
    std::cout << a << " V.S." << b << "\n"
              << "--------------\n"
              << "a >  b : " << boolean(big_a >  big_b) << "\n"
              << "a <  b : " << boolean(big_a <  big_b) << "\n"
              << "a == b : " << boolean(big_a == big_b) << "\n"
              << "a != b : " << boolean(big_a != big_b) << "\n"
              << "a <= b : " << boolean(big_a <= big_b) << "\n"
              << "a >= b : " << boolean(big_a >= big_b) << "\n"
              << "--------------\n\n";
}

void testMinus(std::string&& a) {
    BigInteger big_a(a);
    std::cout << "-----------------\n"
              << big_a << " " 
              << -big_a << "\n"
              << "-----------------\n";
}

void testSum(std::string&& a, std::string&& b) {
    BigInteger big_a(a), big_b(b);

    if (big_b.isPositive()) {
        std::cout << a << " + " << b << " = ";
    } else {
        std::cout << a << " + (" << b << ") = ";
    }
    std::cout << big_a + big_b << "\n";
}

int main() {
    // testValid("+++123");
    // testValid("+0000000123");
    // testValid("000012090");

    // testForComparison("123", "+123");
    // testForComparison("-123", "+123");
    // testForComparison("-12", "-120");
    // testForComparison("-12345", "+12");         // 2024-12-01 19:53 -12345 > 12 !!!
    // testForComparison("22345", "12346");

    // testMinus("123");
    // testMinus("+0123");
    // testMinus("-09182");

    testSum("1234", "4321");
    testSum("-1234", "-223");
    return 0;
}