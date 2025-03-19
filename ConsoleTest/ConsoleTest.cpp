#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>
#include <stdio.h>

//using bigint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<>>;
using bigint = boost::multiprecision::cpp_int;
using bigfloat = boost::multiprecision::cpp_dec_float_50;


int main() {
	bigint x(12345678);
	bigfloat y("0.26");
	std::cout << "x: " << x << "\n";
	std::cout << "y: " << y << "\n";
	bigfloat result = x.convert_to<bigfloat>() * y;

	//bigint z = result; // lossy conversion will not compile
	bigint z1 = static_cast<bigint>(result);
	bigint z2 = result.convert_to<bigint>();

	std::cout << "Result: " << result << "\n";
	std::cout << "z1: " << z1 << "\n";
	std::cout << "z2: " << z2 << "\n";
}