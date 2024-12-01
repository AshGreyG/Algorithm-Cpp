#include "../Other/arbitary_percision.h"
#include <iostream>
#include <string>

void testValid(std::string a) {
    std::cout << a << "\n"
              << "---------------------\n";
    BigInteger big_a(a);
    std::cout << big_a.toString() << "\n"
              << "---------------------\n\n";
}

void testForComparison(std::string a, std::string b) {
    BigInteger big_a(a), big_b(b);
    auto boolean = [=] (bool f) -> std::string { return f ? "True" : "False"; };
    std::cout << a << " V.S." << b << "\n"
              << "--------------\n"
              << "a >  b : " << boolean(big_a >  big_b) << "\n"
              << "a <  b : " << boolean(big_a <  big_b) << "\n"
              << "a == b : " << boolean(big_a == big_b) << "\n"
              << "a <= b : " << boolean(big_a <= big_b) << "\n"
              << "a >= b : " << boolean(big_a >= big_b) << "\n"
              << "--------------\n\n";
}

int main() {
    // testValid("+++123");
    testValid("+0000000123");
    // testForComparison("123", "+123");
    // testForComparison("-123", "+123");
    // testForComparison("-12", "-120");
    return 0;
}